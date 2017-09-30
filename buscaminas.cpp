#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

char jugarAgain;
char **matriz_1,**matriz_2;
int cantMinas, xPosNum, yPosNum, count = 0;
string minas, xPos, yPos;

//esquema de funciones a utilizar
void asignacion(char**, char**, int, int);
void mostrar_matriz(char**, int, int);
void contarMina(char** matriz_2, int fila, int columna);
void juego(char** matriz_1, char** matriz_2, int fila, int columna);
void revisar_zona(char** matriz_1, char** matriz_2, int fila, int columna);
int revisar_juego(char** matriz_1, char** matriz_2, int fila, int columna);

int main()
{
	int fila, columna;//las varibales de tma de matriz
	do
	{
		cout << "Digite el numero de filas que desea:  "; cin >> fila;//solicitamos el num de filas al ussuario
		cout << "Digite el numero de columnas que desea:  "; cin >> columna;//solicitamos el num de filas al ussuario guardando en var columna
		matriz_1 = new char *[fila];//reservamos memoria para las matrices a usar
		matriz_2 = new char *[fila];//reservamos memoria para las matrices a usar
		system("cls");

		do
		{
			cout << "Digite el numero de minas que desea (min = 5, max = 10): ";
			cin >> minas;//guardamos el numero de minas que el usuario quiere
			stringstream(minas) >> cantMinas;//clase para guardar datos dentro del flujo
		}while(cantMinas < 5 || cantMinas > 10);//mientras que el numero de minas sea mayor igual que 5 y menor gual que 10

		system("cls");//refrescamos la pantalla

		asignacion(matriz_1, matriz_2, fila, columna);//llamamos la funcion con la mat1 y la matriz de minas que creamos con punteros
		mostrar_matriz(matriz_1, fila ,columna);//mostramos ambas matrices
		juego(matriz_1, matriz_2, fila, columna);//comenzamos el juego

		cout << "¿Jugar otra vez? (S/N): ";//FIN DE JUEGO, para ver si el usuario quiere volver a jugar
		cin >> jugarAgain;//se guarda en la variable si quiere jugar otra vez
		}while(jugarAgain == 'S' || jugarAgain == 's');//se vuelve a jugar otra vez si el usuario digita s  mayuscula o minuscula

	return 0;
}

void asignacion(char** matriz_1, char** matriz_2, int fila, int columna)//para crear las matrices
{
	srand((unsigned int)time(0));//para tener posiciones aleatorias

	for(int row = 0; row < fila; row ++){//
		matriz_1[row] = new char [columna];
		matriz_2[row] = new char [columna];
		for(int col = 0; col < 10; col ++){
			matriz_1[row][col] = '*';//inicializamos la matriz con asteriscos, la que esta encima
			matriz_2[row][col] = '0';//"debajo" de los asteriscos tambien tendremos los ceros que significa que no hayy bombas
		}
	}

	for(int i = 0; i < cantMinas; i++){
		int row = (rand() % 4);//se colocan los numeros de 0 a 3 random
		int col = (rand() % 4);//en filas y columnas
		while(matriz_2[row][col] == '@'){//el arroba son  bombas
			row = (rand() % 4);
			col = (rand() % 4);
		}
		matriz_2[row][col] = '@';
	}
	contarMina(matriz_2, fila, columna);
}


void contarMina(char** matriz_2, int fila, int columna)
{
	for(int row = 0; row < fila; row ++){//recorremos filas
		for(int col = 0; col < columna; col++){//recorremos columnas
			if(matriz_2[row][col] == '@'){//si es que hay una bomba
				for(int x = row - 1; x <= row + 1; x++){//damos la posicion de bombade
					for(int y = col - 1; y <= col + 1; y++){
						if(x >= 0 && x <= fila){//si esta dentro del rango de 10
							if(y >= 0 && y <= columna){
								if(matriz_2[x][y] != '@'){//si no es bomba
									matriz_2[x][y] += 1;//se aumenta en 1
								}
							}
						}
					}
				}
			}
		}
	}
}

void mostrar_matriz(char** anArray, int fila, int columna)//
{
	for(int row = 0; row < fila; row++){
		for(int col = 0; col < columna; col++){
			cout << anArray [row][col] << " ";//para mostrarr la matriz con la forma correspondiente
		}
		cout << endl;
	}
}

void juego(char** matriz_1, char** matriz_2, int fila, int columna)////se inicia el juego
{
	for(int i = 0; i <= fila*columna; i++){//se recorre toda la matriz hasta el ultimo dato

		do
		{
			cout << "Ingrese el numero de fila del (1 - "<<fila<<"): ";
			cin >> xPos;
			stringstream(xPos) >> xPosNum;
		}while(xPosNum < 1 || xPosNum > fila);//mientras la pos sea mayor que 1 y menor al nueor de filas

		do
		{
			cout << "Ingrese el numero de columna del (1 - "<<columna<<"): ";
			cin >> yPos;
			stringstream(yPos) >> yPosNum;
		}while(yPosNum < 1 || yPosNum > columna);//mientras la pos sea mayor que 1 y menor al nueor de columnas

		while(matriz_1[xPosNum - 1][yPosNum - 1] == matriz_2[xPosNum - 1][yPosNum - 1]){//se accesa a la poscion de la matriz
			cout << "ya ingresaste esa posicion" << endl << endl;

			cout << "Ingrese otro numero de fila: ";
			cin >> xPos;
			stringstream(xPos) >> xPosNum;

			cout << "Ingrese otro numero de columna: ";
			cin >> yPos;
			stringstream(yPos) >> yPosNum;
		}

		if(matriz_2[xPosNum - 1][yPosNum - 1] == '@'){
			cout << "\nUyyy :c! Tocaste una mina!" << endl;
			cout << "Fin del Juego!" << endl << endl;
			mostrar_matriz(matriz_2, fila, columna);
			return;
		}

		else{
			system("cls");
			matriz_1[xPosNum - 1][yPosNum - 1] = matriz_2[xPosNum - 1][yPosNum - 1];
			revisar_zona(matriz_1, matriz_2, fila, columna);
			mostrar_matriz(matriz_1, fila, columna);
			count = revisar_juego(matriz_1, matriz_2, fila, columna);
			if(count == (fila*columna - cantMinas)){
				cout << "\nFelicidades! opd Encontraste todas las minas!" << endl;
				return;
			}
		}
	}
}

void revisar_zona(char** matriz_1, char** matriz_2, int fila, int columna)
{
	if(matriz_2[xPosNum - 1][yPosNum - 1] == '0'){
		for(int x = xPosNum - 2; x != xPosNum + 1; x++){
			for(int y = yPosNum - 2; y != yPosNum + 1; y++){
				if(x >= 0 && x <= 4){
					if(y >= 0 && y <= 4){
						matriz_1[x][y] = matriz_2[x][y];
						if(matriz_2[x][y] == '0'){
							for(int x2 = x - 1; x2 != x + 2; x2++){
								for(int y2 = y - 1; y2 != y + 2; y2++){
									if(x2 >= 0 && x2 <= 4){
										if(y2 >= 0 && y2 <= 4){
											if(matriz_2[x2][y2] != '@'){
											matriz_1[x2][y2] = matriz_2[x2][y2];
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int revisar_juego(char** matriz_1, char** matriz_2, int fila, int columna)
{
	int count = 0;
	for(int x = 0; x < fila; x++){
		for(int y = 0; y < columna; y++){
			if(matriz_1[x][y] == matriz_2[x][y]){
				count += 1;
			}
		}
	}
	return count;
}
