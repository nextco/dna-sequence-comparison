// ga.cpp
#include <iostream> // cout 
#include <algorithm> // max
#include <random> //
#include <string> // stoi
#include <chrono> // diferencia de tiempo 
#include <vector> // struct strip

using namespace std;

void imprimir_chars(char *&s, int size){	
	for (int i = 0; i != size; i++){
		cout << s[i];
	}
	// cout << " => ";
}

// Validar caracteres válidos
bool validar_secuencia(char *&c, int size){
	// To string
	string s;
	for (int i = 0; i != size; i++){
		s.push_back(c[i]);
	}
	
	// cout << "d: "<< s << endl;
	// http://www.cplusplus.com/reference/string/string/find_first_not_of/
	// ATGC
	// Cuando encuentra un cadena diferente devuelve la posición donde la encuentra
	std::size_t found = s.find_first_not_of("ATGC");
	// cout << "found: " << found << endl;
	// cout << "std::string::npos: " << std::string::npos << endl;

	return std::string::npos == found;
}


void leer_sequencias(char *&a, char *&b, int &n, int &m ){	
	cout << "leer_sequencias -> " << endl;
	
	cout << "Primera secuencia?: "; cin >> n ;
	// cout << "n: " << n << endl;
	a = new char[n];
	for(int i = 0; i != n; i++){
		cin >> a[i];
		// cout << "a[i]: " << a[i] << endl;
	}
    
	cout << "Segunda secuencia?: "; cin >> m;
	// cout << "m: " << m << endl;
	b = new char[m];
	for(int i = 0; i != m; i++){
		cin >> b[i];
		// cout << "b[i]: " << b[i] << endl;
	}

	// imprimir_chars(a, n);
	// imprimir_chars(b, m);
	
	
    // Validar caracteres válidos
    // ATGC	
    // cout << "validar_secuencia(a, n): " << validar_secuencia(a, n) << endl;
    if( !validar_secuencia(a, n) ){
    	cout << "ATGC Valid?:";
    	exit(-1);
    }

    if( !validar_secuencia(b, m) ){
    	cout << "ATGC Valid?:";
    	exit(-1);
    } 
}


void imprimir_matriz_int(int **& matrix, int filas, int columnas){
    // cout << "imprimir_matriz_int -> " << endl;
    for(int i = 0; i != filas; i++){
        for(int j = 0; j != columnas; j++){
        	cout << matrix[i][j] << " ";
        }            
        cout << endl;
    }
}

void imprimir_matriz_string(string **& matrix, int filas, int columnas){
    // cout << "imprimir_matriz -> " << endl;
    for(int i = 0; i != filas; i++){
        for(int j = 0; j != columnas; j++){
        	cout << matrix[i][j] << " ";
        }            
        cout << endl;
    }
}

void imprimir_matriz_header_s(int **& matrix, int filas, int columnas, char *&v, char *&w){
    // cout << "imprimir_matriz -> " << endl;
    // v - n - columnas; w - m - filas
    int next = 0;
    for(int i = 0; i != filas; i++){
    	if(i == 0){
    		// cout << "    "; // Valor 0,0
    		cout << "\t";
    		for (int k = 0; k != columnas - 1 ; k++){
				// cout << w[k] << " ";
				cout << w[k] << "\t";
				
			}
			cout << endl;
    	}

        for(int j = 0; j != columnas; j++){
        	if(j == 0 && i > 0){
        		cout << v[next] << " ";
        		next++;
			}else if(i == 0 && j == 0){
				cout << "  ";
			}
        	// cout << matrix[i][j] << " ";
        	cout << matrix[i][j] << "\t";
        }            
        cout << endl;
    }
}

void imprimir_matriz_header_p(string **& matrix, int filas, int columnas, char *&v, char *&w){
    // cout << "imprimir_matriz_header_b -> " << endl;
    // v - n - columnas; w - m - filas
    int next = 0;
    for(int i = 0; i != filas; i++){
    	if(i == 0){
    		cout << "    "; // Fix
    		for (int k = 0; k != columnas - 1 ; k++){
				cout << w[k] << " ";
			}
			cout << endl;
    	}

        for(int j = 0; j != columnas; j++){
        	if(j == 0 && i > 0){
        		cout << v[next] << " ";
        		next++;
			}else if(i == 0 && j == 0){
				cout << "  ";
			}
        	cout << matrix[i][j] << " ";
        }            
        cout << endl;
    }
}


void init_matriz_s(int **&matrix, int filas, int columnas){
    // cout << "init_matriz_s -> " << endl;
    int sequencial = 0;
    
    matrix = new int*[filas];
	for(int i = 0; i < filas; i++) {
		matrix[i] = new int[columnas];
		for(int j = 0; j < columnas; j++) {
			// matrix[i][j] = sequencial;
			matrix[i][j] = 0;
			sequencial++;
		}
	}

}

void init_matriz_b(string **&matrix, int filas, int columnas){
    // cout << "init_matriz_b -> " << endl;
        
    matrix = new string*[filas];
	for(int i = 0; i < filas; i++) {
		matrix[i] = new string[columnas];
		for(int j = 0; j < columnas; j++) {
			matrix[i][j] = "0";
		}
	}

}

// Validar caracteres válidos
// Character To string - Useless C++ miss function
string obtener_char(char *&c, int posicion){	
	// cout << "lcs_dp -> " << endl; 

	string s;	
	s.push_back( c[posicion] );	

	// cout << "posicion -> " << posicion << " => ";
	// cout << "string -> " << s;
	return s;
}

bool comparar_char(char *&v, char *&w, int i, int j){
	bool equals = false;

	string left = obtener_char( v, i ); // WTF
	string right = obtener_char( w, j);

	if( left.compare( right ) == 0 ){ // :S
		equals = true;
	}

	// cout << "comparar_char: " << left <<  ", " << right << "=> " <<  equals <<  endl;
	return equals;

}

void obtener_p(int **& p, int filas, int columnas, char *&v, char *&w){	
	// Linea 5 - 
	for(int i = 1; i < filas; i++){
		for(int j = 1; j < columnas; j++){
			if( comparar_char(v, w, i - 1, j - 1) ){ // Si son iguales
				p[i][j] = 1;
			}else{
				p[i][j] = -1;
			}			
	    }
    }
}

int maximo(int a, int b){
	if( a > b ){
		return a;
	}else{
		return b;
	}
}

void calcular_similaridad(char *&v, char *&w, int n, int m, int g, int **& p, int **& S){
	// Primero se lee v luego w
	cout << "calcular_similaridad -> " << endl;
	int filas, columnas;
	filas = n + 1; // w en las filas
	columnas = m + 1; // v en las columnas

	cout << "filas: " << filas << endl; // v - n - columnas; w - m - filas
	cout << "columnas: " << columnas << endl;

	// Init
	init_matriz_s(S, filas, columnas );
	init_matriz_s(p, filas, columnas );

	// Obtener penalización para p
	obtener_p(p, filas, columnas, v, w);
	
	// Linea 3
	for(int i = 0; i < columnas; i++){
       	S[0][i] = i*g;
    }

    // Linea 5
	for(int j = 1; j < filas; j++){
       	S[j][0] = j*g;
    }

    cout << endl << "S: " << endl;
	imprimir_matriz_header_s(S, filas, columnas, v, w );

	cout << endl << "p: " << endl;
	imprimir_matriz_header_s(p, filas, columnas, v, w );

	// cout << "maximo(5,3,4): " << maximo(5, maximo(3, 4)) << endl;
	// Linea 7	
	for(int i = 1; i < filas; i++){
		for(int j = 1; j < columnas; j++){
			int a = S[i-1][j-1] + p[i][j];
			int b = S[i][j-1] + g;
			int c = S[i-1][j] + g;

			S[i][j] = maximo( a, maximo(b, c) );
	    }
    }
	
	cout << endl << "S: " << endl;
	imprimir_matriz_header_s(S, filas, columnas, v, w );

}



// Pag 176 
void imprimir_lcs(string **& b, char *&v, int i, int j ){	
	
	if( i == 0 || j == 0){ // :S
		return;
    }
    
    if( b[i][j].compare( "D" ) == 0 ){    	    	
    	imprimir_lcs(b, v, i - 1, j - 1 );
    	cout << v[i - 1]; // Fix    	
    }else{
    	if(  b[i][j].compare( "U" ) == 0  ){
    		imprimir_lcs(b, v, i - 1, j);
    	}else{
    		imprimir_lcs(b, v, i, j - 1 );
    	}
    } 
}



int main(int argc, const char* argv[]) {	
	cout << endl << "./lcs-dp.exe < lcs.data" <<  endl;

	int g = -2; // gap
	int** matrix_p = nullptr; // p 

	int** matrix_s = nullptr; // S
	string** matrix_b = nullptr; // b
	
	char* v;
	char* w; // secuencias a comparar

	int n; // Tamaño de las secuencia v: filas
	int m; // Tamaño de las secuencia w: columnas
	
	leer_sequencias(v, w, n, m);
	cout << endl << "Valores Iniciales " << endl;
	cout << "v: "; imprimir_chars(v, n); cout << "=> "<< n << endl;
	cout << "w: "; imprimir_chars(w, m); cout << "=> "<< m << endl;
		
	auto t1 = chrono::high_resolution_clock::now();  	
  	calcular_similaridad(v, w, n, m, g, matrix_p, matrix_s);

  	auto t2 = chrono::high_resolution_clock::now();

  	/*
  	cout << endl << "S: " << endl;
    imprimir_matriz_header(matrix_s, n + 1, m + 1, v, w); // n + 1: filas, m + 1: columnas
    cout << endl << "b: " << endl;
	imprimir_matriz_string(matrix_b, n + 1, m + 1 );

	// cout << "matrix_b[7][8]: " << matrix_b[7][8] << endl;

	cout << endl << "imprimir_lcs: " ;
	imprimir_lcs(matrix_b, v, n , m); cout << endl;
	cout << "tamano_lcs: " << matrix_s[n][m] << endl;

	// cout << endl << "maxima distancia = " <<  maxima_distancia << endl; 
	cout << "Tiempo ejecucion (ns) = " << chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() << endl;
	*/

}

