#ifndef COMMON_H
#define COMMON_H

#define MIN3(x,y,z) ((x) < (y)) ? (((x) < (z)) ? (x) : (z)) : (((y) < (z)) ? (y) : (z))
#define MAX3(x,y,z) ((x) > (y)) ? (((x) > (z)) ? (x) : (z)) : (((y) > (z)) ? (y) : (z))

#define MIN2(x,y) (((x) < (y)) ? (x) : (y))
#define MAX2(x,y) (((x) > (y)) ? (x) : (y))

#endif // COMMON_H
