#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int create_semaphore();

int seller_P(int sem_id);

int seller_V(int sem_id);

int customer_P(int sem_id);

int customer_V(int sem_id);