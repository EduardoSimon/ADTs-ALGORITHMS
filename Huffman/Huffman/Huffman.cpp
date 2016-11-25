#include "Huffman.h"
#include <string>
#include <iostream>
#include <queue>

using namespace std;

Huffman::Nodo::Nodo(char elCaracter, float laFrecuencia) : caracter{elCaracter}, frecuencia{laFrecuencia}
{
	izquierdo = nullptr;
	derecho = nullptr;
	padre = nullptr;
}

bool Huffman::ComparadorNodos::operator()(Nodo * n1, Nodo * n2) const
{
	return n1->frecuencia > n2->frecuencia;
}

Huffman::Huffman(const vector<pair<char, float>>& v) throw(string)
{
	if (v.size() < 2)
	{
		throw ("La tabla no tiene suficientes caracteres.");
	}
	//pq de punteros Nodo, con un vector(HEAP), utilizando la clase ComparadorNodos como criterio de ordenación.
	priority_queue<Nodo*, vector<Nodo*>, ComparadorNodos> simbolosPQ;

	//creamos nuestra pq con el vector de pares que nos dan
	for (auto & elem : v)
	{
		Nodo* nodoAInsertar = new Nodo(elem.first, elem.second);
		codigo[nodoAInsertar->caracter] = nodoAInsertar;
		simbolosPQ.push(nodoAInsertar);
	}

	//mientras el tamaño de la pq sea mayor que un solo nodo extraeremos de la pq
	while (simbolosPQ.size() > 1)
	{
		//extraemos los dos primeros elementos de la pq de arboles y sumamos sus frecuencias para comenzar a contruir nuestro arbol huffman
		Nodo* nuevo = new Nodo(' ', 0);
		nuevo->izquierdo = simbolosPQ.top();
		simbolosPQ.pop();
		nuevo->derecho = simbolosPQ.top();
		simbolosPQ.pop();
		nuevo->frecuencia = nuevo->derecho->frecuencia + nuevo->izquierdo->frecuencia;
		nuevo->izquierdo->bit = '0';
		nuevo->derecho->bit = '1';
		nuevo->izquierdo->padre = nuevo;
		nuevo->derecho->padre = nuevo;
		simbolosPQ.push(nuevo);
	}

	raiz = simbolosPQ.top();
}

string Huffman::codificar(const string & mensaje) const throw(string)
{
	string mensajeCodificado, codigoResultado;
	Nodo* direccionNodo;

	for(auto caracter : mensaje)
	{ 
		try 
		{
			direccionNodo = codigo.at(caracter);
		}
		catch (out_of_range e)
		{
			throw ("No existe loko. ");
		}
		 
		codigoResultado = "";

		for (Nodo* aux = direccionNodo; aux != nullptr; aux = aux->padre)
		{
			codigoResultado += aux->bit;
		}

		reverse(codigoResultado.begin(), codigoResultado.end());
		mensajeCodificado += codigoResultado;
	}
	return mensajeCodificado;
}

string Huffman::decodificar(const string & mensajeCodificado) const
{
	Nodo* aux = raiz;
	string MensajeDecodificado;

	for (auto caracter : mensajeCodificado)
	{
		if (caracter == '0')
			aux = aux->izquierdo;
		else
			aux = aux->derecho;

		if (aux->izquierdo == nullptr)
		{
			MensajeDecodificado += aux->caracter;
			aux = raiz;
		}
	}

	return MensajeDecodificado;
}