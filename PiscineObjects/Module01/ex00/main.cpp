/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:57:39 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/02 16:39:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Garbage.hpp"
#include "Worker.hpp"
#include "Shovel.hpp"
#include "Hammer.hpp"
#include "Workshop.hpp"
#include <cstdlib>

void	clearScreen() {
	#if defined(_WIN32)
		std::system("cls");
	#else
		std::system("clear");
	#endif
}

int main(void) {
	clearScreen();
	Workshop* workshop0 = G.newWorkshop();
	(void)workshop0;

	
	std::cout << std::endl << "###### WORKERS and TOOLS CREATION ######" << std::endl;
	Worker*	worker0 = G.newWorker();
	Tool* hammer0 = G.newHammer();
	Tool* hammer1 = G.newHammer();
	std::cout << *worker0 << std::endl;
	std::cout << *hammer0 << std::endl;
	std::cout << *hammer1 << std::endl;
	
	std::cout << std::endl << "###### USE of TOOLS ######" << std::endl;
	hammer0->use(worker0);
	hammer1->use(worker0);
	std::cout << *worker0 << std::endl;
	std::cout << *hammer0 << std::endl;
	std::cout << *hammer1 << std::endl;


	std::cout << std::endl << "###### LIBERATION OF TOOL ######" << std::endl;
	hammer0->liberateTool();
	std::cout << *worker0 << std::endl;
	std::cout << *hammer0 << std::endl;
	std::cout << *hammer1 << std::endl;
	
	std::cout << std::endl << "###### OTHER WORKER TAKES worker0 TOOL ######" << std::endl;
	Worker* worker1 = G.newWorker();
	hammer1->use(worker1);
	std::cout << *worker0 << std::endl;
	std::cout << *worker1 << std::endl;
	std::cout << *hammer0 << std::endl;
	std::cout << *hammer1 << std::endl;

	G.cleanAll();
	return 0;
}

/* Todo:
	✅1. In case of deletion of the Worker, the Shovel must not be destroyed
		debo poner el Worker*	worker_assigned; a NULL
	✅2. Each tool must have a number of uses and a use method that indicates what tool it is.

	✅3. si delete herramienta, he de eliminarla del trabajador si esta asignada.
*/
