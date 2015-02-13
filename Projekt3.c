#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>



pthread_t pr[4];
pthread_mutex_t se[4];
pthread_mutex_t seEnd[4];
pthread_mutex_t seIndex;

int pIndex = 0;
int fIndex = 0;
int mIndex = 15;

int files[15] = {1,2,3,1,2,3,1,2,3,1,2,3,1,2,3};
int lockTimes[4] = {0,3,4,5};
int file;

int z = 0;

void * print(void *arg){
    pthread_mutex_lock(&seIndex);
    int i = pIndex++;
    pthread_mutex_unlock(&seIndex);

    printf("Start %d \n",i );

    while(fIndex<mIndex){
        pthread_mutex_lock(&se[i]);

        file = files[fIndex];

        pthread_mutex_lock(&seIndex);

        fIndex++;
        pthread_mutex_unlock(&seIndex);

        printf("=> Print %d file %d, time is: %ds.\n",i,file,lockTimes[file]*100 );
        int lockTime = z+lockTimes[file];

        while(z<lockTime);
        pthread_mutex_unlock(&se[i]);
    }

    pthread_mutex_unlock(&seEnd[i]);
}

int main(int argc, char const *argv[])
{

     pthread_mutex_lock(&seEnd[0]);
     pthread_mutex_lock(&seEnd[1]);
     pthread_mutex_lock(&seEnd[2]);
     pthread_mutex_lock(&seEnd[3]);


    pthread_create(&pr[0],NULL,print,NULL);
    pthread_create(&pr[1],NULL,print,NULL);
    pthread_create(&pr[2],NULL,print,NULL);
    pthread_create(&pr[3],NULL,print,NULL);

     while(z<1000)
     {
         printf("%d# \n",z);

      z++;
    }



    return 0;
}
