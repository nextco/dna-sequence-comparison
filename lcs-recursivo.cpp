#include <iostream> // cout 
#include <algorithm> // max
#include <random> //
#include <string> // stoi
#include <chrono> // diferencia de tiempo 
#include <vector> // struct strip

using namespace std;

// Validar caracteres válidos
bool validar_secuencia(string& s){
	// http://www.cplusplus.com/reference/string/string/find_first_not_of/
	// ATGC
	// Cuando encuentra un cadena diferente devuelve la posición donde la encuentra
	std::size_t found = s.find_first_not_of("ATGC");
	// cout << "found: " << found << endl;
	// cout << "std::string::npos: " << std::string::npos << endl;

	return std::string::npos == found;
}

void leer_sequencias(string& a,string& b){	
	// cout << "leer_sequencias -> " << endl;
	a = ""; b = "";

	cout << "Primera secuencia?: "; cin >> a;
	cout << "Segunda secuencia?: "; cin >> b;

    // Validar caracteres válidos
    // ATGC	
    if( !validar_secuencia(a) ){
    	cout << "ATGC Valid?:";
    	exit(-1);
    }

    if( !validar_secuencia(b) ){
    	cout << "ATGC Valid?:";
    	exit(-1);
    }
	
}

int lcs_recursivo(string& a,string& b, int n, int m){	
	// cout << "lcs_recursivo -> " << endl;
	if(n == 0 || m == 0){
		return 0;
	}
	if(a[n - 1] == b[m - 1]){
		return 1 + lcs_recursivo(a, b, n - 1, m - 1);
	}else{
		return max(lcs_recursivo(a, b, n, m - 1), lcs_recursivo(a, b, n-1, m));
	}

}

int main(int argc, const char* argv[]) {	
	cout << endl << "./lcs.exe < recursivo.data" <<  endl;

	int maxima_distancia = 0; // Recursivo
	int n, m; // Tamaño de secuencias
	string v, w;	
	leer_sequencias(v, w);
	n = v.length();
	m = w.length();

	cout << endl << "Valores Iniciales " << endl;
	cout << v << " " << w << endl;
	

	// Calcular tiempo transcurrido.
  	auto t1 = chrono::high_resolution_clock::now();
  		maxima_distancia = lcs_recursivo(v, w, n, m);
  	auto t2 = chrono::high_resolution_clock::now();

	cout << endl << "maxima distancia = " <<  maxima_distancia << endl; 
	cout << "Tiempo ejecucion (ns) = " << chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() << endl;
}

