#ifndef SHOW_H
#define SHOW_H

#include <string>

typedef struct show_ {
  std::string name,
    file;
  unsigned short type;

  show_ ( std::string n = "",
      std::string f = "",
      unsigned short t = 0 ) {
    name = n;
    file = f;
    type = t;
  }

} Show;

#endif 
