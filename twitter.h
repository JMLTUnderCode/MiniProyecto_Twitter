#include "global_variables.h"

// Funcion que muestra la interfaz base del programa. Nombre de la App simulada,
// prompt base y solicitud de datos.
void initial_interfaz();

// Funcion que limpiar el Buffer del teclado extrayendo todos lso caracteres 
// sobrantes hasta conseguir el '\n' que representa el presionar ENTER.
void cleanBuffer(const char*);

// 
void cleanBufferV2();

// Funcion encargada en solicitar por pantalla el username y password al usuario
// por standardInput.
int name_pass();

// Funcion que se encarga de check el userinput del username y password, dado
// que se tiene un maximo de 16 caracteres por campo.
int valid_len(const char*);

// Funcion que se encarga de gestionar la informacion dada por el usuario. 
// Permite en funcion de la opcion dada ir a su respectiva funcion.
void user_input(int);

// Funcion que permite concluir algun proceso, como registrarse y Deslogear
// al usuario.
void Goto_init();

// En caso de el usuario ingresar "signup" se deben solicitar los prompt de 
// "username" y "password" para ser guardados en la tabla de hash donde se 
// almacena la DataUsers.
void signup();

// Funcion que permite Deslogear a un usuario de Twitter y llevarlo a la interfaz inicial
// de Login. 
void logout();

// En caso de el usuario ingresar "leave" se debe "cerrar"/culminar
// el programa indicando un mensaje final.
void leave();

// Funcion que permite mostrar por pantalla el perfil de un usuario.
void goto_perfil();

// Funcion que permite agregar un nuevo tweet a la lista de tweets del usuaro
// Loged.
void add_tweet();

// Funcion que permite buscar en la estructura de datos al user y password
// tal que su cuenta sea correcta. Se retorna TRUE en caso afirmativo, de lo
// contrario FALSE. Con TRUE, FALSE definida por macros.
int user_validation(char*);

// Funcion que permite mostrar el timeline del usuario una vez que este haya
// ingresado con exito.
void user_timeline();

// Funcion que se encarga de ingresar a la lista timeline del usuario dado por
// argumento o en otro caso la lista de twwets del usuario.
void print_messages(char*);

// Funcion para pasar una cadena a solo chars de tipo minuscula.
void lowercase(char*);

// Funcion para el calculo del key de un string(username).
int hash_function(char*);

// Funcion que muestra por terminal la lista de tweets.
void print_tweet(struct list_tweets*);

// Funcion que se encarga de seguir y verificar el seguimiento entre usuarios.
void follow_user(char*);

// Funcion que muestra por terminal el logo de twitter.
void logo_twitter();

/**/







