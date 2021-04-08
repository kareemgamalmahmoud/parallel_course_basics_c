#include<iostream>
#include<pthread.h>
using namespace std;

void* f(void* arg)
{

	int n=(int) arg;
	cout<<"Hello from my thred "<<n*2<<endl;
	return NULL;

}

// pthread _attr_t myatt
//pthread_attr_int(&myatt)
//pthread_attr_setdetach


void main()
{
	pthread_t mythread;
	pthread_attr_t myatt;
	pthread_attr_init(& myatt);
	pthread_attr_setdetachstate(&myatt,PTHREAD_CREATE_JOINABLE);

	int k=3;
	for(int i=0;i<5;i++)
		pthread_create(&mythread,&myatt,*f,(void*)k);
	cout<<"all done"<<endl;
	system("pause");
	pthread_attr_destroy(&myatt);
}