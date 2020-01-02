#include "math.h"

Rect intersect(Rect a, Rect b){
  Rect c = {0, 0, 0, 0};
  s32 left, right, top, bottom;
  left = a.left > b.left ? a.left : b.left;
  right = a.right < b.right ? a.right : b.right;
  top = a.top > b.top ? a.top : b.top;
  bottom = a.bottom < b.bottom ? a.bottom : b.bottom;
  if(left < right && top < bottom){
    c.left = left;
    c.right = right;
    c.top = top;
    c.bottom = bottom;
  }
  return c;
}

u16 saturate(u16 num, u16 min, u16 max){
  return num > max ? max :
         num < min ? min : num;
}