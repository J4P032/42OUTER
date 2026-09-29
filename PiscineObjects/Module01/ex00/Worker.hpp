/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:51:00 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/29 18:44:51 by jrollon-         ###   ########.fr       */
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

	std::vector<Tool*>& getTools() { return tools; }

	void	addTools(Tool* tool) { tools.push_back(tool); }

	const std::string&	getName() const { return name; } 
	
	friend	std::ostream& operator<<(std::ostream& out, const Worker& w) {
		out << w.name << ": [coord]: " << w.coordonnee << " [stat]: " << w.stat;
		return out;
	} 
};


#endif
