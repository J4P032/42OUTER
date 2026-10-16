/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   employeeManagement.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:19:40 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/16 11:38:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EMPLOYEEMANAGEMENT_HPP
# define EMPLOYEEMANAGEMENT_HPP

#include <set>
#include "employee.hpp"

class EmployeeManager {
private:
	std::set<Employee*>	employees;
	
public:
	void addEmployee(Employee* e){}
	
	void removeEmployee(Employee* e){}

	void executeWorkday() const {}

	void calculatePayroll() const {}
};

#endif
