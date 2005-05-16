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
  virtual int onCommand(std::string &command, std::list<std::string> &args);
};

class ShellGlobals
{
 public:
  std::map<std::string, std::string> aliases;
  std::map<std::string, std::string> binds;
};


/**
 * Интерпретатор внутреннего шелла
 */
class ShellInterpreter
{
 public:
  ShellInterpreter();
  
  void execCode(std::string input);
  void addShellUser(ShellUser *user);
  ShellGlobals globals;
 private:
  void doCommand(std::list<std::string> &args);
 
  std::list<ShellUser*> clients;
};


#define S_WAIT_NBLANK 0
#define S_WORD        1
#define S_BRACKET     2
#define S_ERROR       3

#endif
