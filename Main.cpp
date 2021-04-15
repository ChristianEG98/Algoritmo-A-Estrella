#include "Main.h"


int main() {
	cout << "Practica 1: Algoritmo A Estrella. Fernando Bellot y Christian Esteban" << endl;
	chcp1252();
	tMatriz matriz;
	tLista abierta, cerrada, camino;
	tLista caminouwu2;
	caminouwu2.contador = 0;
	bool continuar = true;
	cerrada.contador = 0;
	iniciarMatriz(matriz);
	mostrar(matriz);
	iniciarElementos(matriz, abierta);
	
	//seleccionar modo (paso a paso o automaticamente)
	int modo, replan;
	do {
		cout << "¿Cómo desea ejecutar el algoritmo?" << endl;
		cout << "1. Automáticamente" << endl;
		cout << "0. Paso a paso" << endl;
		cout << "Introduzca una opción: ";
		cin >> modo;
	} while (modo < 0 || modo > 1);

	
	//ejecuta el algoritmo hasta llegar a la casilla final y muestra el contenido de ambas listas
	do {
		aEstrella(matriz, abierta, cerrada, caminouwu2, continuar);
		cout << endl << "Lista abierta: ";
		for (int i = 0; i < abierta.contador; i++) {
			cout << abierta.casillas[i].coor.alto << " " << abierta.casillas[i].coor.ancho << " | ";
		}
		cout << endl << "Lista cerrada: ";
		for (int i = 0; i < cerrada.contador; i++) {
			cout << cerrada.casillas[i].coor.alto << " " << cerrada.casillas[i].coor.ancho << " | ";
		}
		cout << endl;
		mostrar(matriz);
		if (modo == 0) {
			do {
				//cout << "¿Cómo desea ejecutar el algoritmo?" << endl;
				cout << "1. Replanificar" << endl;
				cout << "0. Continuar algoritmo" << endl;
				cout << "Introduzca una opción: ";
				cin >> replan;
			} while (replan < 0 || replan > 1);
			if (replan == 1) {
				replanificar(matriz,abierta);
			}
		}
	} while (continuar);

	//dibuja el camino resultante y las coordenadas del mismo
	cout << endl << " Llegada a meta!" << endl;
	caminoRegreso(matriz, caminouwu2, camino);
	mostrar(matriz);
	cout << " El camino resultante es : ";
	for (int j = camino.contador - 1; j >= 0; j--) {
		cout << " -> | "<< camino.casillas[j].coor.alto << " " << camino.casillas[j].coor.ancho << " |";
	}
	cout << endl;
	pausa();
	return 0;
}
void iniciarMatriz(tMatriz& matriz) {
	do {
		cout << "Introduzca el alto y ancho de la matriz (minimo 2 - maximo 50): ";
		cin >> matriz.limites.alto >> matriz.limites.ancho;
	} while (matriz.limites.alto < 2 || matriz.limites.alto > 50 || matriz.limites.ancho < 2 || matriz.limites.alto > 50);
	//uwu
	//inicializar color [negro ('0') = casilla vacia] y coste casillas [1 predeterminado]
	for (int i = 0; i < matriz.limites.alto; i++) {
		for (int j = 0; j < matriz.limites.ancho; j++) {
			matriz.casillas[i][j].color = '0';
			matriz.casillas[i][j].coste = 1;
		}
	}
}
void iniciarElementos(tMatriz& matriz, tLista& abierta) {
	int opcion, casAlto, casAncho;
	tCoor casillaProhibida;
	//establecer posicion de inicio
	abierta.contador = 0;
	do {
		cout << "Introduzca la casilla de inicio (alto y ancho): ";
		cin >> casAlto >> casAncho;
	} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
	//añadimos la posicion de inicio a la lista abierta
	abierta.casillas[abierta.contador].coor.alto = casAlto;
	abierta.casillas[abierta.contador].coor.ancho = casAncho;
	abierta.casillas[abierta.contador].padre.alto = casAlto;
	abierta.casillas[abierta.contador].padre.ancho = casAncho;
	abierta.contador++;
	//pintamos de color verde ('2') la posicion de inicio
	matriz.casillas[casAlto][casAncho].color = '2';
	mostrar(matriz);

	//establecer posicion de fin
	do {
		cout << "Introduzca la casilla de fin (alto y ancho): ";
		cin >> casAlto >> casAncho;
	} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
	//guardamos la posicion final y la pintamos de color magenta ('5')
	matriz.casillaFin.alto = casAlto;
	matriz.casillaFin.ancho = casAncho;
	matriz.casillas[casAlto][casAncho].color = '5';
	mostrar(matriz);

	//establecer waypoints
	int wayp;
	do {
		cout << "¿Deseas añadir un waypoint?" << endl;
		cout << "1. Si" << endl;
		cout << "0. No" << endl;
		cout << "Introduzca una opción: ";
		cin >> wayp;

		if (wayp == 1) {
			do {
				cout << "Introduzca la casilla del waypoint (alto y ancho): ";
				cin >> casAlto >> casAncho;
			} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
			matriz.waypoints.push({ casAlto,casAncho });
			matriz.casillas[casAlto][casAncho].color = '8';
			mostrar(matriz);
		}

	} while (wayp != 0);

	matriz.waypoints.push({ matriz.casillaFin.alto, matriz.casillaFin.ancho });
	matriz.casillaFin.alto = matriz.waypoints.front().alto;
	matriz.casillaFin.ancho = matriz.waypoints.front().ancho;
	matriz.waypoints.pop();



	//establecer casillas prohibidas y obstaculos
	do {
		cout << "1. Añadir casilla prohibida" << endl;
		cout << "2. Añadir obstaculo coste bajo" << endl;
		cout << "3. Añadir obstaculo coste medio" << endl;
		cout << "4. Añadir obstaculo coste alto" << endl;
		cout << "5. Reestablecer casilla" << endl;
		cout << "0. Ejecutar algoritmo" << endl;
		cout << "Introduzca una opcion: ";
		cin >> opcion;
		if (opcion == 1) { //añadir casilla prohibida color rojo ('1')
			do {
				cout << "Introduzca la casilla prohibida (alto y ancho): ";
				cin >> casAlto >> casAncho;
			} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
			matriz.casillas[casAlto][casAncho].color = '1';
			cout << "Casilla prohibida añadida" << endl;
		}
		else if (opcion == 2) { //añadir casilla obstaculo coste bajo color cian1 ('9')
			do {
				cout << "Introduzca la casilla obstaculo de coste bajo (alto y ancho): ";
				cin >> casAlto >> casAncho;
			} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
			matriz.casillas[casAlto][casAncho].color = '9';
			matriz.casillas[casAlto][casAncho].coste = 1.5;
			cout << "Casilla obstaculo añadida" << endl;
		}
		else if (opcion == 3) { //añadir casilla obstaculo coste medio color cian2 ('6')
			do {
				cout << "Introduzca la casilla obstaculo de coste medio (alto y ancho): ";
				cin >> casAlto >> casAncho;
			} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
			matriz.casillas[casAlto][casAncho].color = '6';
			matriz.casillas[casAlto][casAncho].coste = 2;
			cout << "Casilla obstaculo añadida" << endl;
		}
		else if (opcion == 4) { //añadir casilla obstaculo coste alto color azul ('3')
			do {
				cout << "Introduzca la casilla obstaculo de coste alto (alto y ancho): ";
				cin >> casAlto >> casAncho;
			} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
			matriz.casillas[casAlto][casAncho].color = '3';
			matriz.casillas[casAlto][casAncho].coste = 2.25;
			cout << "Casilla obstaculo añadida" << endl;
		}
		else if (opcion == 5) { //eliminar casilla prohibida restablecer color negro ('0')
			do {
				cout << "Introduzca la casilla a reestablecer (alto y ancho): ";
				cin >> casAlto >> casAncho;
			} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
			matriz.casillas[casAlto][casAncho].color = '0';
			cout << "Casilla reestablecida" << endl;
		}
		mostrar(matriz);
	} while (opcion != 0);

}
void mostrar(tMatriz const& matriz) {
	cout << endl << "  ";
	for (int c = 0; c < matriz.limites.ancho; c++) {
		cout << setw(4) << c << "";
	}
	cout << endl << "  ";
	for (int b = 0; b < matriz.limites.ancho; b++) {
		cout << "  --";
	}
	cout << endl;
	for (int i = 0; i < matriz.limites.alto; i++) {
		cout << setw(2) << i << " ";
		for (int j = 0; j < matriz.limites.ancho; j++) {
			cout << "|";
			colorCTA(15, int(matriz.casillas[i][j].color) - int('0'));
			cout << setw(2) << " ";
			colorCTA(15, 0);
			cout << "|";
		}
		colorCTA(15, 0);
		cout << endl << "  ";
		for (int a = 0; a < matriz.limites.ancho; a++) {
			cout << "  --";
		}
		cout << endl;
	}
	cout << endl;
}
bool operator == (tCoor c1, tCoor c2) {
	return (c1.alto == c2.alto && c1.ancho == c2.ancho);
}
bool operator != (tCoor c1, tCoor c2) {
	return !(c1 == c2);
}
tCoor operator + (tCoor c1, tCoor c2) {
	tCoor c3;
	c3.ancho = c1.ancho + c2.ancho;
	c3.alto = c1.alto + c2.alto;
	return c3;
}
void aEstrella(tMatriz& matriz, tLista& abierta, tLista& cerrada, tLista& camino, bool &continuar) {
	tCoor vec, aux;
	tCoorLista mejorCasilla;
	bool repetida;
	mejorCasilla = casillaMenorCoste(matriz, abierta); //guardamos la casilla de menor coste
	cerrada.casillas[cerrada.contador] = mejorCasilla; //guardamos la casilla en Lista Cerrada
	cerrada.contador++;
	matriz.casillas[mejorCasilla.coor.alto][mejorCasilla.coor.ancho].color = '7'; //casilla recorrida color blanco ('7')
	camino.casillas[camino.contador] = mejorCasilla;
	camino.contador++;
	if (mejorCasilla.coor == matriz.casillaFin) { //si la mejor casilla encontrada es igual a la casilla final se termina
		if (matriz.waypoints.empty()) continuar = false;
		else {
			//reiniciamos la lista de casillas abiertas
			abierta.contador = 0;
			abierta.casillas[abierta.contador].coor.alto = matriz.casillaFin.alto;
			abierta.casillas[abierta.contador].coor.ancho = matriz.casillaFin.ancho;
			abierta.casillas[abierta.contador].padre.alto = matriz.casillaFin.alto;
			abierta.casillas[abierta.contador].padre.ancho = matriz.casillaFin.ancho;
			abierta.contador++;

			cerrada.contador = 0;
			
			//actualizamos el siguiente destino
			matriz.casillaFin.alto = matriz.waypoints.front().alto;
			matriz.casillaFin.ancho = matriz.waypoints.front().ancho;
			matriz.waypoints.pop();
		}	
	}
	//casillas adyacentes
	int numsAdy = 8;
	int adyF[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int adyC[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	for (int i = 0; i < numsAdy; i++) { //calcular todas las posibles casillas adyacentes de la mejor casilla devuelta anteriormente
		vec.alto = adyF[i];
		vec.ancho = adyC[i];
		aux = mejorCasilla.coor + vec;
		repetida = false;
		//si está en una de las casillas permitidas
		if (matriz.casillas[aux.alto][aux.ancho].color == '0' || matriz.casillas[aux.alto][aux.ancho].color == '5' || matriz.casillas[aux.alto][aux.ancho].color == '3' 
			|| matriz.casillas[aux.alto][aux.ancho].color == '6' || matriz.casillas[aux.alto][aux.ancho].color == '9' || matriz.casillas[aux.alto][aux.ancho].color == '8') {
			//miramos si está repetida ya esa casilla en Lista Abierta
			for (int j = 0; j < abierta.contador; j++) {
				if (abierta.casillas[j].coor == aux) {
					repetida = true;
				}
			}
			if (!repetida) { //si no está repetida guardamos la casilla en Lista Abierta
				abierta.casillas[abierta.contador].coor = aux;
				abierta.casillas[abierta.contador].padre = mejorCasilla.coor;
				abierta.contador++;
			}
		}
	}
}
tCoorLista casillaMenorCoste(tMatriz const& matriz, tLista& abierta) {
	int coste, mejorPosicion = 0;
	double distancia = 100;
	tCoor aux, fin;
	tCoorLista casillaMenor;
	fin = matriz.casillaFin;
	//buscamos la casilla de menor coste perteneciente a Lista Abierta
	for (int i = 0; i < abierta.contador; i++) {
		coste = matriz.casillas[abierta.casillas[i].coor.alto][abierta.casillas[i].coor.ancho].coste; //sacamos el coste de esa casilla
		aux = abierta.casillas[i].coor;
		if (minimaDistancia(distancia, coste, aux, fin)) {
			mejorPosicion = i;
		}
	}
	casillaMenor = abierta.casillas[mejorPosicion];
	//eliminar de Lista Abierta la casilla
	for (int j = mejorPosicion; j < abierta.contador; j++) {
		abierta.casillas[j].coor = abierta.casillas[j + 1].coor;
		abierta.casillas[j].padre = abierta.casillas[j + 1].padre;
	}
	abierta.contador--;
	return casillaMenor;
}
bool minimaDistancia(double& distancia, int coste, tCoor inicio, tCoor fin) {
	bool menosDistancia = false;
	double distanciaActual = sqrt(pow((fin.alto - inicio.alto), 2) + pow((fin.ancho - inicio.ancho), 2)) + coste; //f(n) = g(n) + h'(n)
	if (distanciaActual < distancia) { //si la distancia es menor a la guardada anteriormente, cogemos la nueva distancia y devolvemos true
		distancia = distanciaActual;
		menosDistancia = true;
	}
	return menosDistancia;
}
void caminoRegreso(tMatriz& matriz, tLista cerrada, tLista& camino) {
	int pos = cerrada.contador - 1;
	int c = cerrada.contador - 1;
	camino.contador = 0;
	tCoor hijo, padre;
	do {
		hijo = cerrada.casillas[pos].coor; //coordenada por la que hacer el retroceso hasta la casilla inicial
		matriz.casillas[hijo.alto][hijo.ancho].color = '4'; //pintamos de amarillo ('4') la casilla hijo
		camino.casillas[camino.contador].coor = hijo; //añadimos al camino la casilla hijo
		camino.contador++;
		padre = cerrada.casillas[pos].padre; //guardamos la casilla padre de la coordenada
		pos = posicionPadre(padre, cerrada, c); //posición en Lista Cerrada de la coordenada que corresponde al padre de la anterior
	} while (pos != 0);
	//guardamos en camino la casilla de inicio
	camino.casillas[camino.contador].coor = cerrada.casillas[0].coor;
	camino.contador++;
	matriz.casillas[cerrada.casillas[0].coor.alto][cerrada.casillas[0].coor.ancho].color = '4';
}

int posicionPadre(tCoor coor, tLista cerrada, int& i) {
	//int i = cerrada.contador - 1;
	while (coor.alto != cerrada.casillas[i].coor.alto || coor.ancho != cerrada.casillas[i].coor.ancho) {
		i--;
	}
	return i;
}

void replanificar(tMatriz& matriz, tLista& abierta) {

	matriz.casillas[matriz.casillaFin.alto][matriz.casillaFin.ancho].color = '0';
	while (!matriz.waypoints.empty()) {
		matriz.casillas[matriz.waypoints.front().alto][matriz.waypoints.front().ancho].color = '0';
		matriz.waypoints.pop();
	}

	int casAlto, casAncho;

	//establecer posicion de fin
	do {
		cout << "Introduzca la casilla de fin (alto y ancho): ";
		cin >> casAlto >> casAncho;
	} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
	//guardamos la posicion final y la pintamos de color magenta ('5')
	matriz.casillaFin.alto = casAlto;
	matriz.casillaFin.ancho = casAncho;
	matriz.casillas[casAlto][casAncho].color = '5';
	mostrar(matriz);

	//establecer waypoints
	int wayp;
	do {
		cout << "¿Deseas añadir un waypoint?" << endl;
		cout << "1. Si" << endl;
		cout << "0. No" << endl;
		cout << "Introduzca una opción: ";
		cin >> wayp;

		if (wayp == 1) {
			do {
				cout << "Introduzca la casilla del waypoint (alto y ancho): ";
				cin >> casAlto >> casAncho;
			} while (casAlto < 0 || casAlto >= matriz.limites.alto || casAncho < 0 || casAncho >= matriz.limites.ancho);
			matriz.waypoints.push({ casAlto,casAncho });
			matriz.casillas[casAlto][casAncho].color = '8';
			mostrar(matriz);
		}

	} while (wayp != 0);

	matriz.waypoints.push({ matriz.casillaFin.alto, matriz.casillaFin.ancho });
	matriz.casillaFin.alto = matriz.waypoints.front().alto;
	matriz.casillaFin.ancho = matriz.waypoints.front().ancho;
	matriz.waypoints.pop();

}