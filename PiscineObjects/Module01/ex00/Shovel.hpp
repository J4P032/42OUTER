/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shovel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 13:59:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/29 15:13:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOVEL_HPP
# define SHOVEL_HPP

# include <iostream>
# include "Tool.hpp"
# include "Worker.hpp"

struct Shovel : public Tool {
private:
	Worker*	worker_assigned;
	size_t	numberOfUses;

public:
	Shovel() : numberOfUses(0) {}
	Shovel(const Shovel& other) : numberOfUses(other.numberOfUses) {}
	Shovel& operator=(const Shovel& other) {
		if (this != &other){
			numberOfUses = other.numberOfUses;
		}
		return *this;
	}
	~Shovel() {}

	void	use() {
		numberOfUses++;
	}

};


#endif
