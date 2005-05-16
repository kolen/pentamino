#ifndef SHAPE_H
#define SHAPE_H

extern char pShapes[12][8][5][5];

class Shape
{
public:
  int num;			//Номер фигуры
  int x, y, rot, lastx, lasty;
  int isOnField;

  int at (int x, int y)
  {
    return pShapes[num][rot][y][x];
  }
  void setRotation (int rot1)
  {
    rot = rot1;
  }
  void rotate (int dir = 1)
  {
    char r1 = (rot + dir) & 3;
    rot = (rot & (0xf0|8|4)) | r1;
  }
  void sideswap ()
  {
    rot ^= 4;
  }
  void move (int x1, int y1)
  {
    x = x1;
    y = y1;
  };
  void updateLastPos ()
  {
    lastx = x;
    lasty = y;
  };

  Shape ();
};

#endif
