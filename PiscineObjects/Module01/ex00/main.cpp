/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:57:39 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 11:12:30 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Worker.hpp"

int	main(void) {
	Worker	t1((Position(1,2,3)), (Statistic()), "Manolo");
	std::cout << t1 << std::endl;

	return 0;
}

/* Todo:
	1. In case of deletion of the Worker, the Shovel must not be destroyed
	2. Each tool must have a number of uses and a use method that indicates what tool it is.

*/
