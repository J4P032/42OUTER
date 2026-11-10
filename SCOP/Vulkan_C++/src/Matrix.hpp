/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 12:05:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/10 13:35:21 by jrollon-         ###   ########.fr       */
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
	const std::array<float, Rows * Cols>& get_matrix(void) const;
	
	//setters
	bool	set_matrix(size_t row, size_t col, float num);
	
	//vertical ruled array for Vulkan instead of horizontal ruled
	const std::array<float, Rows * Cols>	get_vertical_matrix(void) const;
	
	//operators
	/*for to Matrixes A(a,b), B(c,d), where a & c are rows
	and b & d are columns, it will be only possible to multiply them
	if b = c, and the result Matrix will be C(a,d)*/
	template<size_t otherCols> 
	Matrix<Rows, otherCols> operator*(const Matrix<Cols, otherCols>& M) const;
	
	//out
	friend std::ostream& operator<<(std::ostream& out, const Matrix<Rows, Cols>& M){
	//typename std::array<float, Rows * Cols>::const_iterator it = M._matrix.begin();
		size_t counter = 0;
		size_t elements = Rows * Cols;
		for (const auto& num : M._matrix){
			out << num;
			counter++;
			if (counter != elements)
				out << ", ";
		}
		return out;
	}
	
};

# include "Matrix.tpp"

#endif
