/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Workshop.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 18:15:46 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/02 13:42:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Garbage.hpp"
#include "Workshop.hpp"

size_t Workshop::id_counter = 0;

Workshop::Workshop(void) : id(id_counter++){
	std::cout << GREEN"[🏗️" << id << "] created." << RESET << std::endl;
}

Workshop::Workshop(const Workshop& other) : id(id_counter++), workers(other.workers){
	std::cout << GREEN"[🏗️" << id << "] cloned from [🏗️" << other.id << "]." << RESET << std::endl;	
}

Workshop& Workshop::operator=(const Workshop& other){
	if (this != &other){
		workers = other.workers;
	}
	return (*this);
}




void	Workshop::signIn(const Worker& worker) {(void)worker;}

void	Workshop::leave(const Worker& worker) {(void)worker;}
