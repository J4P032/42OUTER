/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 12:47:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/09 17:47:47 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template<size_t Rows, size_t Cols>
Matrix<Rows, Cols>::Matrix(void) : _matrix{} {} //all elements 0.0f

template<size_t Rows, size_t Cols>
Matrix<Rows, Cols>::Matrix(const Matrix& M) : _matrix{M._matrix} {}

template<size_t Rows, size_t Cols>
Matrix<Rows, Cols>& Matrix<Rows, Cols>::operator=(const Matrix<Rows, Cols>& M){
	_matrix = M._matrix;
	return *this;
}

template<size_t Rows, size_t Cols>
Matrix<Rows, Cols>::~Matrix(void){}

template<size_t Rows, size_t Cols>
const std::array<float, Rows * Cols>& Matrix<Rows, Cols>::get_matrix(void) const{
	return _matrix;
}

template<size_t Rows, size_t Cols>
bool	Matrix<Rows, Cols>::set_matrix(size_t row, size_t col, float num){
	if (row >= Rows || col >= Cols){
		(void)num;
		return false;
	}
	_matrix[row * Cols + col] = num;
	return true;
}

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
