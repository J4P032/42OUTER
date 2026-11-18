/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:26:39 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/18 16:11:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mvp.hpp"

Matrix<4, 4> calculate_mvp(void){
	Matrix<4, 4> unit;
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
