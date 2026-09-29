/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Position.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:44:02 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/29 12:17:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSITION_HPP
# define POSITION_HPP

#include <iostream>

struct Position {
private:	
	int	x;
	int	y;
	int z;

public:
	Position(void) : x(0), y(0), z(0) {}
	Position(int x, int y, int z) : x(x), y(y), z(z) {}
	
	friend std::ostream& operator<<(std::ostream& out, const Position& o) {
		out << "x: " << o.x << " y: " << o.y << " z: " << o.z;
		return out;
	}
	
};

#endif
