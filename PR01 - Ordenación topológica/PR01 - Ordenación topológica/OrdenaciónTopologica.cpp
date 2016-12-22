// g++ GrafoDirigido.cpp -std=c++11 && ./a.out 

#include <iostream>
#include <fstream>
#include <string>
#include <utility>

#include <queue>

using namespace std;

#define DESCONOCIDO -1

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

	//Contador de veces que se ha hecho un pop a la cola
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


float GrafoDirigido::costeCaminoOptimo(int s, int t, vector<float> &resultados, vector<int> &camino) {
	//Llegamos al origen
	if (s == t)
		return 0;

	//Legamos a un vertice sin ningun arco incidente
	if (vertices[t].incidentes.size() == 0) 
		return INFINITY;

	if (resultados[t] == DESCONOCIDO) {
		//De momento el resultado será infinito
		float resultado = INFINITY;
		//Comprobamos todos los nodos incidentes
		for (auto elem : vertices[t].incidentes) {
			float candidato = costeCaminoOptimo(s, elem.origen, resultados, camino) + elem.peso;
			if (candidato < resultado) {
				resultado = candidato;
				camino[t] = elem.origen;
			}
		}
		return resultado;
	}
	else
		return resultados[t];
}

float GrafoDirigido::costeCaminoOptimo(int s, int t) {
	vector<float> resultados(vertices.size(), DESCONOCIDO);
	vector<int> camino(vertices.size());

	float coste = costeCaminoOptimo(s, t, resultados, camino);

	int i = t;

	while (i != s) {
		cout << i << endl;
		i = camino[i];
	}
	cout << i << endl;

	return coste;
}

bool GrafoDirigido::todosAlcanzables(int s) {
	vector<bool> visitados(vertices.size());
	queue<int> colaVertices;

	colaVertices.push(s);

	int contador = 1;

	while (!colaVertices.empty()) {
		int vertice = colaVertices.front();
		colaVertices.pop();
		contador++;

		for (auto v : vertices[vertice].adyacentes) {
			if (!visitados[v.destino]) {
				colaVertices.push(v.destino);
				visitados[v.destino] = true;
			}
		}
	}

	return contador == vertices.size() -1;
}

bool GrafoDirigido::alcanzableDesdeTodos(int s) {
	vector<bool> visitados(vertices.size());
	queue<int> colaVertices;

	colaVertices.push(s);

	int contador = 1;

	while (!colaVertices.empty()) {
		int vertice = colaVertices.front();
		colaVertices.pop();
		contador++;

		for (auto v : vertices[vertice].incidentes) {
			if (!visitados[v.destino]) {
				colaVertices.push(v.destino);
				visitados[v.destino] = true;
			}
		}
	}

	return contador == vertices.size() - 1;
}

bool GrafoDirigido::esFuertementeConexo(int s) { //Coste O( 2(|V|+|E|) )
	return todosAlcanzables(s) && alcanzableDesdeTodos(s);
}

bool GrafoDirigido::esAciclico(int s, vector<bool> &visitados, vector<bool> &acabados) {

}

bool GrafoDirigido::esAciclico() {
	vector<bool> visitados(vertices.size());
	vector<bool> acabados(vertices.size());

	//Empezar recursión
}


int main() {

	try {
		GrafoDirigido miGrafo("grafoEjemplo2.gr");
		miGrafo.mostrar();
		//miGrafo.mostrarOrdenTopologico();
		cout << endl;
		miGrafo.costeCaminoOptimo(1, 8);
	}
	catch (string error) {
		cerr << error << endl;
	}

}