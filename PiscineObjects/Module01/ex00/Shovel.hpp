/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shovel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 13:59:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 15:20:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOVEL_HPP
# define SHOVEL_HPP

# include "Tool.hpp"
# include "Worker.hpp"


struct Shovel : public Tool {
private:
	size_t			id;
	static size_t	id_counter;
	size_t			numberOfUses;
	Worker*			worker_assigned;
	

public:
	Shovel() :  id(id_counter++), numberOfUses(0) {
		std::cout << GREEN"[🪏 " << id << "] created." << RESET << std::endl;
	}
	Shovel(const Shovel& other) : id(id_counter++), numberOfUses(other.numberOfUses), worker_assigned(NULL) {
		std::cout << GREEN"[🪏 " << id << "] cloned from other. But not assigned to anyone" << RESET << std::endl;	
	}
	Shovel& operator=(const Shovel& other) {
		if (this != &other){
			if (worker_assigned)
				worker_assigned->removeTool(this);
			numberOfUses = other.numberOfUses;
		}
		std::cout << YELLOW"[🪏 " << id << "] copied from other. But not assigned to anyone" << RESET << std::endl;	
		return *this;
	}
	~Shovel() {
		std::cout << RED"[🪏 " << id << "] destroyed." << RESET << std::endl;	
		if (worker_assigned){ worker_assigned->removeTool(this); }
	}

	void	liberateTool(void) {
		worker_assigned = NULL;
		std::cout << CYAN"[🪏 " << id << "] liberated." << RESET << std::endl;
	}

	void	use(Worker* w) {
		if (!w)
			return;
		
		//1.Revove tool from previous worker
		if (worker_assigned){ worker_assigned->removeTool(this); }
		
		//2.Give the shovel to the new worker
		worker_assigned = w;
		w->addTool(this);
		
		//3.print and increase use.
		numberOfUses++;
		std::cout << "[🪏 " << id << "] used by Worker" << w->getName() << ". Num of uses: " << numberOfUses << std::endl;
	}
};

#endif
