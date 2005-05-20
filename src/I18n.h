#ifndef I18N_H
#define I18N_H
/* $Id: I18n.h,v 1.1 2005/05/20 12:52:15 kolen Exp $ */

#include <map>
#include <string>
#include <list>
#include <iostream>
#include "Shell.h"
using namespace std;

class I18n: public ShellUser
{
public:
  I18n() {
    shell->registerCommand(this, "string", 0);
  }
  void addString(string id, string translation);
  string& operator[](string id) 
    {
      return strings.find(id)->second;
    }
  int onCommand(int, string, list<string>);
private:
  map<string, string> strings;
};


#endif
