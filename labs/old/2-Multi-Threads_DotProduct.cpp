#include<iostream>
#include<pthread.h>
#include<string>
using namespace std;

long VecLen = 40000000;

struct dotProductData{
	double* a; //first vector
	double* b; //second vector
	double sum; //sum of the multiplied corresponding numbers of the two vectors
	int vecLength; //vector length
	dotProductData(){
		sum = 0;
		vecLength = VecLen;
	}
}dotStr;

#define ThreadsNo 4
pthread_t myThreads[ThreadsNo];

pthread_mutex_t mutexSum; //declares a mutex variable

void* dotProduct(void* arg){
	long offset = (long) arg;
	int len, start, end;
	double mySum = 0;
	len = dotStr.vecLength/ThreadsNo;
	start = offset*len;
	end = start + len;
	
	for(long i = start; i < end; i++){
		mySum += dotStr.a[i]*dotStr.b[i];
	}
	
	pthread_mutex_lock(&mutexSum);
	/*
	locks the specified mutex variable (and then the thread is called THE OWNING THREAD)
	(if it's already locked by another thread then it will wait until the owning thread Unlocks it)
	*/
	
	dotStr.sum += mySum;
	cout<<"Thread "<<offset<<" did from "<<start<<" to "<<end<<": mySum = "<<mySum<<" Global sum = "<<dotStr.sum<<endl;
	
	pthread_mutex_unlock(&mutexSum);
	/*
	unlocks the specific mutex variable IF CALLED BY THE OWNING THREAD
	(if it's not owned by another thread OR it's already unlocked then an error occurs)
	*/

	pthread_exit(NULL);

	return NULL;
}


void main() {

	dotStr.a = new double[VecLen];
	dotStr.b = new double[VecLen];

	for(long i = 0; i < dotStr.vecLength; i++){
		dotStr.a[i] = 1;
		dotStr.b[i] = 1;
	}

	pthread_mutex_init(&mutexSum, NULL); //initially the specific mutexSum is UNLOCKED
	/*
	The pthread_mutex_init() function initializes the specified mutex

	int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);

		mutex: Is the mutex to initialize.
		attr: Specifies the attributes to use to initialize the mutex, or NULL if default attributes should be used.
	*/

	pthread_attr_t attr; //declares an attribute 
	pthread_attr_init(&attr); //initializes a thread attribute object with the default settings for each attribute
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
	/*
	sets the detached state attribute in the specified attribute object.
	The thread's detached state determines whether another thread may wait for the termination of the thread.
	Valid settings for detachstate include:

	PTHREAD_CREATE_DETACHED: 
	Creates a new detached thread.
	-A detached thread disappears without leaving a trace.
	-The thread ID and any of its resources are freed and ready for reuse.
	-pthread_join() cannot wait for a detached thread.

	PTHREAD_CREATE_JOINABLE:
	-Creates a new non-detached thread.
	-The thread ID and some of the threads other resources are not freed until pthread_join() is called.
	-pthread_join() must be called to release any resources associated with the terminated thread.
	*/

	for(long i = 0; i < ThreadsNo; i++){
		pthread_create(&myThreads[i], &attr, dotProduct, (void*) i);
		/*if(i == 1)
			pthread_detach(myThreads[i]); //detach a thread even though it was created as joinable!!!
			(opposite to pthread_join())
		*/
	}

	pthread_attr_destroy(&attr); //free attribute variable

	for(int i = 0; i < ThreadsNo; i++){
		pthread_join(myThreads[i],NULL); //the calling thread (Master thread which is main function) waits for other threads
 	}

	/*  Master thread continues its instructions   */
	
	cout<<"Sum = "<<dotStr.sum<<endl;

	pthread_mutex_destroy(&mutexSum); //free the mutex variable

	system("pause");

	pthread_exit(NULL); //exit Master Thread
}