/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 12:42:13 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 15:52:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Obj.hpp"

Obj::Obj(void){};

Obj::Obj(VMAP points, VINDEX polygon_indexes) : _points(points),
	_polygon_indexes(polygon_indexes) {}

Obj::Obj(const Obj &other) : _points(other._points),
	_polygon_indexes(other._polygon_indexes) {}

Obj&	Obj::operator=(const Obj &other){
	if (this != &other){
		_points = other._points;
		_polygon_indexes = other._polygon_indexes;
	}
	return *this;
}

Obj::~Obj(void){}

void    Obj::stream_insert(std::ostream &out) const{
    out << std::showpoint; //show 0's if is 0 -> 0 = 0.0
	out << "POINTS: " << std::endl;
	for (const auto& [id, vector] : _points){
		out << id << " -> " << vector << std::endl;
	}
}

