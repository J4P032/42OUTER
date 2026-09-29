#include "DivideAndRule.hpp"

size_t Bank::ids = 0;

Account::Account(size_t id) : id(id), value(0){}

std::ostream& operator <<(std::ostream& p_os, const Account& p_account) {
		p_os << "[id: " << p_account.id << "] - [value: " << p_account.value << " cents]";
		return (p_os);
}


Bank::Bank() : liquidity(0){}

void Bank::new_account() {
	Account *aux = new Account(ids++);
	clientAccounts.push_back(aux);
}


const Account& Bank::get_account(size_t id) const {
	std::vector<Account*>::const_iterator cit;
	for (cit = this->clientAccounts.begin(); cit != this->clientAccounts.end(); cit++){
		if ((*cit)->id == id) {
			return **cit;
		} 
	}
	throw std::runtime_error("Account not found");
}


void	Bank::income(size_t id, long ammount) {
	std::vector<Account*>::iterator it = this->clientAccounts.begin();
	while (it != this->clientAccounts.end() && (*it)->id != id)
		it++;
	if (it == this->clientAccounts.end())
		throw std::runtime_error("Cannot add income to non-exist account");
	
	long commission = (ammount * 5) / 100;
	long total_liquidity = static_cast<long>(this->liquidity) + commission;
	if (total_liquidity > INT_MAX || total_liquidity < INT_MIN) {
		throw std::runtime_error("Bank liquidity exceeds integer limits");	
	}

	long net_income = ammount - commission;
	long total_client_value = static_cast<long>((*it)->value) + net_income;
	if (total_client_value > INT_MAX || total_client_value < INT_MIN) {
		throw std::runtime_error("Client account value exceeds integer limits");	
	}

	this->liquidity = static_cast<int>(total_liquidity);
	(*it)->value = static_cast<int>(total_client_value);
}

	
void	Bank::loan(size_t id, long ammount) {
	if (ammount > static_cast<long>(this->liquidity))
		throw std::runtime_error("Our bank don't have such ammount of money to loan it");
	
	std::vector<Account*>::iterator it = this->clientAccounts.begin();
	while (it != this->clientAccounts.end() && (*it)->id != id)
		it++;
	if (it == this->clientAccounts.end())
		throw std::runtime_error("cannot loan. This client is not in our database");
	
	long total_client_value = static_cast<long>((*it)->value) + ammount;
	if (total_client_value > INT_MAX || total_client_value < INT_MIN)
		throw std::runtime_error("Client value exceeds integer limits");

	this->liquidity -= static_cast<int>(ammount);
	(*it)->value = static_cast<int>(total_client_value);
}


void	Bank::delete_account(size_t id) {
	std::vector<Account*>::iterator it = this->clientAccounts.begin();
	while (it != this->clientAccounts.end() && (*it)->id != id)
		it++;
	if (it == this->clientAccounts.end())
		throw std::runtime_error("cannot remove an account that is not in our database");
	
	delete *it;	
	this->clientAccounts.erase(it);
}

Bank::~Bank() {
	std::vector<Account*>::iterator it;
	for (it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++){
		delete *it;
	}
}


std::ostream& operator << (std::ostream& p_os, const Bank& p_bank) 	{
		p_os << "Bank informations : " << std::endl;
		p_os << "Liquidity : " << p_bank.liquidity << " cents." << std::endl;
		std::vector<Account*>::const_iterator cit;
		for (cit = p_bank.clientAccounts.begin(); cit != p_bank.clientAccounts.end(); cit++){
			 p_os << **cit  << std::endl;
		}
		return (p_os);
}
