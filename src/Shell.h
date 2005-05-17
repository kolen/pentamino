#ifndef SHELL_H
#define SHELL_H

#include <istream>
#include <map>
#include <string>
#include <sstream>
#include <list>

class ShellUser
{
public:
  virtual int onCommand(int cmdId, std::string &command, std::list<std::string> &args);
};


/**
 * Интерпретатор внутреннего шелла
 */
class ShellInterpreter
{
 public:
  ShellInterpreter();
  
  void execCode(std::string input);
  void registerCommand(ShellUser *object, std::string cmd, int cmdId);
 
  ShellGlobals globals;
 
  struct cmdEntry{int cmdId; ShellUser *object;};
 
 private:
  void doCommand(std::list<std::string> &args);

  std::map<std::string, cmdEntry> commands;
};


#define S_WAIT_NBLANK 0
#define S_WORD        1
#define S_BRACKET     2
#define S_ERROR       3

#endif
