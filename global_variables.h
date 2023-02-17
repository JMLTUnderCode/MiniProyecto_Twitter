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
#define MAX_INPUT 17 			// Numerom aximo de caracteres para el username/password

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

/***************************************************************/
// Definicion de HashTable y funciones para la misma.
user_data *HashTable[SLOTS_HASH];

void add_node(); 								// Agrega un nodo de tipo USER_DATA a la tabla.
void search_node(const char*); 	// Busca un nodo de tipo USER_DATA en la tabla.

/***************************************************************/
// ESTRUCTURAS TIPO NODO INFORMATIVO.
struct info_tweets{
	char user[MAX_INPUT];
	tm_t time;
	char message[SLOTS_TWEET];
};

struct user_data{
	char user[MAX_INPUT];
	int password_h;
	info_tweets *tweets;
 	list_users *following; 
	list_users *followers;
	info_tweets *timeline;
};


/**************************************************************t*
// LISTAS ENLAZADAS
struct list_users{
	user_data nodo;
	list_users *next;
};

struct list_tweets{
	info_tweets tweets;
	list_tweets *next;
};



/***************************************************************/
