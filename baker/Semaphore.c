#include "Semaphore.h"
#include<stdio.h>
int create_semaphore(){
    int key = ftok("sema", 1);
    if(key == -1){
        printf("Failed to generate key...\n");
        return -1;
    }
    return semget(key, 2, IPC_CREAT | 0666);  //创建两个信号量
}

int seller_P(int sem_id){
    struct sembuf operation = {0, -1, SEM_UNDO};
    return semop(sem_id, &operation, 1);
}

int seller_V(int sem_id){
    struct sembuf operation = {0, 1, SEM_UNDO};
    return semop(sem_id, &operation, 1);
}

int customer_P(int sem_id){
    struct sembuf operation = {1, -1, SEM_UNDO};
    return semop(sem_id, &operation, 1);
}

int customer_V(int sem_id){
    struct sembuf operation = {1, 1, SEM_UNDO};
    return semop(sem_id, &operation, 1);
}
