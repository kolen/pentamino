/* $Id: I18n.cpp,v 1.2 2005/05/20 13:06:08 kolen Exp $ */
#include "I18n.h"

void
I18n::addString(string id, string translation)
{
  strings[id] = translation;
}

int
I18n::onCommand(int id, string command, list<string> args)
{
  if (id != 0) return 0; //Only one command: string
  if (args.size() < 2) {
    cerr << "Usage: string id translation ..." << endl;
    return 1;
  }
  string strId = args.front();
  args.pop_front();
  string translation;

  for (list<string>::iterator i = args.begin(); i != args.end(); i++)
    {
      translation += *i;
      translation += " ";
    }
}

I18n *i18n;
