/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Worker.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:51:00 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/29 12:18:45 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKER_HPP
# define WORKER_HPP

# include "Position.hpp"
# include "Statistic.hpp"
# include <iostream>

class Worker {
private:
	Position	coordonnee;
	Statistic	stat;
	
public:
	Worker(){}
	Worker(Position pos, Statistic stat) : coordonnee(pos), stat(stat) {}

	friend	std::ostream& operator<<(std::ostream& out, const Worker& w) {
		out << "[coord]: " << w.coordonnee << " [stat]: " << w.stat;
		return out;
	} 
};


#endif
