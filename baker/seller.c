#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include"Semaphore.h"

#define SELLER_NUM 3

void * seller_func(void * num){
    int sem_id = create_semaphore();
    if(sem_id == -1){
        printf("Failed to get semaphore...\n");
        return NULL;
    }
    seller_V(sem_id);
    while(1){
        customer_P(sem_id);
        printf("Seller number %d is providing service...\n", (int)num);
        sleep(3);
    }
}

int main(){
    pthread_t sellers[SELLER_NUM];
    int i;
    for(i = 1; i <= SELLER_NUM; i++){
        pthread_create(&sellers[i-1], NULL, seller_func, (void *)i);
    }

    for(i = 0; i < SELLER_NUM; i++){
        pthread_join(sellers[i], NULL);
    }

    return 0;
}
