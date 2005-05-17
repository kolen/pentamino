#include "Shell.h"
#include <iostream>
#include <ctype.h>
#include <sstream>
#include <iterator>


using namespace std;

/**
 * Парзит и выполняет кусок кода 
 *
 * @param commands Строка с кодом
 */
void
ShellInterpreter::execCode(string commands)
{
  char c;
  int depth = 0;
  char state = S_WAIT_NBLANK;
  stringstream strm(commands);
  list<string> args;
  string cur_arg("");
  while (strm.get(c))
    {
      if (c == '\n')
	{
	  doCommand(args);
	  args.clear();
	}
      else if (isspace(c))
	{
	  if (state == S_WORD)
	    {
	      args.push_back(cur_arg);
	      cur_arg = "";
	      state = S_WAIT_NBLANK;
	    }
	  else if (state == S_BRACKET)
	    {
	      if (*cur_arg.end() != ' ')
		cur_arg += " ";
	    }
	}
      else if (c == '{')
	{
	  if (state == S_BRACKET)
	    {
	      depth++;
	    }
	  else if (state == S_WORD)
	    {
	      args.push_back(cur_arg);
	      cur_arg = "";
	      state = S_BRACKET;
	    }
	  else if (state == S_WAIT_NBLANK)
	    {
	      state = S_BRACKET;
	      cur_arg+=c;
	    }
	}
      else if (c == '}')
	{
	  if (state == S_BRACKET)
	    {
	      depth--;
	      if (depth == 0)
		{
		  args.push_back(cur_arg);
		  cur_arg = "";
		  state = S_WAIT_NBLANK;
		}
	      else
		{
		  cur_arg+=c;
		}
	    }
	  else if (state == S_WAIT_NBLANK || state == S_WORD)
	    {
	      state = S_ERROR;
	    }
	}
      else 
	{
	  if (state == S_WAIT_NBLANK)
	    {
	      state = S_WORD;
              strm.unget();
	    }
	  else if (state != S_ERROR)
	    {
	      cur_arg+=c;
	    }
	}
    }

  args.push_back(cur_arg);
  doCommand(args);
}

ShellInterpreter::ShellInterpreter()
{
  return;
}

void
ShellInterpreter::doCommand(list<string>& args)
{
  string cmd;
  cmd = args.front();
  args.pop_front();

  if (commands.find(cmd) != commands.end())
    {
      cmdEntry& centry = commands[cmd];      
      centry.object->onCommand(centry.cmdId, cmd, args);
    }
  else 
    {
      cerr << "No such command: " << cmd << endl;
    }
}

#if 1
int 
ShellUser::onCommand(int cmdId, std::string &command, std::list<std::string> &args)
{
  std::cerr << "Warning: Called stub onCommand" <<std::endl;
  return 0xff;
}
#endif

void 
ShellInterpreter::registerCommand(ShellUser *object, std::string cmd, int cmdId)
{
  cmdEntry e;
  e.cmdId = cmdId;
  e.object = object;
  commands[cmd] = e;
}
