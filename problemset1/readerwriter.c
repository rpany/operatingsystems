#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



#define BUF_SIZE 5
#define NUM_READERS 5
#define NUM_WRITERS 5



int sharedState=0;
int x=3;
int writerQueue=0;
int readerQueue=0;
int waitingReaders=0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_writer = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_reader = PTHREAD_COND_INITIALIZER;


void *writerMain(void *param){
    int id = *((int*)param);
int i;

for(int i=0; i < x; i++){
    usleep(1000 * (random() % NUM_READERS + NUM_WRITERS));
    pthread_mutex_lock(&m);
     
    while(readerQueue != 0){
        pthread_cond_wait(&c_writer,&m);
    }
    readerQueue = -1; // shows that the write is started
    sharedState = rand();
    printf("Written by writer  %d the, iteration %d the value %d   \n",id,i,sharedState);
    readerQueue=0; // finished the write and not say that you are done.
    pthread_mutex_unlock(&m);
    pthread_cond_signal(&c_writer);
    pthread_cond_signal(&c_reader);
    
    
    }

    return 0;
}

void *readerMain(void *param){
     int id = *((int*)param);
int i;
//waitingReaders++;
printf("In the reader /n");
for(int i = 0; i < x; i++){
    usleep(1000 * (random() % NUM_READERS + NUM_WRITERS));
     pthread_mutex_lock(&m);
     
    while(readerQueue < 0){ // while there is a write going on
        pthread_cond_wait(&c_reader,&m);
    }
    readerQueue++;
    // now read the shared state and print it
    printf("Read by reader  %d the, iteration %d the value %d   \n",id,i,sharedState);
    readerQueue--;
    pthread_mutex_unlock(&m);
    pthread_cond_signal(&c_writer);
    pthread_cond_signal(&c_reader);
    printf("Reader completed %d iteration %d\n",id,i);

}

    return 0;
}


int main(int argc, char *argv[]){
    pthread_t writer[NUM_WRITERS];
    pthread_t reader[NUM_READERS];

    int readerThreadIds[NUM_READERS];
    int writerThreadIds[NUM_WRITERS];
    srandom((unsigned int)time(NULL));
    
    printf("Trying to create readers \n");
    for(int i; i < NUM_READERS; i++){
        readerThreadIds[i] = i;
        if(pthread_create(&reader[i], NULL,readerMain,&readerThreadIds[i]) !=0){
            fprintf(stderr, "Unable to create the Reader \n");
            exit(1);
         }
    }


for(int i; i < NUM_WRITERS; i++){
    writerThreadIds[i] = i;
    if(pthread_create(&writer[i], NULL,writerMain,&writerThreadIds[i]) !=0){
        fprintf(stderr, "Unable to create the Writer \n");
        exit(1);
    }
}

    for(int i; i < NUM_READERS; i++){
     pthread_join(reader[i],NULL);
    }

    for(int i; i < NUM_WRITERS; i++){
   pthread_join(writer[i],NULL);
    }



printf("Program completing");

}




