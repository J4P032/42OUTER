/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hourlyEmployee.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:32:14 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 17:11:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOURLYEMPLOYEE_HPP
# define HOURLYEMPLOYEE_HPP

# include "employee.hpp"

class TempWorker : public Employee {
private:
	int	_hours = 0;
	int _mobilizedHours = 0;

public:

	void mobilize(int hours){
		_mobilizedHours += hours;
	}

	int executeWorkday(){
		_hours += 7;
		return 7;
	}
};

#endif
