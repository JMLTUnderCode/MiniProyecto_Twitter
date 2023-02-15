# Renombrado de archivos.
COMP 		 = cc

LINK 		 = cc

FILE 		 = Proyect_1_AstridLauraJunior.c

OBJ 		 = Proyect_1_AstridLauraJunior.o

LIBRERYS = twitter.h global_variables.h

PROGRAM  = Proyect_1_AstridLauraJunior.exe


# Funcion de make
.PHONY: all clean

all: $(OBJ)

clean: 
	rm $(OBJ)

# Compilacion
OBJECTS: $(OBJ)

$(OBJ) : $(FILE)
	$(COMP) $(FILE) -o $(OBJ)

# 
