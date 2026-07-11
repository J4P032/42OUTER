/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect3.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:23:33 by jrollon-          #+#    #+#             */
/*   Updated: 2026/07/11 19:34:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT3_HPP
# define VECT3_HPP
# include <iostream>
//# include <sstream>
# include <map>
# include "Interface.hpp"


class   Vect3 : public Interface{
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
		
        //friend hace que pueda acceder a sus partes privadas, PERO lo considera...
        //...como si estuviera fuera de la clase. De ahí que el el cpp sea como fuera.
        //friend std::ostream&   operator<<(std::ostream &out, const Vect3 &v3);
        //ahora con Interface es más sencillo repetir el operator<<
        void            stream_insert(std::ostream &out) const override;
};

using VMAP = std::map<size_t, Vect3>; //el using tiene que star despues del objeto Vect3 para ser primero definido

void	store_vertex(const std::string& line, VMAP& objPoints);
void	test_data(VMAP& objPoints);

#endif
