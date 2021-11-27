#pragma once
#include "object.h"
int getGIS(char* filename, struct coordinate* a, struct coordinate* b);
int* calculate(struct coordinate* a, struct coordinate* b, int cnt);
void changeDMS(struct coordinate* a, int cnt);
void print(struct coordinate* start, struct coordinate* dest, int cnt);