/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   employeeManagement.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:19:40 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/16 15:06:46 by jrollon-         ###   ########.fr       */
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
	void addEmployee(Employee* e){
		if (!e)
			return;
		employees.insert(e);
	}
	
	void removeEmployee(Employee* e){
		if (!e)
			return;
		employees.erase(e);
	}

	void executeWorkday() const {
		std::set<Employee*>::const_iterator cit = employees.begin();
		for (;cit != employees.end(); cit++){
			(*cit)->executeWorkday();
		}
	}

	void calculatePayroll() const {
		std::set<Employee*>::const_iterator cit = employees.begin();
		for (;cit != employees.end(); cit++){
			(*cit)->();
		}
		
	}
};

#endif
