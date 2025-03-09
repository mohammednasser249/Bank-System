#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<fstream>

using namespace std;


const string FileName = "Client.txt";
enum enChoice { List = 1, AddCleint = 2, DeleteAccount = 3, Update = 4, Find = 5, Transaction = 6, Exit = 7 };

void ShowMenuScreen();
void TransactionMenuScreen();
struct stClient {

	string AccNumber;
	string PinCode;
	string Name;
	string Phone;
	string AccBalance;
	bool Delete = false;
};


void PrintClient(stClient Client)
{
	cout << left << setw(20) << Client.AccNumber << setw(17) << Client.PinCode << setw(26) << Client.Name << setw(20) << Client.Phone << setw(18) << Client.AccBalance << endl;

}


void PrintMenu()
{
	cout << "\n-----------------------------------------------------------------------------------------------\n";
	cout << "\n| Account Number    | Pin Code      | Client Name          | Phone           | Balance         \n";
	cout << "\n-----------------------------------------------------------------------------------------------\n";

}

int SumOfTotalBalances(vector<stClient>Vclients)
{

	int sum = 0;

	for (stClient C : Vclients)
	{
		int balance = stoi(C.AccBalance);
		sum += balance;

	}

	return sum;

}


void TotalBalances(vector<stClient> Clients)
{
	int sum = SumOfTotalBalances(Clients);

	cout << setw(50) << "Client List " << Clients.size() << " Client(s).\n";
	PrintMenu();
	for (stClient& C : Clients)
	{
		PrintClient(C);
	}

	cout << "\n-----------------------------------------------------------------------------------------------\n";
	cout << "Total Balances = " << sum << endl;

}

void ShowListOfClients(vector<stClient> Clients)
{

	int sum = SumOfTotalBalances(Clients);

	cout << setw(50) << "Client List " << Clients.size() << " Client(s).\n";
	PrintMenu();
	for (stClient& C : Clients)
	{
		PrintClient(C);
	}

}



vector<string> SplitString(string Line, string delim = "#//#")
{
	int pos;
	string NewWord;
	vector<string>Words;

	while ((pos = Line.find(delim)) != std::string::npos)
	{

		NewWord = Line.substr(0, pos);
		if (NewWord != " ")
			Words.push_back(NewWord);

		Line.erase(0, pos + delim.length());

	}
	if (Line != " ") // To save the last word 
		Words.push_back(Line);

	return Words;
}


stClient ConvertLineToRecord(string line)
{

	vector<string> Words;
	Words = SplitString(line);
	stClient Client;

	Client.AccNumber = Words[0];
	Client.PinCode = Words[1];
	Client.Name = Words[2];
	Client.Phone = Words[3];
	Client.AccBalance = Words[4];


	return Client;


}


vector<stClient>LoadDataFromFileToVector()
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	vector<stClient>Clients;
	stClient Client;

	string line;

	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{
			Client = ConvertLineToRecord(line);
			Clients.push_back(Client);
		}

		MyFile.close();

	}

	return Clients;
}



void UsersChoice(short c);


bool isFoundByAccNumber(string AccNumber, vector<stClient>Clients, stClient& Client)
{

	for (stClient C : Clients)
	{
		if (C.AccNumber == AccNumber)
		{
			Client = C;
			return true;
		}

	}

	return false;


}

void PrintClientData(stClient Client)
{
	cout << "The following are the client details : \n";

	cout << "-------------------------------------------------\n";
	cout << "Account Number : " << Client.AccNumber << endl;
	cout << "Pin Code : " << Client.PinCode << endl;
	cout << " Name : " << Client.Name << endl;
	cout << "Phone: " << Client.Phone << endl;
	cout << "Account Balance : " << Client.AccBalance << endl;
	cout << "-------------------------------------------------\n";


}


void MarkClientAsDelete(string AccNum, vector<stClient>& Clients)
{

	for (stClient& C : Clients)
	{
		if (C.AccNumber == AccNum)
		{
			C.Delete = true;
		}
	}

}

void FindClient(string AccNum, vector<stClient>Clients)
{
	stClient Client;
	cout << "Please enter client Account number :\n";
	cin >> AccNum;

	if (isFoundByAccNumber(AccNum, Clients, Client))
	{
		PrintClientData(Client);
	}
	else
		cout << "Client number [ " << AccNum << " ] was Not Found !\n";


}

stClient AddClient(vector<stClient>Clients)
{



	stClient Client;


	cout << "\n-------------------------\n";
	cout << "    Add New Client        ";
	cout << "\n-------------------------\n";

	cout << "\nAdding New Client : \n";

	cout << "\nEnter Client Account: ";
	cin >> Client.AccNumber;

	while (isFoundByAccNumber(Client.AccNumber, Clients, Client))
	{
		cout << "Client with [ " << Client.AccNumber << "] already exists Enter anohter Account Number :";
		cin >> Client.AccNumber;
	}

	cout << "Enter Pin Code : ";
	cin >> Client.PinCode;
	cin.ignore();

	cout << "Enter the Name : ";
	getline(cin, Client.Name);

	cout << "Enter the phone number ";
	cin >> Client.Phone;

	cout << "Enter the Account Balance : ";
	cin >> Client.AccBalance;

	return Client;

}

string ConvertRecordToLine(stClient Client, string delim = "#//#")
{
	string line = "";

	line += Client.AccNumber + delim;
	line += Client.PinCode + delim;
	line += Client.Name + delim;
	line += Client.Phone + delim;
	line += Client.AccBalance;

	return line;
}


void SaveClientToTheFile(vector<stClient>& Clients, enChoice Choice)
{
	stClient Client; // Adding a new client ;
	if (Choice == enChoice::AddCleint)
	{
		Client = AddClient(Clients);
		Clients.push_back(Client);
	}

	fstream MyFile;
	MyFile.open(FileName, ios::out);// Write mode
	string line;
	if (MyFile.is_open())
	{

		for (stClient C : Clients)
		{
			if (!C.Delete)
			{
				line = ConvertRecordToLine(C);
				MyFile << line << endl;
			}
		}

		MyFile.close();
	}


}


stClient UpdateClient(string acc)

{
	stClient Client;

	Client.AccNumber = acc;

	cout << "Enter Pin Code : ";
	cin >> Client.PinCode;

	cin.ignore();

	cout << "Enter Name : ";
	getline(cin, Client.Name);

	cout << "Etner Phone : ";
	cin >> Client.Phone;

	cout << "Enter New Account Balance :";
	cin >> Client.AccBalance;

	return Client;


}

void UpdateClientInfo(string& AccNum, vector<stClient>& Clients)
{

	stClient UpdatedClient;
	char c;
	cout << "\n-------------------------\n";
	cout << "   Update Client Screen      ";
	cout << "\n-------------------------\n";

	cout << "Please enter Account Number ?";
	cin >> AccNum;

	if (isFoundByAccNumber(AccNum, Clients, UpdatedClient))
	{

		PrintClientData(UpdatedClient);

		cout << "Are you sure do you want to update this client ?  Y/N \n";
		cin >> c;

		if (c == 'Y' || c == 'y')
		{
			for (stClient& C : Clients)
			{
				if (C.AccNumber == AccNum)
				{
					C = UpdateClient(AccNum);
					break;
				}
			}

			cout << "Client has been updated succssfully \n";

			SaveClientToTheFile(Clients, enChoice::Update);
		}




	}
	else
		cout << "Client number [ " << AccNum << " ] was Not Found !\n";
}


void DeleteClient(string& AccNum, vector<stClient>& Clients)
{
	char c;
	stClient UpdatedClient;

	cout << "\n-------------------------\n";
	cout << "    Delete Client Screen      ";
	cout << "\n-------------------------\n";


	cout << "Please enter Account Number ?";
	cin >> AccNum;

	if (isFoundByAccNumber(AccNum, Clients, UpdatedClient))
	{

		PrintClientData(UpdatedClient);

		cout << "\n\nAre you sure you want delete this client ? y/n ?";
		cin >> c;

		if (c == 'Y' || c == 'y')
		{
			MarkClientAsDelete(AccNum, Clients);
			SaveClientToTheFile(Clients, enChoice::DeleteAccount);
			cout << "\nRecord was deleted succssfully\n";
			LoadDataFromFileToVector();
		}


	}
	else
	{
		cout << "Client number [ " << AccNum << " ] was Not Found !\n";
	}


}







void ShowMenuScreen()
{
	short Choice;

	cout << "=============================================\n";
	cout << "             Main Menu Screen                 \n";
	cout << "=============================================\n";

	cout << "          [1] Show Client List.\n";
	cout << "          [2] Add New Client .\n";
	cout << "          [3] Delete Client .\n";
	cout << "          [4] Update Client .\n";
	cout << "          [5] Find Client .\n";
	cout << "          [6] Transactions .\n";
	cout << "          [7] Exit .\n";

	cout << "=============================================\n";
	cout << "Choose What do you want to do ? [ 1 - 7 ]\n";
	cin >> Choice;
	UsersChoice(Choice);


}

string ReadAccNumber()
{
	string AccN;
	cout << "Please enter the account nuumber ? ";
	cin >> AccN;

	return AccN;
}



enum enTransaction { Depost = 1, Withdraw = 2, TotalBalance = 3, MainMenu = 4 };




void WithDraw(string& AccNumber, vector<stClient>& Vclients)
{

	stClient Client;
	cout << "\n-------------------------\n";
	cout << "     WithDraw Screen        ";
	cout << "\n-------------------------\n";

	cout << "Please enter Account Number ?";
	cin >> AccNumber;

	while (!isFoundByAccNumber(AccNumber, Vclients, Client))
	{

		cout << "Client [" << AccNumber << "] does not exist .";
		cin >> AccNumber;

	}
	PrintClientData(Client);
	short Amount;
	char c;
	cout << "\n\nPlease enter  amount to withdraw : ";
	cin >> Amount;


	int total;


	for (stClient& Client : Vclients)
	{
		if (Client.AccNumber == AccNumber)
		{
			int balance = stoi(Client.AccBalance);
			while (balance < Amount)
			{
				cout << "Amount exceeds the balance , you can withdraw up to " << balance << endl;
				cin >> Amount;
			}

			cout << "Are you sure you want to perform this transaction? y/n ?";
			cin >> c;

			if (c == 'Y' || c == 'y')
			{
				total = balance - Amount;
				Client.AccBalance = to_string(total);
				cout << "\nAmount has been Withdrawed successfully .";
				cout << "\nNew Balance is : " << total << endl;

				SaveClientToTheFile(Vclients, enChoice::Find);
				return;
			}
			else
			{
				cout << "Withdraw faild \n";
				return;
			}


		}
	}




}


void Deposit(string& AccNumber, vector<stClient>& Vclients)
{

	stClient Client;
	cout << "\n-------------------------\n";
	cout << "     Deposit Screen        ";
	cout << "\n-------------------------\n";

	cout << "Please enter Account Number ?";
	cin >> AccNumber;

	while (!isFoundByAccNumber(AccNumber, Vclients, Client))
	{

		cout << "Client [" << AccNumber << "] does not exist .";
		cin >> AccNumber;

	}
	PrintClientData(Client);
	short Amount;
	char c;
	cout << "\n\n Please enter deposit amount ";
	cin >> Amount;

	cout << "Are you sure you want to perform this transaction? y/n ?";
	cin >> c;

	int total;
	if (c == 'y' || c == 'Y')
	{

		for (stClient& Client : Vclients)
		{
			if (Client.AccNumber == AccNumber)
			{
				int balance = stoi(Client.AccBalance);
				total = balance + Amount;
				Client.AccBalance = to_string(total);
				break;
			}
		}

		cout << "Amount has been deposited successfully .";
		cout << " New Balance is : " << total << endl;

		SaveClientToTheFile(Vclients, enChoice::Find);
	}
	else {
		cout << "Transaction Faild \n";
	}

}

void TransactionsOptions(enTransaction TransactionOpt)
{

	vector<stClient>Clients;
	Clients = LoadDataFromFileToVector();
	string AccNumber;

	switch (TransactionOpt)
	{
	case enTransaction::Depost:
		system("cls");
		Deposit(AccNumber, Clients);
		cout << "\n\nClick any key to go back to menu...";
		system("pause>0");
		system("cls");
		TransactionMenuScreen();
		break;
	case enTransaction::Withdraw:
		system("cls");
		WithDraw(AccNumber, Clients);
		cout << "\n\nClick any key to go back to menu...";
		system("pause>0");
		system("cls");
		TransactionMenuScreen();
		break;
	case enTransaction::TotalBalance:
		system("cls");
		TotalBalances(Clients);
		cout << "\n\nClick any key to go back to menu...";
		system("pause>0");
		system("cls");
		TransactionMenuScreen();
		break;
	case enTransaction::MainMenu:
		system("cls");
		ShowMenuScreen();
		break;
	default:
		break;
	}


}

void TransactionMenuScreen()
{

	cout << "=============================================\n";
	cout << "           Transaction Menu Screen           \n";
	cout << "=============================================\n";

	cout << "          [1] Deposit.\n";
	cout << "          [2] Withdraw .\n";
	cout << "          [3] Total Balances .\n";
	cout << "          [4] Main Menu .\n";
	cout << "=============================================\n";
	short choice;

	cout << "Enter what do you want to do [ 1 - 4 ] \n";
	cin >> choice;

	TransactionsOptions((enTransaction)choice);
}

void UsersChoice(short c)
{
	enChoice C;
	C = (enChoice)c;

	vector<stClient> vClients;
	vClients = LoadDataFromFileToVector();
	string AccNumber;

	switch (C)
	{
	case enChoice::List:
		system("cls");
		ShowListOfClients(vClients);
		cout << "\n\nClick any key to go back to menu...";
		system("pause>0");
		system("cls");
		cout << endl;
		ShowMenuScreen();
		break;
	case enChoice::AddCleint:
		system("cls");
		SaveClientToTheFile(vClients, enChoice::AddCleint);
		cout << "\n\nClick any key to go back to menu...";
		system("pause>0");
		system("cls");
		cout << endl;
		ShowMenuScreen();
		break;
	case enChoice::DeleteAccount:
		system("cls");
		DeleteClient(AccNumber, vClients);
		cout << "\n\nClick any key to go back to menu...";
		system("pause>0");
		system("cls");
		cout << endl;
		ShowMenuScreen();
		break;
	case enChoice::Update:
		system("cls");
		UpdateClientInfo(AccNumber, vClients);
		cout << "\n\nClick any key to go back to menu...";
		system("pause>0");
		system("cls");
		cout << endl;
		ShowMenuScreen();
		break;

	case enChoice::Find:
		system("cls");
		FindClient(AccNumber, vClients);
		cout << "\n\nClick any key to go back to menu...";
		system("pause>0");
		system("cls");
		cout << endl;
		ShowMenuScreen();
		break;

	case enChoice::Transaction:
		system("cls");
		TransactionMenuScreen();
		break;
	case enChoice::Exit:
		system("cls");
		return;
		break;
	default:
		break;


	}
}


int main()
{

	ShowMenuScreen();

	return 0;
}
