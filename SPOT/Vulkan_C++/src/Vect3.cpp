/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect3.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 12:39:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/19 13:30:29 by jrollon-         ###   ########.fr       */
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

std::ostream&  operator<<(std::ostream &out, const Vect3 &v3){
    out << std::showpoint;
    out << "x: " << v3._x << ", y: " << v3._y << ", z: " << v3._z;
    return (out);
}