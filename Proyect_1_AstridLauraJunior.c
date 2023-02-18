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

int hash_function(char *key){
	int ln = strlen(key);
	int accum = 0;
	for(int i=0; i<ln; i++){
		accum += key[i];
	}
	return accum % SLOTS_HASH;
}

void add_node(char* u_name){
	list_users *newUser = (list_users*)malloc(sizeof(list_users));	
	int k_user = hash_function(u_name);
	int k_pass = hash_function(password);
	newUser->nodo.password_h = k_pass;
	strncpy(newUser->nodo.user, u_name, 17);
	newUser->next = NULL;

	if( HashTable[k_user]->id != 0) {
		list_users *temp = HashTable[k_user];
		while( temp->next != NULL)
			temp = temp->next;
		temp->next = newUser;

	} else {
		newUser->id = 1;
		HashTable[k_user] = newUser;
	}

	HashTable[k_user]->nodo.tweets = &list_tweets_df;
	HashTable[k_user]->nodo.timeline = &list_tweets_df;
}

int search_node(char* str){
	int k_user = hash_function(str);

	if( HashTable[k_user]->id != 0 ){
		list_users *temp = HashTable[k_user];
		while( temp != NULL ){
			if(strcmp(temp->nodo.user, str )==0 ){
				INFO_USER = &temp->nodo;
				return TRUE;
			} else {
				temp = temp->next;
			}
		}
		return FALSE;

	} else {
		return FALSE;
	}
}

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

	user_input(1);
	return;
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
	lowercase(username);
	if(!user_validation(username)){
		Goto_init();
		return;
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
void user_input(int type){
	fflush(stdin);
	scanf("%s", user_option);
	lowercase(user_option);
	if(type == 1) {
		if(strcmp(user_option, "login")==0){
			name_pass();
			user_timeline();
			return;
		} else if(strcmp(user_option, "signup")==0) {
			signup();
			Goto_init();
			return;
		}else if(strcmp(user_option, "leave")==0) {
			leave();
			return;
		} else {
			printf("|* -> Error! Available Options is:                      *|\n"); 
			printf("|* -> Login, Signup, Leave.                             *|\n");
			printf("|* -> Try again: ");
			user_input(1);
		}
	} else {
		if(strcmp(user_option, "logout")==0){
			logout();
			return;
		}
		else if( user_option[0] == '+' ){
			add_tweet();
			user_timeline();
			return;
		} else if( user_option[0] == '@' ){
			goto_perfil();
			return;
		} else {
			printf("|* -> Error! Available Options is:                      *|\n"); 
			printf("|* ->  +, @, Logout.                                    *|\n");
			printf("|* -> Try again: ");
			user_input(2);
		}
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
	add_node(username);

	printf("|*                                                      *|\n");
	printf("|* -> Registration Completed!                           *|\n");	
	printf("|*                                                      *|\n");
	printf("|* -> Your data is:                                     *|\n");
	printf("|*    ID: %18s                            *|\n", username);
	printf("|*    Pass: %16s                            *|\n", password);
	printf("|* -> Do not forget!                                    *|\n");
	printf("|*                                                      *|\n");
	
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
	system("exit");
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
		printf("|* -> Error: User not found.                            *|\n");
		printf("|* -> Do you want to try again?[Y/n]: ");
		scanf("%s", &opt);
		if( strcmp(&opt, "y")==0 || strcmp(&opt, "Y")==0){
			goto_perfil();
			return;
		}else{
			user_timeline();
			return;
		}
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
			return;
		} else if ( strcmp(&opt, "back") == 0 ) {
			user_timeline();
			return;
		} else if ( strcmp(&opt, "logout") == 0 ) {
			logout();
			return;
		} else if ( strcmp(&opt, "@") == 0 ) {
			goto_perfil();
			return;
		}
	}
}

// Funcion que permite agregar un nuevo tweet a la lista de tweets del usuaro
// Loged.
void add_tweet(){
	// Agregar tweet a la lista de tweets propios del usuario logeado.
	list_tweets *newTweet = (list_tweets*)malloc(sizeof(list_tweets));
	printf("|*                                                      *|\n");
	printf("|* -> Enter tweet(Max. 280 chars): ");
	
	char n_t[SLOTS_TWEET];
	scanf("%s", n_t);

	if(strlen(n_t) == SLOTS_TWEET)
		cleanBuffer(n_t);
	
	strncpy(newTweet->tweets.message, n_t, SLOTS_TWEET);

	time_t t_nt;
	time(&t_nt);
	
	strncpy(newTweet->tweets.user, INFO_USER->user, MAX_INPUT);
	newTweet->tweets.time = localtime(&t_nt);

	list_tweets *list_aux = INFO_USER->tweets;

	while(list_aux->next != NULL)
		list_aux = list_aux->next;
	
	list_aux->next = newTweet;
	
	// Agregar tweet a los timelines de los followers.
	list_users *p_follows = INFO_USER->followers;
	
	printf("addtweet check 2\n");
	// Se busca por todos los usuarios en la lista TINELINE
	if( p_follows != NULL){
		while( p_follows->id != 0) {
			printf("addtweet check 3\n");
			list_tweets *l_temp = p_follows->nodo.timeline;
			while( l_temp->next != NULL )
				l_temp = l_temp->next;
		
			l_temp->next = newTweet;
		
			p_follows = p_follows->next;
		}
	}
	printf("addtweet check final\n");
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
int user_validation( char* str){
	lowercase(user_option);
	printf("CHECK VALID 1\n");	
	// Si el usuario se encontro y estamos en modo login.
	if( search_node(str) && strcmp(user_option, "login")==0 ){
		printf("CHECK VALID 2\n");	
		int t_key = hash_function(password);
		// Si si coinciden las password.
		if(INFO_USER->password_h == t_key)
			return TRUE;
		// Sino coinciden las password
		else {
			printf("incorrect 1\n");
			printf("|* -> Error: Incorrect user or password.                 *|\n");
			return FALSE;
		}
	// Sino encontramos el usuario y estamos en modo login.
	} else if ( !search_node(str) && (strcmp(user_option, "login")==0)){
			printf("incorrect 2\n");
			printf("|* -> Error: Incorrect user or password.                 *|\n");
			return FALSE;
	// Sino encontramos el usuario y estamos en modo signup.
	} else if ( !search_node(str) && (strcmp(user_option, "signup")==0)){
			return TRUE;
	// Si encontramos al usuario y entamos en modo signup.
	} else if ( search_node(str) && (strcmp(user_option, "signup")==0)){
			printf("|* -> Error: User already exists.*|\n");
			return FALSE;
	}

	// Hacer uso de la variable user_option para saber en que caso estamos
	// login o signup para realizar las respectivos retornos.
	//
	// En caso de TRUE y modo LOGIN almacenar en la variable global 
	// INFO_USER el apuntador
	// a dicha estructura de dato.
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
	user_input(2);
}

// Funcion que permite mostrar por pantalla dependiendo el caso de login o 
// signup los tweets.
void print_messages(const char* str){
	if(strcmp(user_option, "login")==0){ // Imprimir TIMELINE del usuario actual.

	} else if (strcmp(user_option, "@")==0){ // imprimir TWEETS de otra persona (@)
		
	}
}
int main(){
	for(int k = 0; k < SLOTS_HASH; k++){
		HashTable[k] = &list_users_df;
		HashTable[k]->nodo = user_data_df;
	}

	initial_interfaz();
	
	return EXIT_SUCCESS;
}
