#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define WAIT_TIME_MAX 3
#define WAIT_TIME_MIN 1

pthread_t philosophers[NUM_PHILOSOPHERS];
pthread_mutex_t forks[NUM_PHILOSOPHERS];

void * run(void * arguments){
	sleep(rand() % WAIT_TIME_MAX + WAIT_TIME_MIN);
	int argument = *((int *) arguments);
	//printf("Philosopher #%u\n", argument);
	int result;
	int a = 50;
	// Pick the lowest chopstick available
//	while(1){
		pthread_mutex_lock(&forks[(argument + 1) % NUM_PHILOSOPHERS]);
		pthread_mutex_lock(&forks[argument]);
		printf("Philosopher %u has chopsticks %u and %u\n", argument, argument, (argument + 1) % NUM_PHILOSOPHERS);
		sleep(rand() % WAIT_TIME_MAX + WAIT_TIME_MIN);
		//pthread_mutex_unlock(&forks[argument]);
		pthread_mutex_unlock(&forks[(argument + 1) % NUM_PHILOSOPHERS]);
		pthread_mutex_unlock(&forks[argument]);
		printf("Philosopher %u has put down chopsticks %u and %u\n", argument, argument, (argument + 1) % NUM_PHILOSOPHERS);
//	}
	// Pickup chopstick. Wait for available chopstick for other hand.
	// eat
	// release chopstick
}

int main(int argc, char * argv[]){

	srand(time(NULL));

	int arguments[NUM_PHILOSOPHERS];
	int index;
	int result;

	for(index = 0; index < NUM_PHILOSOPHERS; index++){
		pthread_mutex_init(&forks[index], NULL);
	}
	
	for(index = 0; index < NUM_PHILOSOPHERS; index++){
		arguments[index] = index;
		result = pthread_create(&philosophers[index], NULL, run, &arguments[index]);		
	}

	for(index = 0; index < NUM_PHILOSOPHERS; index++){
		result = pthread_join(philosophers[index], NULL);
	}
	return 0;	
}
