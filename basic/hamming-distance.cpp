#include <iostream> // cout 
// #include <algorithm> // std::swap
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

    // Validar tamaños
    if( a.length() != b.length() ){
    	cout << "Tamaños difentes :";
    	exit(-1);
    }

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

int distancia_hamming(string& a,string& b){	
	// cout << "distancia_hamming -> " << endl;
	int missmatch = 0;	
	for (int i = 0; i < a.length(); i++){
		// cout << a[i] << ", " << b[i] << endl;
		if( a[i] != b[i] ){
			missmatch++;
		}
	}
	return missmatch;
}

int main(int argc, const char* argv[]) {	
	cout << endl << "./hd.exe < input.data" <<  endl;

	int d_h = 0; // distancia_hamming
	string v, w;	
	leer_sequencias(v, w);

	cout << endl << "Valores Iniciales " << endl;
	cout << v << " " << w << endl;
	

	// Calcular tiempo transcurrido.
  	auto t1 = chrono::high_resolution_clock::now();
  		d_h = distancia_hamming(v, w);
  	auto t2 = chrono::high_resolution_clock::now();

	cout << endl << "distancia hamming = " <<  d_h << endl; 
	cout << "Tiempo ejecucion (ns) = " << chrono::duration_cast<chrono::nanoseconds>(t2-t1).count() << endl;
}

