#pragma disable 4996
#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "system.h"

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