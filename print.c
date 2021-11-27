#include <stdio.h>
#include <stdlib.h>
#include "object.h"

// 두 점의 좌표를 담고 있는 배열과 개수를 입력 받아 distance 리턴
int* calculate(struct coordinate* a, struct coordinate* b, int cnt) {

	// 거리를 저장할 배열 동적 할당
	int* dist = malloc(sizeof(int) * cnt);

	// 거리 계산
	for (int i = 0; i < cnt; i++) {
		dist[i] = abs(a[i].latitude.totalSec - b[i].latitude.totalSec) + abs(a[i].longitude.totalSec - b[i].longitude.totalSec);
	}

	return dist;
}

// first coordinate second coordinate distance seconds DMS 출력
void print(struct coordinate* start, struct coordinate* dest, int cnt) {
	int* dist = malloc(sizeof(int) * cnt);
	dist = calculate(start, dest, cnt);

	int* d = malloc(sizeof(int) * cnt);		// distance의 degree를 저장할 배열
	int* m = malloc(sizeof(int) * cnt);		// distance의 minute을 저장할 배열
	int* s = malloc(sizeof(int) * cnt);		// distance의 second를 저장할 배열

	// distance를 degree, minute, second로 분리
	for (int i = 0; i < cnt; i++) {
		d[i] = dist[i] / 3600;
		m[i] = (dist[i] - d[i] * 3600) / 60;
		s[i] = (dist[i] - d[i] * 3600 - m[i] * 60);
	}

	// 출력
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