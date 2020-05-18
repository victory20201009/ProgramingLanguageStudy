#include<stdio.h>

void left_move(unsigned int* p) {
	unsigned int n = *p;
	unsigned int m = n << 1;
	if (n & (1 << 31)) {
		m |= 1;
	}
	*p = m;
}

void right_move(unsigned int* p) {
	unsigned int n = *p;
	unsigned int m = n >> 1;
	if (n & 1) {
		m |= (1 << 31);
	}
	*p = m;
}

unsigned int move(unsigned int num, int step) {
	if (step > 0) {
		for (int i = 0; i < step; ++i)
			right_move(&num);
	} else {
		step = step * (-1);
		for (int i = 0; i < step; ++i)
			left_move(&num);
	}
	return num;
}

int main() {
	unsigned int tmp;
	int s;
	scanf("%d%d", &tmp,&s);
	printf("%u\n",move(tmp,s));
}

