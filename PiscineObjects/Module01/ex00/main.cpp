/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:57:39 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 15:23:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Worker.hpp"
#include "Shovel.hpp"
#include "Hammer.hpp"
#include <cstdlib>

void	clearScreen() {
	#if defined(_WIN32)
		std::system("cls");
	#else
		std::system("clear");
	#endif
}


int	main(void) {
	clearScreen();
	Worker	w1((Position(1,2,3)), (Statistic()));
	Worker	w2;
	std::cout << w1 << std::endl;
	Tool* s1 = new Shovel();
	Tool* h1 = new Hammer();
	s1->use(&w1);
	h1->use(&w1);
	
	w1 = w2;

	delete s1; delete h1;
	
	return 0;
}

/* Todo:
	1. In case of deletion of the Worker, the Shovel must not be destroyed
		debo poner el Worker*	worker_assigned; a NULL
	✅2. Each tool must have a number of uses and a use method that indicates what tool it is.

*/
