/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:26:39 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/24 13:10:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mvp.hpp"

Matrix<4, 4> calculate_mvp(ScopState& scopState){
	Matrix<4, 4> unit;
	
	const auto seconds = time_passed(scopState.start_time);
	scopState.start_time = grab_time();
	scopState.y_angle += seconds.count() * PI;
	std::fmod(scopState.y_angle, 2.0f * PI); //Start from 0.0f again when 2PI

	
	for (size_t row = 0; row < 4; row++){
		for (size_t col = 0; col < 4; col++){
			if (row == col)
				unit.set_matrix(row, col, 0.05f);
			else
				unit.set_matrix(row, col, 0.0f);
		}
	}
	unit.set_matrix(2, 3, 0.5f);
	unit.set_matrix(3, 3, 1.0f);
	return unit;
}

/*
Para que gire una vuelta cada 2 segundos, tienes dos caminos:
 En cada frame 
le sumas seconds.count() * PI (ya que \(\pi \) radianes por segundo equivale a \(2\pi\) 
cada 2 segundos). Luego usas ese angle acumulado para construir tu matriz de rotación.
 (Este es el mejor método para cuando luego controles cosas con teclado).

 la rotacion y escala estan en al matriz a la izda de 3 x 3. la translacion en la columna ultima


 */
