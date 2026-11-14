#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <stdint.h>

#define SaveFileName  "highs.dat"
#define TotalFileName "totals.dat"

int SaveToFile(const uint64_t* data, const int offset, const char* dest);
uint64_t LoadFromFile(const int offset, const char* src);

#endif
