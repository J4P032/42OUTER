/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hammer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:26:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 15:20:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HAMMER_HPP
# define HAMMER_HPP

# include "Tool.hpp"
# include "Worker.hpp"

class Hammer : public Tool{
private:
	size_t			id;
	static size_t	id_counter;
	size_t			numberOfUses;
	Worker*			worker_assigned;

public:
	Hammer() : id(id_counter++), numberOfUses(0) {
		std::cout << GREEN"[🔨" << id << "] created." << RESET << std::endl;
	}
	Hammer(const Hammer& other) : id(id_counter++), numberOfUses(other.numberOfUses), worker_assigned(NULL) {
		std::cout << GREEN"[🔨" << id << "] cloned from other. But not assigned to anyone" << RESET << std::endl;	
	}
	Hammer& operator=(const Hammer& other) {
		if (this != &other){
			if (worker_assigned)
				worker_assigned->removeTool(this);
			numberOfUses = other.numberOfUses;
		}
		std::cout << YELLOW"[🔨" << id << "] copied from other. But not assigned to anyone" << RESET << std::endl;	

		return *this;
	}
	~Hammer() {
		std::cout << RED"[🔨" << id << "] destroyed." << RESET << std::endl;	
		if (worker_assigned){ worker_assigned->removeTool(this); }
	}

	void	liberateTool(void) {
		worker_assigned = NULL;
		std::cout << CYAN"[🔨" << id << "] liberated." << RESET << std::endl;
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
		std::cout << "[🔨" << id << "] used by Worker" << w->getName() << ". Num of uses: " << numberOfUses << std::endl;
	}
};

#endif
