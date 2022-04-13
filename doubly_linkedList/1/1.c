#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE* lp;
	if (fopen_s(&lp, "input.txt", "r"))
		exit(1);
	int n, a, b;
	fscanf_s(lp, "%d", &n);
	while (fscanf_s(lp, "%d %d", &a, &b) != EOF) {

	}
}