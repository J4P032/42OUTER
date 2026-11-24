/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:24:30 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/24 12:46:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MVP_HPP
# define MVP_HPP

# include "Matrix.hpp"
# include "ScopState.hpp"

Matrix<4, 4> calculate_mvp(ScopState& scopState);

#endif
