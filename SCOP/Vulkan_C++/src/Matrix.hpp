/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 12:05:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/09 13:07:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <iostream>
# include <array>

template <size_t Rows, size_t Cols>
class Matrix {
private:
	std::array<float, Rows * Cols>	_matrix;
	
public:
	Matrix(void);
	Matrix(const Matrix& M);
	Matrix& operator=(const Matrix& M);
	~Matrix(void);
	
	//getters
	std::array<float, Rows * Cols> get_matrix(void) const;
	
	//setters
	void	set_matrix(size_t row, size_t col, float num);
	
	//operators
	/*for to Matrixes A(a,b), B(c,d), where a & c are rows
	and b & d are columns, it will be only possible to multiply them
	if b = c, and the result Matrix will be C(a,d)*/
	template<size_t otherCols> 
	Matrix<Rows, otherCols> operator*(const Matrix<Cols, otherCols>& M) const; 
};

# include "Matrix.tpp"

#endif
