/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Workshop.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:11:26 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/06 17:47:30 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKSHOP_HPP
# define WORKSHOP_HPP

# include "Worker.hpp"
# include "Tool.hpp"
# include <set>

class Workshop {
private:
	size_t					id;
	static size_t			id_counter;
	std::set<Worker*>		workers;
	friend struct			Garbage;

public:
	Workshop(void);
	Workshop(const Workshop& other);
	Workshop& operator=(const Workshop& other);
	
	void	signIn(Worker& worker);
	void	leave(Worker& worker);
	void	executeWorkDay() const;
};


#endif
