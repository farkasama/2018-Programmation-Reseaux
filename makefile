CC  = gcc -Wall -g 
#mettre ici le nom de Exec, il va chercher le nom.c 
#et le compiler avec les dependances donnees
EXEC= client

UNIT= -pthread -lncurses

#prend tout les fichiers .h,filter-out: exclusion,
LIB = $(filter-out ,$(wildcard *.h))

#donne les noms .h ->.o
OBJ = $(LIB:.h=.o)

MPR = mrproper
CLN = clean
all: $(EXEC) 


# ajout de dependances
client: $(OBJ) $(UNIT)
controler.o: mess_treat.o clientUDP_service.o
mess_treat.o: game.o
# fin 

#compiler les Execs
$(EXEC):%: %.c
	$(CC) -o $@ $^

#regle pour les fichiers .h
$(LIB):%.h: %.c

#regle pour les future fichiers .o
$(OBJ):%.o: %.c %.h
	$(CC) -c -o $@ $*.c

#ce qui n'est pas un fichier
.PHONY: all clean mrproper $(UNIT)

test: $(UNIT)
	gcc $@.c $^

#ne garde que les Execs
clean:
	rm -f *.o *~ *.class

#supprime toutes generation de make ()
mrproper: 
	rm -f $(EXEC) *.out *.o *.class *~
