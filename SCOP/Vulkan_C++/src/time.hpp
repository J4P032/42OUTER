/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 11:32:50 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/24 12:13:30 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_HPP
# define TIME_HPP

# include <chrono>

std::chrono::steady_clock::time_point	grab_time(void);
std::chrono::duration<double>			time_passed(std::chrono::steady_clock::time_point);

#endif
