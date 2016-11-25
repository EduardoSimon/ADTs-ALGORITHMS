
#include <iostream>
using namespace std;

#include "ConjuntoDeEnteros.h"

ConjuntoDeEnteros::Nodo::Nodo(int elDato, string elTexto) : dato{ elDato }, texto{ elTexto }, izquierdo { nullptr }, derecho{ nullptr } {
}

ConjuntoDeEnteros::ConjuntoDeEnteros() : raiz{ nullptr }, laTalla{ 0 } {
}

void ConjuntoDeEnteros::insertar(int unDato, const string & elTexto) {
	if (raiz == nullptr)
		insertar(unDato, raiz,elTexto );
	else {
		Nodo * n = raiz;
		bool fin = false;
		while (!fin)
			if (unDato < n->dato)
				if (n->izquierdo != nullptr)
					n = n->izquierdo;
				else {
					insertar(unDato, n->izquierdo, elTexto);
					fin = true;
				}
			else if (unDato > n->dato)
				if (n->derecho != nullptr)
					n = n->derecho;
				else {
					insertar(unDato, n->derecho, elTexto);
					fin = true;
				}
			else
				fin = true; // No insertamos duplicados
	}
}

void ConjuntoDeEnteros::insertar(int unDato, Nodo * & n, const string & texto) {
	n = new Nodo(unDato,texto);
	laTalla++;
}

int ConjuntoDeEnteros::minimoEnSubarbol(Nodo * n) const { // Siendo n != nullptr
	while (n->izquierdo != nullptr)
		n = n->izquierdo;
	return n->dato;
}

void ConjuntoDeEnteros::eliminar(int unDato) {
	eliminar(unDato, raiz);
}

void ConjuntoDeEnteros::eliminar(int unDato, Nodo * & n) {
	if (n == nullptr)
		return;
	if (unDato < n->dato)
		eliminar(unDato, n->izquierdo);
	else if (unDato > n->dato)
		eliminar(unDato, n->derecho);
	else if (n->izquierdo != nullptr && n->derecho != nullptr) {
		n->dato = minimoEnSubarbol(n->derecho);
		n->texto = minimoEnSubarbol(n->derecho);
		eliminar(n->dato, n->derecho);
	}
	else {
		Nodo * basura = n;
		if (n->izquierdo != nullptr)
			n = n->izquierdo;
		else
			n = n->derecho;
		delete basura;
		laTalla--;
	}
}


string & ConjuntoDeEnteros::buscar(int unDato) const {
	return buscar(unDato, raiz);
}

string & ConjuntoDeEnteros::buscar(int unDato, Nodo * n) const {
	if (unDato == n->dato)
		return n->texto;
	if (unDato < n->dato)
		return buscar(unDato, n->izquierdo);
	if (unDato > n->dato)
		return buscar(unDato, n->derecho);

	throw("No se ha encontrado el indice");
}

void ConjuntoDeEnteros::mostrarOrdenados() const {
	cout << "{";
	mostrarOrdenados(raiz);
	cout << "}";
}

void ConjuntoDeEnteros::mostrarOrdenados(Nodo * n) const {
	if (n != nullptr) {
		mostrarOrdenados(n->izquierdo);
		cout << "{clave: " << n->dato << ", valor: " << n->texto << " }.";
		mostrarOrdenados(n->derecho);
	}
}

int ConjuntoDeEnteros::talla() const {
	return laTalla;
}

void ConjuntoDeEnteros::vaciar() {
	vaciar(raiz);
	raiz = nullptr;
	laTalla = 0;
}

void ConjuntoDeEnteros::vaciar(Nodo * n) {
	if (n != nullptr) {
		vaciar(n->izquierdo);
		vaciar(n->derecho);
		delete n;
	}
}
