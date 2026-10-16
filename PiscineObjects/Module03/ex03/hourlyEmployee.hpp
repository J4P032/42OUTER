/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hourlyEmployee.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:32:14 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/16 12:19:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOURLYEMPLOYEE_HPP
# define HOURLYEMPLOYEE_HPP

# include "employee.hpp"

class IMobilizable : public Employee {
protected:
	int _hours;
	int _mobilizedHours;
	
public:
	IMobilizable() : _hours(0), _mobilizedHours(0) {}
    virtual ~IMobilizable() {}
    virtual void mobilize(int hours) = 0;
};

class TempWorker : public IMobilizable {
public:
	TempWorker() {}
	~TempWorker() {}

	void mobilize(int hours){
		_mobilizedHours += hours;
	}

	int executeWorkday(){
		int hoy = 7;
    	int horas_trabajadas_hoy = 0;

    	if (_mobilizedHours > 0) {
        	if (_mobilizedHours < hoy) {
            	horas_trabajadas_hoy = _mobilizedHours;
        	} else {
            	horas_trabajadas_hoy = 7;
        	}
       	 	_mobilizedHours -= horas_trabajadas_hoy;
        	_hours += horas_trabajadas_hoy;
    	}
    	return 7;
	}
};

#endif
