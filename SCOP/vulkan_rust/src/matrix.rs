/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.rs                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 10:48:09 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/23 15:58:37 by jrollon-         ###   ########.fr       */
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

	pub fn get_vertical_matrix(&self) -> [[f32; ROWS]; COLS] {
		let mut arr = [[0.0; ROWS]; COLS];
		for col in 0..COLS{
			for row in 0..ROWS{
				arr[col][row] = self.matrix[row][col];
			}
		}
		arr
	}
}

//SETTER
impl<const ROWS: usize, const COLS: usize> Matrix<ROWS, COLS>{
	pub fn set_matrix(&mut self, row: usize, col: usize, num: f32){
		self.matrix[row][col] = num;	
	}
}

//OPERATOR*
impl<const ROWS: usize, const COLS: usize, const OTHER_COLS: usize> Mul<&Matrix<COLS, OTHER_COLS>> for &Matrix<ROWS, COLS>{
	type Output = Matrix<ROWS, OTHER_COLS>;
	fn mul(self, m: &Matrix<COLS, OTHER_COLS>) -> Matrix<ROWS, OTHER_COLS>{
		let mut aux = Matrix { matrix: [[0.0; OTHER_COLS]; ROWS]};
		
		for row in 0..ROWS{
			for ocol in 0..OTHER_COLS{
				let mut solution = 0.0;
				for col in 0..COLS{
					solution += self.matrix[row][col] * m.matrix[col][ocol];
				}
				aux.matrix[row][ocol] = solution;
			} 
		}
		aux
	}
}

//PRINT
impl<const ROWS: usize, const COLS: usize> Matrix<ROWS, COLS>{
	pub fn print(&self){
		for row in 0..ROWS{
			for col in 0..COLS{
				print!("{} ", self.matrix[row][col]);
			}
			println!();
		}
	}
}
