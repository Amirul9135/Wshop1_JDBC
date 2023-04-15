#include <iostream>
#include <string>
#include <conio.h>
#include "Account.h"
using namespace std;

char menu(string, string*,int, string);
void loginMenu();
void registration();
void homeMenu(Account);
void profileMenu(Account user);
void accountList(Account user);

int main() { 
	string* items = new string[3]{"Register","login","exit"};
	char option = '\0';
	while (option != '1' && option != '2' && option != '3') {
		option = menu("Welcome !!", items, 3, "======");
		cout << option;
	}
	switch (option)
	{
	case '1':
		registration();
		break;
	case '2':
		loginMenu();
		break;
	default:
		break;
	}
}

void registration() {
	string* menus = new string[5]{ "username :","password :","email :","Register","Back" };
	Account newAcc;
	string username, password, email;
	char option = '\0';
	while (1) {
		while (option != '1' && option != '2' && option != '3' && option != '4' && option != '5') {
			option = menu("Registration Form", menus, 5, "Please select an option:");
		}
		switch (option) {
		case '1':
			cin.clear();
			cout << "insert username: ";
			cin >> username;
			menus[0] = "username : " + username;
			option = '\0';
			break;
		case '2':
			cin.clear();
			cout << "insert password: ";
			cin >> password;
			menus[1] = "password : " + password;
			option = '\0';
			break;
		case '3':
			cin.clear();
			cout << "insert email: ";
			cin >> email;
			menus[2] = "email : " + email;
			option = '\0';
			break;
		case '4':
			newAcc.username = username;
			newAcc.password = password;
			newAcc.email = email;
			newAcc.insert();
			cout << endl << "Regisration successul";
			_getch();
			main();
			break;
		case '5':
			main();
			break;
	}
}

}

void loginMenu() { 
	string* menus = new string[4]{ "username :","password :","login","Back" };
	Account account;
	char option = '\0';
	while (1) {
		option = '\0';
		option = menu("====LOGIN====", menus, 4, "Please enter your credential by selecting an option using the number");
		switch (option){
		case '1':
			cin.clear();
			cout << "Insert your username : ";
			cin >> account.username;
			menus[0] = "username : " + account.username; 
			break;
		case '2':
			cin.clear();
			cout << "Insert your password : ";
			cin >> account.password;
			menus[1] = "password : " + account.password;
			break;
		case '3': 
			account.login();
			if (account.accountId == -1) {
				cout << "Invalid Credential please try again"; 
				_getch();
			}
			else {
				homeMenu(account);
			}
			break;
		case '4':
			main();
			break;
		}
	}
}

void homeMenu(Account user) {
	string* menus = new string[3]{ "profile :","list","Logout" }; 
	char option = '\0';
	while (1) {
		option = '\0';
		option = menu("Welcome " + user.username + " !", menus, 3, "Press the number to select an option");
		switch (option){
		case '1':
			profileMenu(user);
			break;
		case '2': 
			accountList(user);
			break;
		case '3': 
			main();
			break;
		}
	}
}

void profileMenu(Account user) {
	string* menus = new string[7]{ "username : " + user.username,"password : " + user.password,"email : " + user.email,"reset", "save","back","Delete account"};
	string username = "", pass = "", email = "";
	char option = '\0';
	bool change = false;
	while (1) {
		option = '\0';
		option = menu("==Profile==", menus, 7, "Press the number to select an option");
		switch (option){
		case '1': 
			cout << "insert new username : ";
			cin.ignore();
			cin >> username;
			menus[0] = "username : " + username;
			break;
		case '2': 
			cout << "insert new password : ";
			cin.ignore();
			cin >> pass;
			menus[1] = "password : " + pass;
			break;
		case '3': 
			cout << "insert new email : ";
			cin.ignore();
			cin >> email;
			menus[2] = "email : " + email;
			break;
		case '4': //reset 
			username = "";
			pass = "";
			email = "";
			menus[0] = "username : " + user.username;
			menus[1] = "password : " + user.password;
			menus[2] = "email : " + user.email;
			break;
		case '5'://save
			if (!username.empty()) {
				change = true;
				user.username = username;
			}
			if (!pass.empty()) {
				change = true;
				user.password = pass;
			}
			if (!email.empty()) {
				change = true;
				user.email = email;
			}
			if (change) {
				user.update();
				cout << "Information updated successfully";
				_getch();
				profileMenu(user);
			}
			break;
		case '6'://back
			homeMenu(user);
			break;
		case '7'://del acc
			cout << "Are you sure you would like to delete your account? (y/n)";
			option = _getch();
			if (option == 'y' || option == 'Y') {
				user.remove();
				main();
			} 
			break;
		}
	}

}


void accountList(Account user) {
	Account searchAcc;
	searchAcc.username = "t";
	searchAcc.email = "om";
	vector<Account> accList = searchAcc.search("username", false);
	if (accList.size() == 0) {
		cout << "No account";
	}
	else {
		for (int i = 0; i < accList.size(); i++) {
			cout << endl << accList[i].username << " | " << accList[i].email << endl;
		}
	}
	_getch();
}

char menu(string title, string* items,int count, string footer) {
	system("cls");
	cout << title << endl;
	for (int i = 0; i < count; i++) {
		cout << i+1 << ") " + items[i]<< endl;
	}
	cout << endl << footer << endl;
	return _getch();
}

