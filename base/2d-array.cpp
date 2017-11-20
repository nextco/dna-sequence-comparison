#include <iostream> // cout 

using namespace std;

int main(int argc, const char* argv[]) {	
	int filas, columnas;
	filas = 5; columnas = 6;
	// 2D array
	
	int **matrix = new int*[filas];
	
	int sequencial = 1;
	for(int i = 0; i < filas; i++) {
		matrix[i] = new int[columnas];
		for(int j = 0; j < columnas; j++) {
			matrix[i][j] = sequencial;
			sequencial++;
		}
	}

	for(int i = 0; i < filas; i++) {		
		for(int j = 0; j < columnas; j++) {
			// cout << "( " << i << ", " << j << ") => " << matrix[i][j] << " ";
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

}