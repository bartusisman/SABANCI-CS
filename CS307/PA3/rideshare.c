#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct semaphore
{
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int value;
} sem_t;

sem_t semA;
sem_t semB;
pthread_mutex_t lock;
pthread_barrier_t barrier;
pthread_mutex_t lock_print;
pthread_cond_t c;

int cnt = 0;
void sem_init(sem_t *s, int value)
{
        pthread_mutex_init(&s->lock, NULL);
        pthread_cond_init(&s->cond, NULL);
        s->value = value;
}

void sem_wait_mutex(sem_t *s, pthread_mutex_t *m)
{
        pthread_mutex_lock(&s->lock);
        s->value--;
        if (s->value < 0)
        {
            pthread_mutex_unlock(m);
            pthread_cond_wait(&s->cond, &s->lock);
        }
        else
        {
             pthread_mutex_unlock(m);
        }
        pthread_mutex_unlock(&s->lock);
}

void sem_wait(sem_t *s)
{
        pthread_mutex_lock(&s->lock);
        s->value--;
        pthread_mutex_unlock(&lock);
        if (s->value < 0)
        {
            pthread_cond_wait(&s->cond, &s->lock);
        }
        pthread_mutex_unlock(&s->lock);
}

void sem_post(sem_t *s)
{
        pthread_mutex_lock(&s->lock);
        s->value++;
        pthread_cond_signal(&s->cond);
        pthread_mutex_unlock(&s->lock);
}

void sem_setvalue(sem_t *sem, int val)
{
    for (int i = 0; i < val; i++)
    {
        sem_post(sem);
    }
}

void routine(sem_t* sem1, sem_t* sem2, char team)
{
        bool is_captain = false;
        pthread_mutex_lock(&lock);
        if(sem1->value < 0 && sem2->value < -1) 
        {
		is_captain  = true;
		sem_post(sem1);
		sem_setvalue(sem2, 2); 
	} 	

	else if(sem1->value < -2) 
	{
		is_captain  = true; 
        	sem_setvalue(sem1, 3); 
    	} 
    	else 
    	{
        	sem_wait(sem1);
    	}
    	
        printf("Thread ID: %ld, Team: %c, I have found a spot in a car\n", pthread_self(), team);
        pthread_barrier_wait(&barrier);
     

        if (is_captain)
        {
        	
            printf("Thread ID: %ld, Team: %c, I am the captain and driving the car\n", pthread_self(), team);
            cnt++;
            pthread_barrier_destroy(&barrier);
            pthread_barrier_init(&barrier, NULL, 4);     
            pthread_mutex_unlock(&lock);
            if(cnt != 0)
            {
        	pthread_cond_signal(&c);
        	pthread_cond_destroy(&c);
        	pthread_cond_init(&c, NULL);
            }
        }
}

void *routine_A()
{
        if(cnt != 0)
        {
        	pthread_cond_wait(&c, &lock);
        }
        printf("Thread ID: %ld, Team: A, I am looking for a car\n", pthread_self());
        routine(&semA, &semB, 'A');
}

void *routine_B()
{
	if(cnt != 0)
        {
        	pthread_cond_wait(&c, &lock);
        }
        printf("Thread ID: %ld, Team: B, I am looking for a car\n", pthread_self());
        
        routine(&semB, &semA, 'B');
}

int main(int argc, char *argv[])
{
        if (argc != 3) // expected 2 arguments
        {
            printf("less or more than 2 arguments, program terminated!\n");
            return 1;
        }
    
        int A = atoi(argv[1]); // number of fans from club A
        int B = atoi(argv[2]); // number of fans from club B
        int total = A + B; // total number of fans
    
        if( (A%2 != 0) || (B%2 != 0) || (total%4 != 0) ) // checks the validity of arguments
        {
            printf("Arguments are not valid! program terminated.\n");
            return 1;
        }
    

        pthread_t th[total];
        sem_init(&semA, 0);
        sem_init(&semB, 0);
        pthread_barrier_init(&barrier, NULL, 4);
        pthread_cond_init(&c, NULL);
        
        for(int i = 0; i < A; i++) // create the threads of A
        {
            pthread_create(&th[i], NULL, &routine_A, NULL);
        }
        for(int i = A; i < total; i++) // create the threads of B
        {
            pthread_create(&th[i], NULL, &routine_B, NULL);
        }
    
        for(int i = 0; i < total; i++)
        {
        
            pthread_join(th[i],NULL);
        }
        printf("The main terminates\n");

        return 0;
}




