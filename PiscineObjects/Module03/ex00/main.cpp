/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 11:46:43 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/13 17:36:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "car.hpp"

int	main() {
	Car coche0;
	Car coche1;
	coche1.set_id(1);
	std::cout << coche0 << std::endl;
	coche1.accelerate(78);
	std::cout << coche1 << std::endl;
	return 0;
}
