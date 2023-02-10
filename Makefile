COMP 		 = cc

LINK 		 = cc

FILE 		 = Assignment_2_AstridLauraJunior.c

OBJ 		 = Assignment_2_AstridLauraJunior.o

LIBRERYS = twitter.h global_variables.h

PROGRAM  = Assignment_2_AstridLauraJunior

$(OBJ) : $(FILE) $(LIBRERYS)
	$(COMP) $(FILE) $(LIBRERYS) -o $(OBJ)

$(PROGRAM) : $(OBJ)
	$(COMP) $(OBJ) -o $(PROGRAM)
