#include "Account.h"
#include "DBConnection.h"
#include <mysql/jdbc.h>

using namespace std;
using namespace sql;

Account::Account() {
	accountId = -1;
	username = "";
	password = "";
	email = "";
}

Account::Account(int accountId) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM account WHERE accountId=?");
	db.stmt->setInt(1, accountId);
	db.QueryResult(); 
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			accountId = db.res->getInt("accountId");
			username = db.res->getString("username");
			password = db.res->getString("password");
			email = db.res->getString("email");
		}
		db.~DBConnection();
	} 
	else {
		accountId = -1;
		username = "";
		password = "";
		email = "";
	}
}

void Account::insert() {
	DBConnection db;
	db.prepareStatement("Insert into account (username,password,email) VALUES (?,?,?)"); 
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, email);
	db.QueryStatement();
	db.~DBConnection();
}

void Account::update() {
	DBConnection db;
	db.prepareStatement("UPDATE account SET username=?, password=?, email=? WHERE accountId=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, email);
	db.stmt->setInt(4, accountId);
	db.QueryStatement();
	db.~DBConnection();
}

void Account::remove() {
	remove(accountId);
}

void Account::remove(int accountId) {
	DBConnection db;
	db.prepareStatement("DELETE FROM account WHERE accountId=?");
	db.stmt->setInt(1, accountId);
	db.QueryStatement();
	db.~DBConnection();
}

bool Account::login() {
	DBConnection db;
	db.prepareStatement("SELECT * FROM account WHERE username=? AND password=?");
	db.stmt->setString(1,username);
	db.stmt->setString(2,password);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			accountId = db.res->getInt("accountId");
			username = db.res->getString("username");
			password = db.res->getString("password");
			email = db.res->getString("email");
		}
		db.~DBConnection();
	}
	else {
		accountId = -1;
		username = "";
		password = "";
		email = "";
	}
}

 vector<Account>  Account::search(string sortBy = "username",bool asc = true) {
	vector<Account> accList;
	DBConnection db;
	string query = "SELECT accountId, username, email FROM account ";
	string condition = "";
	string order = " ORDER BY " + sortBy + (asc ? " ASC" : " DESC");
	if (!username.empty()) {
		condition += " username LIKE ? ";
	}
	if (!email.empty()) {
		if (!condition.empty()) {
			condition += " AND ";
		}
		condition += " email LIKE ? ";
	} 
	if (!condition.empty()) {
		query += " WHERE " + condition + order; 
		db.prepareStatement(query); 
		if (!username.empty()) {
			db.stmt->setString(1, "%" + username + "%");
			if (!email.empty()) {
				db.stmt->setString(2, "%" + email + "%");
			}
		}
		else {
			if (!email.empty()) {
				db.stmt->setString(1, "%" + email + "%");
			}
		}
	}
	else { 
		db.prepareStatement("SELECT accountId, username, email FROM account " + order);
	}


	db.QueryResult();
	if (db.res->rowsCount() > 0) {
		while (db.res->next()) {
			Account nacc;
			nacc.accountId = db.res->getInt("accountId");
			nacc.email = db.res->getString("email");
			nacc.username = db.res->getString("username");
			accList.push_back(nacc);
		}
	}
	return accList;
}


