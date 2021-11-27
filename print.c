#include <stdio.h>
#include <stdlib.h>
#include "object.h"

// �� ���� ��ǥ�� ��� �ִ� �迭�� ������ �Է� �޾� distance ����
int* calculate(struct coordinate* a, struct coordinate* b, int cnt) {

	// �Ÿ��� ������ �迭 ���� �Ҵ�
	int* dist = malloc(sizeof(int) * cnt);

	// �Ÿ� ���
	for (int i = 0; i < cnt; i++) {
		dist[i] = abs(a[i].latitude.totalSec - b[i].latitude.totalSec) + abs(a[i].longitude.totalSec - b[i].longitude.totalSec);
	}

	return dist;
}

// first coordinate second coordinate distance seconds DMS ���
void print(struct coordinate* start, struct coordinate* dest, int cnt) {
	int* dist = malloc(sizeof(int) * cnt);
	dist = calculate(start, dest, cnt);

	int* d = malloc(sizeof(int) * cnt);		// distance�� degree�� ������ �迭
	int* m = malloc(sizeof(int) * cnt);		// distance�� minute�� ������ �迭
	int* s = malloc(sizeof(int) * cnt);		// distance�� second�� ������ �迭

	// distance�� degree, minute, second�� �и�
	for (int i = 0; i < cnt; i++) {
		d[i] = dist[i] / 3600;
		m[i] = (dist[i] - d[i] * 3600) / 60;
		s[i] = (dist[i] - d[i] * 3600 - m[i] * 60);
	}

	// ���
	for (int i = 0; i < cnt; i++) {
		printf("(%03dd %02dm %02ds %c, %02dd %02dm %02ds %c) (%03dd %02dm %02ds %c, %02dd %02dm %02ds %c) %06d %03dd %02dm %02ds\n",
			start[i].longitude.degree, start[i].longitude.minute, start[i].longitude.second, start[i].longitude.direction,
			start[i].latitude.degree, start[i].latitude.minute, start[i].latitude.second, start[i].latitude.direction,
			dest[i].longitude.degree, dest[i].longitude.minute, dest[i].longitude.second, dest[i].longitude.direction,
			dest[i].latitude.degree, dest[i].latitude.minute, dest[i].latitude.second, dest[i].latitude.direction,
			dist[i], d[i], m[i], s[i]
		);
	}
}