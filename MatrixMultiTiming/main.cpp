// main.cpp

/*
Enter Min Matrix Size:
2500

Enter Max Matrix Size:
2520

Result of all Mul3 operations: 13248.7167968750000000000000000

Result of all sgemm operations: 13248.7167968750000000000000000

Enter Min Matrix Size:
600

Enter Max Matrix Size:
700

Result of all Mul3 operations: 16400.9296875000000000000000000

Result of all sgemm operations: 16400.9296875000000000000000000

1

1000

Result of all Mul3 operations: 125211.1640625000000000000000000

Result of all sgemm operations: 125211.1640625000000000000000000

*/


#include <iostream>
#include <algorithm>

#include "chronoTimer.h"
#include <vector>
#include <cstdlib>


#include <iostream>
#include <string>
#include "chronoTimer.h"

using namespace std;

int n = 0;
int m = 0;

int result1 = 0;
int result2 = 0;

#define size1 (n)

#define ROWA n
#define COLA n
#define COLB n
#define ROWB COLA
#define ROWC ROWA
#define COLC COLB

int MatrixMultiTiming(int rowA, int colA, int colB, int type);
void Problem3(int min, int max);

// main function - application entry point
int main()
{
	n = 0;
	float t = 0;
	int q = 0;
	int r = 0;
	int s = 0;
	int a = 0;
	std::vector<float> *arr = new std::vector<float>;
	int rand = 0;
	int length;
	float array[1];

	do
	{
		std::cout << "------------------- \n";
		std::cout << "(1) Matrix Test \n";
		std::cout << "(2) Exit\n";
		std::cout << "------------------- \n";

		std::cin >> q;

		switch (q)
		{
		case 1:

			std::cout << "\nEnter Min Matrix Size: \n";

			std::cin >> n;

			std::cout << "\nEnter Max Matrix Size: \n";

			std::cin >> m;

			Problem3(n, m);

			std::cout << "\n============== Matrix tests done. ============\n\n";

			result1 = 0;
			result2 = 0;
			n = 0;
			r = 0;
			s = 0;

		case 2:
			break;
		}
	} while (q != 2);

	return 0;
}
/*

float A[ROWA][COLA], B[ROWB][COLB], C[ROWC][COLC];

void matrixMul()
{
// index of the C matrix element
int row;
int col;

// Assuming row-major like in C (note CUBLAS, Fortran, and R use column-major)
for (row = 0; row < rowA; ++row)
for (col = 0; col < colA; ++col)
A[row][col] = 1;

for (row = 0; row < rowB; ++row)
for (col = 0; col < colB; ++col)
B[row][col] = 1;


for (row = 0; row < rowC; ++row)
{
for (col = 0; col < colC; ++col)
{
float Cvalue = 0;

for (int k = 0; k < colA; k++)
{
Cvalue += A[row][k] * B[k][col];
}

C[row][col] = Cvalue;
}
}
}
*/