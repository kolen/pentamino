#ifndef I18N_H
#define I18N_H
/* $Id: I18n.h,v 1.2 2005/05/20 13:06:08 kolen Exp $ */

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
    cerr << "i18n init" << endl;
  }
  void addString(string id, string translation);
  string& _(string id) 
    {
      return strings.find(id)->second;
    }
  string language;
  int onCommand(int, string, list<string>);
private:
  map<string, string> strings;
};

extern I18n *i18n;


#endif
