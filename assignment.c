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

// �����̸�, start, destination �迭�� ���ڷ� �޾� �迭�� �����ϰ� ���� ����
int getGIS(char* filename, struct coordinate* a, struct coordinate* b) {
	printf("%s\n", filename);
	FILE* fp = fopen(filename, "r");
	int cur = 0;

	// ������ ������ �о�ͼ� �迭�� �����ϰ� ���� ����
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

// coordinate �迭�� ������ ���ڷ� �޾� DMS�� ��ȯ�Ͽ� �����Ѵ�.
void changeDMS(struct coordinate* a, int cnt) {
	for (int i = 0; i < cnt; i++) {
		// dms�� degree, minute, second�� �и�
		a[i].latitude.degree = a[i].latitude.dms / 10000;
		a[i].latitude.minute = (a[i].latitude.dms - a[i].latitude.degree * 10000) / 100;
		a[i].latitude.second = (a[i].latitude.dms - a[i].latitude.degree * 10000 - a[i].latitude.minute * 100);

		// dms�� degree, minute, second�� �и�
		a[i].longitude.degree = a[i].longitude.dms / 10000;
		a[i].longitude.minute = (a[i].longitude.dms - a[i].longitude.degree * 10000) / 100;
		a[i].longitude.second = (a[i].longitude.dms - a[i].longitude.degree * 10000 - a[i].longitude.minute * 100);

		// totalSec ���
		a[i].latitude.totalSec = a[i].latitude.degree * 3600 + a[i].latitude.minute * 60 + a[i].latitude.second;
		a[i].longitude.totalSec = a[i].longitude.degree * 3600 + a[i].longitude.minute * 60 + a[i].longitude.second;

		// ������ ���
		if (a[i].latitude.direction != 'N') {
			a[i].latitude.totalSec = a[i].latitude.totalSec * -1;
		}

		// ������ ���
		if (a[i].longitude.direction != 'E') {
			a[i].longitude.totalSec = a[i].longitude.totalSec * -1;
		}
	}

	return;
}

// first coordinate second coordinate distance seconds DMS ���
void printDMS(struct coordinate* start, struct coordinate* dest, int cnt) {
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