/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 16:24:40 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 18:26:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <iostream>
# include <map>

static size_t counter = 0;

class Command {
protected:
	size_t											id;
	std::string										date;
	std::string										client;
	std::map<std::string, std::pair<float, int>>	articles;
	

public:
	Command() {
		id		= counter++;
		date	= "00/00/0000";
		client	= "None";
	}

	Command(std::string name, std::string d) {
		id = counter++;
		client = name;
		date = d;
	}

	virtual ~Command(){}

	//GETTERS
	
	float	get_total_price() const{
		if (articles.empty())
			return 0;
		float total;
		std::map<std::string, std::pair<float,int>>::const_iterator it = articles.begin();
		for (; it != articles.end(); it++) {
			total += it->second.first * it->second.second;
		} 
		total -= discount(total);
		return (total);
	}

	//METHODS

	void add(std::string article, float price, int quantity) {
		articles[article] = std::make_pair(price, quantity);
	} 


	virtual float discount(float price) const { 
		(void) price;
		return 0.0f;
	}

	friend std::ostream& operator<<(std::ostream& out, const Command& c) {
		out << "---------------------" << std::endl;
		out << "Command " << c.id << ":" << std::endl;
		out << "Date: " << c.date << " | ";
		out << "Client: " << c.client << std::endl;
		out << "Articles (Quantity): " << std::endl;
		std::map<std::string, std::pair<float,int>>::const_iterator it = c.articles.begin();
		for (; it != c.articles.end(); it++){
			out << it->first << " (" << it->second.second << ")" << std::endl;
		}
		out << "---------------------";
		return out;
	}
};

#endif
