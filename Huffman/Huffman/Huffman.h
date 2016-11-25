#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <string>
#include <vector>
#include <utility> // pair
#include <map>

using namespace std;

class Huffman {

	struct Nodo {
		char   caracter;
		float  frecuencia;
		Nodo * izquierdo;
		Nodo * derecho;
		Nodo * padre;
		char   bit;
		Nodo(char, float);
	};

	struct ComparadorNodos {
		bool operator()(Nodo *, Nodo *) const;
	};

	Nodo * raiz;
	map<char, Nodo *> codigo;

public:

	Huffman(const vector< pair<char, float> > &) throw(string);
	string codificar(const string &) const throw(string);
	string decodificar(const string &) const;

};

#endif