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

// Definicion, inicializacion y estructuras de datos.
char user_option[10];			// Para las  opciones que toma el user.(login, signup, etc)
char username[17]; 				// Para username del usuario, MAX 16 Chars.
char password[17]; 				// Para password del usuario, MAX 16 chars/digitos.

struct list_user;
struct user_data;
struct user_timeline;
struct list_tweets;

struct list_tweets{
	char tweet;
	struct list_tweets *next;
};

struct user_data{
	char user;
	int password_h;
	struct list_tweets *tweets;
 	struct list_user *following; // Los que sigo.
	struct list_user *followers; // Los que me siguen.
	struct user_timeline *timeline;
};

struct lista_user{
	struct user_data nodo;
	struct lista_user *next;
};

struct user_timeline{
	char user;
	struct tm time;
	char message;
};

struct user_data *INFO_USER;


/**/
