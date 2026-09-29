/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:00:19 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/29 10:42:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graph.hpp"

Graph::Graph(void){}

Graph::Graph(float width, float height) : size(width, height){
	if (width < 0 || height < 0){
		throw std::runtime_error("Not possible create a negative width or height Graph");
	}
}

Graph::Graph(const Graph& other) : size(other.size) {}

Graph& Graph::operator=(const Graph& other){
	if (this != &other){
		size = other.size;
	}
	return *this;
}

Graph::~Graph(){}


void Graph::add_point(const Vect2& point) {
	if (point.getX() < 0 || point.getY() < 0)
		return;
	
	std::vector<Vect2>::const_iterator cit;
	for (cit = this->list.begin(); cit != this->list.end(); cit++){
		if (point == *cit){
			return ;
		}
	}
	this->list.push_back(point);
}

void Graph::print_graph() const {
	Vect2	table = this->size;
	int row = static_cast<int>(table.getY());
	int column = static_cast<int>(table.getX());
	std::vector<Vect2>::const_iterator cit;
	Vect2	p_aux;
	
	for (; row > -1; row--) {
		std::cout << ">& " << row << " ";
		for (int c = 0; c <= column; c++){
			p_aux = Vect2(c, row);
			for (cit = this->list.begin(); cit != this->list.end(); cit++){
				if (*cit == p_aux){
					std::cout << "X ";
					break;
				}
			}
			if (cit == this->list.end())
				std::cout << ". ";
		}
		std::cout << std::endl;
	}
	std::cout << ">&   ";
	for (int i = 0; i <= column; i++){
		std::cout << i << " "; 
	}
	std::cout << std::endl;
}
