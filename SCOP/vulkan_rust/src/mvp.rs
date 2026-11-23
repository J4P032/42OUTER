/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.rs                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 14:21:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/23 15:19:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

pub use crate::matrix::Matrix;

pub fn calculate_mvp() -> Matrix<4, 4>{
	let mut unit: Matrix<4,4> = Matrix::new();
	for row in 0..4{
		for col in 0..4{
			if row == col{
				unit.set_matrix(row, col, 0.05);
			}
			else{
				unit.set_matrix(row, col, 0.0);
			}
		}
	}
	unit.set_matrix(2, 3, 0.5);
	unit.set_matrix(3, 3, 1.0);
	unit
}
