/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 12:42:13 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 14:06:09 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Obj.hpp"

Obj::Obj(void){};

Obj::Obj(VMAP points) : _points(points) {}

Obj::Obj(const Obj &other) : _points(other._points) {}

Obj&	Obj::operator=(const Obj &other){
	if (this != &other){
		_points = other._points;
	}
	return *this;
}

Obj::~Obj(void){}

const VMAP&	Obj::get_points(void) const{
	return _points;
}

void    Obj::stream_insert(std::ostream &out) const{
    out << std::showpoint; //show 0's if is 0 -> 0 = 0.0
	out << "POINTS: " << std::endl;
	for (const auto& [id, vector] : _points){
		out << id << " -> " << vector << std::endl;
	}
}

