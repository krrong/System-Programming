#pragma once
#ifndef OBJECT_H // 구조체가 여러번 정의되는 것을 방지
#define OBJECT_H

struct gisinfo {
	int degree;
	int minute;
	int second;
	int totalSec;
	int dms;
	char direction;
};

typedef struct coordinate {
	struct gisinfo longitude;
	struct gisinfo latitude;

}coordinate;

#endif // !OBJECT_H