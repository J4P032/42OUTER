/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:51:00 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 11:53:14 by jrollon-         ###   ########.fr       */
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
	std::string			name;
	std::vector<Tool*>	tools;
	
public:
	Worker() : name("Bob") {}
	Worker(Position pos, Statistic stat, std::string name) : coordonnee(pos), stat(stat), name(name) {}
	Worker(const Worker& other) : coordonnee(other.coordonnee), stat(other.stat), name(other.name) {}
	Worker& operator=(const Worker& other) {
		if (this != &other){
			coordonnee = other.coordonnee;
			stat = other.stat;
			name = other.name;
		}
		return *this;
	}
	~Worker(){}

	void	addTool(Tool* tool) { tools.push_back(tool); }

	void	removeTool(Tool* tool) {
		if (!tool)
			return;
		std::vector<Tool*>::iterator it;
		it = std::find(tools.begin(), tools.end(), tool);
		if (it != tools.end()){ tools.erase(it); }
	}

	const std::string&	getName() const { return name; } 
	
	friend	std::ostream& operator<<(std::ostream& out, const Worker& w) {
		out << w.name << ": [coord]: " << w.coordonnee << " [stat]: " << w.stat;
		return out;
	} 
};

#endif
