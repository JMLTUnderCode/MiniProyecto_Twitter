#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <ctype.h>

#define TRUE (0==0)  			// Macro de TRUE del lenguaje.
#define FALSE !TRUE 			// Macro de FALSE del lenguaje.
#define SLOTS_HASH 97 		// Longitud constante de la tabla de hash.
#define SLOTS_TWEET 281 	// Numero maximo de caracteres para un tweet.

struct user_data; 				// Nodo informativo de un usuario.
struct info_tweets; 			// Nodo informativo de un tweet.
struct list_users; 				// Lista enlazada que usa nodo de tipo USER_DATA.
struct list_tweets; 			// Lista enlazada que usa nodo de tipo INFO_TWEETS.

// Definiciones de tipo de datos.
typedef struct tm tm_t;
typedef struct user_data user_data;
typedef struct info_tweets info_tweets;
typedef struct list_users list_users;
typedef struct list_tweets list_tweets;

// Definicion, inicializacion y estructuras de datos.
char user_option[10];			// Para las  opciones que toma el user.(login, signup, etc)
char username[17]; 				// Para username del usuario, MAX 16 Chars.
char password[17]; 				// Para password del usuario, MAX 16 chars/digitos.
user_data *INFO_USER; 		// Informacion clobal del usuario que esta logeado.

struct list_timeline{
	char user;
	tm_t time;
	char message[SLOTS_TWEET];
};

struct user_data{
	char user;
	int password_h;
	list_tweets *tweets;
 	list_users *following; 
	list_users *followers;
	info_tweets *timeline;
};

struct list_users{
	user_data nodo;
	list_user *next;
};

struct list_tweets{
	info_tweets tweets;
	struct list_tweets *next;
};

/**/
