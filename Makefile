COMP 		 = cc

LINK 		 = cc

FILE 		 = Proyect_1_AstridLauraJunior.c

OBJ 		 = Proyect_1_AstridLauraJunior.o

LIBRERYS = twitter.h global_variables.h

PROGRAM  = Proyect_1_AstridLauraJunior

$(OBJ) : $(FILE) $(LIBRERYS)
	$(COMP) $(FILE) $(LIBRERYS) -o $(OBJ)

$(PROGRAM) : $(OBJ)
	$(COMP) $(OBJ) -o $(PROGRAM)
