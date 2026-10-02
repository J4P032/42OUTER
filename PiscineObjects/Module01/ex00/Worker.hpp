/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:51:00 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/02 12:46:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_HPP
# define WORKER_HPP

# include "Position.hpp"
# include "Statistic.hpp"
# include "Tool.hpp"
# include <iostream>
# include <vector>

class Shovel;

class Worker {
private:
	Position			coordonnee;
	Statistic			stat;
	static size_t		id_counter;
	size_t				id;
	std::vector<Tool*>	tools;
	
public:
	Worker();
	Worker(Position pos, Statistic stat);
	Worker(const Worker& other);
	Worker& operator=(const Worker& other);
	~Worker();

	void	addTool(Tool* tool);
	void	removeTool(Tool* tool);
	size_t	getName() const;
	void	work() const;

	friend	std::ostream& operator<<(std::ostream& out, const Worker& w);
};

#endif
