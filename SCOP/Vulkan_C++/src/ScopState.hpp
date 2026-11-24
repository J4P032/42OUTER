/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScopState.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 12:34:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/24 15:36:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOPSTATE_HPP
# define SCOPSTATE_HPP

# include "time.hpp"
# include <cmath>

constexpr float PI = 3.14159265358979323846f;

struct ScopState{
	std::chrono::steady_clock::time_point	start_time;
	float									y_angle = 0.0f; //radians
};

#endif
