CC = gcc -Wall -g #compilation
RM = rm -f # suppression des fichiers inutiles
SRC = $(wildcard $(srcdir)*.c)# ficiers sources
HEAD =$(wildcard $(srcdir)*.h)# fichiers .h
OBJ = $(subst $(srcdir), $(bindir),$(SRC:.c=.o))  # fichiers objets
PROG = $(bindir)raytracer #nom de l'executable
srcdir = ./src/
bindir = ./bin/
docdir = ./doc/
savedir = ./Archive/Save
dir = ./Makefile ./Doxyfile
CP = cp $(SRC) $(HEAD) $(savedir)
TAR =	tar -cvf razavet_mael.tar $(savedir)
DEBUG = -D2
DOC = doxygen Doxyfile
VALGRIND=valgrind $(bindir)raytracer ./FichiersPov/essaie.pov 1 1 
OPEN=eog ImageFinale.ppm
EXECUTE=$(bindir)raytracer ./FichiersPov/siteduzero.pov 1000 1000

all:$(PROG)

$(PROG):$(OBJ)
	$(CC) $^ -o $@ -lm


$(bindir)%.o:$(srcdir)%.c $(srcdir)%.h
	$(CC) -c $< -o $@

$(bindir)%.o:$(srcdir)%.c
	$(CC) -c $< -o $@

.PHONY:clean

clean:
	$(RM) $(PROG) $(bindir)*.o 

.PHONY:save

save:
	$(CP)

.PHONY:restore

restore:
	cp $(savedir)* $(srcdir)

.PHONY:give

give:
	$(CP); $(TAR)

.PHONY:mkdir

mkdir:	
	$(shell mkdir $(srcdir) $(bindir) $(savedir))

debug:$(OBJ)
	$(CC) $^ -o $@ $(DEBUG) -lm

.PHONY:very-clean

very-clean:
	$(RM) $(PROG) $(bindir)*.o $(srcdir)*.*~ $(srcdir)*.gch $(srcdir)*.*\# 


documentation:
	$(DOC)

valgrind:
	$(VALGRIND)

open:
	$(OPEN)
	
execute:
	$(EXECUTE)	
		
