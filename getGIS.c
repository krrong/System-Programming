#include <stdio.h>
#include <stdlib.h>
#include "object.h"

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