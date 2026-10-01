/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hammer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 13:04:25 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/01 16:05:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Hammer.hpp"

size_t Hammer::id_counter = 0;

Hammer::Hammer() : id(id_counter++), numberOfUses(0) {
	std::cout << GREEN"[🔨" << id << "] created." << RESET << std::endl;
}

Hammer::Hammer(const Hammer& other) : id(id_counter++), numberOfUses(other.numberOfUses), worker_assigned(NULL) {
	std::cout << GREEN"[🔨" << id << "] cloned from other. But not assigned to anyone" << RESET << std::endl;	
}

Hammer& Hammer::operator=(const Hammer& other) {
	if (this != &other){
		if (worker_assigned)
			worker_assigned->removeTool(this);
		numberOfUses = other.numberOfUses;
	}
	std::cout << YELLOW"[🔨" << id << "] copied from other. But not assigned to anyone" << RESET << std::endl;	
	return *this;
}

Hammer::~Hammer() {
	if (worker_assigned){ worker_assigned->removeTool(this); }
	std::cout << RED"[🔨" << id << "] destroyed." << RESET << std::endl;	
}




/////////////////////////////////////
////////////// METHODS //////////////
/////////////////////////////////////

void	Hammer::liberateTool(void) {
	if (worker_assigned){
		Worker* temp = worker_assigned;
		worker_assigned = NULL;
		std::cout << CYAN"[🔨" << id << "] was liberated." << RESET << std::endl;
		temp->removeTool(this);
	}
}

void	Hammer::use(Worker* w) {
	if (!w)
		return;
	//1. take hammer from worker if have it.
	if (worker_assigned){ worker_assigned->removeTool(this); }
	//2.Give the hammer to the new worker
	worker_assigned = w;
	w->addTool(this);
	//3.print and increase use.
	numberOfUses++;
	std::cout << CYAN"[🔨" << id << "] used by [👷" << w->getName() << "]. Num of uses: " << numberOfUses << RESET << std::endl;
}

size_t	Hammer::getid() const { return id; }

void Hammer::stream_insert(std::ostream& out) const {
	out << BLUE"[🔨" << id << "]";
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