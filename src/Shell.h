#ifndef SHELL_H
#define SHELL_H

#include <istream>
#include <map>
#include <string>
#include <sstream>
#include <list>

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
  map<string, string> vars;
  static const int CMD_set = 1;
};


#define S_WAIT_NBLANK 0
#define S_WORD        1
#define S_BRACKET     2
#define S_ERROR       3

extern ShellInterpreter *shell;

#endif
