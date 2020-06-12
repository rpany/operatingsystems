#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUF_SIZE 3


int buffer[BUF_SIZE];
int add=0;
int rem=0;
int num=0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;


void *producer(void *param){
int i;
for(int i=0; i<=5; i++){
    pthread_mutex_lock(&m);
        if(num > BUF_SIZE){
            fprintf(stderr, "Exceeded buffer size in producer num = %d \n",  num);
            exit(1);
        }
    
    while(num==BUF_SIZE){
        pthread_cond_wait(&c_prod,&m);
    }
    buffer[add]=i;
    add = (add+1) % BUF_SIZE;
    num++;
    pthread_mutex_unlock(&m);
    pthread_cond_signal(&c_cons);
    printf("Added producer %d   \n",i);
    }
    return 0;
}

void *consumer(void *pararm){
int i;
while(1){
    pthread_mutex_lock(&m);
    if(num < 0){
        fprintf(stderr,"There is a problem witth the consumer as num is less than zero\n");
    }
    sleep(2);
    while(num == 0){
        pthread_cond_wait(&c_cons,&m);
    }
    i = buffer[rem];
    rem = (rem+1) % BUF_SIZE;
    num--;
    pthread_mutex_unlock(&m);
    pthread_cond_signal(&c_prod);
    printf("Consumer value removed %d\n",i);
}

    return 0;
}


int main(int argc, char *argv[]){
    pthread_t tid1, tid2;
    int i;

if(pthread_create(&tid1, NULL,producer,NULL) !=0){
    fprintf(stderr, "Unable to create the producer \n");
    exit(1);
}

if(pthread_create(&tid2,NULL,consumer,NULL)!=0){
        fprintf(stderr, "Unable to create the consumer \n");
        exit(1);
}

pthread_join(tid1,NULL);
pthread_join(tid2,NULL);
printf("Program completing");

}




