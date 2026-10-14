/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:02:23 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 13:40:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <iostream>

class Engine {
private:
	bool			_started;
	friend class	Car;

public:
	Engine() : _started(false){}
	
	bool status() const {
		return _started;
	}

	void start() {
		if (_started)
			return ; 
		_started = true;
	}

	void stop() {
		if (!_started)
			return ;
		_started = false;
	}
	
};


#endif
