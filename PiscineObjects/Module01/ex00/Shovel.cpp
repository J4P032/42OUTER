/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shovel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 14:34:56 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 17:59:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shovel.hpp"

size_t Shovel::id_counter = 0;

Shovel::Shovel() :  id(id_counter++), numberOfUses(0) {
	std::cout << GREEN"[🪏 " << id << "] created." << RESET << std::endl;
}

Shovel::Shovel(const Shovel& other) : id(id_counter++), numberOfUses(other.numberOfUses), worker_assigned(NULL) {
	std::cout << GREEN"[🪏 " << id << "] cloned from other. But not assigned to anyone" << RESET << std::endl;	
}

Shovel& Shovel::operator=(const Shovel& other) {
	if (this != &other){
		if (worker_assigned)
			worker_assigned->removeTool(this);
		numberOfUses = other.numberOfUses;
	}
	std::cout << YELLOW"[🪏 " << id << "] copied from other. But not assigned to anyone" << RESET << std::endl;	
	return *this;
}

Shovel::~Shovel() {
	std::cout << RED"[🪏 " << id << "] destroyed." << RESET << std::endl;	
	if (worker_assigned){ worker_assigned->removeTool(this); }
}


/////////////////////////////////////
////////////// METHODS //////////////
/////////////////////////////////////


void	Shovel::liberateTool(void) {
	worker_assigned = NULL;
	std::cout << CYAN"[🪏 " << id << "] liberated." << RESET << std::endl;
}

void	Shovel::use(Worker* w) {
	if (!w)
		return;
	//1.Revove tool from previous worker
	if (worker_assigned){ worker_assigned->removeTool(this); }
	//2.Give the shovel to the new worker
	worker_assigned = w;
	w->addTool(this);
	//3.print and increase use.
	numberOfUses++;
	std::cout << "[🪏 " << id << "] used by Worker" << w->getName() << ". Num of uses: " << numberOfUses << std::endl;
}

size_t	Shovel::getid() const { return id; }
