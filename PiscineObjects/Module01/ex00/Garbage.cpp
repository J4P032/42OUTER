/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Garbage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 13:17:23 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/03 17:52:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Garbage.hpp"

Garbage G;

Garbage::Garbage(void){}

Garbage::~Garbage(void){
	this->cleanAll();
}

Workshop*	Garbage::newWorkshop(){
	Workshop* aux = new Workshop(); //if fails automatically throw.
	try{
		workshops.insert(aux);
	} catch (...) {
		delete aux;
		throw std::runtime_error("cannot insert Workshop in Garage");
	}
	return aux;
}

Workshop*	Garbage::newWorkshop(const Workshop& other){
	Workshop* aux = new Workshop(other);
	try {
		workshops.insert(aux);
	} catch (...) {
		delete aux;
		throw std::runtime_error("cannot insert Workshop clone in Garage");
	}
	return aux;
}

Worker*		Garbage::newWorker(){
	Worker* aux = new Worker();
	try {
		workers.insert(aux);
	} catch (...) {
		delete aux;
		throw std::runtime_error("cannot insert Worker in Garage");
	}
	return aux;
}

Worker*		Garbage::newWorker(const Worker& other){
	Worker* aux = new Worker(other);
	try {
		workers.insert(aux);
	} catch (...) {
		delete aux;
		throw std::runtime_error("cannot insert Worker clone in Garage");
	}
	return aux;
}

Tool*		Garbage::newHammer(){
	Tool*	aux = new Hammer();
	try {
		tools.insert(aux);
	} catch (...) {
		delete aux;
		throw std::runtime_error("cannot insert Hammer in Garage");
	}
	return aux;
}

Tool*		Garbage::newHammer(const Tool& other){
	if (dynamic_cast<const Hammer*>(&other)){
		Tool*	aux = new Hammer(static_cast<const Hammer&>(other));
		try {
			tools.insert(aux);
		} catch (...) {
		delete aux;
		throw std::runtime_error("cannot insert Hammer clone in Garage");
	}
		return aux;
	}
	throw std::runtime_error("Cannot create a NULL Hammer*.");
}

Tool*		Garbage::newShovel(){
	Tool*	aux = new Shovel();
	try {
		tools.insert(aux);
	} catch (...) {
		delete aux;
		throw std::runtime_error("cannot insert Shovel in Garage");
	}
	return aux;
}

Tool*		Garbage::newShovel(const Tool& other){
	if (dynamic_cast<const Shovel*>(&other)){
		Tool*	aux = new Shovel(static_cast<const Shovel&>(other));
		try {
			tools.insert(aux);
		} catch (...) {
		delete aux;
		throw std::runtime_error("cannot insert Shovel clone in Garage");
	}
		return aux;
	}
	throw std::runtime_error("Cannot create a NULL Shovel*.");
}

void		Garbage::cleanAll(){
	std::set<Workshop*>::iterator	s_it = workshops.begin();
	std::set<Worker*>::iterator		w_it = workers.begin();
	std::set<Tool*>::iterator		t_it = tools.begin();

	for (; s_it != workshops.end(); s_it++){
		if (*s_it)
			delete *s_it;
	}

	for (; w_it != workers.end(); w_it++){
		if (*w_it)
			delete *w_it;
	}

	for (; t_it != tools.end(); t_it++){
		if (*t_it)
			delete *t_it;
	}
	
	workshops.clear();
	workers.clear();
	tools.clear();
}