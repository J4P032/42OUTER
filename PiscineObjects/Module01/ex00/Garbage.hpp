/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Garbage.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 13:00:01 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/02 14:16:15 by jrollon-         ###   ########.fr       */
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
	Worker*		newWorker();
	Tool*		newHammer();
	Tool*		newShovel();
	void		cleanAll();
};

extern Garbage G; //we make it global

#endif