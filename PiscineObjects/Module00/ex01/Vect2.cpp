/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:56:23 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/28 19:24:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vect2.hpp"

Vect2::Vect2(void) : X(0.0f), Y(0.0f) {}
	
Vect2::Vect2(float x, float y) : X(x), Y(y) {}
	
Vect2::Vect2(const Vect2& other) : X(other.X), Y(other.Y) {}
	
Vect2& Vect2::operator=(const Vect2& other) {
		if (this != &other) {
			X = other.X;
			Y = other.Y;
		}
		return (*this);
}
	
Vect2::~Vect2(void) {}

//[]
float Vect2::operator[](int n) const {
	if (n == 0)
		return (X);
	return (Y);
}

float& Vect2::operator[](int n) {
	return (n == 0 ? X : Y);
}

//==
bool Vect2::operator==(const Vect2& other) const {
	return (X == other.X && Y == other.Y);
}

bool Vect2::operator!=(const Vect2& other) const {
	return (!(*this == other));
}

//Getters
float Vect2::getX(void) const {
	return (X);
}

float Vect2::getY(void) const {
	return (Y);
}



std::ostream& operator<<(std::ostream& out, const Vect2& v) {
	out << "{" << v[0] << ", " << v[1] << "}";
	return (out); 
}


