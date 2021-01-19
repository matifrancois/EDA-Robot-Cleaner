#include <stdio.h>
#include <iostream>
#include "Floor.h"


//Crea un array de tipo Baldosa de tama�o width*height.
Baldosa* createFloor(int width, int height) {	
	
	//Aloca puntero ret a array de Baldosa
	Baldosa* ret = new (std::nothrow) Baldosa[width * height];	
	if (ret) {
		//Pone todas las baldosas en SUCIO.
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				getCurrentBaldosa(ret,i,j,width,height)->State = SUCIO;		
			}
		}
	}
	return ret;		//Devuelve el array creado.
}

//Libera la memoria alocada a array de Baldosa.
void freeFloor(Baldosa* p) {	
	if (p) {
		delete [] p;
		p = nullptr;
	}
}

//Devuelve un puntero a la baldosa referenciada.
Baldosa * getCurrentBaldosa(Baldosa* piso, unsigned int fil, unsigned int col, unsigned int width, unsigned int height) {
	return piso + fil * width + col;		
}

//Devuelve la posici�n de la pr�xima baldosa a la que deber�a ir un robot pasado como par�metro.
Posicion getNextBaldosa(Robot* robot) {		
	Posicion newPosition;
	newPosition.x= cos(-robot->angle) + robot->x;
	newPosition.y = sin(-robot->angle) + robot->y;

	return newPosition;
}

//Chequea si todas las baldosas est�n en LIMPIO.
bool isFloorClean(Baldosa* piso, int width, int height) {	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (!getCurrentBaldosa(piso,i,j,width,height)->State)
				return false;
		}
	}
	return true;
}