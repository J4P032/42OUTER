/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 11:34:57 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/24 12:48:55 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.hpp"

std::chrono::steady_clock::time_point	grab_time(void){
	return std::chrono::steady_clock::now();
}

std::chrono::duration<double>	time_passed(std::chrono::steady_clock::time_point startTime){
	const auto now = std::chrono::steady_clock::now();
	return (now - startTime);
} 
