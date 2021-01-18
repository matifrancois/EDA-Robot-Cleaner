#include <stdio.h>
#include "Floor.h"
#include "Robot.h"
#include <iostream>
#include <math.h>
#include "grafic.h"
#define CORRECTOR 0.000001

//Cambia posici�n y �ngulo del robot.
void moveRobot(Robot* r, Baldosa* p, unsigned int width, unsigned int height) {		

	//Pide la baldosa a la que deber�a moverse el robot.
	Posicion nextBaldosa = getNextBaldosa(r);		

	//Mientras se pase de los l�mites de la pantalla...
	while (nextBaldosa.x <= 0 || nextBaldosa.x >= width || nextBaldosa.y <= 0 || nextBaldosa.y >= height) {

		//Genera un nuevo �ngulo.
		(*r).angle = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * ANG_MAX);
		
		//Pide la nueva baldosa
		nextBaldosa = getNextBaldosa(r);
	}
	/*Cuando encuentra una opci�n v�lida, pasa la nueva posici�n del robot a los miembros X e Y 
	de la esctructura Robot del robot pasado por par�metro. */
	r->x = nextBaldosa.x;
	r->y = nextBaldosa.y;

	//Cambia a LIMPIO el estado de la nueva baldosa.
	getCurrentBaldosa(p, (int)floor(nextBaldosa.y), (int)floor(nextBaldosa.x),width,height)->State = LIMPIO;
}

//Crea un puntero a array de esctructura Robot con los miembros ya inicializados.
Robot* createRobots(Baldosa*p, int count, unsigned int width, unsigned int height, int mode) {
	int i;

	//Asigna memoria.
	Robot* robs = new (std::nothrow)Robot[count];

	//Genera n�meros aleatorios (dentro de sus respectivos par�metros) para X, Y y �ngulo.
	if (robs) {
		for (i = 0; i < count; i++) {
			robs[i].angle = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * ANG_MAX);
			robs[i].x = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (width-CORRECTOR));
			robs[i].y = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (height-CORRECTOR));
			
			//Cambia estado de la baldosa a LIMPIO.
			getCurrentBaldosa(p, (int)floor(robs[i].y), (int)floor(robs[i].x), width, height)->State = LIMPIO;
			
			//Si est� en modo 1, pinta la casilla de blanco.
			if (mode==MODO1)
				paintBox(robs[i].x, robs[i].y, width, height,al_map_rgb(BL,BL,BL));
		}
	}

	//Devuelve el puntero.
	return robs;	
}

//Libera memoria ocupada por puntero a estructura Robot.
void freeRobots(Robot* robs) {	
	if (robs) {
		delete [] robs;
		robs = nullptr;
	}
}