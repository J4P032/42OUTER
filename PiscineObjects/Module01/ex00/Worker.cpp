/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:57:06 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 17:52:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Worker.hpp"
#include "Shovel.hpp"

size_t Worker::id_counter = 0;

Worker::Worker() : coordonnee(Position()), stat(Statistic()), id(id_counter++) {
	std::cout << GREEN"[👷" << id << "] created." << RESET << std::endl;
}

Worker::Worker(Position pos, Statistic stat) : coordonnee(pos), stat(stat), id(id_counter++) {
	std::cout << GREEN"[👷" << id << "] created." << RESET << std::endl;
}

Worker::Worker(const Worker& other) : coordonnee(other.coordonnee), stat(other.stat), id(id_counter++) {
	std::cout << GREEN"[👷" << id << "] cloned from other" << RESET << std::endl;	
}

Worker& Worker::operator=(const Worker& other) {
	if (this != &other){
		//1.clean tools before copy
		std::vector<Tool*>::iterator it = tools.begin();
		for (; it != tools.end(); it++){
			if (*it){
				(*it)->liberateTool();
			}
		}
		tools.clear();
		//2.copy
		coordonnee = other.coordonnee;
		stat = other.stat;
	}
	std::cout << YELLOW"[👷" << id << "] copied from other." << RESET << std::endl;	
	return *this;
}

Worker::~Worker(){
	std::vector<Tool*>::iterator it = tools.begin();
	for (; it != tools.end(); it++){
		if (*it)
		(*it)->liberateTool(); //tool is unassigned
	}	
	std::cout << RED"[👷" << id << "] destroyed." << RESET << std::endl;
}

/////////////////////////////////////
////////////// METHODS //////////////
/////////////////////////////////////

void	Worker::addTool(Tool* tool) { 
	tools.push_back(tool);
	std::cout << GREEN"[👷" << id << "] uses ";
	if (dynamic_cast<Shovel*>(tool)){
		std::cout << "[🪏 " << id << "]" << std::endl;
	} else {
		std::cout << "[🔨" << id << "]" << std::endl;
	}
}

void	Worker::removeTool(Tool* tool) {
	if (!tool)
		return;
	std::vector<Tool*>::iterator it;
	it = std::find(tools.begin(), tools.end(), tool);
	if (it != tools.end()){
		tools.erase(it);
		tool->liberateTool();
	}
}

size_t	Worker::getName() const { return id; }

void	Worker::work() const{}

std::ostream& operator<<(std::ostream& out, const Worker& w) {
	out << "worker" << w.id << ": " << BLUE "[coord]: " << w.coordonnee << MAGENTA" [stat]: " <<  w.stat << RESET;
	return out;
} 
