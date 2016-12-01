
#ifndef _GRAFO_DIRIGIDO_H
#define _GRAFO_DIRIGIDO__H

#include <vector>

using namespace std;

class GrafoDirigido {

	struct Arco {
		int origen;
		int destino;
		float peso;
		Arco(int, int, float);
	};

	struct Vertice {
		vector<Arco> incidentes; // arcos que entran al vertice
		vector<Arco> adyacentes; // arcos que salen del vertice
	};

	vector<Vertice> vertices; // El vertice i estara en la posicion i numerando desde 1

public:

	GrafoDirigido(const char *) throw(string);

	void mostrar() const;

	void mostrarOrdenTopologico() const throw(string);

	float costeCaminoOptimo(int s, int t) const throw (string);

private: 

	bool esCiclico() const;

	float costeCaminoOptimoRecursivo(int s, int t, vector<float> & resultados, vector<int> & camino) const;



};

#endif