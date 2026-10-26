/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect3.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:23:33 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/26 17:25:13 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT3_HPP
# define VECT3_HPP
# include <iostream>
# include "Interface.hpp"

class   Vect3 {
    private:
	    float   _x;
	    float   _y;
	    float   _z;
	
    public:
	    Vect3(void);
	    Vect3(float x, float y, float z);
	    Vect3(const Vect3 &other);
	    Vect3& operator=(const Vect3 &other);
	    ~Vect3(void);

		//Sobrecarta de operadores
		Vect3			operator+(const Vect3& other) const;
		Vect3&			operator+=(const Vect3& other);
		Vect3			operator-(const Vect3& other) const;
		Vect3&			operator-=(const Vect3& other);
		Vect3			operator*(float	num) const;
		Vect3&			operator*=(float num);
		friend Vect3	operator*(float num, const Vect3& other);
		Vect3			operator/(float num) const;
		Vect3&			operator/=(float num);
		
		/*Muy importante: antes hacia uso del interface para componer el mensaje de 
		salida como un stream_insert(std::ostream &out) const override 
		pero esto afecta a la hora de copiar los datos con memcpy de la posicion de
		los vertices en el buffer de vertex de Vulkan. Por que al ser una clase virtual
		el Interface, copiaria tambien los void* de dicha clase entre medias y romperia
		el modelo. Siempre NO HAY QUE PONER CLASES VIRTUALES EN GRAFICOS*/
        friend	std::ostream& operator<<(std::ostream& out, const Vect3& v);
};

#endif
