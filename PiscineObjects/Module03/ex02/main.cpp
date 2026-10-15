/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:44:33 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 15:57:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "triangle.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

void run() {
	Shape* c0 = new Circle(5.0f);
	Shape* t0 = new Triangle(12.0f, 15.0f, 16.16f, 16.16f);
	Shape* r0 = new Rectangle(5.0f, 100.0f);
	std::cout << "area Circulo: " << c0->area() << ", perimetro: " << c0->perimeter() << std::endl;
	std::cout << "area Triangulo: " << t0->area() << ", perimetro: " << t0->perimeter() << std::endl;
	std::cout << "area Rectangle: " << r0->area() << ", perimetro: " << r0->perimeter() << std::endl;
	delete r0;
	delete c0;
	delete t0;
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
