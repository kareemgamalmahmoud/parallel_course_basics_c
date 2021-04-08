#include<iostream>
#define HAVE_STRUCT_TIMESPEC
#include<pthread.h>
#include<ctime>
#include<iomanip>
using namespace std;

const long n = 100000;
long sum = 0;
const int threadno = 4;
long len = n / threadno;
int *a, *b;

pthread_mutex_t mymutex;

void* f(void* arg)
{

	long x, mysum = 0, start, end;

	x = (long)arg;

	start = x * len;
	end = start + len;

	for (int i = start; i < end; i++)
		mysum += a[i] * b[i];

	pthread_mutex_lock(&mymutex);
	sum += mysum;
	cout << "the thread : " << x << " start : " << start << "end : " << end << "  mysum : " << mysum << "  global sum : " << sum << endl;
	pthread_mutex_unlock(&mymutex);

	pthread_exit(NULL);
	return NULL;
}


void main()
{
	a = new int[n];
	b = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = 1;
		b[i] = 1;
	}

	pthread_mutex_init(&mymutex, NULL);
	pthread_t mythread[threadno];

	clock_t t1, t2;
	t1 = clock();

	for (int i = 0; i < threadno; i++)
		pthread_create(&mythread[i], NULL, *f, (void*)i);

	for (int i = 0; i < threadno; i++)
		pthread_join(mythread[i],NULL);


	
	t2 = clock();

	cout << "the sum : " << sum << endl;
	cout << "the time " << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;


	pthread_mutex_destroy(&mymutex);
	system("pause");
	pthread_exit(NULL);
}

/*

#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

const long n = 100000000; //8 zeros
long summ = 0;

void main () {

	int* A, *B;
	A = new int[n];
	B = new int[n];
	for (long i = 0; i < n; i++) {
		A[i] = 1;
		B[i] = 1;
	}

	clock_t t1,t2;
	t1 = clock();
	for (long i = 0; i < n; i++) {
		summ += A[i] * B[i];
	}
	t2 = clock();

	cout << "The product           = " << summ << endl;
	cout << "CPU time (in seconds) = " << (double)(t2-t1) / CLOCKS_PER_SEC << endl;

	system("pause");
}
*/