/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DivideAndRule.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 15:40:23 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/28 16:25:32 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIVIDEANDRULE_HPP
# define DIVIDEANDRULE_HPP

# include <iostream>
# include <vector>
# include <climits>

struct Account {
	private:
		size_t	id;
		int		value; //cents

		Account();
		Account(size_t id);
		friend struct Bank;

	public:
 		friend std::ostream& operator << (std::ostream& p_os, const Account& p_account);
};

struct Bank {
	private:
		static size_t			ids; 
		int						liquidity; //cents
		std::vector<Account*>	clientAccounts;

	public:
		 				Bank();
						~Bank();

		void			new_account();
		const Account&	get_account(size_t id) const;
		void			income(size_t id, long ammount);
		void			loan(size_t id, long ammount);
		void			delete_account(size_t id);
		void			remove_bank();

		friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank);
};

#endif
