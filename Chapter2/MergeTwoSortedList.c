#include <stdio.h>
#include <stdlib.h>

void MergeList(int a[], int la, int b[], int lb, int ans[]) {
	int ia, ib, i;
	ia = 0, ib = 0, i = 0;
	while (ia < la && ib < lb) {
		if (a[ia] < b[ib]) {
			ans[i] = a[ia];
			++ia;
		}
		else {
			ans[i] = b[ib];
			++ib;
		}
		++i;
	}
	if (ia < la) {
		for (int j = 0; j < la; j++) {
			ans[i + j] = a[ia + j];
		}
	}
	if (ib < lb) {
		for (int j = 0; j < lb; j++) {
			ans[i + j] = b[ib + j];
		}
	}
}

int main() {
	int numsa[6] = { 1, 3, 5, 7, 9, 11 };
	int numsb[5] = { 0, 2, 4, 6, 8};
	int la = 6, lb = 5;
	int l = la + lb;
	int *numsAns = (int*)malloc(l);
	MergeList(numsa, la, numsb, lb, numsAns);
	for (int i = 0; i < l - 1; i++) {
		printf("%d ", numsAns[i]);
	}
	printf("%d\n", numsAns[l - 1]);
	return 0;
}