#pragma disable 4996
#include <stdio.h>
#include <stdlib.h>
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

// 파일이름, start, destination 배열을 인자로 받아 배열에 저장하고 개수 리턴
int getGIS(char* filename, struct coordinate* a, struct coordinate* b) {
	printf("%s\n", filename);
	FILE* fp = fopen(filename, "r");
	int cur = 0;

	// 파일의 끝까지 읽어와서 배열에 저장하고 개수 리턴
	while (!feof(fp)) {
		fscanf(fp, "(%d%c, %d%c) (%d%c, %d%c) \n",
			&a[cur].longitude.dms, &a[cur].longitude.direction,
			&a[cur].latitude.dms, &a[cur].latitude.direction,
			&b[cur].longitude.dms, &b[cur].longitude.direction,
			&b[cur].latitude.dms, &b[cur].latitude.direction);
		cur++;
	}

	fclose(fp);
	return cur;
}

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

// coordinate 배열과 개수를 인자로 받아 DMS로 변환하여 저장한다.
void changeDMS(struct coordinate* a, int cnt) {
	for (int i = 0; i < cnt; i++) {
		// dms를 degree, minute, second로 분리
		a[i].latitude.degree = a[i].latitude.dms / 10000;
		a[i].latitude.minute = (a[i].latitude.dms - a[i].latitude.degree * 10000) / 100;
		a[i].latitude.second = (a[i].latitude.dms - a[i].latitude.degree * 10000 - a[i].latitude.minute * 100);

		// dms를 degree, minute, second로 분리
		a[i].longitude.degree = a[i].longitude.dms / 10000;
		a[i].longitude.minute = (a[i].longitude.dms - a[i].longitude.degree * 10000) / 100;
		a[i].longitude.second = (a[i].longitude.dms - a[i].longitude.degree * 10000 - a[i].longitude.minute * 100);

		// totalSec 계산
		a[i].latitude.totalSec = a[i].latitude.degree * 3600 + a[i].latitude.minute * 60 + a[i].latitude.second;
		a[i].longitude.totalSec = a[i].longitude.degree * 3600 + a[i].longitude.minute * 60 + a[i].longitude.second;

		// 음수인 경우
		if (a[i].latitude.direction != 'N') {
			a[i].latitude.totalSec = a[i].latitude.totalSec * -1;
		}

		// 음수인 경우
		if (a[i].longitude.direction != 'E') {
			a[i].longitude.totalSec = a[i].longitude.totalSec * -1;
		}
	}

	return;
}

// first coordinate second coordinate distance seconds DMS 출력
void printDMS(struct coordinate* start, struct coordinate* dest, int cnt) {
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

// 
void print(coordinate* a, int cnt) {
	for (int i = 0; i < cnt; i++) {
		//printf("%d %d\n", a[i].longitude.dms, a[i].latitude.dms);

		printf("%d %d %d ", a[i].longitude.degree, a[i].longitude.minute, a[i].longitude.second);
		printf("%d %d %d\n", a[i].latitude.degree, a[i].latitude.minute, a[i].latitude.second);
	}
}


int main() {

	coordinate start[32];
	coordinate destination[32];

	int cnt = getGIS("input.txt", start, destination);
	changeDMS(start, cnt);
	changeDMS(destination, cnt);
	calculate(start, destination, cnt);
	printDMS(start, destination, cnt);
	return 0;
}