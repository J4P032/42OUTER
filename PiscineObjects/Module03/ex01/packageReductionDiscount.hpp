/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packageReductionDiscount.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 16:24:43 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 10:41:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PACKAGEREDUCTIONDISCOUNT_HPP
# define PACKAGEREDUCTIONDISCOUNT_HPP

# include "command.hpp"
class PackageReductionDiscountCommand : public Command {
private:
	const Command&	command;

public:
	PackageReductionDiscountCommand(const Command& c) : command(c) {}

	float	get_total_price() const{
		float total = command.get_total_price();
		total -= discount(total);
		return total;
	}


	float discount(float price) const { 
		float discount = 0.0f;
		if (price > 150)
			discount += 10.0f;
		return ( discount );		
	}
};

#endif
