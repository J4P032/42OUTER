/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.rs                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 10:48:09 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/16 16:29:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#[derive(Copy, Clone)]
pub struct Matrix<const ROWS: usize, const COLS: usize>{
	matrix: [[f32; COLS]; ROWS],
}

use std::ops::{AddAssign, Mul, MulAssign};

//CONSTRUCTOR
impl<const ROWS: usize, const COLS: usize> Matrix<ROWS, COLS>{
	pub fn new() -> Self{
		Self { matrix: [[0.0; COLS]; ROWS]}
	}

	pub fn new_from_matrix(m: &Matrix<ROWS, COLS>) -> Self{
		Self {matrix: m.matrix}
	}
}

//GETTER
impl<const ROWS: usize, const COLS: usize> Matrix<ROWS, COLS>{
	pub fn get_matrix(&self) -> [[f32; COLS]; ROWS]{
		self.matrix
	}

	pub fn get_vertical_matrix(&self) -> Vec<f32>{
		let mut vec = Vec::<f32>::with_capacity(ROWS * COLS);
		for col in 0..COLS{
			for row in 0..ROWS{
				vec.push(self.matrix[row][col])
			}
		}
		vec
	}
}

//SETTER
impl<const ROWS: usize, const COLS: usize> Matrix<ROWS, COLS>{
	pub fn set_matrix(&mut self, row: usize, col: usize, num: f32){
		self.matrix[row][col] = num;	
	}
}

//OPERATOR*
impl<const ROWS: usize, const COLS: usize, const OTHER_COLS: usize> Mul<Matrix<COLS, OTHER_COLS>> for Matrix<ROWS, COLS>{
	type Output = Matrix<ROWS, OTHER_COLS>;
	fn mul(self, m: Matrix<COLS, OTHER_COLS>) -> Matrix<ROWS, OTHER_COLS>{
		Matrix { matrix: [[0.0; OTHER_COLS]; ROWS]}


	}
}


/* 
template<size_t Rows, size_t Cols>
template<size_t otherCols> 
Matrix<Rows, otherCols> Matrix<Rows, Cols>::operator*(const Matrix<Cols, otherCols>& M) const{
	Matrix<Rows, otherCols> AUX;
	float					solution = 0.0f;
	float					num1, num2 = 0.0f;
	
	for (size_t row = 0; row < Rows; row++){
		for (size_t oCol = 0; oCol < otherCols; oCol++){
			solution = 0.0f;
			for (size_t col = 0; col < Cols; col++){
				num1 = _matrix[row * Cols + col];
				num2 = M.get_matrix()[col * otherCols + oCol];
				solution += num1 * num2;
			}
			AUX.set_matrix(row, oCol, solution);
		}
	}
	return AUX;
}
*/
