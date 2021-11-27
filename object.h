#pragma once
#ifndef OBJECT_H // ����ü�� ������ ���ǵǴ� ���� ����
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