<<<<<<< HEAD
// Banking System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <fstream>

using namespace std;

const string FILENAME = "Clients.txt";
const string SEPARATOR = "|##|";



struct sclient {
    string account_number = "";
    string full_name = "";
    string phone_number = "";
    string pin_code = "";
    double account_balance = 0;

    bool mark_for_delete = false;
    bool mark_for_update = true;

};

sclient add_new_client(sclient client) {

    cout << "------------------------------------------------------\n";
    cout <<"     Client creation screen                             \n";
    cout << "------------------------------------------------------\n";

    cout << "Enter client account number: "; getline(cin >> ws, client.account_number);
    cout << "Enter client full name: "; getline(cin, client.full_name);
    cout << "Enter client phone number: "; getline(cin, client.phone_number);
    cout << "Enter client pin code: "; getline(cin, client.pin_code);
    cout << "Enter client account balance: "; cin >> client.account_balance;

    return client;
}

sclient update_client(string account_number) {

    sclient client;

    client.account_number = account_number;

    cout << "------------------------------------------------------\n";
    cout << "     Client update screen                             \n";
    cout << "------------------------------------------------------\n";
    
    cout << "Enter client full name: "; getline(cin>>ws, client.full_name);
    cout << "Enter client phone number: "; getline(cin, client.phone_number);
    cout << "Enter client pin code: "; getline(cin, client.pin_code);
    cout << "Enter client account balance: "; cin >> client.account_balance;

    return client;
}

string convert_client_record_to_data(const sclient& client) {
    return client.account_number + SEPARATOR +
        client.full_name + SEPARATOR +
        client.phone_number + SEPARATOR +
        client.pin_code + SEPARATOR +
        to_string(client.account_balance);
}

char show_main_menu() {
    char choice;
    cout << "----------------------------------------------\n";
    cout << "  \t\t MAIN MENU \n";
    cout << "----------------------------------------------\n";
    cout << "\t [1]: Add new client\n";
    cout << "\t [2]: Show all clients list\n";
    cout << "\t [3]: Delete client\n";
    cout << "\t [4]: Update client record\n";
    cout << "\t [5]: Search client by account number\n";
    cout << "\t [6]: Transactions\n";
    cout << "\t [7]: Exit the program\n";
    cout << "----------------------------------------------\n";
    cout << "----------------------------------------------\n\n";
    cout << "\t <|>: Select an option to proceed: "; cin >> choice; cout << endl;

    return choice;
}

char show_transactions_menu()
{
    char option;
    cout << "----------------------------------------------\n";
    cout << "  \t\t TRANSACTIONS MENU \n";
    cout << "----------------------------------------------\n";
    cout << "\t [1]: Deposit\n";
    cout << "\t [2]: Withdraw\n";
    cout << "\t [3]: Show total balances\n";
    cout << "\t [4]: Main menu\n";
    cout << "----------------------------------------------\n";
    cout << "----------------------------------------------\n\n";
    cout << "\t <|>: Select an option to proceed: "; cin >> option; cout << endl;

    return option;
}

vector<string> split_string(const string& str, const string& delim) {
    vector<string> vString;
    size_t start = 0, end;

    while ((end = str.find(delim, start)) != string::npos) {
        string part = str.substr(start, end - start);
        if (!part.empty()) {
            vString.push_back(part);
        }
        start = end + delim.length();
    }

    if (start < str.length()) {
        vString.push_back(str.substr(start));
    }

    return vString;
}

sclient ConvertLinetoRecord(const string& line) {
    sclient client;
    vector<string> vClientData = split_string(line, SEPARATOR);

    if (vClientData.size() == 5) {
        client.account_number = vClientData[0];
        client.full_name = vClientData[1];
        client.phone_number = vClientData[2];
        client.pin_code = vClientData[3];
        client.account_balance = stod(vClientData[4]);
    }

    return client;
}

vector<sclient> LoadClientsDataFromFile() {
    vector<sclient> vclient;
    fstream file(FILENAME, ios::in);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            sclient client = ConvertLinetoRecord(line);
            vclient.push_back(client);
        }

        file.close();
    }
    else {
        cerr << "Error: Unable to open file for reading.\n";
    }

    return vclient;
}

void store_client_info_in_file(sclient& client) {
    vector<sclient> existingClients = LoadClientsDataFromFile();

    client = add_new_client(client);
    string client_data = convert_client_record_to_data(client);

    // Check if the account number already exists
    for (const auto& existingClient : existingClients) {
        if (existingClient.account_number == client.account_number) {
            cerr << "Error: Account number already exists. Please use a unique account number.\n";
            return;
        }
    }

    fstream file(FILENAME, ios::app);
    if (file.is_open()) {
        file << client_data << endl;
        cout << "Client was added successfully.\n";
        file.close();
    }
    else {
        cerr << "Error: Unable to open file for writing.\n";
    }
}




void PrintClientRecord(const sclient& client) {
    cout << "| " << setw(15) << left << client.account_number
        << "| " << setw(20) << left << client.full_name
        << "| " << setw(15) << left << client.phone_number
        << "| " << setw(10) << left << client.pin_code
        << "| " << setw(12) << fixed << setprecision(2) << left << client.account_balance << endl;
}

void Print_client_balances(const sclient& client) {
    cout << "| " << setw(15) << left << client.account_number
        << "| " << setw(20) << left << client.full_name
        << "| " << setw(12) << fixed << setprecision(2) << left << client.account_balance << endl;
}

void PrintAllClientsData(const vector<sclient>& vClients) {
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
    cout << "_______________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(20) << "Full Name"
        << "| " << left << setw(15) << "Phone Number"
        << "| " << left << setw(10) << "Pin Code"
        << "| " << left << setw(12) << "Balance" << endl;
    cout << "_______________________________________________________________________________________\n";

    for (const auto& client : vClients) {
        PrintClientRecord(client);
    }

    cout << "_______________________________________________________________________________________\n";
}

vector <sclient> delete_client_in_file(vector <sclient> &vclient, string FILENAME)
{
    fstream file;
    file.open(FILENAME, ios::out);
    string dataline;

    if (file.is_open())
    {
        for (sclient &c : vclient)
        {
            if (c.mark_for_delete == false)
            {
                dataline = convert_client_record_to_data(c);

                file << dataline << endl;

            }
        }
        file.close();
      

    }

    return vclient;

}

vector <sclient> update_clients_in_file(vector <sclient>& vclient, string FILENAME)
{
    fstream file;
    file.open(FILENAME, ios::out);
    string dataline;

    if (file.is_open())
    {
        for (sclient &c : vclient)
        {
            if (c.mark_for_update == true)
            {
                dataline = convert_client_record_to_data(c);

                file << dataline << endl;

            }
        }
        file.close();


    }

    return vclient;

}

void PrintClientCard(sclient client) {

    cout << "------------------------------------------------------\n";
    cout << "     Client card                             \n";
    cout << "------------------------------------------------------\n";


    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << client.account_number;
    cout << "\nFull name : " << client.full_name;
    cout << "\nPhone number : " << client.phone_number;
    cout << "\nPin code : " << client.pin_code;
    cout << "\nAccount balance: " << client.account_balance; cout << endl;
}

string read_account_number(string account_number)
{
   vector <sclient> vclients = LoadClientsDataFromFile();

    cout << "--------------------------------------------------\n";
    cout << "         Client search                        \n";
    cout << "--------------------------------------------------\n";
    cout << "Enter client account number: "; getline(cin >> ws, account_number);cout << endl;

    return account_number;
}

bool FindClientByAccountNumber(string account_number, vector<sclient> &vclients, sclient& client) {

    vclients = LoadClientsDataFromFile();

    for (sclient &c : vclients) {
        if (c.account_number == account_number) {
            client = c;
            c.mark_for_delete = true;
            return true;

        }
    }
    return false;
}

bool delete_client_from_records(string account_number, vector <sclient>& vclients, sclient& client)
{

    char choice = 'y';

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client);
        cout << "Are you sure you want to proceed the deletion of this client? "; cin >> choice; cout << endl;

        if (choice == 'Y' || choice == 'y')
        {
            delete_client_in_file(vclients, FILENAME);
            cout << "\nClient deleted successfully...\n";

            return true;
        }

    }
    else
    {
        cout << "Client with account number is not found...\n";
    }

    return false;
}

bool update_client_record(string account_number, vector <sclient>& vclients, sclient& client)
{
    char choice = 'y';

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client);
        cout << "Are you sure you want to update the records of this client? "; cin >> choice; cout << endl;
        system("cls");
        if (choice == 'Y' || choice == 'y')
        {
            for (sclient &c : vclients)
            {
                if (account_number == c.account_number)
                {
                    c = update_client(account_number);
                    break;
                }
            }
           
            update_clients_in_file(vclients, FILENAME);
            cout << "Client updated successfully...\n";
            return true;
        }

    }
    else
    {
        cout << "Client with account number is not found...\n";
    }

    return false;
}

void find_client(string account_number, vector <sclient>& vclients, sclient& client)
{

    system("cls");

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client); cout << endl;

    }
    else
    {
        cout << "Client with this account number is not found\n";
    }
      
}

void deposit_operation()
{
    cout << "----------------------------------------------\n";
    cout << "          Deposit Screen                \n";
    cout << "----------------------------------------------\n\n";

    string account_number;

    account_number = read_account_number(account_number);

    vector <sclient> vclients;
    sclient client;
    char choice;
    double deposit_amount = 0;

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client); cout << endl;

        cout << "Are you sure you want to deposit money in this account? "; cin >> choice; cout << endl;

        if (choice == 'Y' || choice == 'y')
        {
            cout << "Enter deposit amount: "; cin >> deposit_amount; cout << endl;

            for (sclient &c : vclients)
            {
                if (c.account_number == account_number)
                {
                    client = c;

                    c.account_balance += deposit_amount;
                    break;
                }
            }

            update_clients_in_file(vclients, FILENAME);

            cout << "Deposit was added successfully...\n";
        }

    }
    else
    {
        cout << "Client with this account number is not found\n";
    }


}

void withdraw_operation()
{
    cout << "----------------------------------------------\n";
    cout << "          Withdraw Screen                \n";
    cout << "----------------------------------------------\n\n";

    string account_number;

    account_number = read_account_number(account_number);

    vector <sclient> vclients;
    sclient client;
    char choice;
    double withdraw_amount = 0;

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client); cout << endl;

        cout << "Are you sure you want to withdraw money from this account? "; cin >> choice; cout << endl;

        if (choice == 'Y' || choice == 'y')
        {

            for (sclient& c : vclients)
            {
                if (c.account_number == account_number)
                {
                    do
                    {
                        cout << "Enter withdraw amount: (should not exeed) " << c.account_balance<<" "; cin >> withdraw_amount; cout << endl;

                    } while (withdraw_amount > c.account_balance);

                    client = c;

                    c.account_balance = c.account_balance - withdraw_amount;
                    break;
                }

            }

            update_clients_in_file(vclients, FILENAME);

            cout << "Funds have been successfully withdrawn...\n";
        }

    }
    else
    {
        cout << "Client with this account number is not found\n";
    }


}

void show_total_balances()
{
    vector <sclient> vclients = LoadClientsDataFromFile();
    cout << "_____________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(20) << "Full Name"
        << "| " << left << setw(12) << "Balance" << endl;
    cout << "_____________________________________________________________\n";

    for (const auto& client : vclients) {
        Print_client_balances(client);
    }

    cout << "_____________________________________________________________\n";

    double total_balances = 0;

    for (const auto& client : vclients)
    {
        total_balances += client.account_balance;
    }

    cout << "\n\t\tTotal Balances: (" << total_balances << ")\n\n";
}

void execute_The_program()
{
    char choice;
    char option;
    sclient client;
    string account_number = "";

    do {
        system("cls");
        choice = show_main_menu();

        switch (choice) {
        case '1':
            system("cls");
            store_client_info_in_file(client);
            system("pause");
            break;

        case '2': {
            system("cls");
            vector<sclient> veclient = LoadClientsDataFromFile();
            PrintAllClientsData(veclient);
            system("pause");
            break;
        }
        case '3': {
            system("cls");
            vector <sclient> vclient;
            account_number = read_account_number(account_number);
            delete_client_from_records(account_number, vclient, client);
            system("pause");
            break;
        }

        case '4': {
            system("cls");
            vector <sclient> vclient;
            account_number = read_account_number(account_number);
            system("cls");
            update_client_record(account_number, vclient, client);
            system("pause");
            break;
        }

        case '5': {
            system("cls");
            account_number = read_account_number(account_number);
            vector <sclient> vclient;
            find_client(account_number, vclient, client);
            system("pause");
            break;
        }
        case '6': {
            do
            {
                system("cls");
                option = show_transactions_menu();

                switch (option)
                {
                case '1':
                {
                    system("cls");
                    deposit_operation();
                    system("pause");
                    break;

                }

                case '2':
                {
                    system("cls");
                    withdraw_operation();
                    system("pause");
                    break;
                }

                case '3':
                {
                    system("cls");
                    show_total_balances();
                    system("pause");
                    break;
                }

                case '4':
                {
      
                    break;
                }

                default:
                    cout << "Invalid choice. please try again...\n";
                    system("pause");
                    break;
                }

            } while (option != '4');

            break;
        }

        case '7':
            cout << "Exiting the program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != '7');
}

int main() {
   
    execute_The_program();

    return 0;
}
=======
// Banking System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <fstream>

using namespace std;

const string FILENAME = "Clients.txt";
const string SEPARATOR = "|##|";



struct sclient {
    string account_number = "";
    string full_name = "";
    string phone_number = "";
    string pin_code = "";
    double account_balance = 0;

    bool mark_for_delete = false;
    bool mark_for_update = true;

};

sclient add_new_client(sclient client) {

    cout << "------------------------------------------------------\n";
    cout <<"     Client creation screen                             \n";
    cout << "------------------------------------------------------\n";

    cout << "Enter client account number: "; getline(cin >> ws, client.account_number);
    cout << "Enter client full name: "; getline(cin, client.full_name);
    cout << "Enter client phone number: "; getline(cin, client.phone_number);
    cout << "Enter client pin code: "; getline(cin, client.pin_code);
    cout << "Enter client account balance: "; cin >> client.account_balance;

    return client;
}

sclient update_client(string account_number) {

    sclient client;

    client.account_number = account_number;

    cout << "------------------------------------------------------\n";
    cout << "     Client update screen                             \n";
    cout << "------------------------------------------------------\n";
    
    cout << "Enter client full name: "; getline(cin>>ws, client.full_name);
    cout << "Enter client phone number: "; getline(cin, client.phone_number);
    cout << "Enter client pin code: "; getline(cin, client.pin_code);
    cout << "Enter client account balance: "; cin >> client.account_balance;

    return client;
}

string convert_client_record_to_data(const sclient& client) {
    return client.account_number + SEPARATOR +
        client.full_name + SEPARATOR +
        client.phone_number + SEPARATOR +
        client.pin_code + SEPARATOR +
        to_string(client.account_balance);
}

char show_main_menu() {
    char choice;
    cout << "----------------------------------------------\n";
    cout << "  \t\t MAIN MENU \n";
    cout << "----------------------------------------------\n";
    cout << "\t [1]: Add new client\n";
    cout << "\t [2]: Show all clients list\n";
    cout << "\t [3]: Delete client\n";
    cout << "\t [4]: Update client record\n";
    cout << "\t [5]: Search client by account number\n";
    cout << "\t [6]: Transactions\n";
    cout << "\t [7]: Exit the program\n";
    cout << "----------------------------------------------\n";
    cout << "----------------------------------------------\n\n";
    cout << "\t <|>: Select an option to proceed: "; cin >> choice; cout << endl;

    return choice;
}

char show_transactions_menu()
{
    char option;
    cout << "----------------------------------------------\n";
    cout << "  \t\t TRANSACTIONS MENU \n";
    cout << "----------------------------------------------\n";
    cout << "\t [1]: Deposit\n";
    cout << "\t [2]: Withdraw\n";
    cout << "\t [3]: Show total balances\n";
    cout << "\t [4]: Main menu\n";
    cout << "----------------------------------------------\n";
    cout << "----------------------------------------------\n\n";
    cout << "\t <|>: Select an option to proceed: "; cin >> option; cout << endl;

    return option;
}

vector<string> split_string(const string& str, const string& delim) {
    vector<string> vString;
    size_t start = 0, end;

    while ((end = str.find(delim, start)) != string::npos) {
        string part = str.substr(start, end - start);
        if (!part.empty()) {
            vString.push_back(part);
        }
        start = end + delim.length();
    }

    if (start < str.length()) {
        vString.push_back(str.substr(start));
    }

    return vString;
}

sclient ConvertLinetoRecord(const string& line) {
    sclient client;
    vector<string> vClientData = split_string(line, SEPARATOR);

    if (vClientData.size() == 5) {
        client.account_number = vClientData[0];
        client.full_name = vClientData[1];
        client.phone_number = vClientData[2];
        client.pin_code = vClientData[3];
        client.account_balance = stod(vClientData[4]);
    }

    return client;
}

vector<sclient> LoadClientsDataFromFile() {
    vector<sclient> vclient;
    fstream file(FILENAME, ios::in);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            sclient client = ConvertLinetoRecord(line);
            vclient.push_back(client);
        }

        file.close();
    }
    else {
        cerr << "Error: Unable to open file for reading.\n";
    }

    return vclient;
}

void store_client_info_in_file(sclient& client) {
    vector<sclient> existingClients = LoadClientsDataFromFile();

    client = add_new_client(client);
    string client_data = convert_client_record_to_data(client);

    // Check if the account number already exists
    for (const auto& existingClient : existingClients) {
        if (existingClient.account_number == client.account_number) {
            cerr << "Error: Account number already exists. Please use a unique account number.\n";
            return;
        }
    }

    fstream file(FILENAME, ios::app);
    if (file.is_open()) {
        file << client_data << endl;
        cout << "Client was added successfully.\n";
        file.close();
    }
    else {
        cerr << "Error: Unable to open file for writing.\n";
    }
}




void PrintClientRecord(const sclient& client) {
    cout << "| " << setw(15) << left << client.account_number
        << "| " << setw(20) << left << client.full_name
        << "| " << setw(15) << left << client.phone_number
        << "| " << setw(10) << left << client.pin_code
        << "| " << setw(12) << fixed << setprecision(2) << left << client.account_balance << endl;
}

void Print_client_balances(const sclient& client) {
    cout << "| " << setw(15) << left << client.account_number
        << "| " << setw(20) << left << client.full_name
        << "| " << setw(12) << fixed << setprecision(2) << left << client.account_balance << endl;
}

void PrintAllClientsData(const vector<sclient>& vClients) {
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
    cout << "_______________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(20) << "Full Name"
        << "| " << left << setw(15) << "Phone Number"
        << "| " << left << setw(10) << "Pin Code"
        << "| " << left << setw(12) << "Balance" << endl;
    cout << "_______________________________________________________________________________________\n";

    for (const auto& client : vClients) {
        PrintClientRecord(client);
    }

    cout << "_______________________________________________________________________________________\n";
}

vector <sclient> delete_client_in_file(vector <sclient> &vclient, string FILENAME)
{
    fstream file;
    file.open(FILENAME, ios::out);
    string dataline;

    if (file.is_open())
    {
        for (sclient &c : vclient)
        {
            if (c.mark_for_delete == false)
            {
                dataline = convert_client_record_to_data(c);

                file << dataline << endl;

            }
        }
        file.close();
      

    }

    return vclient;

}

vector <sclient> update_clients_in_file(vector <sclient>& vclient, string FILENAME)
{
    fstream file;
    file.open(FILENAME, ios::out);
    string dataline;

    if (file.is_open())
    {
        for (sclient &c : vclient)
        {
            if (c.mark_for_update == true)
            {
                dataline = convert_client_record_to_data(c);

                file << dataline << endl;

            }
        }
        file.close();


    }

    return vclient;

}

void PrintClientCard(sclient client) {

    cout << "------------------------------------------------------\n";
    cout << "     Client card                             \n";
    cout << "------------------------------------------------------\n";


    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << client.account_number;
    cout << "\nFull name : " << client.full_name;
    cout << "\nPhone number : " << client.phone_number;
    cout << "\nPin code : " << client.pin_code;
    cout << "\nAccount balance: " << client.account_balance; cout << endl;
}

string read_account_number(string account_number)
{
   vector <sclient> vclients = LoadClientsDataFromFile();

    cout << "--------------------------------------------------\n";
    cout << "         Client search                        \n";
    cout << "--------------------------------------------------\n";
    cout << "Enter client account number: "; getline(cin >> ws, account_number);cout << endl;

    return account_number;
}

bool FindClientByAccountNumber(string account_number, vector<sclient> &vclients, sclient& client) {

    vclients = LoadClientsDataFromFile();

    for (sclient &c : vclients) {
        if (c.account_number == account_number) {
            client = c;
            c.mark_for_delete = true;
            return true;

        }
    }
    return false;
}

bool delete_client_from_records(string account_number, vector <sclient>& vclients, sclient& client)
{

    char choice = 'y';

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client);
        cout << "Are you sure you want to proceed the deletion of this client? "; cin >> choice; cout << endl;

        if (choice == 'Y' || choice == 'y')
        {
            delete_client_in_file(vclients, FILENAME);
            cout << "\nClient deleted successfully...\n";

            return true;
        }

    }
    else
    {
        cout << "Client with account number is not found...\n";
    }

    return false;
}

bool update_client_record(string account_number, vector <sclient>& vclients, sclient& client)
{
    char choice = 'y';

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client);
        cout << "Are you sure you want to update the records of this client? "; cin >> choice; cout << endl;
        system("cls");
        if (choice == 'Y' || choice == 'y')
        {
            for (sclient &c : vclients)
            {
                if (account_number == c.account_number)
                {
                    c = update_client(account_number);
                    break;
                }
            }
           
            update_clients_in_file(vclients, FILENAME);
            cout << "Client updated successfully...\n";
            return true;
        }

    }
    else
    {
        cout << "Client with account number is not found...\n";
    }

    return false;
}

void find_client(string account_number, vector <sclient>& vclients, sclient& client)
{

    system("cls");

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client); cout << endl;

    }
    else
    {
        cout << "Client with this account number is not found\n";
    }
      
}

void deposit_operation()
{
    cout << "----------------------------------------------\n";
    cout << "          Deposit Screen                \n";
    cout << "----------------------------------------------\n\n";

    string account_number;

    account_number = read_account_number(account_number);

    vector <sclient> vclients;
    sclient client;
    char choice;
    double deposit_amount = 0;

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client); cout << endl;

        cout << "Are you sure you want to deposit money in this account? "; cin >> choice; cout << endl;

        if (choice == 'Y' || choice == 'y')
        {
            cout << "Enter deposit amount: "; cin >> deposit_amount; cout << endl;

            for (sclient &c : vclients)
            {
                if (c.account_number == account_number)
                {
                    client = c;

                    c.account_balance += deposit_amount;
                    break;
                }
            }

            update_clients_in_file(vclients, FILENAME);

            cout << "Deposit was added successfully...\n";
        }

    }
    else
    {
        cout << "Client with this account number is not found\n";
    }


}

void withdraw_operation()
{
    cout << "----------------------------------------------\n";
    cout << "          Withdraw Screen                \n";
    cout << "----------------------------------------------\n\n";

    string account_number;

    account_number = read_account_number(account_number);

    vector <sclient> vclients;
    sclient client;
    char choice;
    double withdraw_amount = 0;

    if (FindClientByAccountNumber(account_number, vclients, client))
    {
        PrintClientCard(client); cout << endl;

        cout << "Are you sure you want to withdraw money from this account? "; cin >> choice; cout << endl;

        if (choice == 'Y' || choice == 'y')
        {

            for (sclient& c : vclients)
            {
                if (c.account_number == account_number)
                {
                    do
                    {
                        cout << "Enter withdraw amount: (should not exeed) " << c.account_balance<<" "; cin >> withdraw_amount; cout << endl;

                    } while (withdraw_amount > c.account_balance);

                    client = c;

                    c.account_balance = c.account_balance - withdraw_amount;
                    break;
                }

            }

            update_clients_in_file(vclients, FILENAME);

            cout << "Funds have been successfully withdrawn...\n";
        }

    }
    else
    {
        cout << "Client with this account number is not found\n";
    }


}

void show_total_balances()
{
    vector <sclient> vclients = LoadClientsDataFromFile();
    cout << "_____________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(20) << "Full Name"
        << "| " << left << setw(12) << "Balance" << endl;
    cout << "_____________________________________________________________\n";

    for (const auto& client : vclients) {
        Print_client_balances(client);
    }

    cout << "_____________________________________________________________\n";

    double total_balances = 0;

    for (const auto& client : vclients)
    {
        total_balances += client.account_balance;
    }

    cout << "\n\t\tTotal Balances: (" << total_balances << ")\n\n";
}

void execute_The_program()
{
    char choice;
    char option;
    sclient client;
    string account_number = "";

    do {
        system("cls");
        choice = show_main_menu();

        switch (choice) {
        case '1':
            system("cls");
            store_client_info_in_file(client);
            system("pause");
            break;

        case '2': {
            system("cls");
            vector<sclient> veclient = LoadClientsDataFromFile();
            PrintAllClientsData(veclient);
            system("pause");
            break;
        }
        case '3': {
            system("cls");
            vector <sclient> vclient;
            account_number = read_account_number(account_number);
            delete_client_from_records(account_number, vclient, client);
            system("pause");
            break;
        }

        case '4': {
            system("cls");
            vector <sclient> vclient;
            account_number = read_account_number(account_number);
            system("cls");
            update_client_record(account_number, vclient, client);
            system("pause");
            break;
        }

        case '5': {
            system("cls");
            account_number = read_account_number(account_number);
            vector <sclient> vclient;
            find_client(account_number, vclient, client);
            system("pause");
            break;
        }
        case '6': {
            do
            {
                system("cls");
                option = show_transactions_menu();

                switch (option)
                {
                case '1':
                {
                    system("cls");
                    deposit_operation();
                    system("pause");
                    break;

                }

                case '2':
                {
                    system("cls");
                    withdraw_operation();
                    system("pause");
                    break;
                }

                case '3':
                {
                    system("cls");
                    show_total_balances();
                    system("pause");
                    break;
                }

                case '4':
                {
      
                    break;
                }

                default:
                    cout << "Invalid choice. please try again...\n";
                    system("pause");
                    break;
                }

            } while (option != '4');

            break;
        }

        case '7':
            cout << "Exiting the program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != '7');
}

int main() {
   
    execute_The_program();

    return 0;
}
>>>>>>> d272a68751f18c25f3685d17250e8a820fa39ca9
