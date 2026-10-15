/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 13:00:18 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 15:38:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "shape.hpp"

class Triangle : public Shape {
private:
	float	_base;
	float	_height;
	float	_hypotenuse;
	float	_leg;

public:
	Triangle(float base, float height, float hypotenuse, float leg) :
		_base(base), _height(height), _hypotenuse(hypotenuse), _leg(leg) {}
	
	~Triangle(){}
		
	float area() const {
		return ( (_base * _height) / 2.0f );
	}

	float perimeter() const {
		return (_leg + _hypotenuse + _base);
	}
		
};

#endif
