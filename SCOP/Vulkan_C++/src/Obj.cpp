/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 12:42:13 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/25 11:02:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Obj.hpp"
#include <limits>

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


//Getters
size_t	Obj::get_map_size(void) const{
	return (_points.size());
}

const VMAP&	Obj::get_points() const{
	return _points;
}

const VINDEX&	Obj::get_polygon_indexes() const{
	return _polygon_indexes;
}

const Vect3&	Obj::get_center(void) const{
	return _center;
}

//Setters
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

void	Obj::calculate_center(void){
	if (_points.empty())
		return;
	
	float min_x = std::numeric_limits<float>::max();
	float min_y = std::numeric_limits<float>::max();
	float min_z = std::numeric_limits<float>::max();
	float max_x = std::numeric_limits<float>::lowest(); //min() its the min but positive
	float max_y = std::numeric_limits<float>::lowest(); //lowest() c++11 if c++98 use -max()
	float max_z = std::numeric_limits<float>::lowest();

	std::map<size_t, Vect3>::const_iterator cit = _points.begin();
	for (; cit != _points.end(); cit++){
		float aux_x = cit->second.get_x();
		float aux_y = cit->second.get_y();
		float aux_z = cit->second.get_z();
				
		if (aux_x < min_x){
			min_x = aux_x;
		}
		if (aux_y < min_y){
			min_y = aux_y;
		}
		if (aux_z < min_z){
			min_z = aux_z;
		}
		if (aux_x > max_x){
			max_x = aux_x;
		}
		if (aux_y > max_y){
			max_y = aux_y;
		}
		if (aux_z > max_z){
			max_z = aux_z;
		}
	}
	_center = Vect3((max_x + min_x) / 2.0f, (max_y + min_y) / 2.0f, (max_z + min_z) / 2.0f);
}

///
void	Obj::move_to_center(void){
	VMAP::iterator it = _points.begin();
	for (; it != _points.end(); it++){
		it->second.set_x(it->second.get_x() - _center.get_x());
		it->second.set_y(it->second.get_y() - _center.get_y());
		it->second.set_z(it->second.get_z() - _center.get_z());
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
	out << std::endl << "CENTER:" << std::endl;
	out << _center;
}

