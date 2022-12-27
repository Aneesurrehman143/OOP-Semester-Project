/*
Name :Anees ur Rehman
Reg No :4339-FBAS-BSSE-F21-B

Description: this a program for entering telephone directories and display it and also this program contain 

*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;

#define MAX 20 //total account that can be register
int nn = 0;//count of registerd account 

struct userInfo {
   string name;
	string password;
	int ID;
};



class person {
	string Name;
	int id;
public:
	void getter();
	void setter();
	string getName();
};
void person::setter() {
	cout << "Enter the Name";
	getline(cin, Name);

}
void person::getter() {
	cout << "Name is" << Name << endl;

}
string person:: getName() {
	return Name;
}
class telephoneDirect:public person {
	int phoneNum;
public:
	telephoneDirect() :phoneNum(00000000){}
	void setter();
	void getter();
	int getPhoneNum();

};

void telephoneDirect::setter() {
	person::setter();
	cout << "Enter your contact" << endl;
	cin >> phoneNum;
}
void telephoneDirect::getter() {
	person::getter();
	cout << "\nPhone Number is:" << phoneNum << endl;
}
int telephoneDirect::getPhoneNum() {
	return phoneNum;
}


class user:virtual public  telephoneDirect  {
	userInfo users[MAX];//stores register account data
public:
	bool login();
	void registr();
	bool srchPassword(string);
	bool srchId(int);
	void readData();
	void writeData();


};
bool user::login() {
	readData();
	int id;
	string password;
		cout << "\nEnter the id:";
		cin >> id;
		if (srchId(id)) {
			cout << "\nEnter your Password:";
			cin.ignore();
			getline(cin, password);
			if (srchPassword(password)) {
				cout << "\nlogin Successfully";
				system("pause");
				return true;
			}
		}
	
		return false;
}
bool user::srchId(int id) {
	for (int i = 0; i < nn; i++) {
		if (users[i].ID == id)
			return false;
	}
	return true;
}
void user::registr() {
	int id;
	string password, name;

		cout << "Enter you Name:";
		cin.ignore();

		getline(cin, name);
		cout << "Enter  ID";
		cin >> id;
		if (srchId(id)) {
		cout << "Enter Password:";
		cin.ignore();

		getline(cin, users[nn].password);
		users[nn].ID = id;
		users[nn].name = name;
		cout << "Account Registerd Successfully" << endl;
		}
		else cout << "Enter Unique ID" << endl;
	
	nn++;
	writeData();
}
bool user::srchPassword(string pss) {
	readData();
	for (int i = 0; i < nn; i++) {
		if (users[nn].password == pss)
			return true;
	}
	return false;
}
void user::writeData() {
	int size = nn * sizeof(userInfo);
	ofstream outfile;
	outfile.open("Account.DAT", ios::out | ios::app | ios::binary);
	if (!outfile) {
		cout << "can't open the file" << endl;
		return;
	}

		outfile.write((char*)users, sizeof(size));
	
	outfile.close();
	cout << "write Data Successfully on file" << endl;
}
void user::readData() {
	ifstream infile;
	infile.open("Account.DAT", ios::in | ios::binary);
	if (!infile) {
		cout << "can't open the file" << endl;
		return;
	}
	while (!infile.eof()) {
		cout << "Entered" << endl;
		infile.read((char*)users, sizeof(userInfo));
		cout<<users[nn].ID;
		system("pause");
		nn++;
	}
	infile.close();


}

//linked list code 
class nodes {
public:
    telephoneDirect *tdPtr;//pointer that will store  objects addresses
	nodes* nextPtr;

	void setData() {
		tdPtr = new telephoneDirect;
		tdPtr->setter();

	}
	
	void setAddress(nodes* nextPtr) {
		this->nextPtr = nextPtr;
	}
	void getData() {
		tdPtr->getter();
	}
	nodes* getAddress() {
		return nextPtr;
	}

};
class linkedList {

	nodes* curPtr = NULL,//will store node address
		* prevPtr = NULL,//will store node address
		* firstPtr = NULL;//will store first node address

public:
	void setValue();//will set value in the node 
	void saveData(int);
	void loadData(int );
	void getValue(); // will display the data in the list



};
void linkedList::setValue() {
	nodes* nextPtr = NULL;

	curPtr = new nodes;
	curPtr->setData();
	curPtr->setAddress(nextPtr);
	if (firstPtr == NULL) {
		firstPtr = curPtr;
		prevPtr = curPtr;
	}
	else {
		prevPtr->setAddress(curPtr);
		prevPtr = curPtr;
	}
}
void linkedList::getValue() {
	curPtr = firstPtr;
	while (curPtr) { // null treated as false in loops (null all bit set to zero)
		curPtr->getData();
		curPtr = curPtr->getAddress();
	}
}
void  linkedList::saveData(int id ) {

	curPtr = firstPtr;
	ofstream outfile;

	outfile.open("Data.DAT", ios::out | ios::binary);
	if (!outfile)
	{
		cout << "\nCan't open file\n"; return;
	}
	//should write id 
	string temp= curPtr->tdPtr->getName();
	outfile.write((char*)&id ,sizeof(int));
	while (curPtr) //for every person object
	{ //get its type
		//write type to file
	//	outfile.write((char*)&(temp), sizeof(string));
	//	outfile << " ";
	//	outfile.write((char*)(curPtr->tdPtr->getPhoneNum()), sizeof(int));

		outfile.write((char*)(curPtr->tdPtr), sizeof(telephoneDirect));


		if (!outfile)
		{
			cout << "\nCan't write to file\n"; return;
		}
	}
	char ch = '*';
	outfile.write((char*)&ch, sizeof(ch));
	outfile.close();
}
void linkedList::loadData(int idd) {
	
	firstPtr = NULL;
	ifstream infile;
	int id = 0;
	infile.open("Data.DAT", ios::in | ios::binary);
	if (!infile)
	{
		cout << "\nCan't open file\n"; return;
	}
	while (infile.eof()) {
		//should write id 
		infile.read((char*)&id, sizeof(int));
		if (id == idd) {
			char ch;
			ch = infile.peek();
			while (ch != '*') //for every person object
			{ //get its type
				//write type to file
				infile.read((char*)&(curPtr->tdPtr), sizeof(telephoneDirect));
				if (!infile)
				{
					cout << "\nCan't write to file\n"; return;
				}
			}
		}
		else {

			int jump = infile.tellg();
			infile.seekg(jump * sizeof(telephoneDirect) + 1);
		}
	}
	infile.close();
}
//code end

//simple function
void loginMenu(linkedList& l1) {
	cout << "          Login Menu               " << endl;
	cout << "1.Add Contacts " << endl;
	cout << "2.Update Contacts" << endl;
	cout << "3.Delete Contacts" << endl;
	cout << "4.View Contact" << endl;
	cout << "5.Exit" << endl;
	int choice;
	cin >> choice;
	switch (choice) {
	case 1:
		l1.setValue();
		break;
	case 4:
		l1.getValue();
		break;
	case 5:
		exit(0);
		
	}
}
int main() {
	user u1;
	linkedList l1;
	int choice;
	cout << "          MAIN MENU              " << endl;
	cout << "1.Login"<<endl;
	cout << "2. Create New account"<<endl;
	cout << "3.exit"<<endl;
	cout << "Enter the choice:";
	cin >> choice;
	switch (choice) {
	case 1:
		if (u1.login() == true)
		{
		//	int id = 13;
		
		//l1.loadData(id);

			loginMenu(l1);
		}
		else {
			cout << "not entered" << endl;
		}
		break;
	case 2:
		u1.registr();
	case 3:
		exit(0);

	}
	return 0;
}