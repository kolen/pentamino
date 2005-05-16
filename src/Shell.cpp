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
  std::list<ShellUser*>::iterator user;
  string cmd = args.front();
  args.pop_front();

  for (user = clients.begin(); user != clients.end() ;user++)
    {
      std::cerr << "[.]";
      if (int i=(*user)->onCommand(cmd, args)){std::cerr << i; return;};
    }
  std::cerr << "No such command: " << cmd << std::endl;
}


int 
ShellUser::onCommand(std::string &command, std::list<std::string> &args)
{return 0;}

void 
ShellInterpreter::addShellUser(ShellUser *user)
{
  clients.push_back(user);
}
