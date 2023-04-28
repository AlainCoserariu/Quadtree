CC = gcc
CFLAGS = -Wall -Wfatal-errors -std=c17 -pedantic
CLIBS = -lMLV
OBJ = affichage.o main.o quadtree.o particule.o utilitaire.o
EXEC = quadtree

exec : $(OBJ)
	$(CC) $^ -o $(EXEC) $(CLIBS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f *.o

mrproper : clean
	rm -f $(EXEC)