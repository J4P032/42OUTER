/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   salariedEmployee.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 17:11:34 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/16 15:28:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SALARIEDEMPLOYEE_HPP
# define SALARIEDEMPLOYEE_HPP

# include "employee.hpp"
# include <algorithm>


class IAbsentee : public Employee {
protected:
	int _absentHours;

public:
	IAbsentee() : _absentHours(0) {}
	virtual ~IAbsentee(){}
		
	virtual void registerAbsentHours(int hours) = 0;
};

class ContractEmployee : public IAbsentee {
public:
	ContractEmployee() {}

	void registerAbsentHours(int  hours) {
		_absentHours += hours;
	}

	int executeWorkday(){
		return 7;
	}	
};

class ISchool : public IAbsentee {
protected:
	int _schoolHours;
	int	_totalSchoolHoursDone;
	int	_totalSchoolHoursPaid;

public:
	ISchool() : _schoolHours(0), _totalSchoolHoursDone(0), _totalSchoolHoursPaid(0) {}
	virtual ~ISchool(){}
		
	virtual void registerSchoolHours(int hours) = 0;
};

class Apprentice : public ISchool {
public:
	
	void registerAbsentHours(int  hours) {
		_absentHours += hours;
	}

	void registerSchoolHours(int hours) {
		_schoolHours += hours;
	}

	int executeWorkday(){
		int day_hours = 7;
		int hours_school_today = 0;
		if (_schoolHours > 0) {
			hours_school_today = std::min(day_hours, _schoolHours);
			_schoolHours -= hours_school_today;
			_totalSchoolHoursDone += hours_school_today;
			_totalSchoolHoursPaid += hours_school_today;
		}
		totalHoursWorked += 7;
		return 7;
	}

	int calculatePayroll() {
		int total_earned = 0;
		total_earned = hourlyValue * totalHoursWorked + _totalSchoolHoursPaid * (hourlyValue / 2);
		totalHoursWorked = 0;
		_totalSchoolHoursPaid = 0;
		return total_earned;
	}
	
};

#endif
