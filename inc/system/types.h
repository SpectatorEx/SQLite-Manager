#ifndef TYPES_H
#define TYPES_H

typedef long long int64;

typedef unsigned char bool;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef struct {
    short x, y;
} point;

typedef struct {
    short x, y;
    short width, height;
} rect;

#endif