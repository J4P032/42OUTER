/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 13:28:25 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 13:34:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECTANGLE_HPP
# define RECTANGLE_HPP

# include "shape.hpp"

class Rectangle : public Shape {
private:
	float	_side1;
	float	_side2;

public:
	Rectangle(float side1, float side2) : _side1(side1), _side2(side2) {}
	~Rectangle(){}

	float area() const {
		return (_side1 * _side2);
	}

	float perimeter() const {
		return (2 * _side1 + 2 * _side2);
	}
};


#endif
