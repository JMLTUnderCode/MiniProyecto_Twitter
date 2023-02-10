/* Autores: Astrid Alvarado - 1810938
 * 					Laura Parilli   - 1710778
 * 					Junior Lara     - 1710303
 *
 * Tarea 2: Twitter
 * El proposito de esta tarea es evaluar el manejo de apuntadores, estructuras,
 * y estrings en C a traves de un programa iterativo.
 *
 */

#include "twitter.h"

// Funcion que limpiar el Buffer del teclado extrayendo todos lso caracteres 
// sobrantes hasta conseguir el '\n' que representa el presionar ENTER.
void cleanBuffer(const char* str){
	int toint = (int)(str[strlen(str)-1]);
	if(toint != 10 &&  toint != 0) 
		while(getchar() != '\n');
}

// Funcion encargada en solicitar por pantalla el username y password al usuario
// por standardInput.
void name_pass(){
	fflush(stdin);
	printf("|* -> USERNAME(Max. 16 caracters): "); scanf("%s", &username);
	fflush(stdin);
	printf("|* -> PASSWORD(Max. 16 Caracters): "); scanf("%s", &password);
}


// Funcion que permite mostrar por pantalla el perfil de un usuario.
void goto_perfil(){

}

// Funcion que permite agregar un nuevo tweet a la lista de tweets del usuaro
// Loged.
void add_tweet(){

}

// En caso de el usuario ingresar "signup" se deben solicitar los prompt de 
// "username" y "password" para ser guardados en la tabla de hash donde se 
// almacena la DataUsers.
void signup(){
	system("clear");
	printf(".--------------------------------------------------------.\n");
	printf("|********************************************************|\n");
	printf("|*           -=-   Register on TWITTER   -=-            *|\n");
	printf("|*                                                      *|\n");
	
	// Solicitamos datos para registrar.
	name_pass();

	printf("|*                                                      *|\n");
	printf("|* -> Registration Completed!                           *|\n");	
	printf("|*                                                      *|\n");
	printf("|* -> Your data is:                                     *|\n");
	printf("|*    ID: %18s                            *|\n", username);
	printf("|*    Pass: %16s                            *|\n",password);
	printf("|* -> Do not forget!                                    *|\n");
	printf("|*                                                      *|\n");
	printf("|* -> Press any key to continue...");

	// Limpiamos y detenemos output.
	fflush(stdout);
	system("bash -c \"read -sn 1\"");	

	// Vamos al prompt inicial del programa.
	initial_interfaz();
}

// Funcion que permite Deslogear a un usuario de Twitter y llevarlo a la interfaz inicial
// de Login. 
void logout(){
	printf("|*                                                      *|\n");
	printf("|* -> Logout Successful!                                *|\n");

	Goto_init();
}

// En caso de el usuario ingresar "leave" se debe "cerrar"/culminar
// el programa indicando un mensaje final.
void leave(){
	printf("|*                                                      *|\n");
	printf("|* -> SEE YOU LATER!                                    *|\n");
	printf("|*                                                      *|\n");
	printf("|********************************************************|\n");
	printf("`--------------------------------------------------------`\n");
}

// Funcion que se encarga de gestionar la informacion dada por el usuario. 
// Permite en funcion de la opcion dada ir a su respectiva funcion.
void user_input(){
	fflush(stdin);
	scanf("%s", &user_option);
		
	if(strcmp(user_option, "login")==0 || strcmp(user_option, "Login")==0 || strcmp(user_option, "LOGIN")==0)
		name_pass();

	else if(strcmp(user_option, "signup")==0 || strcmp(user_option, "Signup")==0 || strcmp(user_option, "SIGNUP")==0)
		signup();

	else if(strcmp(user_option, "leave")==0 || strcmp(user_option, "Leave")==0 || strcmp(user_option, "LEAVE")==0)
		leave();

	else if(strcmp(user_option, "logout")==0 || strcmp(user_option, "Logout")==0 || strcmp(user_option, "LOGOUT")==0)
		logout();

	else if( user_option[0] == '+' )
		add_tweet();

	else if( user_option[0] == '@' )
		goto_perfil();

	else {
			printf("|* -> Error! Available Opt.: Login, Signup, Leave, +, @, Logout. *|\n");
			printf("|* -> Option: ");
			user_input();
	}
}

// Funcion que muestra la interfaz base del programa. Nombre de la App simulada,
// prompt base y solicitud de datos.
void initial_interfaz(){
	system("clear");
	printf(".--------------------------------------------------------.\n");
	printf("|********************************************************|\n");
	printf("|*                  -=-   TWITTER   -=-                 *|\n");
	printf("|*                                                      *|\n");
	printf("|* -> DON'T MISS WHAT'S HAPPENING!                      *|\n");
	printf("|* ->  Login, SignUp or Leave: ");

	user_input();
}

// Funcion que permite concluir algun proceso, como registrarse y Deslogear
// al usuario.
void Goto_init(){
	printf("|* -> Press any key to continue...");

	// Limpiamos y detenemos output.
	fflush(stdout);
	system("bash -c \"read -sn 1\"");	

	// Vamos al prompt inicial del programa.
	initial_interfaz();
}

int main(){
	initial_interfaz();
	
	return EXIT_SUCCESS;
}
