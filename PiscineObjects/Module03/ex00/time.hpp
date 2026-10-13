/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 17:05:32 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/13 17:07:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_HPP
# define TIME_HPP

# include <chrono>
# include <thread>

void	wait_time(int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


#endif
