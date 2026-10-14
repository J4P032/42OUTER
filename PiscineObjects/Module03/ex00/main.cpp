/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 11:46:43 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 10:53:24 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "car.hpp"
#include <cstdlib>

void	clearScreen() {
	#if defined(_WIN32)
		std::system("cls");
	#else
		std::system("clear");
	#endif
}


void run() {
	clearScreen();
	Car coche0;
	std::cout << coche0 << std::endl;
	coche0.start();
	coche0.apply_force_on_brakes(0);
	coche0.accelerate(78);
	std::cout << coche0 << std::endl;
	
}


int	main() {
	try{
		run();
	}
	catch (const std::exception& e){
		std::cout << e.what() << std::endl;
	}
	return 0;
}
