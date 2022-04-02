FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: main.o ALGORITHMS.o readNwrite.o eigenPAIR.o SET.o LIST.o spmat.o GROUP.o
	gcc main.o ALGORITHMS.o readNwrite.o eigenPAIR.o SET.o LIST.o spmat.o GROUP.o -o cluster $(LIBS)
	
clean:
	rm -rf *.o cluster



main.o: main.c ALGORITHMS.h readNwrite.h
	gcc $(FLAGS) -c main.c 
	
ALGORITHMS.o : ALGORITHMS.c ALGORITHMS.h spmat.h SET.h eigenPAIR.h
	gcc $(FLAGS) -c ALGORITHMS.c 

readNwrite.o : readNwrite.c readNwrite.h spmat.h SET.h
	gcc $(FLAGS) -c readNwrite.c
	
eigenPAIR.o : eigenPAIR.c eigenPAIR.h
	gcc $(FLAGS) -c eigenPAIR.c

SET.o : SET.c SET.h LIST.h
	gcc $(FLAGS) -c SET.c
	
LIST.o : LIST.c LIST.h spmat.h
	gcc $(FLAGS) -c LIST.c 
	
spmat.o : spmat.c spmat.h GROUP.h
	gcc $(FLAGS) -c spmat.c
	
GROUP.o : GROUP.c GROUP.h  
	gcc $(FLAGS) -c GROUP.c



