#pragma once
typedef int (*pCallback) (char*, char*, void*);


/*parseCmdLine: 
1. Recibe:
	- (int) argC: Cantidad de par�metros, keys y opciones.
	- (char*) argV: Vector con los par�metros, keys y opciones.
	- (*pCallback) parseCallback: Funci�n de callback a la cual referirse al encontrar un
	par�metro, key u opci�n.
	- (void*) userData: Vector que le transferir� a parseCallback para guardar los datos.
2. Devuelve:
	- (int) 0 si se encontraron errores de forma o errores l�gicos (detectados por pCallback).
	- (int) Suma de par�metros y opciones. */

int parseCmdLine(int argC, char* argV[], pCallback parseCallback, void* userData);
/*validateInput:
1. Recibe:
	- (char*) key = Clave de la opci�n.
	- (char*) value = Valor de la opci�n.
	- (void*) userData = Donde se guardar�n los valores recibidos en caso de ser l�gicamente v�lidos.

2. Devuelve:
	- (int) 0 si lo ingresado no fue v�lido.
	- (int) 1 si lo ingresado fue v�lido.

Opciones v�lidas: 
	- key = h, 0<(int)value<MAX_ALTO
	- key = w, 0<(int)value<MAX_ANCHO
	- key = r, 0<(int)value<MAX_ROBOTS
	- key = m, (m==1 || m==2) */

int validateInput (char* key, char* value , void* userData);

/*checkModeValue:
1. Recibe:
	- (int) value: Valor a chequear.
2. Devuelve:
	- (bool) true: Si el valor proporcionado es v�lido como modo.
	- (bool) false: Si el valor proporcionado no es v�lido como modo.

Se fija si el valor pasado es uno de los modos v�lidos (1 � 2). */

bool checkModeValue(int value);

/*checkKey:
1. Recibe:
	- (char*) key: Valor a chequear si es una de las claves v�lidas.
2. Devuelve:
	- (int) 0 si la clave no es v�lida.
	- (int) 1 si la clave es "h".
	- (int) 2 si la clave es "w".
	- (int) 3 si la clave es "r".
	- (int) 4 si la clave es "m".  */

int checkKey(char* key);

void lowerstring(char* s);