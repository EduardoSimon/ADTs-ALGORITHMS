#include <iostream>
using namespace std;

#include "ConjuntoDeEnteros.h"

int main() {

	ConjuntoDeEnteros d;
	cout << "a) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	d.insertar(5, "cinco");
	cout << "b) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	d.insertar(7, "siete");
	cout << "c) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	d.insertar(3, "tres");
	cout << "d) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	d.eliminar(5);
	cout << "e) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	d.eliminar(4);
	cout << "f) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	d.vaciar();
	cout << "g) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	d.insertar(6, "seis");
	cout << "h) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	d.insertar(2, "dos");
	cout << "i) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	d.buscar(6) = "six";
	cout << "j) Talla=" << d.talla() << "   "; d.mostrarOrdenados(); cout << endl;

	for (int k = 0; k < 10; k++)
		try {
		cout << "k" << k << ") ";
		cout << d.buscar(k) << endl;
	}
	catch (string mensaje) {
		cout << mensaje << endl;
	}


}