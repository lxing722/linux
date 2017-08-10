#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>

#define CHAIRS 4

sem_t mutex;
sem_t barber;
sem_t customer;
int waiting;
void * barber_func(){
    sem_post(&barber);  //barber信号量加1,
    while(1){
        sem_wait(&customer);  //等待顾客，如果有顾客信号量大于0，则执行下面的步骤
        printf("The barber is cutting hair...\n");
	printf("A customer is receiving service...\n");
        sleep(4);
	printf("A customer finished...\n");
        sem_wait(&mutex);  //给顾客理完发之后，给waiting加锁，waiting减一，再解锁
        waiting--;
        sem_post(&mutex);
    }
}

void * customer_func(){
    if(waiting < CHAIRS){  //保证等待人数不超过椅子数
        sem_post(&customer);  //顾客信号量加1
        printf("A customer comes in and is waiting for service...\n");
        sem_wait(&mutex);  
        waiting++;
        sem_post(&mutex);
        sem_wait(&barber);  //等待理发师空闲
        sleep(4);
        sem_post(&barber);
    }
    else{
        printf("A customer comes in, but there is no empty chair, so the customer leaves...\n");
    }
}

int main(){
    waiting = 0;
    
    sem_init(&mutex, 0, 1);
    sem_init(&barber, 0, 0);
    sem_init(&customer, 0, 0);

    pthread_t barber_id;
    pthread_t customer_id[20];
    pthread_create(&barber_id, NULL, barber_func, NULL);
    for(int i = 0; i < 20; i++){
        pthread_create(&customer_id[i], NULL, customer_func, NULL);  //创建顾客线程
        sleep(3);
    }

    pthread_join(barber_id, NULL);
    for(int i = 0; i < 20; i++){
        pthread_join(customer_id[i], NULL);
    }

    return 0;
}

