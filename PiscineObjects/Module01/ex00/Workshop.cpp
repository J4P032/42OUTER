/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Workshop.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 18:15:46 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/06 18:30:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Garbage.hpp"
#include "Workshop.hpp"
#include <algorithm>


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

void	Workshop::signIn(Worker& worker) {
	workers.insert(&worker);
	std::vector<Workshop*>::const_iterator cit;
	cit = std::find(worker.workshops.begin(), worker.workshops.end(), this);
	if (cit == worker.workshops.end()) {
		worker.workshops.push_back(this);
	}
	std::cout << CYAN"[👷" << worker.getName() << "] is registered in [🏗️" << id << "]" << RESET << std::endl; ;
}

void	Workshop::leave(Worker& worker) {
	workers.erase(&worker);
	std::vector<Workshop*>::iterator it;
	it = std::find(worker.workshops.begin(), worker.workshops.end(), this);
	if (it != worker.workshops.end()) {
		worker.workshops.erase(it);
	}
	std::cout << CYAN"[👷" << worker.getName() << "] leaves [🏗️" << id << "]" << RESET << std::endl; ;
}

void	Workshop::executeWorkDay() const{
	std::set<Worker*>::const_iterator cit = workers.begin();
	for (; cit != workers.end(); cit++) {
		(*cit)->work();
	}
	
}
