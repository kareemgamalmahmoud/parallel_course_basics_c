#include<iostream>
//because i face some problems with out it.
#define HAVE_STRUCT_TIMESPEC
#include<ctime>
#include<pthread.h>
#include<iomanip>
using namespace std;

const int ThreadNo = 5;
const long n = 10000000;
long len = n / ThreadNo;
double step = 1.0 / n;
double pi = 0;//sum glopal

pthread_mutex_t mymutex;//1

void* f(void* arg)
{
	int id = (int)arg;
	double mysum = 0;
	double x = id * len*step;

	for (long i = 0; i < len; i++) {
		x += step;
		mysum += (4 / (1 + x * x))*step;
	}


	pthread_mutex_lock(&mymutex);//3
	pi += mysum;//need mutex
	cout << "thread :" << id << " , mysum :" << mysum << " , global sum = " << pi << endl;
	pthread_mutex_unlock(&mymutex);//4


	pthread_exit(NULL);
	return NULL;

}



void main()
{
	clock_t t1, t2;

	pthread_mutex_init(&mymutex, NULL);//2
	pthread_t mythreads[ThreadNo];

	t1 = clock();

	for (int i = 0; i < ThreadNo; i++)
	{
		pthread_create(&mythreads[i], NULL, *f, (void*)i);

	}


	for (int i = 0; i < ThreadNo; i++)
	{
		pthread_join(mythreads[i], NULL);
	}

	t2 = clock();

	cout << setprecision(15);
	cout << "pi = " << pi << endl;
	cout << "time : " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;

	pthread_mutex_destroy(&mymutex);//5
	


	/*
	clock_t t1 = clock();

	int n = 1000000;
	double sum = 0;
	double x = 0;
	double step = 1.0 / n;

	for (int i = 0; i < n; i++)
	{
		x += step;
		sum += (4.0 / (1 + x * x))* step;
	}

	cout << setprecision(20);
	cout << "pi : " << sum  << endl;

	clock_t t2 = clock();

	cout << "time : " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;
	*/

	system("pause");
	pthread_exit(NULL);
}