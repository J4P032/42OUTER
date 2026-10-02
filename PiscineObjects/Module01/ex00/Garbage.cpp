/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Garbage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 13:17:23 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/02 14:17:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Garbage.hpp"

Garbage G;

Garbage::Garbage(void){}

Garbage::~Garbage(void){}

Workshop*	Garbage::newWorkshop(){
	Workshop* aux = new Workshop();
	workshops.insert(aux);
	return aux;
}

Worker*		Garbage::newWorker(){
	Worker* aux = new Worker();
	workers.insert(aux);
	return aux;
}

Tool*		Garbage::newHammer(){
	Tool*	aux = new Hammer();
	tools.insert(aux);
	return aux;
}
	
Tool*		Garbage::newShovel(){
	Tool*	aux = new Shovel();
	tools.insert(aux);
	return aux;
}

void		Garbage::cleanAll(){
	std::set<Workshop*>::iterator s_it = workshops.begin();
	for (; s_it != workshops.end(); s_it++){
		delete *s_it;
	}
	workshops.clear();
}