/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 11:18:34 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 15:08:57 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAR_HPP
# define CAR_HPP

# include <iostream>
# include "color.hpp"
# include "Engine.hpp"
# include "Brake.hpp"
# include "Gears.hpp"

class Car {

private:
	int		_speed;
	int		_angle;
	size_t	_id;

	//composicion
	Engine	_engine;
	Brake	_brake;
	Gears	_gear;

	

public:
	Car() : 
		_speed(0),
		_angle(0),
		_id(0){
		std::cout << GREEN "🚘" << _id << " is created." << RESET <<  std::endl;	
	}

	Car(size_t id) : 
		_speed(0),
		_angle(0),
		_id(id){
		std::cout << GREEN "🚘" << _id << " is created." << RESET <<  std::endl;	
	}

	Car(const Car& other) :
		_speed(other._speed),
		_angle(other._angle),
		_id(other._id),
		_engine(other._engine),
		_brake(other._brake),
		_gear(other._gear) {
		std::cout << GREEN "🚘" << _id << " is created from " << "🚘" << other._id << RESET <<  std::endl;	
	}
	
	Car& operator=(const Car& other){
		_speed = other._speed;
		_angle = other._angle;
		_engine = other._engine;
		_brake = other._brake;
		_gear = other._gear;
		_id = other._id;
		return *this;
	}

	~Car(){
		std::cout << RED "🚘" << _id << " destroyed." << RESET <<  std::endl;	
	}

	//GETTER
	int	speed() const {
		return _speed;
	}

	//SETTER
	void speed(int speed) {
		_speed = speed;
	}
	
	void	set_id(size_t id) {
		std::cout << GREEN "🚘" << _id << " changed to id " << id << RESET <<  std::endl;	
		_id = id;
	}
	

	// METHODS 

	void start() {
		if (_engine._started)
			return ; 
		_engine.start();
		std::cout << CYAN "🚘" << _id << " starts engine." << RESET <<  std::endl;
	}

	void stop() {
		if (!_engine._started)
			return ;
		_engine.stop();
		_brake.apply_emergency_brakes();
		_speed = 0;
		std::cout << YELLOW "🚘" << _id << " stops engine." << RESET <<  std::endl;
	}
	
	void apply_force_on_brakes(unsigned int force) {
		_brake.apply_force_on_brakes(force);
		accelerate(0);
		std::cout << YELLOW "🚘" << _id << " applies " << _brake.get_brake() << "% brakes" << RESET <<  std::endl;
	}

	void apply_emergency_brakes() {
		_brake.apply_emergency_brakes();
		accelerate(0);
		std::cout << YELLOW "🚘" << _id << " applies emergency brakes" << RESET <<  std::endl;
	}

	void shift_gears_up() { 
		_gear.shift_gears_up();
		std::cout << CYAN "🚘" << _id << " changed to " << _gear.get_gear() << " gear." << RESET <<  std::endl;
	}

	void shift_gears_down() {
		_gear.shift_gears_down();
		std::cout << YELLOW "🚘" << _id << " changed to " << _gear.get_gear() << " gear." << RESET <<  std::endl;
	}

	void accelerate(int speed) { 
		if (!_engine._started) {
			std::cout << RED "⚠️ 🚘" << "_id" << " don't have engines running!" << RESET << std::endl; 
			return ;
		}
		if (_brake.get_brake() > 0) {
			std::cout << RED "⚠️ 🚘" << "_id" << " has " << _brake.get_brake() << "% of brakes applied!" << RESET << std::endl; 
			return ;
		}
		_gear.reverse_off();
		_gear.accelerate(speed, *this);
		std::cout << CYAN "🚘 " << _id << " accelerates up to " << _speed << " km/h." << RESET <<  std::endl;
	}

	void reverse() {
		_gear.reverse();
		std::cout << YELLOW "🚘 " << _id << " turns reverse on" << RESET <<  std::endl;
	}

	void turn_wheel(int angle) {
		if (angle >= 180)
			angle = 180;
		if (angle <= -180)
			angle = -180;
		_angle = angle;
		std::cout << CYAN "🚘 " << _id << " turns wheel to " << _angle << "°" << RESET <<  std::endl;
	}

	void straighten_wheel() {
		if (_angle == 0)
			return;
		_angle = 0;
		std::cout << CYAN "🚘 " << _id << " straight the wheel." << RESET <<  std::endl;
	}


	//operator<<
	friend std::ostream& operator<<(std::ostream& out, const Car& c) {
		out << "-------------------------" << std::endl;
		out << BLUE << "🚘" << c._id << ":" <<  std::endl;
		out << BLUE "engine running: " << RESET << std::boolalpha << c._engine.status() << std::noboolalpha << std::endl;
		
		out << "Speed: " << RESET << c._speed << std::endl;
		out << BLUE "gear: " << RESET << c._gear.get_gear() << std::endl;
		out << BLUE "reverse: " << RESET << std::boolalpha << c._gear.get_reverse() << std::noboolalpha << std::endl;
		out << BLUE "angle: " << RESET << c._angle << std::endl;
		out << BLUE "brake: " << RESET << c._brake.get_brake() << "%" << std::endl;
		out << "--------------------------"; 
	
		return out;
	}
};

#endif

/*tengo de implementar las funciones de Gears aqui ya que no se permite
en el ejercicio poner un Gears.cpp, y asi eludo la dependencia circular
que se evita parcialmente haciendo un "class Car;" en Gear.hpp, pero
no compila al llamar a c.speed() o c.shift_gears_down(), por que aunque
declarada la clase, no encuentra la implementacion.
De esta manera primero se completa la clase Car y ya podemos leer sus
metodos */
void Gears::accelerate_to_speed(int speed, Car& c) {
		int max_speed = 220;
		if (speed > max_speed)
			speed = max_speed; 
		while (c.speed() != speed) {
			if (c.speed() >= 0 && c.speed() < 10){
				while (_gear != 1){
					if (_gear > 1)
						c.shift_gears_down();
					else
						c.shift_gears_up();
				}
			}

			if (c.speed() >= 10 && c.speed() < 30){
				while (_gear != 2){
					if (_gear > 2)
						c.shift_gears_down();
					else
						c.shift_gears_up();
				}
			}

			if (c.speed() >= 30 && c.speed() < 60){
				while (_gear != 3){
					if (_gear > 3)
						c.shift_gears_down();
					else
						c.shift_gears_up();
				}
			}

			if (c.speed() >= 60 && c.speed() < 80){
				while (_gear != 4){
					if (_gear > 4)
						c.shift_gears_down();
					else
						c.shift_gears_up();
				}
			}

			if (c.speed() >= 80 && c.speed() < 110){
				while (_gear != 5){
					if (_gear > 5)
						c.shift_gears_down();
					else
						c.shift_gears_up();
				}
			}

			if (c.speed() >= 110 && c.speed() <= 220){
				while (_gear != 6){
					if (_gear < 6)
						c.shift_gears_up();
				}
			}
			c.speed(c.speed() + 1);
		}
	}

	void Gears::accelerate(int speed, Car& c) { 
		_reverse = false;
		accelerate_to_speed(speed, c);
	}
