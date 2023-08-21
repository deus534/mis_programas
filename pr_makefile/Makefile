
CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -Wall
OBJS = main.o funciones.o

# comentarios con #
# introduccion de macros
# <  ---> contiene la dependencia del target
# @  ---> contiene al target
# %  ---> actua como wildcard..(cualquier cosa) + lo que sigue

ejec: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
%.o: %.c Makefile
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f *.o
	rm -f ejec
new: clean ejec

#crea la carpeta src
src: 
	mkdir $@

help:
	@echo "+++++++++++++++++++++++++++++"
	@echo "USO"
	@echo "\tmake ejec        linkea y compila"
	@echo "\tmake clean       remueve objecs y ejecutables"
	@echo "\tmake new         realiza clean y ejec"
	@echo "\tmake help        muestra la ayuda"
	@echo "\tmake src         crea una carpeta src"
	@echo "+++++++++++++++++++++++++++++"
