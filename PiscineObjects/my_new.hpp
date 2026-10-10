#ifndef MY_NEW_HPP
# define MY_NEW_HPP

#include <new>


//fallo asignación de memoria
template <typename T>
T*	my_new() {
	static int nContador = 0;
	if (nContador < 1) {
		nContador++;
		return new T;
	}
	else {
		throw std::bad_alloc();
	}
}

template <typename T, typename Arg1>
T*	my_new(Arg1 arg) {
	static int nContador = 0;
	
	if (nContador < 1) {
		nContador++;
		return new T(arg);
	}
	else {
		throw std::bad_alloc();
	}
}


// fallo en contenedores memoria
template <typename T, typename element>
void	mi_push_back(T& contenedor, element* elem) {
	static int nFallo = 0;

	if (nFallo >= 1) {
		throw std::bad_alloc();
	}
	nFallo++;
	contenedor.push_back(elem);
}

template <typename T, typename element>
void	mi_insert(T& contenedor, element* elem) {
	static int nFallo = 0;

	if (nFallo >= 1) {
		throw std::bad_alloc();
	}
	nFallo++;
	contenedor.insert(elem);
}



#endif
