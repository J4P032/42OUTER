/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect3.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:23:33 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/19 13:10:58 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class   Vect3{
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
        //friend hace que pueda acceder a sus partes privadas, PERO lo considera...
        //...como si estuviera fuera de la clase. De ahí que el el cpp sea como fuera.
        friend std::ostream&   operator<<(std::ostream &out, const Vect3 &v3);
};
