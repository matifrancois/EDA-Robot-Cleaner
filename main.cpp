#include <iostream>
#include "prototipos.h"
#include "CmdLine.h"
#include "Simulation.h"
#include <stdio.h>
#include "grafic.h"
#include "graph.h"

using namespace std;

int main(int argC, char** argV) {
	user_t userData;
	
	//Inicializa cantidad de robots y modo en NULL.
	userData.robot_amount = NULL;
	userData.mode = NULL;
	
	//Se hace chequeo de par�metros pasados por l�nea de comando.
	int Input = parseCmdLine(argC, argV, validateInput, &userData);

	//Si no cumplen las condiciones, se muestra mensaje de error y se devuelve 1. Sale del programa.
	if ((Input != EXPECTEDPARAMS && (Input != (EXPECTEDPARAMS - 1))) || ((Input == (EXPECTEDPARAMS - 1) && (userData.mode != MODO2 || userData.robot_amount != NULL)))) {
		/*cout << "Data Input Error\n";
		return -1;*/
		cout << "Enter the following values to run the program\n";
		cout << "Number of rows:\n";
		cin >> userData.height;
		cout << "Number of columns:\n";
		cin >> userData.width;
		cout << "Number of robots\n";
		cin >> userData.robot_amount;
		cout << "Operating Mode (1 or 2)\n";
		cin >> userData.mode;
		while (userData.mode != 1 && userData.mode != 2)
		{
			cout << "Error, enter a right operating mode (1 or 2)\n";
			cin >> userData.mode;
		}
	}
	
	//Semilla para n�meros aleatorios.
	srand(time(NULL));
	unsigned int tickTemp;
	Sim* s;
	
	//Si se eligi� modo 1...
	if (userData.mode == MODO1) {	

		//Inicializaci�n de Allegro. Si hay error, muestra mensaje y devuelve -1. Sale del programa.
		if (!iniciar_allegro()) {
			cout << "Failed to initialize Allegro\n";
			return -1;
		}

		//Crea la simulaci�n y la inicializa con los valores de userData.
		s = createSimulation(userData.robot_amount, userData.width, userData.height, userData.mode);
		
		/*Si la pudo crear, lo simula y guarda el resultado en tickTemp.
		Libera memoria de la simulaci�n y muestra la cantidad de ticks que tom�. */
		if (s!=NULL){
			tickTemp = simulate(s, userData.mode);
			freeSimulation(s, userData.mode);
			cout << "\nIt took " << tickTemp << " tick(s).\n" << endl;
		}

		//Si no la puede crear, muestra mensaje de error, libera la variable y devuelve -1. Sale del programa.
		else{
			cout << "Failed to create simulation.\n";
			freeSimulation(s, userData.mode);
			return -1;
		}
	}

	//Si se eligi� modo 2...
	else{

		//Vector donde se guardar�n los promedios de cada iteraci�n.
		double timeTaken[MAX_ROBOTS] = { 0.0 };
		int m = 0, d;
		
		//Se hacen dos iteraciones de 1000 simulaciones (1 robot y 2 robots) para iniciar con dos valores a comparar.
		while (m < 2) {

			//SIM_CANT (1000 por consigna) repeticiones.
			for (d = 0; d < SIM_CANT; d++) {

				//Crea simulaci�n.
				s = createSimulation(m + 1, userData.width, userData.height, userData.mode);
				
				/*Si la pudo crear, la simula y guarda el resultado en tickTemp.
				Suma el valor en la posici�n correspondiente de timeTaken y libera la simulaci�n. */
				if (s != NULL) {
					tickTemp = simulate(s,userData.mode);
					timeTaken[m] += tickTemp;
					freeSimulation(s, userData.mode);
				}

				/*Si no pudo crear la simulaci�n, muestra mensaje de error, libera la memoria y devuelve -1.
				Sale del programa. */
				else {
					cout << "Failed to create simulation.\n";
					freeSimulation(s,userData.mode);
					return -1;
				}
			}
			/*Terminan las SIM_CANT simulaciones con m+1 robots. 
			Se divide el resultado por la cantidad para sacar promedio. */
			timeTaken[m] /= SIM_CANT;

			//Se muestra cu�ntos ticks tom� con m+1 robots y se incrementa contador.
			cout << m + 1 << " robots --- > " << timeTaken[m] << " tick(s)." << endl;
			m++;
		}

		/*Ahora se tienen dos datos para tener de input en la condici�n.

		Se hace un ciclo for que termina cuando el m�dulo de la diferencia entre las cantidades de ticks que
		//toman en promedio las simulaciones con m-2 y m-1 robots es menor a 0,1.

		Se repite el procedimiento anterior de creado de simulaci�n, simulado, chequeo de errores,
		relevado de datos y liberaciones de memoria en cada iteraci�n. */ 
		for (m = 2; abs((timeTaken[m - 2] - timeTaken[m - 1])) > MODE_2_LIM; m++) {
			for (d = 0; d < SIM_CANT; d++) {
				s = createSimulation(m + 1, userData.width, userData.height, userData.mode);
				if (s != NULL) {
					tickTemp = simulate(s,userData.mode);
					timeTaken[m] += tickTemp;
					freeSimulation(s, userData.mode);
				}
				else {
					freeSimulation(s, userData.mode);
					cout << "Failed to create simulation.\n";
					return -1;
				}
			}

			//Se va mostrando cu�ntos ticks toma con m+1 robots.
			timeTaken[m] /= SIM_CANT;
			cout << m + 1 << " robots --- > " << timeTaken[m] << " tick(s)." << endl;
		}
		//Cuando termina, muestra cu�ntos robots se necesitaron para cumplir la condici�n especificada.
		cout << "It took " << m << " robot(s)." << endl;

		/*Grafica los resultados con Allegro. Si no puede, muestra mensaje de error y devuelve -1. 
		Sale del programa. */
		if (!graph(timeTaken, m)) {
			cout << "Failed to initialize Allegro.\n";
			return -1;
		}
	}

	//Si sali� por v�as exitosas, se devuelve 0.
	return 0;
}