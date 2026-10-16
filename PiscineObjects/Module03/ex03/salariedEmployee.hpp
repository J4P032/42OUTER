/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   salariedEmployee.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 17:11:34 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/16 12:09:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SALARIEDEMPLOYEE_HPP
# define SALARIEDEMPLOYEE_HPP

#include "employee.hpp"


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

public:
	ISchool() : _schoolHours(0), _totalSchoolHoursDone(0) {}
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
			if (_schoolHours < day_hours)
				hours_school_today = _schoolHours;
			else
				hours_school_today = 7;
			_schoolHours -= hours_school_today;
			_totalSchoolHoursDone += hours_school_today;
		}
		return 7;
	}
};

#endif
