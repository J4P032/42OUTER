/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 11:18:34 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/13 17:52:11 by jrollon-         ###   ########.fr       */
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

			if (_speed >= 110 && _speed <= 220){
				while (_gear != 6){
					if (_gear < 6)
						shift_gears_up();
				}
			}
			_speed++;
		}
	}

public:
	Car() : 
		_started(false),
		_speed(0),
		_gear(0),
		_reverse(false),
		_angle(0),
		_brake(100),
		_id(0){
		std::cout << GREEN "🚘" << _id << " is created." << RESET <<  std::endl;	
	}

	Car(size_t id) : 
		_started(false),
		_speed(0),
		_gear(0),
		_reverse(false),
		_angle(0),
		_brake(100),
		_id(id){
		std::cout << GREEN "🚘" << _id << " is created." << RESET <<  std::endl;	
	}

	Car(const Car& other) :
		_started(other._started),
		_speed(other._speed),
		_gear(other._gear),
		_reverse(other._reverse),
		_angle(other._angle),
		_brake(other._brake),
		_id(other._id) {
		std::cout << GREEN "🚘" << _id << " is created from " << "🚘" << other._id << RESET <<  std::endl;	
	}
	
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

	~Car(){
		std::cout << RED "🚘" << _id << " destroyed." << RESET <<  std::endl;	
	}

	//SETTER
	void	set_id(size_t id) {
		std::cout << GREEN "🚘" << _id << " changed to id " << id << RESET <<  std::endl;	
		_id = id;
	}
	

	// METHODS 

	void start() { 
		_started = true;
		std::cout << CYAN "🚘" << _id << " starts engine." << RESET <<  std::endl;
	}
	
	void stop() {
		_gear = 0;
		_started = false;
		_brake = 100;
		_speed = 0;
		std::cout << YELLOW "🚘" << _id << " stops engine." << RESET <<  std::endl;
	}

	void apply_force_on_brakes(unsigned int force) {
		if (force > 100)
			force = 100;
		_brake = force;
		std::cout << YELLOW "🚘" << _id << " applies " << _brake << "% brakes" << RESET <<  std::endl;
	
	}

	void shift_gears_up() { 
		_reverse = false;
		if (_gear == 6)
			return ;
		_gear++;
		std::cout << CYAN "🚘" << _id << " changed to " << _gear << " gear." << RESET <<  std::endl;
	}

	void shift_gears_down() {
		
	}


	


	void accelerate(int speed) { 
		if (!_started) {
			std::cout << RED "⚠️ 🚘" << "_id" << " don't have engines running!" << RESET << std::endl; 
			return ;
		}
		if (_brake > 0) {
			std::cout << RED "⚠️ 🚘" << "_id" << " has " << _brake << "% applied!" << RESET << std::endl; 
			return ;
		}
		accelerate_to_speed(speed);
		std::cout << CYAN "🚘 " << _id << " accelerates up to " << _speed << " km/h." << RESET <<  std::endl;
	}


	//operator<<
	friend std::ostream& operator<<(std::ostream& out, const Car& c) {
		out << "-------------------------" << std::endl;
		out << BLUE << "🚘" << c._id << ":" <<  std::endl;
		out << BLUE "engine running: " << RESET << std::boolalpha << c._started << std::noboolalpha << std::endl;
		
		out << "Speed: " << RESET << c._speed << std::endl;
		out << BLUE "gear: " << RESET << c._gear << std::endl;
		out << BLUE "reverse: " << RESET << std::boolalpha << c._reverse << std::noboolalpha << std::endl;
		out << BLUE "angle: " << RESET << c._angle << std::endl;
		out << BLUE "brake: " << RESET << c._brake << "%" << std::endl;
		out << "--------------------------"; 
	
		return out;
	}
};


#endif
	