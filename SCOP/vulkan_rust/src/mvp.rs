/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.rs                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 14:21:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/25 15:37:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

pub use crate::matrix::Matrix;
use crate::scopstate::ScopState;

pub fn translation_matrix(t: f32) -> Matrix<4,4>{
	let mut translation: Matrix<4,4> = Matrix::new();
	translation.set_identity();
	translation.set_matrix(2, 3, 0.5);
	translation
}

pub fn rotation_matrix(angle: f32) -> Matrix<4,4>{
	let mut rotation = Matrix::new();
	rotation.set_identity();
	let c = angle.cos();
	let s = angle.sin();
	rotation.set_matrix(0, 0, c);
	rotation.set_matrix(0, 2, s);
	rotation.set_matrix(2, 0, -s);
	rotation.set_matrix(2, 2, c);
	rotation
}

pub fn scale_matrix(s: f32) -> Matrix<4,4>{
	let mut scale = Matrix::new();
	scale.set_identity();
	scale.set_matrix(0, 0, s);
	scale.set_matrix(1, 1, -s); //-y in vulkan
	scale.set_matrix(2, 2, s);
	scale
}


pub fn calculate_mvp(scop_state: &mut ScopState) -> Matrix<4, 4>{
	let mut unit: Matrix<4,4> = Matrix::new();
	let seconds = std::time::Instant::now() - scop_state.get_start_time();
	scop_state.set_y_angle(seconds);
	scop_state.grab_time();
	
	let tr = translation_matrix(1.0);
	let ro = rotation_matrix(scop_state.get_y_angle());
	let sc = scale_matrix(0.2);

	unit = &(&tr * &ro) * &sc;
	unit
}
