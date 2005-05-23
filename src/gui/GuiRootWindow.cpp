#include "GuiRootWindow.h"

#include <iostream>
#include "../I18n.h"
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
}

void
GuiRootWindow::newmenuCreate()
{
  list<mitem>::iterator i;
  GuiMenu *m = new GuiMenu(newmenu_pos[0], newmenu_pos[1]);
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
    CHKARGS(1);
    newmenu_title = POPARG;
    //FIXME:
    newmenu_pos[0] = 0;
    newmenu_pos[1] = 16;
    break;
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
    }
  }
}
