/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 12:47:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/09 13:32:05 by jrollon-         ###   ########.fr       */
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
