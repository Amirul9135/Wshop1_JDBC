#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Account
{
public:
	int accountId;
	std::string username, password, email;
	Account();
	Account(int accountId);
	bool login();
	void insert();
	void update();
	void remove();
	void remove(int accountId);  
	std::vector<Account> search(std::string sort, bool asc);
};

#endif

