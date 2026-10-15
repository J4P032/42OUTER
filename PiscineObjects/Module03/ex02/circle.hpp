/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 13:35:19 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 15:35:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCLE_HPP
# define CIRCLE_HPP

# include "shape.hpp"

class Circle : public Shape {
private:
	float	_radius;

public:
	Circle(float radius) : _radius(radius) {}
	~Circle(){}

	float area() const {
		return (3.141592f * _radius * _radius);
	}

	float perimeter() const {
		return (2.0f * 3.141592f * _radius);
	}
};


#endif
