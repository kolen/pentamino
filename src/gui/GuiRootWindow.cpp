#include "GuiRootWindow.h"
#include <sys/types.h>
#include <dirent.h>
#include <iostream>

#include "../I18n.h"
#include "../File.h"
using namespace std;

GuiRootWindow::GuiRootWindow()
{
  ::GuiContainer();
  addChild(&shapeSel);
  addChild(&field);
  addChild(&menubar);

  shell->registerCommand(this, "menu", CMD_menu);
  shell->registerCommand(this, "m+", CMD_mplus);
  shell->registerCommand(this, "menu_end", CMD_menuend);
  shell->registerCommand(this, "filemenu", CMD_filemenu);
}

void
GuiRootWindow::newmenuCreate()
{
  list<mitem>::iterator i;
  GuiMenu *m = new GuiMenu(newmenu_pos[0], newmenu_pos[1]);
  m->title = newmenu_title;
  for (i=newmenu_items.begin(); i!=newmenu_items.end(); i++)
    {   
      m->addItem(i->title, i->cmd);
    }
  addChild(m);
  setExclusive(m);
}

int
GuiRootWindow::onCommand(int cmdId, string &command, list<string>& args)
{
  switch(cmdId) {
  case CMD_menu:
    {
    CHKARGS(3);
    newmenu_title = POPARG;
    string s1;
    s1 = POPARG;
    newmenu_pos[0] = atoi(s1.c_str());
    s1 = POPARG;
    newmenu_pos[1] = atoi(s1.c_str());
    newmenu_items.clear();
    break;
    }
  case CMD_mplus:
    {
    CHKARGS(2);
    mitem item;
    item.title = POPARG;
    item.title = i18n->_(item.title);
    item.cmd = POPARG;
    newmenu_items.push_back(item);
    break;
    }
  case CMD_menuend:
    {
    CHKARGS(0);
    newmenuCreate();
    break;
    }
  case CMD_filemenu:
    {
    CHKARGS(3);
    string action = POPARG;
    string title = POPARG;
    string dir = POPARG;
    fileMenu(action, title, dir);
    break;
    }
  }
}

void
GuiRootWindow::fileMenu(string action, string title, string dir1)
{
  DIR *dir = opendir(path(dir1).c_str());
  if (!dir) return;
  dirent *de;
  string dname;

  shell->execCode("menu "+title+" 200 16");

  while (de = readdir(dir))
    {
      dname = de->d_name;    
      int pos = dname.rfind(".map");
      if (pos==dname.size()-4 && pos != -1)
        shell->execCode((string)"m+ "+dname+" {"+action+" "+dname+"}");
      else if(de->d_type == DT_DIR)
        {
          shell->execCode((string)"m+ "+dname+" {filemenu "+
          action+" "+title+" "+dir1+"/"+dname+"}");
        }
    }
  shell->execCode("menu_end");
}
