#include "math.h"

u16 saturate(u16 num, u16 min, u16 max){
  return num > max ? max :
         num < min ? min : num;
}