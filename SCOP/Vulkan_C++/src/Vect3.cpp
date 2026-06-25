/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect3.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 12:39:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/25 19:09:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vect3.hpp"

Vect3::Vect3(void) : _x(0.0f), _y(0.0f), _z(0.0f){}

Vect3::Vect3(float x, float y, float z) : _x(x), _y(y), _z(z){}

Vect3::Vect3(const Vect3 &other) : _x(other._x), _y(other._y), _z(other._z){}

Vect3& Vect3::operator=(const Vect3& other){
    if (this != &other){
		_x = other._x;
		_y = other._y;
		_z = other._z;
	}
	return (*this);
}

Vect3::~Vect3(void){}

//operators
Vect3   Vect3::operator+(const Vect3& other) const{
	return (Vect3(_x + other._x, _y + other._y, _z + other._z));
}

Vect3&  Vect3::operator+=(const Vect3& other){
	_x += other._x;
	_y += other._y;
	_z += other._z;
	return (*this);
}

Vect3	Vect3::operator-(const Vect3& other) const{
	return (Vect3(_x - other._x, _y - other._y, _z - other._z));
}

Vect3&	Vect3::operator-=(const Vect3& other){
	_x -= other._x;
	_y -= other._y;
	_z -= other._z;
	return (*this);
}

Vect3	Vect3::operator*(float num) const{
	return (Vect3(_x * num, _y * num, _z * num));
}

Vect3&	Vect3::operator*=(float num){
	_x *= num;
	_y *= num;
	_z *= num;
	return (*this);
}

Vect3	operator*(float num, const Vect3& other){
	return (other * num);
}

Vect3	Vect3::operator/(float num) const{
	if (num == 0.0f)
		return (*this);
	return (Vect3(_x / num, _y / num, _z / num));
}

Vect3&	Vect3::operator/=(float num){
	if (num == 0.0f)
		return (*this);
	_x /= num;
	_y /= num;
	_z /= num;
	return (*this);
}

//ostream
std::ostream&	operator<<(std::ostream &out, const Vect3 &v3){
	out << std::showpoint;
	out << "x: " << v3._x << ", y: " << v3._y << ", z: " << v3._z;
	return (out);
}

/*El istrinstream parsea al tipo que se le dice saltandose
los espacios por tokens. si hay fallo dara el iss(words) como falso pero puede
haber basura por ejemplo:
v 1 2 3 8
en ese caso words >> extra seria true y nos salimos por que es linea no valida*/
void	store_vertex(const std::string& line, VMAP& objPoints){
	char				type;
	std::istringstream	words(line); //conecta el line con el iss words
	float				x, y, z;

	words >> type >> x >> y >> z;
	if (!words || type != 'v')
		return;
	std::string	extra;
	if (words >> extra)
		return;
	Vect3	aux(x,y,z);
	size_t	num = objPoints.size();
	objPoints.emplace(num + 1, aux);
}

void	test_data(VMAP& objPoints){
	size_t 	i = 1;
	size_t	mSize = objPoints.size();
	while ( i <= mSize){
		std::cout << objPoints[i] << std::endl;
		i++;
	}
}
