seller:seller.o Semaphore.o
	gcc seller.o Semaphore.o -o seller -lpthread

customer:customer.o Semaphore.o
	gcc customer.o Semaphore.o -o customer -lpthread

reset:reset.o Semaphore.o
	gcc reset.o Semaphore.o -o reset

seller.o:seller.c Semaphore.h
	gcc seller.c -c -lpthread

customer.o:customer.c Semaphore.h
	gcc customer.c -c -lpthread

reset.o:reset.c Semaphore.h
	gcc reset.c -c

Semaphore.o:Semaphore.c Semaphore.h
	gcc Semaphore.c -c

.PHONY:clean

clean:
	-rm *.o seller customer reset