/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:57:06 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/06 17:20:51 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Worker.hpp"
#include "Shovel.hpp"
#include <algorithm>

size_t Worker::id_counter = 0;

Worker::Worker() : coordonnee(Position()), stat(Statistic()), id(id_counter++) {
	std::cout << GREEN"[👷" << id << "] created." << RESET << std::endl;
}

Worker::Worker(Position pos, Statistic stat) : coordonnee(pos), stat(stat), id(id_counter++) {
	std::cout << GREEN"[👷" << id << "] created." << RESET << std::endl;
}

Worker::Worker(const Worker& other) : coordonnee(other.coordonnee), stat(other.stat), id(id_counter++) {
	std::cout << GREEN"[👷" << id << "] cloned from [👷" << other.id << "]." << RESET << std::endl;	
}

Worker& Worker::operator=(const Worker& other) {
	if (this != &other){
		//1.clean tools before copy
		while (!tools.empty()){
			Tool* tool = tools.back();
			tools.pop_back();
			if (tool)
				tool->liberateTool();
		}
		while (!workshops.empty()) {
			Workshop* ws = workshops.back();
			workshops.pop_back();
			if (ws)
				ws->leave(*this);
		}
		//2.copy
		coordonnee = other.coordonnee;
		stat = other.stat;
	}
	std::cout << YELLOW"[👷" << id << "] copied from [👷" << other.id << "]." << RESET << std::endl;	
	return *this;
}

Worker::~Worker(){
	while (!tools.empty()){
		Tool* tool = tools.back();
		tools.pop_back();
		if (tool) {
			tool->liberateTool();
		}
	}
	while (!workshops.empty()) {
		Workshop* ws = workshops.back();
		workshops.pop_back();
		if (ws)
			ws->leave(*this);
	}	
	std::cout << RED"[👷" << id << "] destroyed." << RESET << std::endl;
}

/////////////////////////////////////
////////////// METHODS //////////////
/////////////////////////////////////

void	Worker::addTool(Tool* tool) { 
	if (!tool){
		throw std::runtime_error("Worker cannot take a NULL tool");
	}
	
	std::vector<Tool*>::iterator it;
	it = std::find(tools.begin(), tools.end(), tool);
	if (it == tools.end()) {
		tools.push_back(tool);
		std::cout << CYAN"[👷" << id << "] takes ";
		if (dynamic_cast<Shovel*>(tool)){
			std::cout << "[🪏 " << tool->getid() << "]" << RESET << std::endl;
		} else {
			std::cout << "[🔨" << tool->getid() << "]" << RESET << std::endl;
		}
	}
}

void	Worker::removeTool(Tool* tool) {
	if (!tool){
		throw std::runtime_error("Worker cannot remove a NULL tool");
	}
	std::vector<Tool*>::iterator it;
	it = std::find(tools.begin(), tools.end(), tool);
	if (it != tools.end()){
		tools.erase(it);
		std::cout << CYAN"[👷" << id << "] leaves ";
		if (dynamic_cast<Shovel*>(tool)){
			std::cout << "[🪏 " << tool->getid() << "]";
		} else {
			std::cout << "[🔨" << tool->getid() << "]";;
		}
		std::cout << std::endl;
		tool->liberateTool();
	}
}

size_t	Worker::getName() const { return id; }


//private
void	Worker::work() {
	std::vector<Tool*>::const_iterator cit = tools.begin();
	for (; cit != tools.end(); cit++) {
		(*cit)->use(this);
	}
	
}

std::ostream& operator<<(std::ostream& out, const Worker& w) {
	out << "worker" << w.id << ": " << BLUE "[coord]: " << w.coordonnee << MAGENTA" [stat]: " <<  w.stat << RESET;
	std::vector<Tool*>::const_iterator cit = w.tools.begin();
	out << ". Has these Tools: ";
	for (; cit != w.tools.end(); cit++){
		if (dynamic_cast<Shovel*>(*cit)){
			out << "[🪏 ";
		} else {
			out << "[🔨";
		}
		out << (*cit)->getid() << "]";
		if (cit + 1 != w.tools.end()){
			out << ", "; 
		} else { out << "."; }
	}
	return out;
} 
