/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:26:10 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 13:40:16 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAKE_HPP
# define BRAKE_HPP

class Brake {
private:
	int				_brake;

public:

	Brake() : _brake(0){}

	int get_brake() const {
		return _brake;
	}
	
	void apply_force_on_brakes(unsigned int force) {
		if (force > 100)
			force = 100;
		_brake = force;
	}

	void apply_emergency_brakes() {
		if (_brake == 100)
			return;
		_brake = 100;
	}
	
};


#endif
