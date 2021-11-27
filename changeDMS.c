#include <stdio.h>
#include <stdlib.h>
#include "object.h"

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