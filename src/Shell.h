#ifndef SHELL_H
#define SHELL_H

// $Id: Shell.h,v 1.8 2005/05/23 17:53:40 kolen Exp $

#include <istream>
#include <map>
#include <string>
#include <sstream>
#include <list>

#define POPARG args.front();args.pop_front()
#define CHKARGS(num) if(args.size()!=num){std::cerr<<command<<": "<<num<<" args required"<<std::endl; return 0;}

using namespace std;

class ShellUser
{
public:
  virtual int onCommand(int cmdId, std::string &command, std::list<std::string> &args);
};


/**
 * Интерпретатор внутреннего шелла
 */
class ShellInterpreter: public ShellUser
{
 public:
  ShellInterpreter();
  
  void execCode(std::string input);
  void registerCommand(ShellUser *object, std::string cmd, int cmdId);
  //Builtins
  int onCommand(int, string&, list<string>&);
 
  struct cmdEntry{int cmdId; ShellUser *object;};
 private:
  void doCommand(std::list<std::string> &args);

  map<string, cmdEntry> commands;
  map<string, string> defs;
  map<string, string> vars;
  //----- Command ids ------: //
  static const int CMD_set  = 1;
  static const int CMD_def  = 2;
  static const int CMD_if   = 3;
  static const int CMD_exec = 4;
  static const int CMD_echo = 5;
};


#define S_WAIT_NBLANK 0
#define S_WORD        1
#define S_BRACKET     2
#define S_ERROR       3

extern ShellInterpreter *shell;

#endif
