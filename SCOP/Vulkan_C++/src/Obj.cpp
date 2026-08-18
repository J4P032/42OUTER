/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 12:42:13 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 18:23:34 by jrollon-         ###   ########.fr       */
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

size_t	Obj::get_map_size(void){
	return (_points.size());
}

void	Obj::insert_vert3(size_t i, Vect3 vertex){
	_points.emplace(i, vertex);
}

void	Obj::insert_findex(uint32_t num){
	_polygon_indexes.push_back(num);
}

uint32_t	Obj::show_last_findex(void){
	return (_polygon_indexes.back());
}

void	Obj::remove_findex(size_t num){
	for (size_t i = 0; i < num; i++){
		_polygon_indexes.pop_back();
	}
}


void    Obj::stream_insert(std::ostream &out) const{
    size_t	contador = 0;
	out << std::showpoint; //show 0's if is 0 -> 0 = 0.0
	out << "POINTS:" << std::endl;
	for (const auto& [id, vector] : _points){
		out << id << " -> " << vector << std::endl;
	}
	out << std::endl << "FACES:" << std::endl;
	for (const auto& v : _polygon_indexes){
		out << v << " ";
		contador++;
		if (contador == 3){
			out << std::endl;
			contador = 0;
		}
	}
}

