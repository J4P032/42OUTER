#ifndef MY_NEW_HPP
# define MY_NEW_HPP

#include <new>
extern int nContador;

template <typename T>
T*	my_new() {
	if (nContador < 2) {
		nContador++;
		return new T;
	}
	else {
		throw std::bad_alloc();
	}
}

template <typename T, typename Arg1>
T*	my_new(Arg1 arg) {
	if (nContador < 2) {
		nContador++;
		return new T(arg);
	}
	else {
		throw std::bad_alloc();
	}
}

#endif
