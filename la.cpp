// Bug lcs-a.data
// Alineamiento Local
#include <iostream> // cout 
#include <algorithm> // max
#include <random> //
#include <string> // stoi
#include <chrono> // diferencia de tiempo 
#include <vector> // struct strip
#include <limits> // Maximo & minimo valor de int

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

void init_matrix(int **&matrix, int filas, int columnas){
    // cout << "init_matrix -> " << endl;
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

// Devuelve true si dos caracteres son iguales
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

	// cout << "filas: " << filas << endl; // v - n - columnas; w - m - filas
	// cout << "columnas: " << columnas << endl;

	// Init
	init_matrix(S, filas, columnas );
	init_matrix(p, filas, columnas );

	// Obtener penalización para p
	obtener_p(p, filas, columnas, v, w);
	
	// Linea 3
	for(int i = 0; i < columnas; i++){
       	S[0][i] = 0; // Fix
    }

    // Linea 5
	for(int j = 1; j < filas; j++){
       	S[j][0] = 0; // Fix
    }

    /*
    cout << endl << "S: " << endl;
	imprimir_matriz_header_s(S, filas, columnas, v, w );

	cout << endl << "p: " << endl;
	imprimir_matriz_header_s(p, filas, columnas, v, w );
	*/

	// cout << "maximo(5,3,4): " << maximo(5, maximo(3, 4)) << endl;
	// Linea 7	
	for(int i = 1; i < filas; i++){
		for(int j = 1; j < columnas; j++){
			
			int a = S[i-1][j] + g;
			int b = S[i-1][j-1] + p[i][j];
			int c = S[i][j-1] + g;
			int d = 0; // Aplicacion			

			S[i][j] = maximo( maximo(a, b), maximo(c, d) );
	    }
    }
	
	// cout << endl << "S: " << endl;
	// imprimir_matriz_header_s(S, filas, columnas, v, w );

}

void maximo_score(int **&S, int &score_maximo_i, int &score_maximo_j, int i, int j){	
	int max_score = numeric_limits<int>::min(); // minimo valor que puede tomar int
	// cout << "max_score: " << max_score << endl;
	for (int k = 1; k != i ; k++){
		for (int l = 1; l != j ; l++){
			// cout << "(k, l) => " << k << ", " << l << " = " << S[k][l]<< endl;
			if( S[k][l] >= max_score){
				// cout << "(k, l) => " << k << ", " << l << " = " << S[k][l]<< endl;
				max_score = S[k][l];
				score_maximo_i = k;
				score_maximo_j = l;
			}
		}
	}
	// cout << "max_score: " << max_score << endl; 
}

void obtener_cadena_alineamiento_local(int **&S, int i, int j, string &max_secuencia, char *&v){

	// cout << "obtener_cadena_alineamiento_local: " << i << ", "<< j << " = "<< S[i][j] << endl;
	
	// Hasta encontrar un cero - Fixed
	if( S[i][j] == 0 ){				
		return;
	}

	obtener_cadena_alineamiento_local(S, i-1, j-1, max_secuencia, v);
    // cout << "Sequencia: "<< v[i - 1] << endl;
    max_secuencia.push_back( v[i - 1] );
}

// c = a + b
void sumar_matrix(int **&a, int **&b, int **&c, int filas, int columnas){
    cout << "sumar_matrix -> " << endl;

    init_matrix(c, filas, columnas );    
    
	for(int i = 0; i < filas; i++) {
		for(int j = 0; j < columnas; j++) {
			c[i][j] = a[i][j]  + b[i][j];
		}
	}

}

void alineamiento_local(int **& S, int filas , int columnas, char *&v, char *&w, int **& p, int g,
	string &max_secuencia){

	cout << "alineamiento_local -> " << filas << ", " << columnas << endl;
	
	// Buscar maximo score en matriz
	int score_maximo_i = 0;
	int score_maximo_j = 0;

	maximo_score(S, score_maximo_i, score_maximo_j, filas, columnas);
	
	cout << "score_maximo_i: "<< score_maximo_i;
    cout << ", score_maximo_j: "<< score_maximo_j;
    cout << "=> max_score: " << S[score_maximo_i][score_maximo_j] << endl;


    obtener_cadena_alineamiento_local(S, score_maximo_i, score_maximo_j, max_secuencia, v);

    // cout << "=> max_secuencia: " << max_secuencia << endl;

}


void obtener_indels(string &alinea_vl, int &inserciones, string &alinea_wl, int &eliminaciones){
	// cout << "obtener_indels -> " << endl; 
	inserciones = 0;
	for (int i = 0; i != alinea_vl.length(); i++){
		// cout << alinea_vl[i];
		if(alinea_vl[i] == '-' ){
		 	inserciones++;
		}
	}

	eliminaciones = 0;
	for (int i = 0; i != alinea_wl.length(); i++){
		if(alinea_wl[i] == '-'){
			eliminaciones++;
		}
	}
	
}

void obtener_alineacion(char *&v, int n, char *&w, int m, string &alinea_vl, string &alinea_wl, string &max_secuencia){
	cout << "obtener_alineacion -> " << endl;
	alinea_vl = ""; alinea_wl = "";

	// Quick Bug Fix
	if(max_secuencia.length() == 1){
		// Copiar secuencias
		for (int i = 0; i != n; i++){
			alinea_vl.push_back( v[i] );
		}

		for (int j = 0; j != m; j++){
			alinea_wl.push_back( w[j] );
		}
		return;
	}	

	int i = 0;
	int j = 0;	
	// Posible restricción cadenas de igual tamaño
	while(i != n){

		// cout << endl <<  v[i] << ", " << w[j] << "=> "<< comparar_char(v, w, i, j)<< endl;

		if( comparar_char(v, w, i, j) ){ // Son iguales
			alinea_vl.push_back( v[i] );
			alinea_wl.push_back( w[j] );

			// cout << "vl: " << alinea_vl << endl;
			// cout << "wl: " << alinea_wl;
			i++; // Avanzar ambos
			j++;

		}else if( !comparar_char(v, w, i, j) && j < m ) { // No Son iguales			
			alinea_vl.push_back( '-' );
			alinea_wl.push_back( w[j] );

			// cout << "vl: " << alinea_vl << endl;
			// cout << "wl: " << alinea_wl;

			j++; // Avanzar w
		}else{
			alinea_vl.push_back( v[i]);
			alinea_wl.push_back( '-' );

			// cout << "vl: " << alinea_vl << endl;
			// cout << "wl: " << alinea_wl;

			i++;// Avanzar i
		}		
	
	}

	// cout << endl << "vl: " << alinea_vl << endl;
	// cout << "wl: " << alinea_wl;
	

}



int main(int argc, const char* argv[]) {	
	cout << endl << "./lcs-dp.exe < lcs.data" <<  endl;

	int g = -2; // gap
	int** matrix_s = nullptr; // S
	int** matrix_p = nullptr; // p
	
	char* v;
	char* w; // secuencias a comparar

	int n; // Tamaño de las secuencia v: filas
	int m; // Tamaño de las secuencia w: columnas
	
	leer_sequencias(v, w, n, m);
	cout << endl << "Valores Iniciales " << endl;
	cout << "v: "; imprimir_chars(v, n); cout << "=> "<< n << endl;
	cout << "w: "; imprimir_chars(w, m); cout << "=> "<< m << endl;
	
	calcular_similaridad(v, w, n, m, g, matrix_p, matrix_s);

	cout << endl << "p: " << endl;
	imprimir_matriz_header_s(matrix_p, n+1, m+1, v, w );

  	cout << endl << "S: " << endl;
	imprimir_matriz_header_s(matrix_s, n+1, m+1, v, w );
	cout << endl;
	// 13 Elementos => Matriz 14 Elementos
	
	string max_secuencia = ""; // secuencia maxima de alineamiento
	alineamiento_local(matrix_s, n + 1 , m + 1, v, w, matrix_p, g, max_secuencia); cout << endl;
	cout << "=> max_secuencia: " << max_secuencia << endl;
	cout << "v: "; imprimir_chars(v, n); cout << "=> "<< n << endl;
	cout << "w: "; imprimir_chars(w, m); cout << "=> "<< m << endl;

	// Interpretacion
	string alinea_vl, alinea_wl;
	obtener_alineacion(v, n, w, m, alinea_vl, alinea_wl, max_secuencia);

	cout << endl << "vl: " << alinea_vl << endl;
	cout << "wl: " << alinea_wl;

	
	int inserciones, eliminaciones;

	obtener_indels(alinea_vl, inserciones, alinea_wl, eliminaciones);

	cout << endl << endl << "Resultados de Alineamiento Local e Interpretacion; para transformar v en w se requieren: "<< endl;
	cout << "alinea_vl: " << alinea_vl << "=> " << inserciones << " inserciones" << endl;
	cout << "alinea_wl: " << alinea_wl << "=> " << eliminaciones <<" eliminaciones" << endl;

}

