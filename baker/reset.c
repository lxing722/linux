#include"Semaphore.h"
#include<stdio.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
    struct seminfo *__buf;
};

int main(){
    int sem_id = create_semaphore();
    if(sem_id == -1){
        printf("Failed to get semaphore...\n");
        return -1;
    }
    union semun sem;
    sem.val = 0;
    if(semctl(sem_id, 0, SETVAL, sem) == -1 || semctl(sem_id, 1, SETVAL, sem) == -1) //将信号量初始值都重置为0
        printf("Failed to set value...\n");
    return 0;
}
