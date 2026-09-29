/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 15:37:31 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/28 16:56:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DivideAndRule.hpp"

void run(std::vector<Bank*>& Banks) {
	Bank* bancoA = Banks[0];	

	bancoA->new_account();
	bancoA->new_account();

	bancoA->income(0, 10000);
	//bancoA->income(4, 10000);

	const Account& accountA = bancoA->get_account(0);
	const Account& accountB = bancoA->get_account(1);

	std::cout << "Account : " << std::endl;
	std::cout << accountA << std::endl;
	std::cout << accountB << std::endl;

	std::cout << " ----- " << std::endl;

	std::cout << "Bank : " << std::endl;
	std::cout << *bancoA << std::endl;

	bancoA->loan(1, 250);
	

	std::cout << "Bank : " << std::endl;
	std::cout << *bancoA << std::endl;

	
	bancoA->income(1, 100);
	std::cout << "Bank : " << std::endl;
	std::cout << *bancoA << std::endl;

	bancoA->delete_account(1);
	std::cout << "Bank : " << std::endl;
	std::cout << *bancoA << std::endl;
}

int main()
{
	std::vector<Bank*> Banks;
	Bank bancoA = Bank();
	Banks.push_back(&bancoA);
	try {
		run(Banks);
	}
	catch (const std::exception& e){
		std::cout << "Error: " << e.what() << std::endl;
	}

	return (0);
}
