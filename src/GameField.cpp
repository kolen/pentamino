// $Id: GameField.cpp,v 1.3 2005/05/20 15:42:18 kolen Exp $

#include "GameField.h"
#include "File.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

GameField::GameField()
{
  std::memset(tiles, 0x10, sizeof(tiles));
  std::memset(shapenums, 0x00, sizeof(tiles));

  isSelected = selected = 0;

  //Ставим начальное поле которое будет после запуска
  for (int i = 0; i< 12; i++)
    {
      shapes[i].num = i;
      shapes[i].x = 20 + (i%3) * 6;
      shapes[i].y = (i/3) * 6;
      updateShape(i);
    }
  
  shell->registerCommand(this, "save", CMD_save);
  shell->registerCommand(this, "load", CMD_load);
  shell->registerCommand(this, "edit", CMD_edit);
}

void
GameField::removeShape(int num)
{
  int x, y, xt, yt;
  Shape &thisshape = shape(num);
  if (!thisshape.isOnField) return;

  for (x=0; x<5; x++)
    for (y=0; y<5; y++)
      if (thisshape.at(x, y))
        {
          at(x+thisshape.x, y+thisshape.y) = 0x00;
          tileAt(x+thisshape.x, y+thisshape.y) = 0x10;
        }
  thisshape.isOnField = 0;
}

void 
GameField::updateShape(int num)
{
  Shape &tshape = shapes[num];

  if (tshape.x > width-5 || tshape.x < -1 || 
      tshape.y > height-5 || tshape.y < -1) {
        tshape.isOnField = 0;
        return;
      }

  int x, y;
  for (x=0; x<5; x++)
    for (y=0; y<5; y++)
      {
        if (tshape.at(x, y)) {
          tileAt(x + tshape.x, y + tshape.y) = tshape.at(x, y) & 0x0f;
          at(x + tshape.x, y+tshape.y) = num | 0x10;
        }
      }
  
  tshape.updateLastPos();
  tshape.isOnField = 1;
}

int GameField::getShapeAt(int x, int y)
{
  if (at(x, y) & 0x10)
    {
      return at(x, y) & 0x0f;
    }
  else
    {
      return -1;
    }
}

int GameField::tryFit(int n, int x, int y)
{
  Shape &sh = shapes[n];
  int xx, yy;

  for (xx=0; xx<5; xx++)
    for (yy=0; yy<5; yy++)
      {
        if (sh.at(xx, yy) && (at(xx+x, yy+y) & 0xf0))
          return 0;
      }
  return 1;  
}

void
GameField::selectShape(int n)
{
  if (isSelected)
    {
      selected = n;
    }
  else
    {
      if (shape(n).isOnField)
        removeShape(n); 
      isSelected = 1;
      selected = n;
    }
}

void
GameField::clear(bool edit)
{
  for(int i=0; i<12; i++)
    shape(i).isOnField = 0;
  if (edit) {
    std::memset(tiles, 0x10, sizeof(tiles));
    std::memset(shapenums, 0, sizeof(shapenums));
  } else {
    std::memset(tiles, 0x11, sizeof(tiles));
    std::memset(shapenums, 0x20, sizeof(shapenums));
  }
  isEditing = edit;
}

void
GameField::divideShape(int n)
{
  int x, y;
  Shape &ts = shape(n);
  for(x=0; x<5; x++)
    for(y=0; y<5; y++)
      {
        if (ts.at(x, y)) {
          at(x+ts.x, y+ts.y) = 0;
          tileAt(x+ts.x, y+ts.y) = 0x10;          
        }
      }
}

int
GameField::loadFile(std::string filename, bool edit)
{
  std::ifstream f(path("maps/"+filename).c_str());
  std::string s;
  f >> s;
  if (s != "penta") goto fault;
  
  int mapwidth, mapheight;
  f >> mapwidth; f >> mapheight;
  if (mapwidth > width || mapwidth < 5 
    || mapheight > height || mapheight < 5) {
      std::cerr << "Error: invalid map size " << std::endl;
      goto fault;
    }
  
  clear(edit);
  
  int i, s_x, s_y, s_r;
  for (i=0; i<12; i++) {
    f >> s_x; f >> s_y; f >> s_r;
    if (s_x > width || s_y > height || s_r >= 12 || s_r < 0) {
      std::cerr << "Error: invalid shape " << i << std::endl;
    }
    shape(i).x = s_x;
    shape(i).y = s_y;
    shape(i).rot = s_r;
    edit ? updateShape(i) : divideShape(i);
  }
  isEditing = edit;
fault:
  return 0;
}

int
GameField::saveFile(string filename)
{
  std::ofstream f(path("maps/"+filename).c_str());

  //Calculate size of shape
  int xx=0, yy=0, xx1=width, yy1=height;
  int x, y, i;
  for (x=0; x<width; x++)
    for (y=0; y<height; y++)
      if (at(x, y)) {
        if (x<xx)  xx=x;
        if (x>xx1) xx1=x;
        if (y<yy)  yy=y;
        if (y>yy1) yy1=y;
      }
  
  f<<"penta "<<(xx1-xx)<<" "<<(yy1-yy)<<endl;
    
  for (i=0; i<12; i++) {
    Shape &s = shape(i);
    f << s.x << " " << s.y << " " << s.rot << endl;
  }
  return 0;
}

int
GameField::onCommand(int cmdId, std::string &command, std::list<std::string> &args)
{
  switch(cmdId) {
    case CMD_save:
      {
      CHKARGS(1);
      if (!isEditing) {
        cerr << "Cannot save while not editing!" << endl;
      }
      string file = POPARG;
      saveFile(file);
      break;
      }
    case CMD_load:
    case CMD_edit:  
      {
      CHKARGS(1);
      string file = POPARG;
      loadFile(file, cmdId==CMD_edit);
      break;
      }
    
  }
}
