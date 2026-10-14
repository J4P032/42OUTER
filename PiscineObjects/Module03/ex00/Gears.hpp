/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gears.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:46:50 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 15:10:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEARS_HPP
# define GEARS_HPP

class Car;

class Gears {
private:
	int				_gear;
	bool			_reverse;
	
	void 			accelerate_to_speed(int speed, Car& c);
	

public:
	Gears() : _gear(0), _reverse(false){}

	//getter

	int get_gear() const {
		return _gear;
	}

	bool get_reverse() const {
		return _reverse;
	}

	//methods
	
	
	void shift_gears_up() { 
		_reverse = false;
		if (_gear == 6)
			return ;
		_gear++;
	}

	void shift_gears_down() {
		_reverse = false;
		if (_gear == 0)
			return ;
		_gear--;
	}

	void reverse() {
		if (_reverse)
			return ;
		_gear = 0;
		_reverse = true;
	}

	void reverse_off() {
		if (!_reverse)
			return ;
		_gear = 0;
		_reverse = false;
	}
	
	void accelerate(int speed, Car& c);
};

#endif

