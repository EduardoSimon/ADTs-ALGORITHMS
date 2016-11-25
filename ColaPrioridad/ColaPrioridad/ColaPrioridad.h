#pragma once
#ifndef COLA_PRIORIDAD_INT
#define COLA_PRIORIDAD_INT

#include <string>

using namespace std;

class ColaPrioridad
{
public:
	ColaPrioridad();
	void mostrar() const;
	void insertar(int);
	void eliminarMinimo() throw (string);
	int consultarMinimo() throw (string);

private:

	struct Nodo
	{
		int prioridad;
		Nodo* siguiente;
		Nodo(int, Nodo*);
	};

	int talla;
	Nodo* minimo;
	Nodo* entrada;
};

#endif // !COLA_PRIORIDAD_INT
