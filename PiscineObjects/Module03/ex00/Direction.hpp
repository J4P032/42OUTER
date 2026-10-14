/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Direction.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 15:20:16 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 15:38:23 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTION_HPP
# define DIRECTION_HPP

class Direction {
private:
	int _angle;	

public:
	Direction() : _angle(0){}	
	
	int get_angle() const {
		return _angle;
	}

	void turn_wheel(int angle) {
		if (angle >= 180)
			angle = 180;
		if (angle <= -180)
			angle = -180;
		_angle = angle;
	}
};

#endif
