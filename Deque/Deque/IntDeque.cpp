#include<iostream>
#include <string>
#include "IntDeque.h"

using namespace std;

IntDeque::Nodo::Nodo(int eldato, Nodo* elsiguiente, Nodo* elanterior) : dato{ eldato }, siguiente{ elsiguiente }, anterior{ elanterior }{}

IntDeque::IntDeque() : talla{ 0 }, entrada{ nullptr }, salida{ nullptr }{}

void IntDeque::EncolarPorDetras(int dato)
{
	Nodo* nuevo = new Nodo(dato, nullptr, nullptr);

	if (entrada == nullptr)
	{
		entrada = nuevo;
		salida = nuevo;
	}
	else
	{
		nuevo->anterior = entrada;
		entrada->siguiente = nuevo;
		entrada = nuevo;
	}

}

void IntDeque::EncolarPorDelante(int dato)
{
	Nodo* nuevo = new Nodo(dato, nullptr, nullptr);

	if (salida == nullptr)
	{
		salida = nuevo;
		entrada = nuevo;
	}
	else
	{
		nuevo->siguiente = salida;
		salida->anterior = nuevo;
		salida = nuevo;
	}
}

int IntDeque::DesencolarPorDelante() throw (string)
{
	if (entrada == nullptr && salida == nullptr)
	{
		throw ("ERROR: Intentas desencolar un elemento de una cola vacia. ");
	}

	Nodo* temp = salida;
	int datoDevuelto = salida->dato;
	salida = salida->siguiente;
	if (salida == nullptr)
	{
		entrada == nullptr;
	}
	salida->anterior = nullptr;
	delete temp;
	return datoDevuelto;
}

int IntDeque::DesencolarPorDetras() throw(string)
{
	if (entrada == nullptr && salida == nullptr)
	{
		throw ("ERROR: Intentas desencolar un elemento de una cola vacia. ");
	}

	Nodo* temp = entrada;
	int resultadoDevuelto = entrada->dato;
	entrada = entrada->anterior;
	if (entrada == nullptr)
	{
		salida = nullptr;
	}
	entrada->siguiente = nullptr;
	delete temp;
	return resultadoDevuelto;
}

