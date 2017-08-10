#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include"Semaphore.h"

#define customer_num 20

void * customer_func(void * num){
    printf("Customer number %d is waiting for service...\n", (int)num);
    int sem_id = create_semaphore();
    if(sem_id == -1){
        printf("Failed to get semaphore...\n");
        return NULL;
    }
    customer_V(sem_id);
    seller_P(sem_id);
    printf("Customer number %d is receiving service...\n", (int)num);
    sleep(3);
    seller_V(sem_id);
}

int main(){
    pthread_t customers[customer_num];
    int i;
    for(i = 1; i <= customer_num; i++){
        pthread_create(&customers[i-1], NULL, customer_func, (void *)i);
        sleep(3);
    }

    for(i = 0; i < customer_num; i++){
        pthread_join(customers[i], NULL);
    }

    return 0;
}
