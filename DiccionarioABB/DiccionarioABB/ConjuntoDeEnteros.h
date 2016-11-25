#ifndef _CONJUNTO_ENTEROS_H
#define _CONJUNTO_ENTEROS_H

#include <string>
#include <vector>

class ConjuntoDeEnteros {

	struct Nodo {
		int dato;
		string texto;
		Nodo * izquierdo;
		Nodo * derecho;
		Nodo(int, string);
	};

	Nodo * raiz;
	int laTalla;

	void insertar(int, Nodo * &, const string&);
	void eliminar(int, Nodo * &);
	string & buscar(int, Nodo *) const ;
	void mostrarOrdenados(Nodo *) const;
	int  minimoEnSubarbol(Nodo *) const;
	void vaciar(Nodo *);

public:

	ConjuntoDeEnteros();
	void insertar(int, const string&);
	void eliminar(int);
	string & buscar(int) const throw(string);
	void mostrarOrdenados() const;
	int  talla() const;
	void vaciar();

};

#endif