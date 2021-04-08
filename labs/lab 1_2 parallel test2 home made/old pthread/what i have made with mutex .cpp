/*
	now we will use mutex to solve the problem of (m7dsh y5osh 3la sho5l al tany fe al thread)	
	
	1- declare mutex variable which is (globally)
	2- initialization : int pthread_mutex_init(pthread_mutex_t* mutexAddress, const pthread_mutexattr_t* attr);
	3- int pthread_mutex_lock(pthread_mutex_t* mutexAddress);
		note: we put the thread which we need to finsh his task completly between step (3 and 4)
	4- int pthread_mutex_unlock(pthread_mutex_t* mutexAddress);
	5- int pthread_mutex_destroy(pthread_mutex_t* mutexAddress);
*/

//note : the intialization write it in the main.
pthread_mutex_t myMutex;



void* f(void* arg) {
	int n = (int)arg;


	pthread_mutex_lock(&myMutex);
	cout << "Hell from thread : " << n << endl;
	pthread_mutex_unlock(&myMutex);

	//How to terminate a thread:
	pthread_exit(NULL);

	return NULL;
}

void main()
{

	/*
		how to creat a pthread
		---------------------------
		1-declare a thread first.
		2- use fun pthread_create() which contain 4 arg
			int pthread_create(&name of the thread, null--> by defult (joinable) or detachstate, void* fun, void* arg);
	*/

	/*
		how to create an attribute for a pthread
			1- declare an attribute
				note: we declare it before the criation of pthread
			2- initialization 
			3- determind with attribute you will use joinable or detachstate
			4- destroy to save memory
	*/

	/*

	questions : 

		1- why ? void*  | |
	*/



	//-------------create an attribute-------------
	pthread_attr_t myAttr;
	pthread_attr_init(&myAttr);

	pthread_attr_setdetachstate(&myAttr, PTHREAD_CREATE_JOINABLE);
	//----------------------------------------------


	//------------------mutex---------------
	pthread_mutex_init(&myMutex , NULL);
	//--------------------------------------


	pthread_t myThreads[5];
	int k = 3;
	for (int i = 0; i < 5; i++)
		pthread_create(&myThreads[i], &myAttr, *f, (void*)i);


//	for (int i = 3; i < 5; i++)
//		pthread_create(&myThreads[i], NULL, *f, (void*)i);


	//to make  ( main thread) may5oshsh 3la sho5l 7ad tany:)
	//	note main thread will wait the joinable but will not wait the detached
	for (int i = 0; i < 5; i++)
		pthread_join(myThreads[i], NULL);






	cout << "All Done!" << endl;


	//remember to distroy the attr.
	pthread_attr_destroy(&myAttr);

	//remember to distroy the mutex
	pthread_mutex_destroy(&myMutex);

	//return 0;
	system("pause");

	//How to terminate a thread:
	//the thread does not any thing end his task(maybe make him wait) -->if and only if he finsh his work
	pthread_exit(NULL);
}