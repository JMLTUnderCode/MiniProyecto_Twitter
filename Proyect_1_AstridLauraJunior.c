/* Autores: Astrid Alvarado - 1810938
 * 					Laura Parilli   - 1710778
 * 					Junior Lara     - 1710303
 *
 * Tarea 2: Twitter
 * El proposito de esta tarea es evaluar el manejo de apuntadores, estructuras,
 * y estrings en C a traves de un programa iterativo.
 *
 *
 */

#include "twitter.h"

// Funcion que muestra la interfaz base del programa. Nombre de la 
// App simulada, prompt base y solicitud de datos.
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

// Funcion que limpiar el Buffer del teclado extrayendo todos lso caracteres 
// sobrantes hasta conseguir el '\n' que representa el presionar ENTER.
void cleanBuffer(const char* str){
	int toint = (int)(str[strlen(str)-1]);
	if(toint != 10 &&  toint != 0) 
		while(getchar() != '\n');
}

// Funcion encargada en solicitar por pantalla el username y password al 
// usuario por standardInput.
void name_pass(){
	while(TRUE){
		fflush(stdin);
		printf("|* -> USERNAME(Min. 8 - Max. 16 chars): "); scanf("%s", username);
		if(valid_len(username)) 
			break;
	}
	while(TRUE){
		fflush(stdin);
		printf("|* -> PASSWORD(Min. 8 - Max. 16 Chars): "); scanf("%s", password);
		if(valid_len(password)) 
			break;
	}
	if(user_validation(username) && (strcmp(user_option, "signup")==0 || strcmp(user_option, "Signup")==0 || strcmp(user_option, "SIGNUP")==0)) {
		printf("|* -> Error: User already exists.*|\n");
		Goto_init();

	} else if ( !user_validation(username) && (strcmp(user_option, "login")==0 || strcmp(user_option, "Login")==0 || strcmp(user_option, "LOGIN")==0)){
		printf("|* -> Error: Incorrect user or password.                 *|\n");
		Goto_init();
	}
}

// Funcion que se encarga de check el userinput del usarname y password, dado
// que se tieneu n maximo de 16 caracteres por campo.
int valid_len(const char* str){
	if(strlen(str) > 16 || strlen(str) < 8 ){
		printf("|* -> Error: Invalid amount of chars.                    *|\n");
		printf("|*                                                       *|\n");
		return FALSE;
	} else
		return TRUE;
}

// Funcion que se encarga de gestionar la informacion dada por el usuario. 
// Permite en funcion de la opcion dada ir a su respectiva funcion.
void user_input(){
	fflush(stdin);
	scanf("%s", user_option);
	lowercase(user_option);		
	if(strcmp(user_option, "login")==0)
		name_pass();

	else if(strcmp(user_option, "signup")==0)
		signup();

	else if(strcmp(user_option, "leave")==0)
		leave();

	else if(strcmp(user_option, "logout")==0)
		logout();

	else if( user_option[0] == '+' )
		add_tweet();

	else if( user_option[0] == '@' )
		goto_perfil();

	else {
			printf("|* -> Error! Available Options is:                      *|\n"); 
			printf("|* -> Login, Signup, Leave, +, @, Logout.               *|\n");
			printf("|* -> Try again: ");
			user_input();
	}
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
	printf("|*    Pass: %16s                            *|\n", password);
	printf("|* -> Do not forget!                                    *|\n");
	printf("|*                                                      *|\n");
	
	Goto_init();
}

// Funcion que permite Deslogear a un usuario de Twitter y llevarlo a la interfaz inicial
// de Login. 
void logout(){
	printf("|*                                                      *|\n");
	printf("|* -> Logout Successful!                                *|\n");
	printf("|*                                                      *|\n");

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

// Funcion que transforma a minusculas una cadena.
void lowercase(char* str){
	for(int i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
}

// Funcion que permite mostrar por pantalla el perfil de un usuario.
void goto_perfil(){
	
	char user_temp;
	char opt;
	printf("|*                                                      *|\n");
	printf("|* -> Enter user: @"); scanf("%s", &user_temp);
	
	if(user_validation(&user_temp))
		print_messages(&user_temp);
	else {
		printf("|* -> Error: User not found.                          *|\n");
		printf("|* -> Do you want to try again?[Y/n]: ");
		scanf("%s", &opt);
		if( strcmp(&opt, "y") || strcmp(&opt, "Y"))
			goto_perfil();
		else
			user_timeline();
	}
	
	while(TRUE){
		printf("|*                                                      *|\n");
		printf("|* -> What to do?                                       *|\n");
		printf("|* ->  Follow, Back, Logout, @ (Go to perfil)           *|\n");
		printf("|* -> Option: ");
		scanf("%s", &opt);
		lowercase(&opt);
		if( strcmp(&opt, "follow") == 0 ) {
			// funcion follow
			break;
		} else if ( strcmp(&opt, "back") == 0 ) {
			user_timeline(username);
			break;
		} else if ( strcmp(&opt, "logout") == 0 ) {
			logout();
			break;
		} else if ( strcmp(&opt, "@") == 0 ) {
			goto_perfil();
			break;
		}
	}
}

// Funcion que permite agregar un nuevo tweet a la lista de tweets del usuaro
// Loged.
void add_tweet(){
	// Sew debe leer por pantalla el mensaje, luego asegurarse de que se lean 
	// no mas de 280 chars, es decir usar la funcion cleanBuffer.
	// Agregar a la estructura de datos del usuario en lista tweets el mensaje.
	// Similarmente se debe agregar este tweets a los timeline de los followers
	// del usuario acutal.
	//
}

// Funcion que permite buscar en la estructura de datos al user y password
// tal que su cuenta sea correcta. Se retorna TRUE en caso afirmativo, de lo
// contrario FALSE. Con TRUE, FALSE definida por macros.
int user_validation(const char* str){

	// Hacer uso de la variable user_option para saber en que caso estamos
	// login o signup para realizar las respectivos retornos.
	//
	// En caso de TRUE y modo LOGIN almacenar en la variable global 
	// INFO_USER el apuntador
	// a dicha estructura de dato.

	return TRUE;
}

// Funcion que permite motrar el timeline del usuario una vez este haya
// ingresado con exito.
void user_timeline(){
	system("clear");
	char aux[18] = "@";
	strcat(aux, username);
	printf(".--------------------------------------------------------.\n");
	printf("|********************************************************|\n");
	printf("|*        -=-   Welcome %17s   -=-         *|\n", aux);
	printf("|*                                                      *|\n");
	printf("|* -> Tweets Timeline:                                  *|\n");
	printf("|*                                                      *|\n");
	
	print_messages(username);
	
	printf("|*                                                      *|\n");
	printf("|* -> WHAT'S HAPPENING?                                 *|\n");
	printf("|* ->  + (add tweet), @ (Go to perfil of), Logout: ");
	user_input();
}

// Funcion que permite mostrar por pantalla dependiendo el caso de login o 
// signup los tweets.
void print_messages(const char* str){
	if(strcmp(user_option, "login")==0){ // Imprimir TIMELINE del usuario actual.

	} else if (strcmp(user_option, "@")==0){ // imprimir TWEETS de otra persona (@)
		
	}
}

int main(){
	initial_interfaz();
	
	return EXIT_SUCCESS;
}
