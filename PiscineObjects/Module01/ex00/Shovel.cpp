/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shovel.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 14:34:56 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/01 16:04:57 by jrollon-         ###   ########.fr       */
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
	if (worker_assigned){ worker_assigned->removeTool(this); }
	std::cout << RED"[🪏 " << id << "] destroyed." << RESET << std::endl;	
}


/////////////////////////////////////
////////////// METHODS //////////////
/////////////////////////////////////


void	Shovel::liberateTool(void) {
	if (worker_assigned){
		Worker* temp = worker_assigned;
		worker_assigned = NULL;
		std::cout << CYAN"[🪏 " << id << "] was liberated." << RESET << std::endl;
		temp->removeTool(this);
	}
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
	std::cout << CYAN"[🪏 " << id << "] used by [👷" << w->getName() << "]. Num of uses: " << numberOfUses << RESET << std::endl;
}

size_t	Shovel::getid() const { return id; }

void	Shovel::stream_insert(std::ostream& out) const {
	out << BLUE"[🪏 " << id << "]";
	switch (numberOfUses){
		case 0:
			out << " never used.";
			break;
		case 1:
			out << " used once.";
			break;
		case 2:
			out << " used twice.";
			break;
		default:
			out << " used " << numberOfUses << " times.";
			break;
	}
	out << " Now used by ";
	if (worker_assigned) {
		out << "[👷" << worker_assigned->getName() << "]" << RESET;
	} else {
		out << "nobody" << RESET;
	}
}
