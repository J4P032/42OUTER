/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hammer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:26:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 12:01:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HAMMER_HPP
# define HAMMER_HPP

# include "Tool.hpp"
# include "Worker.hpp"

class Hammer : public Tool{
private:
	size_t	numberOfUses;
	Worker*	worker_assigned;
	
	Hammer() : numberOfUses(0) {
		std::cout << GREEN"[🔨] created." << RESET << std::endl;
	}
	Hammer(const Hammer& other) : numberOfUses(other.numberOfUses), worker_assigned(NULL) {
		std::cout << GREEN"[🔨] cloned from other. But not assigned to anyone" << RESET << std::endl;	
	}
	Hammer& operator=(const Hammer& other) {
		if (this != &other){
			numberOfUses = other.numberOfUses;
		}
		std::cout << YELLOW"[🔨] copied from other. But not assigned to anyone" << RESET << std::endl;	

		return *this;
	}
	~Hammer() {
		std::cout << RED"[🔨] destroyed." << RESET << std::endl;	
		if (worker_assigned){ worker_assigned->removeTool(this); }
	}

	void	use(Worker* w) {
		if (!w)
			return;
		
		//1. take hammer from worker if have it.
		if (worker_assigned){ worker_assigned->removeTool(this); }
		
		//2.Give the hammer to the new worker
		worker_assigned = w;
		w->addTool(this);
		
		//3.print and increase use.
		numberOfUses++;
		std::cout << "[🔨] used by " << w->getName() << ". Num of uses: " << numberOfUses << std::endl;
	}
};

#endif
