CC = gcc

CFLAGS = -c -O2  -I/home/$(USER)/local/include/ -I/usr/include/ -I.

CFLAGSDEBUG = -g -Wall -c -I/home/$(USER)/local/include/ -I/usr/include/ 

LFLAGS = -lm -L/home/$(USER)/local/lib -Wl,-R /home/$(USER)/local/lib 


#distancia:distancia.h
#	echo Estoy compilando $@.c
#	$(CC) $(CFLAGS) $@.c -lm -o $@.o

LRT_box:
	echo Estoy compilando $@.c
	$(CC) $(CFLAGS) $@.c -o $@.o
	$(CC) $@.o $(LFLAGS) -lm -lgsl -lgslcblas -lfftw3 -o  $@.x		



debug: 
	echo Estoy compilando para debugear $@.c
	$(CC) $(CFLAGSDEBUG) $@.c -o $@.o
	$(CC) $@.o $(LFLAGS)  -o $@.x


clean:
	rm -rf *.~
	rm -rf *.out
	rm -rf *#
	rm -rf *.o
	rm -rf *.a
	rm -rf *.so
	rm *.x	
