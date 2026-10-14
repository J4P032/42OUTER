/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 11:46:43 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 15:39:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "car.hpp"


void	clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

void run() {
	clearScreen();
	Car coche0;
	std::cout << coche0 << std::endl;
	coche0.start();
	coche0.apply_force_on_brakes(0);
	coche0.accelerate(78);
	coche0.turn_wheel(-190);
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
