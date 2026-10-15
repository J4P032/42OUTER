/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:43:56 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 12:59:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_HPP
# define SHAPE_HPP

class Shape {
public:
	Shape(){}
	virtual ~Shape(){}

	//METODOS
	virtual float	area() const = 0;
	virtual float	perimeter() const = 0;
};

#endif
