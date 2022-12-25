#include <iostream>
#include <omp.h.>
#include <windows.h>
#include <iomanip>
using namespace std;
const int MAX_THREADS = 16, BLOCKSIZE = 100, N = 100000000;
double pi = 0;
int main()
{
	int CountBlock = N / BLOCKSIZE;
	int startTime, endTime;
	omp_lock_t lock;
	omp_set_num_threads(MAX_THREADS);
	omp_init_lock(&lock);
	startTime = GetTickCount();
#pragma omp parallel  
	{
		double tempPi = 0;
#pragma omp for
		for (int block = 0; block < CountBlock; ++block)
			for (int i = block * BLOCKSIZE; i < block * BLOCKSIZE + BLOCKSIZE; ++i)
				tempPi += 4 / (1 + ((i + 0.5) / N) * ((i + 0.5) / N));
		omp_set_lock(&lock);
		pi += tempPi;
		omp_unset_lock(&lock);
	}
	endTime = GetTickCount();
	pi /= N;
	std::cout <<
		"pi: " << fixed << setprecision(20) << pi <<
		"\nAverage time: " << endTime - startTime << " ms";
}