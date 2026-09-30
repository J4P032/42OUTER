/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:51:00 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 15:16:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_HPP
# define WORKER_HPP

# include "Position.hpp"
# include "Statistic.hpp"
# include "Tool.hpp"
# include <iostream>
# include <vector>

class Worker {
private:
	Position			coordonnee;
	Statistic			stat;
	static size_t		id_counter;
	size_t				id;
	std::vector<Tool*>	tools;
	
public:
	Worker() : coordonnee(Position()), stat(Statistic()), id(id_counter++) {
		std::cout << GREEN"[👷" << id << "] created." << RESET << std::endl;
	}
	Worker(Position pos, Statistic stat) : coordonnee(pos), stat(stat), id(id_counter++) {
		std::cout << GREEN"[👷" << id << "] created." << RESET << std::endl;
	}
	Worker(const Worker& other) : coordonnee(other.coordonnee), stat(other.stat), id(id_counter++) {
		std::cout << GREEN"[👷" << id << "] cloned from other" << RESET << std::endl;	
	}
	Worker& operator=(const Worker& other) {
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
	~Worker(){
		std::cout << RED"[👷" << id << "] destroyed." << RESET << std::endl;
		std::vector<Tool*>::iterator it = tools.begin();
		for (; it != tools.end(); it++){
			if (*it)
				(*it)->liberateTool(); //tool is unassigned
		}	
	}

	void	addTool(Tool* tool) { tools.push_back(tool); }

	void	removeTool(Tool* tool) {
		if (!tool)
			return;
		std::vector<Tool*>::iterator it;
		it = std::find(tools.begin(), tools.end(), tool);
		if (it != tools.end()){
			tools.erase(it);
			tool->liberateTool();
		}
	}

	size_t	getName() const { return id; } 
	
	friend	std::ostream& operator<<(std::ostream& out, const Worker& w) {
		out << "worker" << w.id << ": " << BLUE "[coord]: " << w.coordonnee << MAGENTA" [stat]: " <<  w.stat << RESET;
		return out;
	} 
};

#endif
