/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:57:39 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/02 14:17:30 by jrollon-         ###   ########.fr       */
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
	Workshop* B0 = G.newWorkshop();
	(void)B0;	

	Worker	w0;
	Tool* h0 = new Hammer();
	Tool* h1 = new Hammer();
	
	h0->use(&w0);
	h1->use(&w0);
	std::cout << w0 << std::endl;
	h0->liberateTool();
	std::cout << w0 << std::endl;
	
	G.cleanAll();
	
	
	delete h0;
	delete h1;
	h0 = NULL;
	h1 = NULL;
	return 0;
}

/* int	main(void) {
	clearScreen();
	Worker	w0((Position(1,2,3)), (Statistic()));
	Worker	w1;
	std::cout << w0 << std::endl;
	Tool* s0 = new Shovel();
	Tool* h0 = new Hammer();
	s0->use(&w0);
	h0->use(&w0);
	
	{
		std::cout << std::endl;
		std::cout << "REMOVE OF A WORKER TEST" << std::endl;
		std::cout << w0 << std::endl;
		Worker w2;
		std::cout << w2 << std::endl;
		if (h0)
			std::cout << *h0 << std::endl;
		
		h0->use(&w2);
		std::cout << w0 << std::endl;
		std::cout << w2 << std::endl;
		std::cout << "END of REMOVE OF A WORKER TEST" << std::endl;
		std::cout << std::endl;
	}
	
	std::cout << w0 << std::endl;
	
	
	if (s0)
		std::cout << *s0 << std::endl;
	if (h0)
		std::cout << *h0 << std::endl;
	
	std::cout << w0 << std:: endl;
	
	
	
	h0->liberateTool();

	if (h0)
		std::cout << *h0 << std::endl;

	std::cout << w0 << std:: endl;

	
	std::cout << w1 << std:: endl;
	
	w0 = w1;
	
	std::cout << w0 << std:: endl;
	

	delete s0; 
	delete h0;
	
	return 0;
} */

/* Todo:
	✅1. In case of deletion of the Worker, the Shovel must not be destroyed
		debo poner el Worker*	worker_assigned; a NULL
	✅2. Each tool must have a number of uses and a use method that indicates what tool it is.

	✅3. si delete herramienta, he de eliminarla del trabajador si esta asignada.
*/
