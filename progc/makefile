all : exec

AVL.o : AVL.c AVL.h
	gcc -c AVL.c -o AVL.o
	
Recup.o : Recup.c Recup.h
	gcc -c Recup.c -o Recup.o

Tri.o : Tri.c Tri.h
	gcc -c Tri.c -o Tri.o
	
main.o : main.c AVL.h Tri.h Recup.h
	gcc -c main.c -o main.o
	
exec : main.o Tri.o Recup.o AVL.o
	gcc *.o -o exec

clean : 
	rm -f *.o
	rm -f exec
