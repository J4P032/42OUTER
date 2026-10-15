/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 16:24:36 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 11:25:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thuesdayDiscount.hpp"
#include "packageReductionDiscount.hpp"

void run() {
	Command c0("manolo", "hoy");
	c0.add("patatas", 50.0f, 1);
	c0.add("tomates", 101.0f, 1);
	PackageReductionDiscountCommand c1(c0);
	ThuesdayDiscountCommand c2(c1);
	std::cout << c0 << std::endl;
	std::cout << "precio total: " << c2.get_total_price() << std::endl;
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
