#include<iostream>
using namespace std;



template<class T>
class node
{
public:
	T data;
	int lineNum;
	string filepath;
	node<T>* next;

	node(T d,T num,string f)
	{
		data = d;
		lineNum = num;
		filepath = f;
		next = NULL;
	}
};


template<class T>
class AD {

	node<T>* front;
	int size;

public:

	AD() {
		front = NULL;
	}

	int getSize()
	{
		return size;
	}



	void push_roll(T value,int num,string f) {

		node<T>* temp;
		temp = new node<T>(value,num,f);

		if (front == NULL)
		 {
			temp->next = NULL;
			++size;
		 }

		else
		 {
			temp->next = front;
			++size;
		 }

		front = temp;
	}

	T& top() {

		return front->data;
	}

	node<T> pop() {

		if (front == NULL)
			cout << "UNDERFLOW\n";

		else
		{
			node<T>* temp = front;
			front = front->next;
			size--;
			return *temp;
		}
	}

	bool is_empty() {

		if (front == NULL)
			return true;

		return false;
	}


	void display()
	{
		node<T>* temp = front;
		
		while (temp != NULL)
		{
			cout << temp->data;
			temp = temp->next;
		}
	}
};