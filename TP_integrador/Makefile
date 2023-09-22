#realizacion de mi makefile

CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -Wall
OBJS = main.o client.o server.o
EDITOR = vim

FOBJ = obj/
FBIN = bin/
FSRC = src/

ejec: $(OBJS) Makefile
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	mv $(OBJS) $(FOBJ)
	mv ejec $(FBIN)
%.o: $(FSRC)%.c
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(FOBJ)*.o
	rm -f $(FBIN)ejec

new: clean ejec

%.c: 
	$(EDITOR) src/$@
%.h:
	$(EDITOR) headers/$@	

help:
	@echo "+++++++++++++++++++++++++++++"
	@echo "\t\t COMANDOS LINKEO COMPILO BORRADO"
	@echo "\tmake ejec        linkea y compila"
	@echo "\tmake clean       remueve objecs y ejecutables"
	@echo "\tmake new         realiza clean y ejec"
	@echo "\tmake help        muestra la ayuda"
	
	@echo "\n\t\t COMANDOS EDICION DE ARCHIVOS"
	@echo "\tmake client.c         abre con $(EDITOR) client.c"
	@echo "\tmake main.c           abre con $(EDITOR) main.c"
	@echo "\tmake server.c         abre con $(EDITOR) server.c"
	@echo "\tmake client.h         abre con $(EDITOR) client.h"
	@echo "\tmake server.h         abre con $(EDITOR) server.h"
	@echo "\tNOTA: puede cambiar tipo de editor en el archivo Makefile"
	@echo "+++++++++++++++++++++++++++++"
