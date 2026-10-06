/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Garbage.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 13:00:01 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/06 11:10:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_HPP
# define GARBAGE_HPP
# include <set> //avoid double data.
# include "Workshop.hpp"
# include "Worker.hpp"
# include "Tool.hpp"
# include "Hammer.hpp"
# include "Shovel.hpp"

struct Garbage{
	std::set<Workshop*>	workshops;
	std::set<Worker*>	workers;
	std::set<Tool*>		tools;

	Garbage(void);
	~Garbage(void);

	Workshop*	newWorkshop();
	Workshop*	newWorkshop(const Workshop& other);
	Worker*		newWorker();
	Worker*		newWorker(const Worker& other);
	Tool*		newHammer();
	Tool*		newHammer(const Tool& other);
	Tool*		newShovel();
	Tool*		newShovel(const Tool& other);
	
	void		cleanAll();
};

extern Garbage G; //we make it global

#endif
