/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 11:18:34 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/13 12:27:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAR_HPP
# define CAR_HPP

# include <iostream>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[38;2;255;0;0m"
#define GREEN "\033[38;2;0;255;0m"
#define YELLOW "\033[38;5;226m"
#define BLUE "\033[38;2;0;100;255m"
#define MAGENTA "\033[38;2;100;50;255m"
#define CYAN "\033[38;2;0;200;255m"
#define WHITE "\033[37m"


class Car {

private:
	bool	_started;
	int		_speed;
	int		_gear;
	bool	_reverse;
	int		_angle;
	int		_brake;
	size_t	_id;

public:
	Car() : 
		_started(false),
		_speed(0),
		_gear(0),
		_reverse(false),
		_angle(0),
		_brake(100),
		_id(0){}

	Car(const Car& other) :
		_started(other._started),
		_speed(other._speed),
		_gear(other._gear),
		_reverse(other._reverse),
		_angle(other._angle),
		_brake(other._brake),
		_id(other._id) {}
	
	Car& operator=(const Car& other){
		_started = other._started;
		_speed = other._speed;
		_gear = other._gear;
		_reverse = other._reverse;
		_angle = other._angle;
		_brake = other._brake;
		_id = other._id;
		return *this;
	}

	~Car(){}

	// METHODS 

	void start() { 
		_started = true;
		std::cout << CYAN "🚘 " << _id << " starts engine." << RESET <<  std::endl;
	}
	
	void stop() {
		_gear = 0;
		_started = false;
		_brake = 100;
		_speed = 0;
		std::cout << YELLOW "🚘 " << _id << " stops engine." << RESET <<  std::endl;
	}

	void shift_gears_up() { 
		_reverse = false;
		if (_gear == 6)
			return ;
		_gear++;
		std::cout << CYAN "🚘 " << _id << " changed to " << _gear << " gear." << RESET <<  std::endl;
	}

	void shift_gears_down() {
		
	}


	void accelerate_to_speed(int speed) {
		int max_speed = 220;
		if (speed > max_speed)
			speed = max_speed; 
		while (_speed != speed) {
			if (_speed >= 0 && _speed < 10){
				while (_gear != 1){
					if (_gear > 1)
						shift_gears_down();
					else
						shift_gears_up();
				}
			}

			if (_speed >= 10 && _speed < 30){
				while (_gear != 2){
					if (_gear > 2)
						shift_gears_down();
					else
						shift_gears_up();
				}
			}

			if (_speed >= 30 && _speed < 60){
				while (_gear != 3){
					if (_gear > 3)
						shift_gears_down();
					else
						shift_gears_up();
				}
			}

			if (_speed >= 60 && _speed < 80){
				while (_gear != 4){
					if (_gear > 4)
						shift_gears_down();
					else
						shift_gears_up();
				}
			}

			if (_speed >= 80 && _speed < 110){
				while (_gear != 5){
					if (_gear > 5)
						shift_gears_down();
					else
						shift_gears_up();
				}
			}
			
			_speed++;
		}
	}


	void accelerate(int speed) { 
		if (!_started)
			start();
		_brake = 0;
		
		if (speed > 220)
		_speed = speed;
		std::cout << CYAN "🚘 " << _id << " accelerates up to " << _speed << " km/h." << RESET <<  std::endl;
	}

	
	
};


#endif
	