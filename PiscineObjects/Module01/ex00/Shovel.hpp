/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shovel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 13:59:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/29 18:43:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOVEL_HPP
# define SHOVEL_HPP

# include <iostream>
# include "Tool.hpp"
# include "Worker.hpp"
# include <vector>
# include <algorithm>

struct Shovel : public Tool {
private:
	size_t	numberOfUses;
	Worker*	worker_assigned;
	

public:
	Shovel() : numberOfUses(0) {}
	Shovel(const Shovel& other) : numberOfUses(other.numberOfUses), worker_assigned(NULL) {}
	Shovel& operator=(const Shovel& other) {
		if (this != &other){
			numberOfUses = other.numberOfUses;
		}
		return *this;
	}
	~Shovel() {}

	void	use(Worker* w) {
		if (!w)
			return;
		if (worker_assigned){
			std::vector<Tool*>& tools = worker_assigned->getTools();
			std::vector<Tool*>::iterator it;
			it = std::find(tools.begin(), tools.end(), this);
			if (it != tools.end()){
				tools.erase(it);
			}
		}
		worker_assigned = w;
		w->addTools(this);
		numberOfUses++;
		std::cout << "[shovel] used by " << w->getName() << std::endl;
	}
};


#endif
