#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>

class FilePath
{
public:
  FilePath();
  std::string operator()(std::string fname)
  {
    return prefix + fname;
  }
private:
  std::string prefix;
  static char* paths[];
};

std::string path(std::string file);

#endif
