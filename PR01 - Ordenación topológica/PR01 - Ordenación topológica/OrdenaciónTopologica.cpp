// g++ GrafoDirigido.cpp -std=c++11 && ./a.out 

#include <iostream>
#include <fstream>
#include <string>

#include <queue>

using namespace std;


#include "OrdenacionTopologica.h"

GrafoDirigido::Arco::Arco(int elOrigen, int elDestino, float elPeso)
	: origen{ elOrigen }, destino{ elDestino }, peso{ elPeso } {

}

void GrafoDirigido::mostrar() const {

	cout << "Listas de adyacencia: " << endl;
	for (int i = 1; i < vertices.size(); i++) {
		cout << "  vertice " << i << ":" << endl;
		for (const auto & arco : vertices[i].adyacentes)
			cout << "    " << arco.origen << "-->" << arco.destino << " (peso = " << arco.peso << ")" << endl;
		cout << endl;
	}

	cout << "Listas de incidencia: " << endl;
	for (int i = 1; i < vertices.size(); i++) {
		cout << "  vertice " << i << ":" << endl;
		for (const auto & arco : vertices[i].incidentes)
			cout << "    " << arco.origen << "-->" << arco.destino << " (peso = " << arco.peso << ")" << endl;
		cout << endl;
	}

}

GrafoDirigido::GrafoDirigido(const char * nombreFichero) throw(string) {

	ifstream flujoEntrada(nombreFichero);

	if (!flujoEntrada.is_open())
		throw string("ERROR: Imposible abrir el fichero ") + nombreFichero;

	char tipoLinea;
	int cantidadVertices = -1, origen, destino;
	float peso;

	while (!flujoEntrada.eof()) {
		flujoEntrada >> tipoLinea;
		if (!flujoEntrada.eof()) {
			if (tipoLinea == 'n') {
				flujoEntrada >> cantidadVertices;
				vertices.resize(cantidadVertices + 1); // Numeramos desde 1 dejando la posicion 0 sin usar
			}
			else if (tipoLinea == 'a') {
				if (cantidadVertices == -1) {
					flujoEntrada.close();
					throw string("ERROR: falta linea n antes de linea a en ") + nombreFichero;
				}
				flujoEntrada >> origen >> destino >> peso;
				vertices[origen].adyacentes.push_back(Arco(origen, destino, peso));
				vertices[destino].incidentes.push_back(Arco(origen, destino, peso));
			}
		}
	}

	flujoEntrada.close();

}

void GrafoDirigido::mostrarOrdenTopologico() const throw(string) {

	// A completar en el primer ejercicio
	vector<int> numeroIncidentes(vertices.size());
	queue<int> colaVertices;

	for (int i = 1; i < numeroIncidentes.size(); i++) { //Contadores de incidentes
		numeroIncidentes[i] = vertices[i].incidentes.size();
	}

	//buscar las raizes y encolarlas
	for (int i = 1; i < numeroIncidentes.size(); i++) {
		if (numeroIncidentes[i] == 0)
			colaVertices.push(i);
	}

	int contador = 0;
	//Recorrer los arcos del grafo a partir de los vértices de la cola
	while (!colaVertices.empty()) {
		int vertice = colaVertices.front();
		cout << vertice << " - ";
		colaVertices.pop();
		contador++;
		//cout << vertice << " - " << contador << endl;

		for (auto elem : vertices[vertice].adyacentes) {
			numeroIncidentes[elem.destino]--;
			if (numeroIncidentes[elem.destino] == 0)
				colaVertices.push(elem.destino);
		}
	}

	//Comprobar si el grafo es cíclico o acíclico
	if (contador != numeroIncidentes.size() - 1)
		throw string("El grafo no es aciclico");
}


int main() {

	try {
		GrafoDirigido miGrafo("grafoEjemplo2.gr");
		miGrafo.mostrar();
		miGrafo.mostrarOrdenTopologico();
	}
	catch (string error) {
		cerr << error << endl;
	}

}