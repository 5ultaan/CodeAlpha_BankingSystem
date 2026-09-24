// ============================================================
//         (C++)  BANKING SYSTEM - CodeAlpha Project
// ============================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cctype>
#include <windows.h>

using namespace std;


const int CLR_DEFAULT = 7;
const int CLR_BORDER = 3;      // Aqua
const int CLR_TITLE = 6;       // Gold
const int CLR_LABEL = 11;      // Light aqua
const int CLR_INPUT = 15;      // Bright white
const int CLR_SUCCESS = 10;    // Green
const int CLR_ERROR = 12;      // Red
const int CLR_MENU = 14;       // Yellow

void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen()
{
	system("cls");
}

void printLine(char symbol = '=', int width = 72)
{
	setColor(CLR_BORDER);

	for (int i = 0; i < width; i++)
	{
		cout << symbol;
	}

	cout << endl;
	setColor(CLR_DEFAULT);
}

void printTitle(string title)
{
	printLine('=');

	setColor(CLR_TITLE);
	cout << "                    " << title << endl;

	printLine('=');
	setColor(CLR_DEFAULT);
}

void pauseScreen()
{
	setColor(CLR_MENU);
	cout << "\nPress Enter to continue...";
	setColor(CLR_DEFAULT);

	cin.ignore(10000, '\n');
}

// ------------------------------------------------------------
// Input Helpers
// ------------------------------------------------------------
string readText(string message)
{
	string input;

	while (true)
	{
		setColor(CLR_LABEL);
		cout << message;
		setColor(CLR_INPUT);

		getline(cin, input);

		if (input.length() > 0)
		{
			return input;
		}

		setColor(CLR_ERROR);
		cout << "Error: This field cannot be empty.\n";
		setColor(CLR_DEFAULT);
	}
}

double readPositiveAmount(string message)
{
	string input;
	double amount;

	while (true)
	{
		try
		{
			setColor(CLR_LABEL);
			cout << message;
			setColor(CLR_INPUT);

			getline(cin, input);

			amount = stod(input);

			if (amount <= 0)
			{
				throw out_of_range("Amount must be positive.");
			}

			return amount;
		}
		catch (exception&)
		{
			setColor(CLR_ERROR);
			cout << "Error: Enter a valid amount greater than zero.\n";
			setColor(CLR_DEFAULT);
		}
	}
}

string readAccountNumber(string message)
{
	string accountNumber;

	while (true)
	{
		setColor(CLR_LABEL);
		cout << message;
		setColor(CLR_INPUT);

		getline(cin, accountNumber);

		bool valid = true;

		if (accountNumber.length() == 0)
		{
			valid = false;
		}

		for (int i = 0; i < accountNumber.length(); i++)
		{
			if (!isdigit(accountNumber[i]))
			{
				valid = false;
			}
		}

		if (valid)
		{
			return accountNumber;
		}

		setColor(CLR_ERROR);
		cout << "Error: Account number must contain digits only.\n";
		setColor(CLR_DEFAULT);
	}
}

// ------------------------------------------------------------
// Get current date and time
// ------------------------------------------------------------
string getCurrentDateTime()
{
	time_t currentTime = time(0);
	tm timeInfo;

	localtime_s(&timeInfo, &currentTime);

	char dateTime[30];

	strftime(dateTime, sizeof(dateTime),
		"%d-%m-%Y %I:%M %p", &timeInfo);

	return dateTime;
}

// ============================================================
// CLASS: Transaction
// ============================================================
class Transaction
{
private:
	string type;
	double amount;
	string description;
	string dateTime;

public:
	Transaction()
	{
		type = "";
		amount = 0;
		description = "";
		dateTime = "";
	}

	Transaction(string newType, double newAmount, string newDescription)
	{
		type = newType;
		amount = newAmount;
		description = newDescription;
		dateTime = getCurrentDateTime();
	}

	void display()
	{
		cout << left
			<< setw(16) << type
			<< setw(14) << fixed << setprecision(2) << amount
			<< setw(25) << description
			<< dateTime << endl;
	}
};

// ============================================================
// CLASS: Customer
// ============================================================
class Customer
{
private:
	string customerID;
	string fullName;
	string cnic;
	string phoneNumber;

public:
	Customer(string id, string name, string customerCnic, string phone)
	{
		customerID = id;
		fullName = name;
		cnic = customerCnic;
		phoneNumber = phone;
	}

	string getCustomerID()
	{
		return customerID;
	}

	string getCNIC()
	{
		return cnic;
	}

	string getName()
	{
		return fullName;
	}

	void display()
	{
		cout << "\nCustomer ID: " << customerID << endl;
		cout << "Name       : " << fullName << endl;
		cout << "CNIC       : " << cnic << endl;
		cout << "Phone      : " << phoneNumber << endl;
	}
};

// ============================================================
// CLASS: Account
// ============================================================
class Account
{
private:
	string accountNumber;
	string customerCNIC;
	string accountType;
	double balance;

	Transaction* transactions;
	int transactionCount;
	int transactionCapacity;

	void increaseTransactionCapacity()
	{
		transactionCapacity = transactionCapacity * 2;

		Transaction* temporaryTransactions =
			new Transaction[transactionCapacity];

		for (int i = 0; i < transactionCount; i++)
		{
			temporaryTransactions[i] = transactions[i];
		}

		delete[] transactions;
		transactions = temporaryTransactions;
	}

public:
	Account(string number, string cnic, string type)
	{
		accountNumber = number;
		customerCNIC = cnic;
		accountType = type;
		balance = 0;

		transactionCount = 0;
		transactionCapacity = 5;

		transactions = new Transaction[transactionCapacity];
	}

	~Account()
	{
		delete[] transactions;
	}

	string getAccountNumber()
	{
		return accountNumber;
	}

	string getCustomerCNIC()
	{
		return customerCNIC;
	}

	double getBalance()
	{
		return balance;
	}

	void addTransaction(string type, double amount, string description)
	{
		if (transactionCount == transactionCapacity)
		{
			increaseTransactionCapacity();
		}

		transactions[transactionCount] =
			Transaction(type, amount, description);

		transactionCount++;
	}

	void deposit(double amount, string description)
	{
		balance = balance + amount;
		addTransaction("Deposit", amount, description);
	}

	bool withdraw(double amount, string description)
	{
		if (amount > balance)
		{
			return false;
		}

		balance = balance - amount;
		addTransaction("Withdrawal", amount, description);

		return true;
	}

	void displayAccountInfo(string customerName)
	{
		printTitle("ACCOUNT INFORMATION");

		setColor(CLR_LABEL);
		cout << "Account Number : ";
		setColor(CLR_INPUT);
		cout << accountNumber << endl;

		setColor(CLR_LABEL);
		cout << "Account Holder : ";
		setColor(CLR_INPUT);
		cout << customerName << endl;

		setColor(CLR_LABEL);
		cout << "Account Type   : ";
		setColor(CLR_INPUT);
		cout << accountType << endl;

		setColor(CLR_LABEL);
		cout << "Current Balance: ";
		setColor(CLR_SUCCESS);
		cout << fixed << setprecision(2) << balance << endl;

		setColor(CLR_DEFAULT);
	}

	void displayTransactions()
	{
		printTitle("RECENT TRANSACTION HISTORY");

		if (transactionCount == 0)
		{
			setColor(CLR_ERROR);
			cout << "No transactions found for this account.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		setColor(CLR_BORDER);
		cout << left
			<< setw(16) << "Type"
			<< setw(14) << "Amount"
			<< setw(25) << "Description"
			<< "Date and Time" << endl;

		printLine('-');

		setColor(CLR_INPUT);

		int start = 0;

		if (transactionCount > 10)
		{
			start = transactionCount - 10;
		}

		for (int i = start; i < transactionCount; i++)
		{
			transactions[i].display();
		}

		setColor(CLR_DEFAULT);
	}
};

// ============================================================
// CLASS: Bank
// ============================================================
class Bank
{
private:
	Customer** customers;
	Account** accounts;

	int customerCount;
	int accountCount;

	int customerCapacity;
	int accountCapacity;

	int nextCustomerNumber;
	int nextAccountNumber;

	void increaseCustomerCapacity()
	{
		customerCapacity = customerCapacity * 2;

		Customer** temporaryCustomers =
			new Customer*[customerCapacity];

		for (int i = 0; i < customerCount; i++)
		{
			temporaryCustomers[i] = customers[i];
		}

		delete[] customers;
		customers = temporaryCustomers;
	}

	void increaseAccountCapacity()
	{
		accountCapacity = accountCapacity * 2;

		Account** temporaryAccounts =
			new Account*[accountCapacity];

		for (int i = 0; i < accountCount; i++)
		{
			temporaryAccounts[i] = accounts[i];
		}

		delete[] accounts;
		accounts = temporaryAccounts;
	}

public:
	Bank()
	{
		customerCount = 0;
		accountCount = 0;

		customerCapacity = 5;
		accountCapacity = 5;

		nextCustomerNumber = 1001;
		nextAccountNumber = 500001;

		customers = new Customer*[customerCapacity];
		accounts = new Account*[accountCapacity];
	}

	~Bank()
	{
		for (int i = 0; i < customerCount; i++)
		{
			delete customers[i];
		}

		for (int i = 0; i < accountCount; i++)
		{
			delete accounts[i];
		}

		delete[] customers;
		delete[] accounts;
	}

	Customer* findCustomer(string cnic)
	{
		for (int i = 0; i < customerCount; i++)
		{
			if (customers[i]->getCNIC() == cnic)
			{
				return customers[i];
			}
		}

		return NULL;
	}

	Account* findAccount(string accountNumber)
	{
		for (int i = 0; i < accountCount; i++)
		{
			if (accounts[i]->getAccountNumber() == accountNumber)
			{
				return accounts[i];
			}
		}

		return NULL;
	}

	void createCustomer()
	{
		clearScreen();
		printTitle("CREATE NEW CUSTOMER");

		string fullName = readText("Enter full name: ");
		string cnic = readText("Enter CNIC: ");
		string phone = readText("Enter phone number: ");

		if (findCustomer(cnic) != NULL)
		{
			setColor(CLR_ERROR);
			cout << "\nError: A customer with this CNIC already exists.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		if (customerCount == customerCapacity)
		{
			increaseCustomerCapacity();
		}

		string customerID = "CUS" + to_string(nextCustomerNumber);

		customers[customerCount] =
			new Customer(customerID, fullName, cnic, phone);

		customerCount++;
		nextCustomerNumber++;

		setColor(CLR_SUCCESS);
		cout << "\nCustomer created successfully.\n";
		cout << "Customer ID: " << customerID << endl;
		setColor(CLR_DEFAULT);
	}

	void createAccount()
	{
		clearScreen();
		printTitle("CREATE BANK ACCOUNT");

		string cnic = readText("Enter existing customer CNIC: ");

		Customer* customer = findCustomer(cnic);

		if (customer == NULL)
		{
			setColor(CLR_ERROR);
			cout << "\nError: Customer not found. Create customer first.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		string accountType = readText(
			"Enter account type (Saving/Current): "
		);

		if (accountCount == accountCapacity)
		{
			increaseAccountCapacity();
		}

		string accountNumber = to_string(nextAccountNumber);

		accounts[accountCount] =
			new Account(accountNumber, cnic, accountType);

		accountCount++;
		nextAccountNumber++;

		setColor(CLR_SUCCESS);
		cout << "\nAccount created successfully.\n";
		cout << "Account Number: " << accountNumber << endl;
		setColor(CLR_DEFAULT);
	}

	void depositMoney()
	{
		clearScreen();
		printTitle("DEPOSIT MONEY");

		string accountNumber = readAccountNumber("Enter account number: ");

		Account* account = findAccount(accountNumber);

		if (account == NULL)
		{
			setColor(CLR_ERROR);
			cout << "\nError: Account not found.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		double amount = readPositiveAmount("Enter deposit amount: ");

		account->deposit(amount, "Cash Deposit");

		setColor(CLR_SUCCESS);
		cout << "\nDeposit completed successfully.\n";
		cout << "New Balance: " << fixed << setprecision(2)
			<< account->getBalance() << endl;
		setColor(CLR_DEFAULT);
	}

	void withdrawMoney()
	{
		clearScreen();
		printTitle("WITHDRAW MONEY");

		string accountNumber = readAccountNumber("Enter account number: ");

		Account* account = findAccount(accountNumber);

		if (account == NULL)
		{
			setColor(CLR_ERROR);
			cout << "\nError: Account not found.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		double amount = readPositiveAmount("Enter withdrawal amount: ");

		bool successful = account->withdraw(amount, "Cash Withdrawal");

		if (successful)
		{
			setColor(CLR_SUCCESS);
			cout << "\nWithdrawal completed successfully.\n";
			cout << "Remaining Balance: " << fixed << setprecision(2)
				<< account->getBalance() << endl;
		}
		else
		{
			setColor(CLR_ERROR);
			cout << "\nError: Insufficient balance.\n";
		}

		setColor(CLR_DEFAULT);
	}

	void transferMoney()
	{
		clearScreen();
		printTitle("FUND TRANSFER");

		string senderNumber =
			readAccountNumber("Enter sender account number: ");

		Account* sender = findAccount(senderNumber);

		if (sender == NULL)
		{
			setColor(CLR_ERROR);
			cout << "\nError: Sender account not found.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		string receiverNumber =
			readAccountNumber("Enter receiver account number: ");

		Account* receiver = findAccount(receiverNumber);

		if (receiver == NULL)
		{
			setColor(CLR_ERROR);
			cout << "\nError: Receiver account not found.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		if (senderNumber == receiverNumber)
		{
			setColor(CLR_ERROR);
			cout << "\nError: Sender and receiver accounts cannot be same.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		double amount = readPositiveAmount("Enter transfer amount: ");

		bool successful = sender->withdraw(
			amount, "Transfer to " + receiverNumber
		);

		if (successful)
		{
			receiver->deposit(
				amount, "Transfer from " + senderNumber
			);

			setColor(CLR_SUCCESS);
			cout << "\nFund transfer completed successfully.\n";
			cout << "Sender Balance: " << fixed << setprecision(2)
				<< sender->getBalance() << endl;
		}
		else
		{
			setColor(CLR_ERROR);
			cout << "\nError: Insufficient balance for transfer.\n";
		}

		setColor(CLR_DEFAULT);
	}

	void viewAccountInfo()
	{
		clearScreen();

		string accountNumber = readAccountNumber("Enter account number: ");

		Account* account = findAccount(accountNumber);

		if (account == NULL)
		{
			setColor(CLR_ERROR);
			cout << "\nError: Account not found.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		Customer* customer = findCustomer(account->getCustomerCNIC());

		account->displayAccountInfo(customer->getName());
	}

	void viewTransactionHistory()
	{
		clearScreen();

		string accountNumber = readAccountNumber("Enter account number: ");

		Account* account = findAccount(accountNumber);

		if (account == NULL)
		{
			setColor(CLR_ERROR);
			cout << "\nError: Account not found.\n";
			setColor(CLR_DEFAULT);
			return;
		}

		account->displayTransactions();
	}
};

// ============================================================
// MAIN FUNCTION
// ============================================================
int main()
{
	Bank bank;
	string choice;

	while (true)
	{
		clearScreen();
		printTitle("SMART BANKING SYSTEM");

		setColor(CLR_MENU);
		cout << "  [1] Create Customer\n";
		cout << "  [2] Create Account\n";
		cout << "  [3] Deposit Money\n";
		cout << "  [4] Withdraw Money\n";
		cout << "  [5] Transfer Funds\n";
		cout << "  [6] View Account Information\n";
		cout << "  [7] View Transaction History\n";
		cout << "  [8] Exit System\n";

		setColor(CLR_LABEL);
		cout << "\nEnter your choice: ";
		setColor(CLR_INPUT);

		getline(cin, choice);

		if (choice == "1")
		{
			bank.createCustomer();
			pauseScreen();
		}
		else if (choice == "2")
		{
			bank.createAccount();
			pauseScreen();
		}
		else if (choice == "3")
		{
			bank.depositMoney();
			pauseScreen();
		}
		else if (choice == "4")
		{
			bank.withdrawMoney();
			pauseScreen();
		}
		else if (choice == "5")
		{
			bank.transferMoney();
			pauseScreen();
		}
		else if (choice == "6")
		{
			bank.viewAccountInfo();
			pauseScreen();
		}
		else if (choice == "7")
		{
			bank.viewTransactionHistory();
			pauseScreen();
		}
		else if (choice == "8")
		{
			clearScreen();
			printTitle("THANK YOU");

			setColor(CLR_SUCCESS);
			cout << "\nThank you for using Smart Banking System.\n\n";
			setColor(CLR_DEFAULT);

			break;
		}
		else
		{
			setColor(CLR_ERROR);
			cout << "\nInvalid option. Select a number from 1 to 8.\n";
			setColor(CLR_DEFAULT);

			pauseScreen();
		}
	}

	return 0;
}