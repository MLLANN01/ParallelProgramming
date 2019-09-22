// main.cpp
//
// This program shows you how to use three different timers to
// measure exection times of squential and c++11 multithreading
// dot prodduct.

/*

Testing Array of size: 1000000
Runtime of plain_max = 0.0005 seconds
Max for plain_max: 999
Runtime of plain_max_unroll_2 = 0.000536 seconds
Max for plain_max_unroll_2: 999
Runtime of plain_max_unroll_2 = 0.000562 seconds
Max for plain_max_unroll_2: 999

Testing Array of size: 10000000
Runtime of plain_max = 0.005294 seconds
Max for plain_max: 999
Runtime of plain_max_unroll_2 = 0.005232 seconds
Max for plain_max_unroll_2: 999
Runtime of plain_max_unroll_2 = 0.005325 seconds
Max for plain_max_unroll_2: 999

Testing Array of size: 100000000
Runtime of plain_max = 0.051716 seconds
Max for plain_max: 999
Runtime of plain_max_unroll_2 = 0.052309 seconds
Max for plain_max_unroll_2: 999
Runtime of plain_max_unroll_2 = 0.053357 seconds
Max for plain_max_unroll_2: 999

Testing Array of size: 1000000000
Runtime of plain_max = 0.528571 seconds
Max for plain_max: 999
Runtime of plain_max_unroll_2 = 0.529172 seconds
Max for plain_max_unroll_2: 999
Runtime of plain_max_unroll_2 = 0.538039 seconds
Max for plain_max_unroll_2: 999

*/

#include <iostream>
#include <algorithm>

#include "chronoTimer.h"
#include <vector>
#include <cstdlib>
#include <malloc.h>

#include <iostream>
#include <string>
#include "chronoTimer.h"

int n = 0;

using namespace std;

#define _N	(n)		// Number of vector elements
#define NOMINMAX
#define BUFFER 1000000000


float SequentialDot(const std::vector<float>& v1, const std::vector<float>& v2);
float SequentialDot2(const std::vector<float>& v1, const std::vector<float>& v2);
float ThreadDot(const std::vector<float>& v1, const std::vector<float>& v2, int nr_threads);
void plain_max();
void plain_max_unroll_2();
void plain_max_unroll_4();

float SequentialDot(float* v1, float* v2, int n)
{
	float result = 0;

	for (int i = 0; i < n; ++i)
		result += v1[i] * v2[i];

	return result;
}

// 
// Use the timer based on C++11 chrono functions (requiring chronoTimer.h)
//

#include "chronoTimer.h"

void chronoTimer(int N, int t)
{
	float dot;
	float time1, time2;

	std::vector<float> v1(N, 1.0f), v2(N, 1.0f);

	INIT_TIMER

		start = std::chrono::high_resolution_clock::now();
	dot = SequentialDot(v1, v2);
	time1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000.0;

	std::cout << "Sequential time measured by chrono timer = " << time1 << " seconds \n";
	std::cout << "Sequential dot product result = " << dot << std::endl;

	start = std::chrono::high_resolution_clock::now();
	dot = ThreadDot(v1, v2, t);
	time2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000000.0;

	std::cout << "MultiThreading time measured by chrono timer = " << time2 << " seconds \n";
	std::cout << "MultiThreading dot product result = " << dot << std::endl;

	std::cout << "\tSpeed-up = " << time1 / time2 << "\n";
}

//
// Use Windows timers (requiring timers.cpp and timers.h)
//
#include "timers.h"

void WindowsTimer(int N, int t)
{
	double time1, time2;
	float dot;
	std::vector<float> v1(N, 1.0f), v2(N, 1.0f);

	StartCounter();
	dot = SequentialDot(v1, v2);
	time1 = GetCounter();
	std::cout << "Sequential time measured by Windows timer = " << time1 << " seconds \n";
	std::cout << "Sequential dot product result = " << dot << std::endl;

	StartCounter();
	dot = ThreadDot(v1, v2, t);
	time2 = GetCounter();
	std::cout << "MultiThreading time measured by Windows timer = " << time2 << " seconds\n";
	std::cout << "MultiThreading dot product result = " << dot << std::endl;

	std::cout << "\tSpeed-up = " << time1 / time2 << "\n";
}

//
// Use chTimer.h (a cross-platform timer)
//
#include "chTimer.h"

void chTimerTest(int N, int t)
{
	double time1, time2;
	float dot;
	chTimerTimestamp start, stop;

	std::vector<float> v1(N, 1.0f), v2(N, 1.0f);

	chTimerGetTime(&start);
	dot = SequentialDot(v1, v2);
	chTimerGetTime(&stop);
	time1 = chTimerElapsedTime(&start, &stop);
	std::cout << "Sequential time measured by chTimer = " << time1 << " seconds\n";
	std::cout << "Sequential dot product result = " << dot << std::endl;

	chTimerGetTime(&start);
	dot = ThreadDot(v1, v2, t);
	chTimerGetTime(&stop);
	time2 = chTimerElapsedTime(&start, &stop);
	std::cout << "MutiThreading time measured by chTimer = " << time2 << " seconds\n";
	std::cout << "MutiThreading dot product result = " << dot << std::endl;

	// Calculating Speed-Up
	std::cout << "\tSpeed-up = " << time1 / time2 << "\n";
}

void plain_max() {

	float max = -INFINITY;

	float* array = new float[BUFFER];

	for (int i = 0; i < BUFFER; i++)
	{
		array[i] = std::rand() % 1000;
	}

	INIT_TIMER;

	START_TIMER;

	for (uint64_t i = 0; i < BUFFER; i++)
	{
		max = (std::max)(max, array[i]);
	}

	STOP_TIMER("plain_max");

	std::cout << "Max for plain_max: " << max << "\n";

	delete[] array;

}

void plain_max_unroll_2() {

	float max = -INFINITY;
	float max_0 = -INFINITY;
	float max_1 = -INFINITY;

	float* array = new float[BUFFER];

	for (int i = 0; i < BUFFER; i++)
	{
		array[i] = std::rand() % 1000;
	}


	INIT_TIMER;

	START_TIMER;

	for (uint64_t i = 0; i < BUFFER; i += 2)
	{
		max_0 = (std::max)(max_0, array[i + 0]);
		max_1 = (std::max)(max_1, array[i + 1]);
	}

	max = (std::max)(max_0, max_1);

	STOP_TIMER("plain_max_unroll_2");

	std::cout << "Max for plain_max_unroll_2: " << max << "\n";

	delete[] array;

}

void plain_max_unroll_4() {

	float max = -INFINITY;
	float max_0 = -INFINITY;
	float max_1 = -INFINITY;
	float max_2 = -INFINITY;
	float max_3 = -INFINITY;

	float* array = new float[BUFFER];

	for (int i = 0; i < BUFFER; i++)
	{
		array[i] =  std::rand() % 1000;
	}


	INIT_TIMER;

	START_TIMER;

	for (uint64_t i = 0; i < BUFFER; i += 4)
	{
		max_0 = (std::max)(max_0, array[i + 0]);
		max_1 = (std::max)(max_1, array[i + 1]);
		max_2 = (std::max)(max_2, array[i + 2]);
		max_3 = (std::max)(max_3, array[i + 3]);
	}

	max = (std::max)(max_0, (std::max)(max_1, (std::max)(max_2, max_3)));

	STOP_TIMER("plain_max_unroll_2");

	std::cout << "Max for plain_max_unroll_2: " << max << "\n";

	delete[] array;
}

int main()
{
	int t = 0;

	int q = 0;

	std::vector<float>* arr = new std::vector<float>;
	int rand = 0;
	int length;
	int size;

	do
	{
		std::cout << "------------------- \n";
		std::cout << "(1) Timer Test \n";
		std::cout << "(2) Arrray Comparison\n";
		std::cout << "(3) Exit\n";
		std::cout << "------------------- \n";

		std::cin >> q;

		switch (q)
		{
		case 1:

			std::cout << "\nEnter Vector Size: \n";

			std::cin >> n;

			std::cout << "\nEnter Thread Size: \n";

			std::cin >> t;

			std::cout << "Dot product of two float vectors of length " << _N << " with thread pool size of " << t << " ----->\n";

			std::cout << "\nchrono timer tests\n";
			chronoTimer(_N, t);

			std::cout << "\nWinodows timer tests\n";
			WindowsTimer(_N, t);

			std::cout << "\nchTimer tests\n";
			chTimerTest(_N, t);

			std::cout << "\n============== Timer tests done. ============\n\n";

		case 2:

			std::cout << "\nTesting Array of size: " << BUFFER << " \n";

			plain_max();

			plain_max_unroll_2();

			plain_max_unroll_4();

			std::cout << "\n-----------------------\n";
			
			system("pause");

		case 3:
			break;
		}
	} while (q != 2);

	std::cout << "\nBye \n";

	//system("PAUSE");


	return 0;
}

