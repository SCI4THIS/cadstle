#ifndef CADSTLE_H
#define CADSTLE_H 1

#include <stdint.h>

typedef enum {
  GENERATOR_GREEK_COLUMNS,
  GENERATOR_GREEK_CORINTHIAN_COLUMN,
  GEN_COLUMN_ADORN_CROSS,
  GEN_COLUMN_ADORN_ACANTHUS,
  GEN_SOIC_CLIP_SIDE,
} generator_t;

typedef struct {
  float x;
  float y;
  float z;
} point_t;

typedef struct {
  struct {
    char hdr[80];
    uint32_t n;
  } h;
  struct {
    char data[50];
  } tri[];
} stl_t;


#endif
