CFLAGS := -Wall -Wextra -O -g

all: exe

fonctions.o : fonctions.c fonctions.h
	@echo "Compilation de fonctions"
	gcc -c fonctions.c -o fonctions.o $(CFLAGS)
 
main.o : main.c fonctions.h
	@echo "Compilation du main"
	gcc -c main.c -o main.o $(CFLAGS)

exe : fonctions.o main.o
	@echo "Compilation de l'exécutable"
	gcc fonctions.o main.o -o exe
  
clean :
	@echo "On clean pour apporter les modifs"
	rm -f *.o
