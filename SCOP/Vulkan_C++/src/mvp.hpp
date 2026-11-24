/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:24:30 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/24 15:52:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MVP_HPP
# define MVP_HPP

# include "Matrix.hpp"
# include "ScopState.hpp"

Matrix<4, 4> calculate_mvp(ScopState& scopState);
Matrix<4, 4> translation_matrix(float);
Matrix<4, 4> rotation_matrix(float);
Matrix<4, 4> scale_matrix(float);


#endif
