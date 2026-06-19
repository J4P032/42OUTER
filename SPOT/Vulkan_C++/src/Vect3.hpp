/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect3.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:23:33 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/19 11:31:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Vect3{
private:
    float   _x;
    float   _y;
    float   _z;
    
public:
    Vect3(void);
    Vect3(float x, float y, float z);
    Vect3(const Vect3 &other);
    Vect3 operator=(const Vect3 &other) const;
    ~Vect3(void);

    Vect3 getVect3(void) const;
};