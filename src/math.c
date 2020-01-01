#include "math.h"

Rect intersect(Rect a, Rect b){
  Rect c;
  c.pos[X] = a.pos[X] < b.pos[X] ? b.pos[X] : a.pos[X];
  c.pos[Y] = a.pos[Y] < b.pos[Y] ? b.pos[Y] : a.pos[Y];
  c.size[X] = c.pos[X] == a.pos[X] ? 
    a.pos[X] + a.size[X] - c.pos[X] :
    b.pos[X] + b.size[X] - c.pos[X];
  c.size[Y] = c.pos[Y] == a.pos[Y] ? 
    a.pos[Y] + a.size[Y] - c.pos[Y] :
    b.pos[Y] + b.size[Y] - c.pos[Y];
  return c;
}

u16 saturate(u16 num, u16 min, u16 max){
  return num > max ? max :
         num < min ? min : num;
}