#include "ColaPrioridad.h"
#include <string>
#include <iostream>

using namespace std;

ColaPrioridad::Nodo::Nodo(int laPrioridad, Nodo * elSiguiente) : prioridad{ laPrioridad }, siguiente{elSiguiente}
{
}

ColaPrioridad::ColaPrioridad() : talla{0}, minimo{nullptr} , entrada{nullptr}
{
}

void ColaPrioridad::insertar(int prioridad)
{
	entrada = new Nodo(prioridad, entrada);

	if (minimo == nullptr || entrada->siguiente->prioridad > entrada->prioridad)
	{
		minimo = entrada;
	}
}

void ColaPrioridad::mostrar() const
{
	for (Nodo* actual = entrada; actual != nullptr; actual= actual->siguiente)
	{
		cout << actual->prioridad << endl;
	}
}

int ColaPrioridad::consultarMinimo() throw(string)
{
	if (minimo == nullptr || entrada == nullptr)
		throw ("Intentando consultar el minimo de una cola vacia.");

	return minimo->prioridad;
}

void ColaPrioridad::eliminarMinimo() throw(string)
{
	Nodo* nuevoMinimo = nullptr, * anterior = nullptr;
	for (Nodo* actual = entrada; actual != nullptr; actual = actual->siguiente)
	{
		if (actual == minimo)
		{
			if (anterior == nullptr)
			{
				entrada = minimo->siguiente;
			}
			else 
			{
				anterior->siguiente = minimo->siguiente;
			}
		}
		else 
		{
			if (minimo == nullptr || actual ->prioridad < nuevoMinimo->prioridad)
			{
				nuevoMinimo = actual;
			}
		}
		anterior = actual;
	}

	delete minimo;
	minimo = nuevoMinimo;

}