#include <stdio.h>
#include <assert.h>

#define true 1
#define false 0

#define N_QUEEN 8

int is_conflict(int mat[N_QUEEN][N_QUEEN], int i, int j)
{
	int m = 0, n = 0;

	for (m = 0;m < N_QUEEN;m++) {
		for (n = 0;n < N_QUEEN;n++) {
			if ((m == i) && (n == j))
				continue;
			if (mat[m][n] && ((m == i) ||
							  (n == j)))
				return true;
			if (mat[m][n] && (((m+n) == (i+j)) ||
							  ((m-n) == (i-j))))
				return true;
		}
	}
	return false;
}

void print_board(int mat[N_QUEEN][N_QUEEN])
{
	int m = 0, n = 0;
	for (m = 0;m < N_QUEEN;m++) {
		for (n = 0;n < N_QUEEN;n++) {
			printf ("%d ", mat[m][n]);
		}
		printf ("\n");
	}
	return;
}


void fill_queens(int mat[N_QUEEN][N_QUEEN])
{
	int prob[N_QUEEN] = {0};
	int m = 0, n = 0, nqueens = 0;

	while (1) {
		for (m = 0;m >= 0 && m < N_QUEEN;) {
			while ((m < N_QUEEN) && (prob[m] < N_QUEEN)) {
				if (!is_conflict(mat, m, prob[m])) {
					mat[m][prob[m]] = 1;
					nqueens++;
					m++;
					continue;
				}
				prob[m]++;
			}
			if (nqueens == N_QUEEN)
				break;
			while (prob[m] >= N_QUEEN) {
				print_board(mat);
				printf ("\n");
				assert(m);
				prob[m] = 0;
				m--;
				assert(mat[m][prob[m]]);
				mat[m][prob[m]] = 0;
				prob[m]++;
				nqueens--;
			}
		}
		if (nqueens == N_QUEEN)
			break;
	}
}

int main()
{
	int mat[N_QUEEN][N_QUEEN] = {{0}};

	fill_queens(mat);
	print_board(mat);
}

