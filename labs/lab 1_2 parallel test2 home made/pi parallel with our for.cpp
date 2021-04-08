#include<iostream>
#include<ctime>
#include<omp.h>
#include<iomanip>
using namespace std;

const int n = 1000000;
const int threadsNo = 4;



void main()
{
	clock_t t1, t2;
	double wt1, wt2;

	double deltax = 1.0 / n;
	double sum = 0.0;
	long len = (long)n / (long)threadsNo;

	t1 = clock();
	wt1 = omp_get_wtime();
#pragma omp parallel num_threads(threadsNo)
	{
		int id = omp_get_thread_num();

		double start = id * len;
		double end = start + len;

		double mysum = 0.0;
		double x;
		for (long i = start; i < end; i++)
		{
			x = (double)i * deltax;
			mysum += (4 / (i + x * x))*deltax;
		}

#pragma omp critical
		{
			sum += mysum;
			cout << "thread id : " << id << "   started from : " << start << "  ended at : " << end << "   mysum = " << mysum << "   global sum " << sum << endl;
		}
	}
	
	t2 = clock();
	wt2 = omp_get_wtime();
	cout << "pi = " << sum << endl;
	cout << "time = " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	cout << "time omp = " << (wt2 - wt1)<< endl;

	system("pause");
}