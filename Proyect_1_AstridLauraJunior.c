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

// Funcion que limpiar el Buffer del teclado extrayendo todos lso caracteres 
// sobrantes hasta conseguir el '\n' que representa el presionar ENTER.
void cleanBuffer(const char* str){
	int toint = (int)(str[strlen(str)-1]);
	if(toint != 10 &&  toint != 0) 
		while(getchar() != '\n');
}

void cleanBufferV2(){
	int c;
	do{
		c = getchar();
	}while( c != EOF && c != '\n');
}

void add_node(char* u_name){
	list_users *newUser = (list_users*)malloc(sizeof(list_users));	
	int k_user = hash_function(u_name);
	int k_pass = hash_function(password);
	newUser->nodo.password_h = k_pass;
	strncpy(newUser->nodo.user, u_name, 17);
	newUser->next = NULL;

	newUser->nodo.following = NULL;
	newUser->nodo.followers = NULL;
	newUser->nodo.tweets = NULL;
	newUser->nodo.timeline = NULL;

	if( HashTable[k_user]->id != 0) {
		list_users *temp = HashTable[k_user];
		while( temp->next != NULL)
			temp = temp->next;
		newUser->id = temp->id + 1;
		temp->next = newUser;
	} else {
		newUser->id = 1;
		HashTable[k_user] = newUser;
	}
}

int search_node(char* str){
	int k_user = hash_function(str);

	if( HashTable[k_user]->id != 0 ){
		list_users *temp = HashTable[k_user];
		while( temp != NULL ){
			if(strcmp(temp->nodo.user, str )==0 ){
				if(strcmp(str, username) == 0)
					INFO_USER = &temp->nodo;
				else
					INFO_FUSER = &temp->nodo;
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
	while(TRUE){
		system("clear");
		printf("|* .'````````````````````````````````````````````````'. *|\n");
		printf("|*.^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^.*|\n");
		printf("|*'^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^````^^^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^`'^^^^^^^^^^^^^^^^`'.       .``''.`^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^  .'^^^^^^^^^^^^^'              .''`^^^^^^^'*|\n");
		printf("|*'^^^^^^^^`     .`^^^^^^^^^`                .`^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^.       ..'`^^^^.               `^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^.             .               .^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^` ..                            .^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^'                              `^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^`.                           .^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^`'.                        .^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^^.                        .^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^^^`.                     `^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^^^^^^`.                '^^^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^````''.                .`^^^^^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^`'..               .'`^^^^^^^^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^^^``''''''''``^^^^^^^^^^^^^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^'*|\n");
		printf("|*'^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^'*|\n");
		printf("|* '``^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^``' *|\n");
		printf(".--------------------------------------------------------.\n");
		printf("|********************************************************|\n");
		printf("|*                  -=-   TWITTER   -=-                 *|\n");
		printf("|*                                                      *|\n");
		printf("|* -> DON'T MISS WHAT'S HAPPENING!                      *|\n");
		printf("|* ->  Login, SignUp or Leave: ");

		while (TRUE){
			fflush(stdin);
			scanf("%s", user_option);
			cleanBufferV2();
			lowercase(user_option);
			if(strcmp(user_option, "login")==0){
				if(name_pass()){
					user_timeline();
					break;
				}
				break;
			} else if(strcmp(user_option, "signup")==0) {
				signup();
				Goto_init();
				break;
			}else if(strcmp(user_option, "leave")==0) {
				leave();
				break;
			} else {
				printf("|* -> Error! Available Options is:                      *|\n"); 
				printf("|* -> Login, Signup, Leave.                             *|\n");
				printf("|* -> Try again: ");
			}

		}
		if(strcmp(user_option, "leave") == 0){
			break;
		}
	}
}

// Funcion encargada en solicitar por pantalla el username y password al 
// usuario por standardInput.
int name_pass(){
	while(TRUE){
		fflush(stdin);
		printf("|* -> USERNAME(Min. 8 - Max. 16 chars): "); scanf("%s", username);
		cleanBufferV2();
		if(valid_len(username)) 
			break;
	}
	while(TRUE){
		fflush(stdin);
		printf("|* -> PASSWORD(Min. 8 - Max. 16 Chars): "); scanf("%s", password);
		cleanBufferV2();
		if(valid_len(password)) 
			break;
	}
	lowercase(username);
	if(!user_validation(username)){
		Goto_init();
		return FALSE;
	}

	return TRUE;
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

// Funcion que permite concluir algun proceso, como registrarse y Deslogear
// al usuario.
void Goto_init(){
	printf("|* -> Press any key to continue...");

	// Limpiamos y detenemos output.
	fflush(stdout);
	system("bash -c \"read -sn 1\"");	
	
	return;
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
	return;
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
	char user_temp[17];
	char opt[10];
	while(TRUE){
		
		printf("|*                                                      *|\n");
		printf("|* -> Enter user: @"); scanf("%s", user_temp);
		cleanBufferV2();

		if(user_validation(user_temp)){
			if( INFO_FUSER->tweets ){
				printf("GOTOPER CHECK 1\n");
				print_messages(user_temp);
			}else{
				printf("|*                                                      *|\n");
				printf("|* -> This user hasn't tweeted yet.                     *|\n");
			}
			break;
		} else{
			printf("|* -> Error: User not found.                            *|\n");
			printf("|* -> Do you want to try again?[Y/n]: ");
			scanf("%s", opt);
			cleanBufferV2();
			lowercase(opt);
			if( opt[0] == 'n')
				return;	
		}
	}
	
	while(TRUE){
		printf("|*                                                      *|\n");
		printf("|* -> What do you want to do?                           *|\n");
		printf("|* -> Follow, GoBack, Logout, @ (Go to another profile) *|\n");
		printf("|* -> Option: ");
		scanf("%s", user_option);
		cleanBufferV2();
		lowercase(user_option);
		if( strcmp(user_option, "follow") == 0 ) {
			follow_user(user_temp);	
		} else if ( strcmp(user_option, "goback") == 0 ) {
			user_timeline();
			return;
		} else if ( strcmp(user_option, "logout") == 0 ) {
			logout();
			return;
		} else if ( strcmp(user_option, "@") == 0 ) {
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
	
	//char n_t[SLOTS_TWEET];
	fgets(newTweet->tweets.message, SLOTS_TWEET, stdin);

	if(strlen(newTweet->tweets.message) == SLOTS_TWEET)
		cleanBuffer(newTweet->tweets.message);
	
	//strncpy(newTweet->tweets.message, n_t, SLOTS_TWEET);

	time_t t_nt;
	time(&t_nt);

	strncpy(newTweet->tweets.user, INFO_USER->user, MAX_INPUT);
	newTweet->tweets.time = localtime(&t_nt);
	newTweet->next = NULL;

	if( INFO_USER->tweets ){
		list_tweets *list_aux = INFO_USER->tweets;
	
		while(list_aux->next != NULL)
			list_aux = list_aux->next;
		newTweet->id = list_aux->id + 1;
		list_aux->next = newTweet;
	} else { 
		newTweet->id = 1;
		INFO_USER->tweets = newTweet;
		printf("CHECK MESS 1: %s\n\n", INFO_USER->tweets->tweets.message);
	}
	
	// Se busca por todos los usuarios en la lista TIMELINE
	if( INFO_USER->followers ){
		list_users *p_follows = INFO_USER->followers;

		while( p_follows != NULL) {

			list_tweets *l_temp = p_follows->nodo.timeline;
			if(l_temp != NULL){
				while( l_temp->next != NULL)
					l_temp = l_temp->next;
			
				newTweet->id = l_temp->id + 1;
				l_temp->next = newTweet;
			} else {
				newTweet->id = 1;
				p_follows->nodo.timeline = newTweet;
				printf("CHECK MESS 2: %s\n", INFO_USER->followers->nodo.timeline->tweets.message);
			}

			p_follows = p_follows->next;
		}
	}

	printf("|*                                                       *|\n");
	printf("|* -> Tweet add success!                                 *|\n");
	printf("|*                                                       *|\n");
	
	printf("|* -> Press any key to continue...");
	fflush(stdout);
	system("bash -c \"read -sn 1\"");	
}

// Funcion que permite buscar en la estructura de datos al user y password
// tal que su cuenta sea correcta. Se retorna TRUE en caso afirmativo, de lo
// contrario FALSE. Con TRUE, FALSE definida por macros.
int user_validation( char* str){
	lowercase(user_option);
	// Si el usuario se encontro y estamos en modo login.
	if( search_node(str) && strcmp(user_option, "login")==0 ){
		int t_key = hash_function(password);
		// Si si coinciden las password.
		if(INFO_USER->password_h == t_key)
			return TRUE;
		// Sino coinciden las password
		else {
			printf("|* -> Error: Incorrect user or password.                 *|\n");
			return FALSE;
		}
	// Sino encontramos el usuario y estamos en modo login.
	} else if ( !search_node(str) && (strcmp(user_option, "login")==0)){
			printf("|* -> Error: Incorrect user or password.                 *|\n");
			return FALSE;
	// Sino encontramos el usuario y estamos en modo signup.
	} else if ( !search_node(str) && (strcmp(user_option, "signup")==0)){
			return TRUE;
	// Si encontramos al usuario y entamos en modo signup.
	} else if ( search_node(str) && (strcmp(user_option, "signup")==0)){
			printf("|* -> Error: User already exists.*|\n");
			return FALSE;
	// Cuando no encontramos al usuario a seguir.
	} else if ( !search_node(str) && user_option[0] == '@'){
			return FALSE;
	// Cuando encontramos al usuario y estamos en modo seguir..
	} else if ( search_node(str) && user_option[0] == '@'){
			return TRUE;
	} 
}

// Funcion que permite motrar el timeline del usuario una vez este haya
// ingresado con exito.
void user_timeline(){
	while (TRUE){
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

		while(TRUE){
			fflush(stdin);
			scanf("%s", user_option);
			cleanBufferV2();
			lowercase(user_option);

			if(strcmp(user_option, "logout") == 0 || user_option[0] == '+' || user_option[0] == '@' ){
				break;
			}else{
				printf("|* -> Error! Available Options is:                      *|\n"); 
				printf("|* ->  +, @, Logout.                                    *|\n");
				printf("|* -> Try again: ");
			}
		}

		if(strcmp(user_option, "logout") == 0){
			logout();
			break;
		}else if( user_option[0] == '+' ){
			add_tweet();
		} else if( user_option[0] == '@' ){
			goto_perfil();
			break;
		}
	}
	return;
}

// Funcion que permite mostrar por pantalla dependiendo el caso de login o 
// signup los tweets.
void print_messages(char* str){
	if(strcmp(user_option, "login")==0){ // Imprimir TIMELINE del usuario actual.;
		print_tweet(INFO_USER->timeline);

	}else if (user_option[0] == '@' ){ // imprimir TWEETS de otra persona (@)
		//int k = hash_function(str);
		//list_users *usertemp = HashTable[k];
		printf("CHECK 1\n");
		//if (strcmp(usertemp->nodo.user, str) != 0){
		//	while( strcmp(usertemp->nodo.user, str) != 0)
		//		usertemp = usertemp->next;
		//}
		print_tweet(INFO_FUSER->tweets);	
	}
}

void print_tweet(list_tweets *temp){

	while(temp != NULL){
		char aux[18] = "@";
		char format_time[25];
		strftime(format_time, 25, "%X%p - %x", temp->tweets.time );
		strcat(aux, temp->tweets.user);

		printf("|*------------------------------------------------------*|\n");
		printf("|*  %17s        %25s  *|\n",aux, format_time);
		
		char usertweet[SLOTS_TWEET];
		strncpy(usertweet, temp->tweets.message, SLOTS_TWEET);
		while (strlen(usertweet) > 50 ){  
			printf("|*  %.50s  *|\n",usertweet);
			memmove(usertweet, usertweet+OFFSET, strlen(usertweet)+1-OFFSET);
		}
		printf("|*  %.50s  *|\n",usertweet);
		temp = temp->next;
	}
}

void follow_user(char *str){
		
	if(strcmp(str, username) == 0){
		printf("|*                                                      *|\n");
		printf("|* -> You can't follow you.                             *|\n");
		printf("|*                                                      *|\n");
		return;
	}
	/*
	int h_usert = hash_function(str);
	
	list_users *new_fuser = HashTable[h_usert];
	while(new_fuser->id != 0){
		if( strcmp(new_fuser->nodo.user, str)==0 )
			break;
		new_fuser = new_fuser->next;
	}
	*/
	
	list_users *new_follow = (list_users*)malloc(sizeof(list_users));
	
	// Agregar a la lista de SIGUIENDOS del usuario principal.
	if(INFO_USER->following != NULL) {
		list_users *user_aux = INFO_USER->following;
		while(user_aux->next != NULL)
			user_aux = user_aux->next;
		new_follow->nodo = *INFO_FUSER;
		user_aux->next = new_follow;
	}else {
		new_follow->nodo = *INFO_FUSER;
		INFO_USER->following = new_follow;
	}
	printf("SIGUIENDOS DEL MAIN: %s\n", INFO_USER->following->nodo.user);

	// Agregar a la lista de SEGUIDORES del usuario a seguir.
	if(INFO_FUSER->followers != NULL) {
		list_users *user_aux = INFO_FUSER->followers;
		while(user_aux->next != NULL)
			user_aux = user_aux->next;
		new_follow->nodo = *INFO_USER;
		user_aux->next = new_follow;
	} else {
		new_follow->nodo = *INFO_USER;
		INFO_FUSER->followers = new_follow;	
	}

	printf("SIGUIDORES DE USER A SEGUIR: %s\n", INFO_FUSER->followers->nodo.user);

	printf("|*                                                      *|\n");
	printf("|* -> Following success!                                *|\n");
	printf("|*                                                      *|\n");
}

int main(){
	for(int k = 0; k < SLOTS_HASH; k++){
		HashTable[k] = &list_users_df;
		HashTable[k]->nodo = user_data_df;
	}
	INFO_USER = &user_data_df;
	INFO_FUSER = &user_data_df;

	initial_interfaz();
	
	return EXIT_SUCCESS;
}
