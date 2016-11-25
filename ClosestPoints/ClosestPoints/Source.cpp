#include <iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include <time.h>
#include <math.h>
#include <cmath>
#include <random>

using namespace std;

typedef vector<pair<float,float>> VectorPuntos;
typedef pair<float, float> Punto;

float distancia(pair<float,float> & p1, pair<float,float> & p2)
{
	return sqrt((powf((p2.first - p1.first),2) + powf((p2.second - p1.second), 2)));
}

bool comparadorMenorX(Punto & p1, Punto & p2)
{
	return p1.first < p2.first;
}

bool comparadorMenorY(Punto & p1, Punto & p2)
{
	return p1.second < p2.second;
}

vector<Punto> copiarVector(vector<Punto> puntos)
{
	vector<Punto> nuevo;
	nuevo.swap(puntos);
	return nuevo;
}

float cPFuerzaBruta(vector<Punto> myVector)
{
	//inicializamos el valor de minima distancia al maximo del float
	float minDist = FLT_MAX;

	for (int i = 0; i < myVector.size() ; i++)
	{
		for (int j = i + 1; j < myVector.size(); j++)
		{
			if (distancia(myVector[i], myVector[j]) < minDist)
			{
				minDist = distancia(myVector[i], myVector[j]);
			}
		}
	}

	return minDist;
}

/*
float DivideXRecursive(vector<Punto> & puntosX, int a, int b, float minDistIzquierda, float minDistDerecha)
{
	if (abs(a-b) < 4)
	{
		float minDistFuerzaBruta = cPFuerzaBruta(puntosX, a, b);

		if (minDistDerecha > minDistFuerzaBruta || minDistIzquierda > minDistFuerzaBruta)
		{
			return minDistFuerzaBruta;
		}

		else
		{
			if (minDistDerecha < minDistDerecha)
				return minDistDerecha;
			else
				return minDistIzquierda;
		}
	}

	int puntoMedio = (a + b)/ 2;
	return minDistIzquierda = DivideXRecursive(puntosX, a, puntoMedio - 1, minDistIzquierda, minDistDerecha);
	return minDistDerecha = DivideXRecursive(puntosX, puntoMedio, b, minDistIzquierda, minDistDerecha);

	if (minDistDerecha < minDistDerecha)
		return minDistDerecha;
	else
		return minDistIzquierda;
}
*/


float distanciaMinimaRecursiva(vector<Punto> pX, vector<Punto> pY)
{
	//caso base 1
	if (pX.size() < 4)
	{
		return cPFuerzaBruta(pX);
	}

	//caso base 2
	if (pY.size() < 4)
	{
		return cPFuerzaBruta(pY);
	}

	//obtenemos el punto medio de el vector X y el Y
	Punto medioX = pX[pX.size() / 2];
	Punto medioY = pY[pY.size() / 2];

	//los dividimos
	VectorPuntos derechaX(pX.begin(), pX.begin() + pX.size() / 2);
	VectorPuntos izquierdaX((pX.begin() + pX.size() / 2) + 1, pX.end());
	VectorPuntos derechaY;
	VectorPuntos izquierdaY;

	// este for se encarga de ordenar el array por la coordenada Y correctamente respetando en que lado de la frontera están los puntos.
	for (auto elem : pY)
	{
		if (elem.first < medioX.first)
			izquierdaY.push_back(elem);
		else if (elem.first > medioX.first)
			derechaY.push_back(elem);
		else
			if (elem.second < medioY.second)
				izquierdaY.push_back(elem);
			else
				derechaY.push_back(elem);
	}

	//llamadas recursivas a la derecha y la izquierda
	float distanciaMinimaDerecha = distanciaMinimaRecursiva(derechaX, derechaY);
	float distanciaMinimaIzquierda = distanciaMinimaRecursiva(izquierdaX, izquierdaY);
	
	return min(distanciaMinimaDerecha, distanciaMinimaIzquierda);
}


float closestPoints(vector<Punto> puntosX)
{
	//ordenamos por coordenada x
	sort(puntosX.begin(), puntosX.end());

	//copiamos el vector en otro vector llamado puntosY
	vector<Punto> puntosY = copiarVector(puntosX);

	//ordenamos ese vector de puntos Y
	sort(puntosY.begin(), puntosY.end(), comparadorMenorY);

	//la frontera
	Punto frontera = puntosX[puntosX.size() / 2];

	//si hay repetidos devolvemos 0 ya que la solucion es dist 0
	for (int i = 0; i < puntosY.size() - 1 ; i++)
	{
		if (puntosY[i] == puntosY[i + 1])
			return 0;
	}

	// delta es la distancia minima de la derecha y de la izquierda
	float delta = distanciaMinimaRecursiva(puntosX, puntosY);

	VectorPuntos fronteraPuntos;

	//nos quedamos delta a la izquierda de la frontera y delta a la derecha, estos elementos los metemos en un nuevo array
	for (int i = 0; i < puntosX.size(); i++)
	{
		if (puntosX[i].first > (frontera.first - delta) && puntosX[i].first < (frontera.first + delta) || puntosX[i].first == (frontera.first - delta))
		{
			fronteraPuntos.push_back(puntosX[i]);
		}

	}

	//ordenamos los elementos por su coordenada Y
	sort(fronteraPuntos.begin(), fronteraPuntos.end(), comparadorMenorY);

	float minDist = delta;

	//recorres todos los puntos y en el de dentro como maximo 6 veces por lo que es coste 0(6N) = 0(N)
	for (int i = 0; i < fronteraPuntos.size(); i++)
	{
		// sale del segundo for cuando la distancia entre el siguiente punto es mayor que delta
		for (int j = i + 1; j < fronteraPuntos.size() && (fronteraPuntos[j].second - fronteraPuntos[i].second) < minDist ; j++)
		{
			float dist = distancia(fronteraPuntos[i], fronteraPuntos[j]);

			if (dist < minDist)
			{
				minDist = dist;
			}
		}
	}

	return min(delta, minDist);
}


int main()
{
	char hola;
	/*
	default_random_engine default_random;
	uniform_real_distribution<float> generadorAleatorio(-1000.0, 1000.0);

	vector<Punto> puntos;

	for (int talla = 2, tallaMax = 10; tallaMax <= 100000; tallaMax *= 10)

		for (; talla < tallaMax; talla += tallaMax / 10) {

			while (puntos.size() < talla)
				puntos.push_back(Punto(generadorAleatorio(default_random), generadorAleatorio(default_random)));

			float distancia = closestPoints(puntos);

			if (distancia != cPFuerzaBruta(puntos)) {
				cout << "ERROR." << endl;
				return EXIT_FAILURE;
			}
			else
				cout << talla << "\t" << distancia << endl;
		}*/

	VectorPuntos Puntos = { { 2, 3 },{ 12, 30 },{ 40, 50 },{ 5, 1 },{ 12, 10 },{ 3, 4 } };
	printf("The smallest distance is %f ", closestPoints(Puntos));

	/*
	for (int i = 0; i < Puntos.size(); i++)
	{

		for (int j = i + 1; j < Puntos.size(); j++)
		{
			printf("la distancia es %f ", distancia(Puntos[i], Puntos[j]));
			cout << "" << endl;
		}
	}
	*/
	VectorPuntos Puntos2 = { { 2, 3 },{ 12, 30 },{ 40, 50 },{ 5, 1 },{ 12, 10 },{ 3, 4 } };
	printf("The smallest distance by bruteForce is %f ", cPFuerzaBruta(Puntos2));
	cin >> hola;
}