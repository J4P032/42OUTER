/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shovel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 13:59:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 11:59:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOVEL_HPP
# define SHOVEL_HPP

# include "Tool.hpp"
# include "Worker.hpp"


struct Shovel : public Tool {
private:
	size_t	numberOfUses;
	Worker*	worker_assigned;
	

public:
	Shovel() : numberOfUses(0) {
		std::cout << GREEN"[🪏] created." << RESET << std::endl;
		
	}
	Shovel(const Shovel& other) : numberOfUses(other.numberOfUses), worker_assigned(NULL) {
		std::cout << GREEN"[🪏] cloned from other. But not assigned to anyone" << RESET << std::endl;	
	}
	Shovel& operator=(const Shovel& other) {
		if (this != &other){
			numberOfUses = other.numberOfUses;
		}
		std::cout << YELLOW"[🪏] copied from other. But not assigned to anyone" << RESET << std::endl;	
		return *this;
	}
	~Shovel() {
		std::cout << RED"[🔨] destroyed." << RESET << std::endl;	
		if (worker_assigned){ worker_assigned->removeTool(this); }
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
		std::cout << "[🪏] used by " << w->getName() << ". Num of uses: " << numberOfUses << std::endl;
	}
};

#endif
