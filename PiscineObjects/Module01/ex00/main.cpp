/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:57:39 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/03 17:56:08 by jrollon-         ###   ########.fr       */
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

void run(void) {
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
}

int	main(void) {
	try{
		run();
	} catch (const std::exception& e){
		std::cout << RED"Error: " << e.what() << RESET << std::endl;
	}

	return 0;
}



/* Todo:
	✅
*/
