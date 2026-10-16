/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   employee.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:21:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/16 15:18:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EMPLOYEE_HPP
# define EMPLOYEE_HPP

class Employee {
protected:
	int	hourlyValue;
	int totalHoursWorked;

public:
	Employee() : hourlyValue(50), totalHoursWorked(0) {}

	virtual ~Employee(){}
	
	virtual int executeWorkday() = 0;

	virtual int	calculatePayroll() = 0;
};

#endif
