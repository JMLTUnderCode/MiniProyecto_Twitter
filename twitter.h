#include "global_variables.h"

// Funcion que limpiar el Buffer del teclado extrayendo todos lso caracteres 
// sobrantes hasta conseguir el '\n' que representa el presionar ENTER.
void cleanBuffer(const char*);

// Funcion encargada en solicitar por pantalla el username y password al usuario
// por standardInput.
void name_pass();

// Funcion que se encarga de gestionar la informacion dada por el usuario. 
// Permite en funcion de la opcion dada ir a su respectiva funcion.
void user_input();

// Funcion que muestra la interfaz base del programa. Nombre de la App simulada,
// prompt base y solicitud de datos.
void initial_interfaz();

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

// Funcion que permite mostrar por pantalla el perfil de un usuario.
void goto_perfil();

// Funcion que permite agregar un nuevo tweet a la lista de tweets del usuaro
// Loged.
void add_tweet();

// En caso de el usuario ingresar "leave" se debe "cerrar"/culminar
// el programa indicando un mensaje final.
void leave();

