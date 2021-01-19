#include "cmdline.h"
#include "prototipos.h"
#include <string>

int validModeValues[] = { MODO1, MODO2 };           //Keys v�lidas.
char validKeys[][KEYLENGHT] = { "h","w","r","m" };  //Values v�lidos.
int parseCmdLine(int argC, char* argV[], pCallback parseCallback, void* userData){
    int i, res = 0;
    for (i = 1; i < argC; i++){  //Desde i=1 (salteando nombre del ejecutable) chequea los valores recibidos.
        if (*argV[i] == '-'){    // Si comienza con '-', se encontr� una opci�n.
            if (!*(argV[i] + 1) || (i + 1) == argC || !parseCallback(argV[i]+1, argV[i + 1], userData)){ // Detecta errores de forma o l�gicos.
                res = ERROR;   // El resultado pasa a ser -1, porque hubo un error.
                break;      
            }
            i++;            // Si estuvo todo correcto, se saltea el siguiente valor, porque es el value de la opci�n.
            res++;          // Suma uno a la cantidad de opciones+par�metros detectados.
        }
        else{                // Si se detecta un par�metro.
            if (!parseCallback(NULL, argV[i], userData)){  // Si hay error l�gico.
                res = ERROR;       // El resultado pasa a ser -1, porque hubo un error.
                break;
            }
            res++;          // Si estuvo todo correcto, suma uno a la cantidad de opciones+par�metros detectados.
        }
    }
    return res;         // Devuelve el resultado de la suma.
}

int validateInput(char* key, char* value, void* userData){      //Callback. Chequea si el input es correcto.
    int res = 0;
    user_t* userDataPtr = (user_t*)userData;            //Casteo de userData en puntero a user_t.

    if (key != NULL) {                  //Si hay key...
        lowerstring(key);               //La pasa a min�scula.
        switch (checkKey(key)) {        //Llamo al chequeo de key y lo cambio.
        case KEY_H:                      //Si fue H...
            if (std::stoi(value) < MAX_ALTO && std::stoi(value) > 0) {  //Chequeo l�mites 0<Value<MAX_ALTO
                res = OK;                                       //Si todo OK, res=OK.
                userDataPtr->height = std::stoi(value);         //Guardo valor en userData.
            }
            break;
        case KEY_W:                                                         //Si fue W...
            if (std::stoi(value) < MAX_ANCHO && std::stoi(value) > 0) { //Chequeo l�mites 0<Value<MAX_ANCHO
                res = OK;                                               //Si todo OK, res=OK.
                userDataPtr->width = std::stoi(value);                  //Guardo valor en userData.
            }
            break;
        case KEY_R:                                                            //Si fue R...
            if (std::stoi(value) < MAX_ROBOTS && std::stoi(value) > 0) {   //Chequeo l�mites 0<Value<MAX_ROBOTS
                res = OK;                                                  //Si todo OK, res=OK.
                userDataPtr->robot_amount = std::stoi(value);              //Guardo valor en userData.
            }
            break;
        case KEY_M:                                                 //Si fue M...
            if (checkModeValue(std::stoi(value))) {             //Chequeo valor.
                res = OK;                                       //Si todo OK, res=OK.
                userDataPtr->mode = std::stoi(value);           //Guardo valor en userData.
            }
            break;
        default:                                       //Si no, res mantiene valor 0.
            break;
        }
       }
 
    return res;             //Devuelve res.
}

bool checkModeValue(int value) {                    //Chequeo valor del modo.
    for (int j = 0; validModeValues[j]; j++) {
        if (validModeValues[j]==value)
            return true;                            //Si es alguno de los que set�n en validModeValues, devuelve true.
    }                                               
    return false;                                    //Si no, devuelve false.
}

int checkKey(char* key){                        //Chequeo de key.
    for (int j = 0; validKeys[j]; j++) {
        if (!strcmp(validKeys[j], key))
            return j+1;                        //Si es alguna de las que est�n en validKeys, devuelve su �ndice +1(c�digo).
    }
    return ERROR;                              //Si no, devuelve 0.
}
void lowerstring(char* s) {           //convierte strings a min�scula para poder comparar con la lista de keys o par�metros v�lidos...
    int i;
    for (i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}