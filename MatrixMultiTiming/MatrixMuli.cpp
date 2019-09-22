// MatrixMulti.cpp
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iomanip>

#include <random>

#include "chronoTimer.h"

void matrixMul1(float* C, float* A, float* B, int RA, int CA, int CB);	// CPU matrix multiplication (row-major)
void matrixMul2(float* C, float* A, float* B, int RA, int CA, int CB);	// CPU matrix multiplication (row-major)
void matrixMul3(float* C, float* A, float* B, int RA, int CA, int CB);	// CPU matrix multiplication (column-major)
void matrixMul4(float* C, float* A, float* B, int RA, int CA, int CB);	// CPU matrix multiplication (row-major)
void sgemm(char transa, char transb, int m, int n, int k,
	float alpha, float a[], int lda, float b[], int ldb, float beta,
	float c[], int ldc);

void printMatrix(float* M, int RM, int CM);

int MatrixMultiTiming(int RA, int CA, int CB, int type)
{
	int RB = CA, RC = RA, CC = CB;
	float *A, *B, *C, *Ref_C;

	printf("single precision %dx%d matrix times %dx%d matrix:\n\n", RA, CA, RB, CB);

	INIT_TIMER;

	START_TIMER;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(0, 1);

	A = (float *)malloc(RA * CA * sizeof(float));		assert(A);
	B = (float *)malloc(RB * CB * sizeof(float));		assert(B);
	C = (float *)malloc(RC * CC * sizeof(float));		assert(C);
	Ref_C = (float *)malloc(RC * CC * sizeof(float));	assert(Ref_C);
	
	for (int i = 0; i < RA * CA; ++i)
		A[i] = (float)(dist(rd));
	for (int i = 0; i < RB * CB; ++i)
		B[i] = (float)(dist(rd));
	for (int i = 0; i < RC * CC; ++i)
		C[i] = Ref_C[i] = 0;

	STOP_TIMER("allocating and initilizing matrices using uniform distribution(0,1)");
	std::cout << "\n\n";
	
//	START_TIMER;
//	matrixMul1(C, A, B, RA, CA, CB);
//	STOP_TIMER("matrixMul1");
//	std::cout << "C[2] = " << C[2] << "\n\n";

//	START_TIMER;
//	matrixMul2(C, A, B, RA, CA, CB);
//	STOP_TIMER("matrixMul2");
//	std::cout << "C[2] = " << C[2] << "\n\n";
	
		std::cout << "Values1: " << RA << CA << CB << "\n";
		START_TIMER
			matrixMul3(C, A, B, RA, CA, CB);
		STOP_TIMER("MatrixMul3", "")
			std::cout << "C[2] = " << C[2] << "\n\n";
		return C[2];
	
//	START_TIMER;
//	matrixMul4(C, A, B, RA, CA, CB);
//	STOP_TIMER("matrixMul4");
//	std::cout << "C[2] = " << C[2] << "\n\n";

		std::cout << "Values2: " << RA << CA << CB << "\n";
		START_TIMER;
		//  Ref_C := alpha*op( A )*op( B ) + beta*C
		sgemm('n', 'n', RA, CB, CA, 1.0, A, CA, B, RB, 1.0, Ref_C, CB);
		STOP_TIMER("sgemm", "");
		std::cout << "Ref_C[2] = " << Ref_C[2] << "\n\n";
		return Ref_C[2];
	
}

void Problem3(int min, int max)
{
	float result1 = 0.0;
	float result2 = 0.0;

	for (int i = min; i <= max; i++)
	{
		min = i;

		int RA = min;
		int CA = min;
		int CB = min;

		int RB = CA, RC = RA, CC = CB;
		float *A, *B, *C, *Ref_C;

		printf("single precision %dx%d matrix times %dx%d matrix:\n\n", RA, CA, RB, CB);

		INIT_TIMER;

		START_TIMER;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dist(0, 1);

		A = (float *)malloc(RA * CA * sizeof(float));		assert(A);
		B = (float *)malloc(RB * CB * sizeof(float));		assert(B);
		C = (float *)malloc(RC * CC * sizeof(float));		assert(C);
		Ref_C = (float *)malloc(RC * CC * sizeof(float));	assert(Ref_C);

		for (int i = 0; i < RA * CA; ++i)
			A[i] = (float)(dist(rd));
		for (int i = 0; i < RB * CB; ++i)
			B[i] = (float)(dist(rd));
		for (int i = 0; i < RC * CC; ++i)
			C[i] = Ref_C[i] = 0;

		STOP_TIMER("allocating and initilizing matrices using uniform distribution(0,1)");
		std::cout << "\n\n";

		START_TIMER
			matrixMul3(C, A, B, RA, CA, CB);
		STOP_TIMER("MatrixMul3", "")
			std::cout << "C[2] = " << C[2] << "\n\n";

		result1 = C[2] + result1;

		START_TIMER;
		//  Ref_C := alpha*op( A )*op( B ) + beta*C
		sgemm('n', 'n', RA, CB, CA, 1.0, A, CA, B, RB, 1.0, Ref_C, CB);
		STOP_TIMER("sgemm", "");
		std::cout << "Ref_C[2] = " << Ref_C[2] << "\n\n";

		result2 = Ref_C[2] + result2;
	}

	std::cout << "\nResult of all Mul3 operations: " << std::fixed << std::setprecision(25) << result1 << "\n";

	std::cout << "\nResult of all sgemm operations: " << std::fixed << std::setprecision(25) << result2 << "\n";
}

//======================================================================================
//
// CPU Matrix multiplication: C = A * B (Row-major)
// where A is a RAxCA matrix, B is a CAxCB matrix and C is a RAxCB matrix.
// Assume matrices are stored in row-major linear array, and matrix indexing is 0-based.
//
//=====================================================================================

void matrixMul1(float* C, float* A, float* B, int RA, int CA, int CB)
{
	// index of the C matrix element 
	int row, col;

	for (row = 0; row < RA; ++row)
	{
		for (col = 0; col < CB; ++col)
		{
			float Cvalue = 0;
			int indexA = row * CA;
			int indexB = col;

			// Assuming row-major like in C (note CUBLAS and Fortran uses column-major)
			for (int k = 0; k < CA; k++)
			{
				Cvalue += A[indexA++] * B[indexB];
				indexB += CB;
			}

			C[row * CB + col] = Cvalue;
		}
	}
}
void matrixMul2(float* C, float* A, float* B, int RA, int CA, int CB)
{
	// index of the C matrix element 
	int row;
	int col;

	// Assuming row-major like in C (note CUBLAS and Fortran uses column-major)
	for (row = 0; row < RA; ++row)
	{
		for (col = 0; col < CB; ++col)
		{
			float Cvalue = 0;

			for (int k = 0; k < CA; k++)
			{
				Cvalue += A[row * CA + k] * B[k * CB + col];
			}

			C[row * CB + col] = Cvalue;
		}
	}
}

//=========================================================================================
//
// CPU Matrix multiplication: C = A * B (Columnn-major)
// where A is a RAxCA matrix, B is a CAxCB matrix, and C is a RAxCB matrix.
// Assume matrices are stored in column-major linear array, and matrix indexing is 0-based.
//
//=========================================================================================

void matrixMul3(float* C, float* A, float* B, int RA, int CA, int CB)
{
	// index of the C matrix element 
	int row, col;

	// Assuming colimn-major like in CUBLAS and Fortran, but matrix indexing is 0-based
	for (row = 0; row < RA; ++row)
	{
		for (col = 0; col < CB; ++col)
		{
			float Cvalue = 0.0;

			for (int k = 0; k < CA; k++)
			{
				Cvalue += A[row + RA * k] * B[col * CA + k];
			}

			C[row + col * RA] = Cvalue;  // Note column-major !!
		}
	}
}

//======================================================================================
//
// CPU Matrix multiplication: C = A * B (Row-major)
// where A is a RAxCA matrix, B is a CAxCB matrix and C is a RAxCB matrix.
// Assume matrices are stored in row-major linear array, and matrix indexing is 0-based.
//
//=====================================================================================

void matrixMul4(float* C, float* A, float* B, int RA, int CA, int CB)
{
	// index of the C matrix element 
	int row, col;
	
	// printMatrix(B, CA, CB);
	// Transpose B matrix
	float temp;
	for (row = 0; row < CA; row++)
		for (col = 0; col < CB; col++)
		{
			if (row > col) continue;

			temp = B[row * CA + col];
			B[row * CA + col] = B[col * CA + row];
			B[col * CA + row] = temp;
		}
	//printMatrix(B, CA, CB);


	for (row = 0; row < RA; ++row)
	{
		for (col = 0; col < CB; ++col)
		{
			float Cvalue = 0;
			int index = row * CA;

			for (int k = 0; k < CA; k++)
				Cvalue += A[index] * B[index++];

			C[row * CB + col] = Cvalue;
		}
	}
/*
	// Assuming row-major like in C (note CUBLAS and Fortran uses column-major)
	for (row = 0; row < RA; ++row)
	{
		for (col = 0; col < CB; ++col)
		{
			float Cvalue = 0;

			for (int k = 0; k < CA; k++)
			{
				Cvalue += A[row * CA + k] * B[col * CB + k];
			}

			C[row * CB + col] = Cvalue;
		}
	}
*/
}

void printMatrix(float* M, int RM, int CM)
{
	int col, row;

	int maxRow = RM <= 8 ? RM : 8;
	int maxCol = CM <= 8 ? CM : 8;
	for (row = 0; row < maxRow; row++)
	{
		for (col = 0; col < maxCol; col++)
		{
			std::cout << "\t" << M[row * CM + col];
		}
		std::cout << "\n";
	}
}
