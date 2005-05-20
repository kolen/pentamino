#include "File.h"
#include <cstdio>
#include <fstream>

#ifndef DATADIR
#define DATADIR 0
#endif



char* FilePath::paths[] = {
  "./",
  "../",
  "/usr/share/pentamino/",
  "/usr/local/share/pentamino/",
  DATADIR,
  0
};

FilePath::FilePath()
{
  char** i;
  std::cerr << "Looking up directories..." <<std::endl;
  for (i=paths; *i; i++)
    {
      std::string s = *i;
      s += "img/shapes.png";
      std::ifstream f(s.c_str());
      std::cerr << "Looking path: "<< *i <<std::endl;
      if (f)
        {
          prefix = *i;
          std::cerr << "Found path: " << prefix << std::endl;
          return;
        }
    }
  std::cerr << "Warning: shapes.png not found" << std::endl;
}

std::string path(std::string file)
{
  static FilePath fpath;
  return fpath(file);
}
