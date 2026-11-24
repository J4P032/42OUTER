/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:26:39 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/24 16:05:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mvp.hpp"

using	std::cos;
using	std::sin;

Matrix<4, 4> translation_matrix(float t){
	(void)t;
	Matrix<4, 4> translation;
	translation.set_identity();
	translation.set_matrix(2, 3, 0.5f);
	return translation;
}

Matrix<4, 4> rotation_matrix(float angle){
	Matrix<4, 4> rotation;
	float c = cos(angle);
	float s = sin(angle);
	rotation.set_identity();
	rotation.set_matrix(0, 0, c);
	rotation.set_matrix(0, 2, s);
	rotation.set_matrix(2, 0, -s);
	rotation.set_matrix(2, 2, c);
	return rotation;
}

Matrix<4, 4> scale_matrix(float s){
	Matrix<4, 4> scale;
	scale.set_identity();
	scale.set_matrix(0, 0, s);
	scale.set_matrix(1, 1, -s); //-y in vulkan
	scale.set_matrix(2, 2, s);
	return scale;
}


Matrix<4, 4> calculate_mvp(ScopState& scopState){
	const auto seconds = time_passed(scopState.start_time);
	scopState.start_time = grab_time();
	scopState.y_angle += seconds.count() * PI;
	scopState.y_angle = std::fmod(scopState.y_angle, 2.0f * PI); //Start from 0.0f again when 2PI

	auto T = translation_matrix(1.0);
	auto R = rotation_matrix(scopState.y_angle);
	auto S = scale_matrix(0.2f);

	auto M = T * R * S;

	return M;
}

/*
 la rotacion y escala estan en al matriz a la izda de 3 x 3. la translacion en la columna ultima
 */
