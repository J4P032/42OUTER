/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   employee.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:21:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 16:52:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EMPLOYEE_HPP
# define EMPLOYEE_HPP

class Employee {
protected:
	int	hourlyValue;

public:
	Employee(){}

	virtual ~Employee(){}
	
	virtual int executeWorkday() = 0;
};

#endif
