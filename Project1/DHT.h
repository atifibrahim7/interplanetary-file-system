#include "List.h"
#include "Sha-1.h"
#include<string>
#include<cmath>
#include<fstream>
using namespace std;


template<class T>
class RingDHT
{

	List<int> x;
	T bits;
	T NumOfAm;
	T count;

public:


	// specifying identifier space and actual machines

	void setBits(int n)
	{
		bits = n;
		x.setb(n);
	}

	void setActualMachines(int n)
	{
		NumOfAm = n;
		x.setCapacity(n);
		ActualMachnes();
		makeroutingtables();
	}


	void ActualMachnes()
	{
		string input;
		int choice = 0;
		int a = pow(2, bits);
		int v = 0;
		while (choice != 1 && choice != 2)
		{
			int i = 0;
			while (i < NumOfAm)
			{
				cout << "\nPress 1 to manually assign ID to the machine or 2 To enter key then the system  automatically generate numerical Id.\n";
				cin >> choice;
				if (choice == 1)
				{
					
					int k;

					cout << "\nEnter ID of machine :\n";
					cin >> k;

					do
					{
						while (k < 0 || k >= a)
						{
							cout << "\nId out of range of identifier Space !!!!!\nAs it is a " << bits << " bit system. So id must be in between 0 and " << a - 1 << ". Please enter the value in range:\n";
							cin >> k;
						}


						v = x.check(k);

						while (v != -1)
						{
							cout << "Machine with that id alreaady exist!!Enter a new id:\n";
							cin >> k;
							v = x.check(k);
						}

					} while (v != -1 || k < 0 || k >= a);

					x.insertAtEnd(k);

					i++;

				}

				else if (choice == 2)
				{
					long long int k;
					do
					{
						cout << "Enter Key : \n";
						cin >> input;

						SHA1 checksum;
						checksum.update(input);
						const string hash = checksum.final();

						string key = hash.substr(0, 7);
						k = stoi(key, 0, 16);
						k = k % a;
						v = x.check(k);
					}
					while (v != -1);

					x.insertAtEnd(k);

					i++;

				}
			}
		}
		        showRing();
	}


	// add machine

	void insertActualMachine()
	{
		string input;
		int choice = 0, k = 0;
		int v = 1;
		int a = pow(2, bits);

		while (choice != 1 && choice != 2)
		{

			cout << "Press 1 to manually assign ID to the machine or 2 To enter key then the system  automatically generate a numerical ID\n";
			cin >> choice;
			if (choice == 1)
			{
				cout << "Enter Id:\n";
				cin >> k;
				
				do
				{
					while (k < 0 || k >= a)
					{
						cout << "\nId out of range of identifier Space !!!!!\nAs it is a " << bits << " bit system. So id must be in between 0 and " << a - 1 << ". Please enter the value in range:\n";
						cin >> k;
					}

					v = x.check(k);

					while (v != -1)
					{
						cout << "Machine with that id alreaady exist!!Enter a new id:\n";
						cin >> k;
						v = x.check(k);
					}

				} while (v != -1 || k < 0 || k >= a);

				x.insertAtEnd(k);
				x.setCapacity(++NumOfAm);
				x.maketable();
				maketrees(EmptyTrees());
			}

			else if (choice == 2)
			{
				do
				{
					cout << "Enter Key : \n";
					cin >> input;
					int a = pow(2, bits);
					SHA1 checksum;
					checksum.update(input);
					const string hash = checksum.final();
					string key = hash.substr(0, 7);
					long long int k = stoi(key, 0, 16);
					k = k % a;
					v = x.check(k);
				}

				while (v != -1);
				
				x.insertAtEnd(k);
				x.setCapacity(++NumOfAm);
				x.maketable();
				maketrees(EmptyTrees());
			}
		}
	}

	
	// remove machine


	void removeActualMachine(int id)
	{
		AD<int>* s = EmptyTrees();
		x.deleteAtMid(id);
		x.setCapacity(--NumOfAm);
		x.maketable();
		maketrees(s);
	}

	
	// Avl Data Redistribution

	AD<int>* EmptyTrees()
	{
		AD<int>* c = new AD<int>;
		MachineNode<T>* t = x.head;
		for (int i = 0; i < NumOfAm; i++)
		{
			MachineNode<T>* temp = x.returnIndexMachine(t->data);
			temp->tree.fillContainer(c);
			t = t->nextPtr;
		}

		t = x.head;
		for (int i = 0; i < NumOfAm; i++)
		{
			t->tree.deleteTree();
			t = t->nextPtr;
		}
		
		return c;
	}

	void maketrees(AD<int>* x)
	{
		int size = x->getSize();
		for (int i = 0; i < size; i++)
		{
			 node<int> y = x->pop();
			insert(y.data,y.lineNum,y.filepath);
		}

	}

	void insert(int key,int lineNum , string filepath)
	{
		MachineNode<T>* temp = x.returnMachine(x.head->data);
		cout << "\n\nInsertion of data is originated at Machine iD " << temp->data << ".\n";
		bool flag = false;
		while (1)
		{

			if (temp->data == key)
			{
				cout << temp->data << endl;
				temp->tree.insert(key,lineNum,filepath);
				return;
			}
			else if (temp->data < key && key <= temp->Table.head->ptr->data)
			{
				temp = temp->Table.head->ptr;
				cout << "\nInsertion Query is forwarded to the machine of ID " << temp->data << ".\n";
				if (temp->data > key)
					flag = true;
			}
			else
			{
				temp = temp->search(key);
				cout << "\nInsertion Query is forwarded to the machine of ID " << temp->data << ".\n";
				if (temp->data > key)
					flag = true;

			}
			if (x.succ(key) == temp->data) {
				flag = true;
			}
			else {
				flag = false;
			}
			if (flag)
			{

				cout << "\nMachine of ID " << temp->data << " is responsible for this data id.\n";
				temp->tree.insert(key, lineNum, filepath);
				return;
			}
		}
	}


	// file handling


	int write(string filename, string text)
	{
		int line = 0;
		string test, test2;
		ofstream myfile;
		ifstream read;
		myfile.open(filename, ios::app);
	//	cout << " File Opened " << endl;
		myfile << text << endl;
	//	cout << "Text Written " << endl;
		myfile.close();
	//	cout << " File closed " << endl;

		read.open(filename);
		while (getline(read, test2))
		{
			line++;
		}

		return line;
	}
	

	string readfunc(string filepath, int line)
	{

		ifstream infile;
		infile.open(filepath);
		int i = 1;
		string read;
		while (getline(infile, read))
		{
			if (i == line)
			{
				return read;
			}
			read = "";
			i++;
		}
	}

	// data insertion

	void insertData()
	{
		string file = "filename.txt";
		string value,input;
		int id;
		cout << "Enter key :\n";
		cin >> input;
		cout << "Enter value :\n";
		cin >> value;
		int a = pow(2, bits);
		SHA1 checksum;
		checksum.update(input);
		const string hash = checksum.final();
		string k = hash.substr(0, 7);
		long long int key = stoi(k, 0, 16);
		key = key % a;



		cout << "Enter from which machine you want to insert data :\n";
		cin >> id;
		id = validate(id);
		file = "file";
		file.append(to_string(id));
		file.append(".txt");
		int lNum = write(file, value);

		MachineNode<T>* temp = x.returnMachine(id);
		
		cout << "\n\nInsertion of data is originated at Machine iD " << temp->data << ".\n";

		bool flag = false;
		while (1)
		{
			if (temp->data == key)
			{
				cout << temp->data << endl;
				temp->tree.insert(key,lNum,file);
				return;
			}

			else if (temp->data < key && key <= temp->Table.head->ptr->data)
			{
				temp = temp->Table.head->ptr;
				cout <<"\nInsertion Query is forwarded to the machine of ID "<<temp->data << ".\n";
				if (temp->data >= key)
					flag = true;
			}

			else
			{
				temp = temp->search(key);
				cout << "\nInsertion Query is forwarded to the machine of ID " << temp->data << ".\n";
				if (temp->data >= key)
					flag = true;
			}
			if (x.succ(key) == temp->data) {
				flag = true;
			}
			else {
				flag = false;
			}
			if (flag)
			{

				cout << "\nMachine of ID " << temp->data << " is responsible for this data id.\n";
				temp->tree.insert(key, lNum, file);
				return;
			}
		}
	}



	void removeData()
	{
		int a = pow(2, bits);
		string  input;
		cout << "Enter key :\n";
		cin >> input;
		SHA1 checksum;
		checksum.update(input);
		const string hash = checksum.final();
		string k = hash.substr(0, 7);
		long long int key = stoi(k, 0, 16);
		key = key % a;


		int id;
		cout << "Enter from which machine you want to remove data :\n";
		cin >> id;
		id = validate(id);


		MachineNode<T>* temp = x.returnMachine(id);
		cout << "\n\nRemoval of data is originated at Machine iD " << temp->data << ".\n";
		bool flag = false;

		while (1)
		{
			if (temp->data == key)
			{
				cout << temp->data << endl;
				temp->tree.deleteNode(key);
				return;
			}

			else if (temp->data < key && key <= temp->Table.head->ptr->data)
			{
				temp = temp->Table.head->ptr;
				cout << "\nRemoval Query is forwarded to the machine of ID " << temp->data << ".\n";
				if (temp->data >= key)
					flag = true;
			}

			else
			{
				temp = temp->search(key);
				cout << "\nRemoval Query is forwarded to the machine of ID " << temp->data << ".\n";
				if (temp->data >= key)
					flag = true;
			}
			if (x.succ(key) == temp->data) {
				flag = true;
			}
			else {
				flag = false;
			}
			if (flag)
			{

				cout << "\nMachine of ID " << temp->data << " is responsible for this data id.\n";
				temp->tree.deleteNode(key);
				return;
			}
		}

	}


	int validate(int id)
	{
		int v = x.check(id);

		while (v == -1)
		{
			cout << "\nNo machine with that id exist!!\nFollowing machines exist :";
			showRing();
			cout << "\nPlease enter the correct machine id:\n";
			cin >> id;
			v = x.check(id);
		}

		return v;
	}


	// display functions


	void displayTable(int id)
	{
		id = validate(id);

		MachineNode<T>* temp = x.returnIndexMachine(id);
		temp->Table.Display();
	}
	
	void displayTree(int id)
	{
		id = validate(id);

		MachineNode<T>* temp = x.returnIndexMachine(id);
		temp->tree.Display();
	}


	void showRing()
	{
		x.print();
	}


	void makeroutingtables()
	{
		x.maketable();
	}

	

	void searchAlgo()
	{
		int line;
		string f;

		int a = pow(2, bits);
		string  input;
		cout << "Enter key :\n";
		cin >> input;
		SHA1 checksum;
		checksum.update(input);
		const string hash = checksum.final();
		string k = hash.substr(0, 7);
		long long int key = stoi(k, 0, 16);
		key = key % a;


		int id;
		cout << "Enter from which machine you want to search data :\n";
		cin >> id;
		id = validate(id);


		MachineNode<T>* temp = x.returnMachine(id);
		cout << "\n\nSeatching of data is originated at Machine iD " << temp->data << ".\n";
		bool flag = false;

		while (1)
		{
			if (temp->data == key)
			{
				//cout << temp->data << endl;
				line=temp->tree.returnNum(key);
				f = temp->tree.returnfile(key);
				cout<<readfunc(f,line);
				return;
			}

			else if (temp->data < key && key <= temp->Table.head->ptr->data)
			{
				temp = temp->Table.head->ptr;
				cout << "\nSearching Query is forwarded to the machine of ID " << temp->data << ".\n";
				if (temp->data >= key)
					flag = true;
			}

			else
			{
				temp = temp->search(key);
				cout << "\nSearching Query is forwarded to the machine of ID " << temp->data << ".\n";
				if (temp->data >= key)
					flag = true;
			}
			if (x.succ(key) == temp->data) {
				flag = true;
			}
			else {
				flag = false;
			}
			if (flag)
			{

				cout << "\nMachine of ID " << temp->data << " is responsible for this data id.\n";
				line = temp->tree.returnNum(key);
				f =  temp->tree.returnfile(key);
				cout<<readfunc(f,line);
				return;
			}
		}
	}



	void displaymenu()
	{
		cout << "\n\n============================================================================================================================================================" << endl;
		cout << "                                                                              MENU                   " << "\n";
		cout << "============================================================================================================================================================" << endl;
		cout << "0.To exit : " << endl;
		cout << "1.To add a machine : " << endl;
		cout << "2.To remove a machine" << endl;
		cout << "3.To print routing table of any machine  " << endl;
		cout << "4.To print avl tree of any machine" << endl;
		cout << "5.To enter data from any machine " << endl;
		cout << "6.To remove data from any machine " << endl;
		cout << "7.To search data from any machine " << endl;
	}

	void menu()
	{
		int n, n1,choice,id;
		cout << "Specify the bits of identifierspace :  \n";
		cin >> n1;
		setBits(n1);
		cout << "Specify the number of machines :  \n";
		cin >> n;
		setActualMachines(n);
		while (1)
		{
			displaymenu();
			cout << "Enter the choice : " << endl;
			cin >> choice;
			if (choice == 0)
			{
				break;
			}
			else if (choice == 1)
			{
				insertActualMachine();
				showRing();
			}
			else if (choice == 2)
			{
				cout << "Enter the Machine ID which you wanted to remove :\n";
				cin >> id;
				removeActualMachine(id);
				showRing();
			}
			else if (choice == 3)
			{
				cout << "Enter the machine ID whose routing table you wanted to see : \n";
				cin >> id;
				displayTable(id);
			}
			else if (choice == 4)
			{
				cout << "Enter the machine ID whose avl tree you wanted to see : \n";
				cin >> id;
				displayTree(id);
			}
			else if (choice == 5)
			{	
				insertData();
			}
			else if (choice == 6)
			{
				removeData();
			}

			else if (choice == 7)
			{
				searchAlgo();
			}
			
		}
	}
};
