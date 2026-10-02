/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Garbage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 13:17:23 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/02 16:10:19 by jrollon-         ###   ########.fr       */
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

Workshop*	Garbage::newWorkshop(const Workshop& other){
	Workshop* aux = new Workshop(other);
	workshops.insert(aux);
	return aux;
}

Worker*		Garbage::newWorker(){
	Worker* aux = new Worker();
	workers.insert(aux);
	return aux;
}

Worker*		Garbage::newWorker(const Worker& other){
	Worker* aux = new Worker(other);
	workers.insert(aux);
	return aux;
}

Tool*		Garbage::newHammer(){
	Tool*	aux = new Hammer();
	tools.insert(aux);
	return aux;
}

Tool*		Garbage::newHammer(const Tool& other){
	if (dynamic_cast<const Hammer*>(&other)){
		Tool*	aux = new Hammer(static_cast<const Hammer&>(other));
		tools.insert(aux);
		return aux;
	}
	return NULL;
}

Tool*		Garbage::newShovel(){
	Tool*	aux = new Shovel();
	tools.insert(aux);
	return aux;
}

Tool*		Garbage::newShovel(const Tool& other){
	if (dynamic_cast<const Shovel*>(&other)){
		Tool*	aux = new Shovel(static_cast<const Shovel&>(other));
		tools.insert(aux);
		return aux;
	}
	return NULL;
}

void		Garbage::cleanAll(){
	std::set<Workshop*>::iterator	s_it = workshops.begin();
	std::set<Worker*>::iterator		w_it = workers.begin();
	std::set<Tool*>::iterator		t_it = tools.begin();

	for (; s_it != workshops.end(); s_it++){
		delete *s_it;
	}

	for (; w_it != workers.end(); w_it++){
		delete *w_it;
	}

	for (; t_it != tools.end(); t_it++){
		delete *t_it;
	}
	
	workshops.clear();
}