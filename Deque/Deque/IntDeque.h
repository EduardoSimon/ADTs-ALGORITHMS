#pragma once
#ifndef INT_DEQUE
#define INT_DEQUE

#include <string>

using namespace std;

class IntDeque
{
public:
	IntDeque();
	void EncolarPorDetras(int);
	void EncolarPorDelante(int);
	int DesencolarPorDetras() throw (string);
	int DesencolarPorDelante() throw (string);

private:
	struct Nodo
	{
		int dato;
		Nodo* anterior;
		Nodo* siguiente;
		Nodo(int, Nodo*, Nodo*);
	};

	int talla;
	Nodo* entrada;
	Nodo* salida;
};

#endif 
