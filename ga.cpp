// Alineamiento Global
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

	// cout << "filas: " << filas << endl; // v - n - columnas; w - m - filas
	// cout << "columnas: " << columnas << endl;

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

			S[i][j] = maximo( a, maximo(b, c) );
	    }
    }
	
	// cout << endl << "S: " << endl;
	// imprimir_matriz_header_s(S, filas, columnas, v, w );

}

// Pag 177
void alineamiento_global(int **& S, int i , int j, int L, char *&v, char *&w, int **& p, int g,
	string &alinea_vl, string &alinea_wl){
	// cout << "ag -> " << i << ", " << j << endl; 
	if( i == 0 && j == 0){
		L = 0;
		return;
    }else if(i > 0 && ( S[i][j] == S[i-1][j] + g) ){
    	alineamiento_global(S, i-1, j, L, v, w, p, g, alinea_vl, alinea_wl);
    	L++;

    	cout << "vl: "<< v[i-1];
    	cout << ", wl: "<< '-' << endl;

    	alinea_wl.push_back( v[i - 1] );
    	alinea_wl.push_back( '-' );

    }else if( i > 0 && j > 0 && ( S[i][j] == S[i-1][j-1] + p[i][j]) ){
    	alineamiento_global(S, i-1, j-1, L, v, w, p, g, alinea_vl, alinea_wl);
    	L++;
    	
    	cout << "vl: "<< v[i-1];
    	cout << ", wl: "<< w[j-1] << endl;

    	alinea_vl.push_back( v[i - 1] );
    	alinea_wl.push_back( w[j - 1] );

    }else if( j > 0 && ( S[i][j] == S[i][j-1] + g) ){
    	alineamiento_global(S, i, j-1, L, v, w, p, g, alinea_vl, alinea_wl);
    	L++;

    	cout << "vl: "<< '-';
    	cout << ", wl: "<< w[j-1] << endl;
    	alinea_vl.push_back( '-' );
    	alinea_wl.push_back( w[j - 1] );
    }
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

  	cout << endl << "S: " << endl;
	imprimir_matriz_header_s(matrix_s, n+1, m+1, v, w );

	cout << endl << "p: " << endl;
	imprimir_matriz_header_s(matrix_p, n+1, m+1, v, w );
	
	int L = 0; // Longitud de alineamiento ?
	string alinea_vl;
	string alinea_wl;
	// 
	cout << endl;
	alineamiento_global(matrix_s, n , m, L, v, w, matrix_p, g, alinea_vl, alinea_wl); cout << endl;
	
	// Interpretacion
	int inserciones, eliminaciones;
	obtener_indels(alinea_vl, inserciones, alinea_wl, eliminaciones);

	cout << endl << "Resultados de Alineamiento Global e Interpretacion; para transformar v en w se requieren: "<< endl;
	cout << "alinea_vl: " << alinea_vl << "=> " << inserciones << " inserciones" << endl;
	cout << "alinea_wl: " << alinea_wl << "=> " << eliminaciones <<" eliminaciones" << endl;

}

