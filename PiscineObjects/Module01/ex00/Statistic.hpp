/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Statistic.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 11:47:59 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/29 12:25:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATISTIC_HPP
# define STATISTIC_HPP

# include <iostream>

struct Statistic {
private:
	int	level;
	int	exp;

public:
	Statistic() : level(0), exp(0) {}
	Statistic(int l, int e) : level(l), exp(e) {}

	friend std::ostream& operator<<(std::ostream& out, const Statistic& s){
		out << "level: " << s.level << " exp: " << s.exp;
		return out;
	}

	
};

#endif
