#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <limits>
#include "inputsLib.h"
#include "myLibString.h"
using namespace std;

enum enMainMenuOption
{
  eShow = 1,
  eAdd = 2,
  eDelete = 3,
  eUpdate = 4,
  eFind = 5,
  eTranaction = 6,
  eExit = 7
};

enum enTransactions
{
  eDeposit = 1,
  eWithdraw = 2,
  eTotalBalance = 3,
  eBack = 4
};

struct stRecord
{
  string AccountNumber;
  string Name;
  string Phone;
  string PinCode;
  double AccountBalance;
  bool MarkForDeleted = false;
};

const string clientsFileName = "ClientsRecord.txt";
const string delimeter = "#//#";
void showMainMenu();
void showTransactionScreen();

void setWordInCenter(string text, short width)
{
  short totalWidth = width - text.length();
  short rightWidth = totalWidth / 2;
  short leftWidth = totalWidth - rightWidth;
  cout << setw(leftWidth) << "" << text << setw(rightWidth) << "" << endl;
}

void printHeaderWithMsg(string msg)
{
  system("cls");
  cout << "\n---------------------------------\n";
  setWordInCenter(msg, 33);
  cout << "\n---------------------------------\n";
}

stRecord convertLineToRecord(string line, string separator)
{
  stRecord client;
  vector<string> lineToVec = myLibString::mySplit(line, separator);
  client.AccountNumber = lineToVec.at(0);
  client.PinCode = lineToVec.at(1);
  client.Name = lineToVec.at(2);
  client.Phone = lineToVec.at(3);
  client.AccountBalance = stod(lineToVec.at(4));
  return client;
}

string convertRecordToLine(stRecord client, string separator)
{
  string line = "";
  line += client.AccountNumber + separator;
  line += client.PinCode + separator;
  line += client.Name + separator;
  line += client.Phone + separator;
  line += to_string(client.AccountBalance);
  return line;
}

vector<stRecord> loadClientsFromFile(string fileName)
{
  vector<stRecord> vClients;
  fstream clientsFile;
  clientsFile.open(fileName, ios::in);
  if (clientsFile.is_open())
  {
    string line;
    stRecord client;
    while (getline(clientsFile, line))
    {
      client = convertLineToRecord(line, delimeter);
      vClients.push_back(client);
    }
    clientsFile.close();
  }
  return vClients;
}

short chooseOption()
{
  short answer = 0;
  do
  {
    cout << "Choose What Do you Want to do ? [1 to 7] ?" << endl;
    cin >> answer;
    while (cin.fail())
    {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "Invalid Number , Enter a new One : ";
      cin >> answer;
    }

    if (answer < 1 || answer > 7)
    {
      cout << "===== Out Of Range! =====\n";
    }

  } while (answer < 1 || answer > 7);

  return answer;
}

short chooseTransaction()
{
  short answer = 0;
  do
  {
    answer = inputsLib::readNumber("\nChoose What Do You Want To Do ? [1 to 4] ? ");

    if (answer < 1 || answer > 4)
    {
      cout << "\n===== Out Of Range! =====\n";
    }
  } while (answer < 1 || answer > 4);
  return answer;
}

void showClientsList()
{
  vector<stRecord> vClients = loadClientsFromFile(clientsFileName);

  setWordInCenter("Client List (" + to_string(vClients.size()) + ") Client(s)", 70);
  cout << "_____________________________________________________________________________________\n\n";
  cout << "| " << setw(16) << left << "Accout Number";
  cout << "| " << setw(16) << left << "PIN CODE";
  cout << "| " << setw(16) << left << "Name";
  cout << "| " << setw(16) << left << "Phone";
  cout << "| " << setw(16) << left << "Account Balance";
  cout << "\n_____________________________________________________________________________________\n";
  for (stRecord &client : vClients)
  {
    cout << "| " << setw(16) << left << client.AccountNumber;
    cout << "| " << setw(16) << left << client.PinCode;
    cout << "| " << setw(16) << left << client.Name;
    cout << "| " << setw(16) << left << client.Phone;
    cout << "| " << setw(16) << left << client.AccountBalance << endl;
  }
  cout << "\n_____________________________________________________________________________________\n";
}

void printClientInfo(stRecord client)
{
  cout << "\n---------------------------------\n";
  cout << "\nThe following are the client details " << endl;
  cout << "\nAccount Number : " << client.AccountNumber << endl;
  cout << "PIN CODE : " << client.PinCode << endl;
  cout << "Client Name : " << client.Name << endl;
  cout << "Client Phone : " << client.Phone << endl;
  cout << "Account Balance : " << client.AccountBalance << endl;
  cout << "\n---------------------------------\n";
}

bool findClientByAccNumber(string accountNumber, vector<stRecord> vClients, stRecord &sClient)
{
  for (stRecord &client : vClients)
  {
    if (client.AccountNumber == accountNumber)
    {
      sClient = client;
      return true;
    }
  }
  return false;
}

bool clientExistsByAccountNumber(string accountNumber, string fileName)
{
  fstream clientFile;
  clientFile.open(fileName, ios::in);
  if (clientFile.is_open())
  {
    string line = "";
    stRecord client;
    while (getline(clientFile, line))
    {
      client = convertLineToRecord(line, delimeter);
      if (client.AccountNumber == accountNumber)
      {
        clientFile.close();
        return true;
      }
    }
    clientFile.close();
  }
  return false;
}

stRecord readNewClient()
{
  vector<stRecord> vClients = loadClientsFromFile(clientsFileName);
  stRecord newClient;
  newClient.AccountNumber = inputsLib::readString("\nEnter Account Number : ");
  while (clientExistsByAccountNumber(newClient.AccountNumber, clientsFileName))
  {
    cout << "\nClient With [" << newClient.AccountNumber << "] Already Exists!\n";
    newClient.AccountNumber = inputsLib::readString("\nEnter Account Number : ");
  }
  newClient.PinCode = inputsLib::readString("\nEnter PIN Code : ");
  newClient.Name = inputsLib::readString("\nEnter Name : ");
  newClient.Phone = inputsLib::readString("\nEnter Phone Number : ");
  cout << "\nEnter Account Balance : ";
  cin >> newClient.AccountBalance;

  return newClient;
}

void saveRecordInFileAfterAdd(string fileName, stRecord clients)
{
  string dataLine = "";
  fstream clientFile;
  clientFile.open(fileName, ios::out | ios::app);
  if (clientFile.is_open())
  {
    dataLine = convertRecordToLine(clients, delimeter);
    clientFile << dataLine << endl;

    clientFile.close();
  }
}

void saveRecordInFile(string fileName, vector<stRecord> vClients)
{
  string dataLine = "";
  fstream clientFile;
  clientFile.open(fileName, ios::out);
  if (clientFile.is_open())
  {
    for (stRecord &c : vClients)
    {
      if (c.MarkForDeleted == false)
      {
        dataLine = convertRecordToLine(c, delimeter);
        clientFile << dataLine << endl;
      }
    }
    clientFile.close();
  }
}

void addNewClient()
{

  stRecord client = readNewClient();
  saveRecordInFileAfterAdd(clientsFileName, client);
}

void askForClient()
{

  char answer = 'n';
  string line = "";
  do
  {

    system("cls");
    cout << "\n------------------------\n";
    setWordInCenter("Add New Client", 24);
    cout << "\n------------------------\n";
    cout << "Adding New Client :\n";

    addNewClient();
    cout << "Client Added Successfully, Do you want to add more clients ? (y/n)";
    cin >> answer;
  } while (tolower(answer) == 'y');
}

string askForAccountNumber()
{
  string accountNumber = "";
  cout << "\nPlease Enter Account Number : ";
  getline(cin >> ws, accountNumber);
  return accountNumber;
}

bool markForDeleteByAccNumber(string accountNumber, vector<stRecord> &vClients)
{
  for (stRecord &c : vClients)
  {
    if (c.AccountNumber == accountNumber)
    {
      c.MarkForDeleted = true;
      return true;
    }
  }
  return false;
}

bool deleteClientByAccNumber(string accountNumber, vector<stRecord> &vClients)
{
  stRecord client;
  char answer = 'n';
  if (findClientByAccNumber(accountNumber, vClients, client))
  {

    printClientInfo(client);

    cout << "Are You Sure You Want to Delete This Client y/n ? " << endl;
    cin >> answer;
    if (tolower(answer) == 'y')
    {
      markForDeleteByAccNumber(accountNumber, vClients);
      saveRecordInFile(clientsFileName, vClients);

      vClients = loadClientsFromFile(clientsFileName);
      cout << "\n\nClient Deleted Successfully !";
      return true;
    }
  }
  cout << "\nClient With Account Number (" << accountNumber << ") Not Found!";
  return false;
}

void ShowDeleteClientScreen()
{
  vector<stRecord> vClients = loadClientsFromFile(clientsFileName);
  char answer = 'n';
  string accountNumber = "";
  do
  {
    printHeaderWithMsg("Delete Client Screen");
    accountNumber = askForAccountNumber();
    deleteClientByAccNumber(accountNumber, vClients);
    cout << "Do you want to delete more client ? y/n ? ";
    cin >> answer;
  } while (tolower(answer) == 'y');
}

stRecord changeClientDetails(string accountNumber)
{
  stRecord clientAfterUpdate;
  clientAfterUpdate.AccountNumber = accountNumber;
  clientAfterUpdate.PinCode = inputsLib::readString("\nEnter PIN Code : ");
  clientAfterUpdate.Name = inputsLib::readString("\nEnter Name : ");
  clientAfterUpdate.Phone = inputsLib::readString("\nEnter Phone Number : ");
  cout << "\nEnter Account Balance : ";
  cin >> clientAfterUpdate.AccountBalance;
  return clientAfterUpdate;
}

bool updateClientByAccNumber(string accountNumber, vector<stRecord> &vClients)
{
  stRecord tempClient;
  char answer = 'n';
  if (findClientByAccNumber(accountNumber, vClients, tempClient))
  {

    printClientInfo(tempClient);

    cout << "Are You Sure You Want to Update This Client y/n ? " << endl;
    cin >> answer;
    if (tolower(answer) == 'y')
    {
      for (stRecord &client : vClients)
      {
        if (client.AccountNumber == accountNumber)
        {
          client = changeClientDetails(accountNumber);
          break;
        }
      }
      saveRecordInFile(clientsFileName, vClients);
      cout << "\n\nClient Updated Successfully !";
      return true;
    }
  }
  cout << "\nClient With Account Number (" << accountNumber << ") Not Found!";
  return false;
}

bool depositBalanceToClientByAccountNumbe(vector<stRecord> &vClients, string accountNumber, double amount)
{
  char answer = 'n';
  cout << "Are you sure you want to perform this transaction ? y/n ? ";
  cin >> answer;
  if (tolower(answer) == 'y')
  {
    for (stRecord &c : vClients)
    {
      if (c.AccountNumber == accountNumber)
      {
        c.AccountBalance += amount;
        saveRecordInFile(clientsFileName, vClients);
        printf("Done successfully, new balance : %.0f ", c.AccountBalance);
        return true;
      }
    }
  }
  return false;
}

void ShowUpdateClientScreen()
{

  vector<stRecord> vClients = loadClientsFromFile(clientsFileName);
  string accountNumber = "";
  printHeaderWithMsg("Update Client Screen");
  accountNumber = askForAccountNumber();
  updateClientByAccNumber(accountNumber, vClients);
}

void ShowFindClientScreen()
{
  vector<stRecord> vClients = loadClientsFromFile(clientsFileName);

  char answer = 'n';
  string accountNumber = "";
  stRecord client;
  do
  {
    system("Cls");
    printHeaderWithMsg("Find Client Screen");
    accountNumber = askForAccountNumber();
    if (findClientByAccNumber(accountNumber, vClients, client))
    {
      printClientInfo(client);
    }
    cout << "\nDo you want to Find more client ? y/n ? ";
    cin >> answer;
  } while (tolower(answer) == 'y');
}

void showDepositScreen()
{
  stRecord client;
  vector<stRecord> vClients = loadClientsFromFile(clientsFileName);
  printHeaderWithMsg("Deposit Screen");
  string accountNumber = askForAccountNumber();
  while (!findClientByAccNumber(accountNumber, vClients, client))
  {
    cout << "\nClient With Account Number (" << accountNumber << ") Not Found!";
    accountNumber = askForAccountNumber();
  }
  printClientInfo(client);

  double Amount = 0;
  cout << "\nPlease Enter Deposit Amount : ";
  cin >> Amount;
  depositBalanceToClientByAccountNumbe(vClients, accountNumber, Amount);
}

void showWithdrawScreen()
{
  stRecord client;
  vector<stRecord> vClients = loadClientsFromFile(clientsFileName);
  printHeaderWithMsg("Withdraw Screen");
  string accountNumber = askForAccountNumber();
  while (!findClientByAccNumber(accountNumber, vClients, client))
  {
    cout << "\nClient With Account Number (" << accountNumber << ") Not Found!";
    accountNumber = askForAccountNumber();
  }
  printClientInfo(client);
  double Amount = 0;
  cout << "\nPlease Enter Withdraw Amount : ";
  cin >> Amount;
  while (Amount > client.AccountBalance)
  {
    cout << "\nAmount Exceeds the balance, you can withdraw up to : " << client.AccountBalance << endl;
    cout << "Please enter another amount? ";
    cin >> Amount;
  }
  depositBalanceToClientByAccountNumbe(vClients, accountNumber, Amount * -1);
}

void showTotalBalance()
{
  vector<stRecord> vClients = loadClientsFromFile(clientsFileName);
  double totalBalance = 0;
  setWordInCenter("Client List (" + to_string(vClients.size()) + ") Client(s)", 70);
  cout << "_____________________________________________________________________________________\n\n";
  cout << "| " << setw(16) << left << "Accout Number";
  cout << "| " << setw(28) << left << "Name";
  cout << "| " << setw(16) << left << "Account Balance";
  cout << "\n_____________________________________________________________________________________\n";
  for (stRecord &client : vClients)
  {
    cout << "| " << setw(16) << left << client.AccountNumber;
    cout << "| " << setw(28) << left << client.Name;
    cout << "| " << setw(16) << left << client.AccountBalance << endl;
    totalBalance += client.AccountBalance;
  }
  cout << "\n_____________________________________________________________________________________\n";
  setWordInCenter("Total Balance = " + to_string(totalBalance), 85);
}

void goBackToMainMenu()
{
  cout << "\n\nPress Any Key To Go Back To Main Menu...";
  system("pause>0");
  showMainMenu();
}

void goBackToTransactionScreen()
{
  cout << "\n\nPress Any Key To Go Back To Transaction Menu...";
  system("pause>0");
  showTransactionScreen();
}

void executeSelectedOption(enMainMenuOption option)
{

  switch (option)
  {
  case enMainMenuOption::eShow:
  {
    system("cls");
    showClientsList();
    goBackToMainMenu();
    break;
  }
  case enMainMenuOption::eAdd:
  {
    system("cls");
    askForClient();
    goBackToMainMenu();
    break;
  }
  case enMainMenuOption::eDelete:
  {
    system("cls");
    ShowDeleteClientScreen();
    goBackToMainMenu();
    break;
  }
  case enMainMenuOption::eUpdate:
  {
    system("cls");
    ShowUpdateClientScreen();
    goBackToMainMenu();
    break;
  }
  case enMainMenuOption::eFind:
  {
    system("cls");
    ShowFindClientScreen();
    goBackToMainMenu();
    break;
  }
  case enMainMenuOption::eTranaction:
  {
    showTransactionScreen();
    goBackToMainMenu();
    system("cls");
  }
  case enMainMenuOption::eExit:
  {
    system("cls");
    printHeaderWithMsg("Program Ending :|");
    system("pause>0");
    break;
  }
  }
}

void executeTransactionOption(enTransactions transaction)
{
  switch (transaction)
  {
  case enTransactions::eDeposit:
  {
    system("cls");
    showDepositScreen();
    goBackToTransactionScreen();
    break;
  }
  case enTransactions::eWithdraw:
  {
    system("cls");
    showWithdrawScreen();
    goBackToTransactionScreen();
    break;
  }
  case enTransactions::eTotalBalance:
  {
    system("cls");
    showTotalBalance();
    goBackToTransactionScreen();
    break;
  }
  case enTransactions::eBack:
  {
    system("cls");
    showMainMenu();
    break;
  }
  }
}

void showMainMenu()
{
  system("cls");
  cout << "==============================================\n";
  setWordInCenter("Main Menu Options", 46);
  cout << "==============================================\n";
  cout << "\t" << "[1] Show Client List." << endl;
  cout << "\t" << "[2] Add New Client." << endl;
  cout << "\t" << "[3] Delete Client." << endl;
  cout << "\t" << "[4] Update Client Info." << endl;
  cout << "\t" << "[5] Find Client." << endl;
  cout << "\t" << "[6] Transaction." << endl;
  cout << "\t" << "[7] Exit." << endl;
  cout << "==============================================\n";
  executeSelectedOption(enMainMenuOption(chooseOption()));
}

void showTransactionScreen()
{
  system("cls");
  cout << "==============================================\n";
  setWordInCenter("Transaction Menu Screen", 46);
  cout << "==============================================\n";
  cout << "\t" << "[1] Deposit." << endl;
  cout << "\t" << "[2] Withdraw." << endl;
  cout << "\t" << "[3] Total Balance." << endl;
  cout << "\t" << "[4] Main Menu." << endl;
  cout << "==============================================\n";
  executeTransactionOption(enTransactions(chooseTransaction()));
}

int main()
{

  showMainMenu();

  return 0;
}
