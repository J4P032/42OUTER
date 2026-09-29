/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:43:36 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/28 19:26:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>

class Vect2 {
private:
	float	X;
	float	Y;

public:
	
	Vect2(void);
	Vect2(float x, float y);
	Vect2(const Vect2& other);
	Vect2& operator=(const Vect2& other);
	~Vect2(void);

	//[]
	float operator[](int n) const;

	float& operator[](int n);

	//==
	bool operator==(const Vect2& other) const;
	bool operator!=(const Vect2& other) const;

	//Getters
	float getX(void) const;
	float getY(void) const;
};


inline std::ostream& operator<<(std::ostream& out, const Vect2& v);

#endif
