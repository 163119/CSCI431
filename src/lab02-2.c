#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

long* counter;

void* printSelf(void* in);
long isPrime(long x);
void* findPrimes(void* in);

int main (int argc, char* argv[]) {
if (argc != 3) {
  	printf("Please enter two parameters to this program.\n");
	return(-1);
}
int N = atoi(argv[1]);
if ( N == 0 ) {
	printf("Invalid parameter passed to this program, please provide an integer > 0.\n");
	return(-2);
}
long M = atol(argv[2]);
if ( M < 2) {
	printf("Invalid parameter passed to this program, please provide an integer >= 2\n");
}
pthread_t* thread = (pthread_t*)calloc(N, sizeof(pthread_t)); //initialize threads
counter = (long*)calloc(N, sizeof(long));//initialize counter array
//Create ranges
long range[N*3];
long total = M-2;
long chunkSize = (total/N)+1;
int n;
for (n = 0; n<N; n++) {
	range[n*3] = n; //First parameter will be the threads index
	if (n==0) range[(n*3)+1] = 2; //Second parameter will be the first value in the range
	else range[(n*3)+1] = range[(n*3)-1]+1; //This sets it to the previous ranges end value + 1
	range[(n*3)+2] = range[(n*3)+1]+chunkSize; //Third parameter will be the last value in the range
	if (range[(n*3)+2] > M) range[(n*3)+2] = M; //Set the end value to total range end value if it was greater
	if(pthread_create(&thread[n], NULL, findPrimes, &range[n*3])) { //start thread
		printf("Error creating thread %d\n", n+1);
		return(-3);
	}
}
void* tmp;
long ret = 0;
for (n = 0; n < N; n++) {
	pthread_join(thread[n], tmp);
	ret += counter[n];
}

printf("%d\n", ret);

free(thread);
free(counter);
return 0;
}

void* printSelf(void* in) {
	int* input = (int*)in;
	printf("I am child %d\n", (*input));
	return NULL;
}

long isPrime(long x) {
	double sqrtX = sqrt((double)x);
	if (sqrtX == 0) sqrtX = x;
	int i; //iterator
	if (x == 2 || x == 3) return 1; //2 and 3 are prime numbers
	if (x < 2 || x%2 == 0) return 0; //0, 1, and even numbers are not
	for (i = 3; i < sqrtX+1; i+=2) if ((x%i) == 0) return 0; //check for divisibility
	return 1; //if nothing divided evenly, it is prime
}

void* findPrimes(void* in) {
	long* input = (long*)in; //convert parameter to long pointer
	long threadNum = input[0]; //get thread number
	long start = input[1]; //grab ranges from pointer
	long stop = input[2];
	counter[threadNum] = 0; //initialize counter
	for(; start <= stop; start++) if (isPrime(start) == 1) counter[threadNum]++; //check primality of each number
	return &counter[threadNum]; //return pointer to number of primes in this range
}
