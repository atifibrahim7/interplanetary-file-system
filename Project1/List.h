#include<iostream>
#include "AVL.h"
#include "Tables.h"


template<class T>
class MachineNode
{
public:

	T data;
	MachineNode<T>* nextPtr;
	AVL<int>tree;
	//BTree Tree;
	FT <MachineNode> Table;

	MachineNode<T>* search(int value)
	{
		bool flag = false;

		if (value > Table.tail->ptr->data)
		{
			TableNode<MachineNode>* curr1 = Table.head;

			for (int i = 0; i < Table.getSize(); i++)
			{
				if (value > curr1->ptr->data)
					flag = true;

				else
					flag = false;

				if (flag == false)
					break;

				curr1 = curr1->next;
			}

			if (flag)
			{
				return Table.tail->ptr;
			}

		}

			TableNode<MachineNode>* curr = Table.head;
			while (value > curr->ptr->data)
			{
				curr = curr->next;
			}
			return curr->prev->ptr;		
	}

};


template<class T>
class List
{
private:
	
	
	MachineNode<T>* cursor;
	T size;
	T capacity;
	T bits;
public:
	MachineNode<T>* head;
	MachineNode<T>* tail;

	List() :head{ nullptr }, tail{ nullptr }, cursor{ tail }, capacity{ 100 }, size{ 0 }{}

	bool isEmpty() { return size == 0; }

	bool isFull() { return size == capacity; }

	void setCapacity(int c)
	{
		capacity = c;
	}


	void setb(int a)
	{
		bits = a;
	}


	void insertAtStart(int val) {
		MachineNode<T>* cur = new MachineNode<T>;
		cur->data = val;
		if (isEmpty()) {
			head = cur;
			tail = cur;
			cursor = tail;
			cur->nextPtr = nullptr;
		}
		else {
			cur->nextPtr = head;
			head = cur;
		}
		size++;

	}

	void insertAtMid(int val, int pos) {
		MachineNode<T>* newMachineNode = new MachineNode<T>;
		newMachineNode->data = val;
		if (pos <= size) {
			if (head == nullptr) {
				insertAtStart(val);
			}
			else {
				MachineNode<T>* pre = new MachineNode<T>;
				MachineNode<T>* cur = new MachineNode<T>;
				cur = head;
				for (int i = 0; i < pos; i++) {
					pre = cur;
					cur = cur->nextPtr;
				}
				newMachineNode->nextPtr = pre->nextPtr;
				pre->nextPtr = newMachineNode;
				size++;
			}
		}
		else {
			cout << "Invalid Index Provided!" << endl;
			cursor = tail;
		}
	}

	void insertAtEnd(int val) {
		MachineNode<T>* newMachineNode = new MachineNode<T>;
		newMachineNode->data = val;
		if (head == nullptr) {
			insertAtStart(val);
		}
		else {
			newMachineNode->nextPtr = head;
			tail->nextPtr = newMachineNode;
			tail = newMachineNode;
			size++;
		}

		sort();

	}

	void deleteAtStart() {
		if (isEmpty()) {
			cout << "List is Already empty" << endl;
		}
		else {
			if (size == 1) {
				delete head;
				delete tail;
				head = nullptr;
				tail = nullptr;
			}
			else {
				head = head->nextPtr;
				tail->nextPtr = head;
			}
			size--;
		}
	}


	void deleteAtEnd() {

		if (isEmpty())
			cout << "List is already empty!" << endl;
		else {
			if (size == 1)
				deleteAtStart();
			else {
				MachineNode<T>* cur = new MachineNode<T>;
				MachineNode<T>* pre = new MachineNode<T>;
				cur = head;
				for (int i = 0; i < size-1; i++) {
					pre = cur;
					cur = cur->nextPtr;
				}
				pre->nextPtr = nullptr;
				tail = pre;
				cursor = tail;
				size--;
			}
		}
	}

	void deleteAtMid(int id)
	{
		if (isEmpty())
			cout << "CircularLinkedList is alread empty!" << endl;

		else if (id == tail->data)
		{
			this->deleteAtEnd();
		}

		else
		{
			if (head->data == id)
				this->deleteAtStart();

			else {
				MachineNode<T>* cur = new MachineNode<T>;
				MachineNode<T>* pre = new MachineNode<T>;
				cur = pre = head;
				for (int i = 0; cur->data != id; i++) {
					pre = cur;
					cur = cur->nextPtr;
				}
				pre->nextPtr = cur->nextPtr;
				size--;
			}
		}
	}


	void sort() {
		int temp;
		MachineNode<T>* cur = new MachineNode<T>;
		MachineNode<T>* pre = new MachineNode<T>;
		cur = pre = head;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (cur->data < pre->data) {
					temp = cur->data;
					cur->data = pre->data;
					pre->data = temp;
				}
				pre = cur;
				cur = cur->nextPtr;
			}
			cur = pre = head;
		}
	}

	void clear() {
		if (!isEmpty()) {
			MachineNode<T>* temp = new MachineNode<T>;
			MachineNode<T>* cur = new MachineNode<T>;
			cur = head;
			for (int i = 0; i < size; i++) {
				temp = cur;
				cur = cur->nextPtr;
				delete temp;
			}
			size = 0;
			//cout << "Linked List cleared!" << endl;
		}
	}

	void print() {
		cout << endl;
		MachineNode<T>* cur = head;
		for (int i = 0; i < size; i++) {
			cout << cur->data<< "---";
		//	cout << cur << " , ";

			cur = cur->nextPtr;
		}
		cout << endl;
	}



	int succ(int value) {
		  
	    if(value > tail->data)
		  {
			 return head->data;
		  }

		else
		{
			MachineNode<T>* cur = head;

			for (int i = 0; i < size; i++) {
				if (cur->data == value || cur->data > value)
				{
					return cur->data;
				}
				cur = cur->nextPtr;
			}
		}	   
	}


	MachineNode<T>* returnMachine(int value)
	{
		if (value > tail->data)
		{
			return head;
		}

		else
		{
			MachineNode<T>* cur = head;

			for (int i = 0; i < size; i++) {
				if (cur->data == value || cur->data > value)
				{
					return cur;
				}
				cur = cur->nextPtr;
			}
		}
	}


	MachineNode<T>* returnIndexMachine(int value)
	{
			MachineNode<T>* cur = head;

			for (int i = 0; i < size; i++) {
				if (cur->data == value )
				{
					return cur;
				}
				cur = cur->nextPtr;
			}
	}


	int check(int value)
	{
		MachineNode<T>* cur = head;

		for (int i = 0; i < size; i++) {
			if (cur->data == value)
			{
				return cur->data;
			}
			cur = cur->nextPtr;
		}

		return -1;

	}


	void maketable()
	{
		MachineNode<T>* cur = head;
		int a = pow(2, bits);
		int index = 0, j = 0, p = 0;

		for (int i = 0; i < bits; i++)
		{
			cur->Table.clear();
			cur = cur->nextPtr;
		}

		cur = head;

		while (j < size)
		{
			p = cur->data;

			for (int i = 1; i <= bits ;i++)
			{
				index = p + pow(2, i - 1);
				index = index % a;
				MachineNode<T>* temp = returnMachine(index);
				cur->Table.InsertNode(temp);
			}

			  j++;
		 	  cur = cur->nextPtr;
		}
	}
		


	~List() {
		clear();
	}
};