#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <ctype.h>

// Macros para True and False.
#define TRUE (0==0)
#define FALSE !TRUE

// Hass length
#define SLOTS_HASH 97

struct list_user;
typedef struct list_user list_user;

struct user_data;
typedef struct user_data user_data;

struct list_timeline;
typedef struct list_timeline list_timeline;

struct list_tweets;
typedef struct list_tweets list_tweets;

// Definicion, inicializacion y estructuras de datos.
char user_option[10];			// Para las  opciones que toma el user.(login, signup, etc)
char username[17]; 				// Para username del usuario, MAX 16 Chars.
char password[17]; 				// Para password del usuario, MAX 16 chars/digitos.
user_data *INFO_USER; 		// Informacion clobal del usuario que esta logeado.

struct list_tweets{
	char tweet;
	struct list_tweets *next;
};

struct user_data{
	char user;
	int password_h;
	list_tweets *tweets;
 	list_user *following; // Los que sigo.
	list_user *followers; // Los que me siguen.
	list_timeline *timeline;
};

struct list_user{
	user_data nodo;
	list_user *next;
};

struct list_timeline{
	char user;
	struct tm time;
	char message;
};

/**/
