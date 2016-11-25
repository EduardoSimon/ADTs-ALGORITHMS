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

	//declaramos un vector paralelo para tener el contador de los incidentes
	vector<int> numeroIncidentes(vertices.size());
	queue<Vertice> colaVertices;

	for (int i = 1; i < numeroIncidentes.size(); i++) { //Contadores de incidentes
		numeroIncidentes[i] = vertices[i].incidentes.size();
	}

	int indice = 1;

	while (indice < numeroIncidentes.size()) 
	{
		if (numeroIncidentes[indice] == 0) 
		{
			colaVertices.push(vertices[indice]);

			Vertice temp = vertices[indice];

			//el for recorre todos los arcos que salen del vertice que tiene 0 arcos incidentes
			for (int i = 0; i < temp.adyacentes.size(); i++)
			{
				//acedemos al contador del vertice destino de ese mismo arco y restamos 1.
				numeroIncidentes[temp.adyacentes[i].destino] --;
			}
		}

		indice++;
	}

	if (colaVertices.size() != numeroIncidentes.size())
		throw string("El grafo es cíclico");

	while (!colaVertices.empty())
	{
		//ir mostrando los resultados

	}

}


int main() {

	try {
		GrafoDirigido miGrafo("grafoEjemplo2.gr");
		miGrafo.mostrar();
		//miGrafo.mostrarOrdenTopologico();
	}
	catch (string error) {
		cerr << error << endl;
	}

}