/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 16:24:36 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 18:15:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"
#include "thuesdayDiscount.hpp"

void run() {
	Command c0;
	ThuesdayDiscount c1("manolo", "hoy");
	c1.add("patatas", 50.0f, 1);
	c1.add("tomates", 50.0f, 1);
	std::cout << c0 << std::endl;
	std::cout << c1 << std::endl;
	std::cout << "precio total: " << c1.get_total_price() << std::endl;

}



int main() {
	try {
		run();
	}
	catch (const std::exception& e){
		std::cout << e.what() << std::endl; 
	}
	return 0;
}
