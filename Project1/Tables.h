#include <iostream>
using namespace std;

template<class T>
class TableNode
{
public:
	
	TableNode* next;
	TableNode* prev;
	T* ptr = NULL;
    int index;

	TableNode()
	{
		next = NULL;
		prev = NULL;
		ptr = NULL;
		index = 0;
	}
};

template<class T>
class FT
{
	int capacity;
	int size;


public:
	TableNode<T>* head;
	TableNode<T>* tail;


	FT()
	{
		head = NULL;
		tail = NULL;
		size = capacity = 0;
	}

	void setcapacity(int c)
	{
		capacity = c;
	 }


	int getSize()
	{
		return size;
	}


	void InsertNode(T *obj)
	{
		if (head == NULL)
		{
			TableNode<T>* temp = new TableNode<T>;
			temp->ptr = obj;
			temp->next = NULL;
			temp->prev = NULL;
			temp->index = 1;
			head = temp;
			tail = temp;
			++size;
		}
		else
		{
			TableNode<T>* temp = new TableNode<T>;
			temp->ptr = obj;
			temp->next = NULL;
			temp->prev = tail;
			temp->index = tail->index + 1;
			tail->next = temp;
			tail = tail->next;
			++size;
		}
	}

	
	bool IsEmpty()
	{
		if (head == NULL)
		{
			return true;
		}
		return false;
	}

	void Display()
	{
		cout << endl;
		TableNode<T>* curr = new TableNode<T>;
		curr = head;
		if (curr == NULL)
		{
			cout << "FT is empty." << endl;
		}
		else
		{
			TableNode<T>* curr = head;
			while (curr != NULL)
			{
				cout << "i = " << curr->index << "     Machine ID: "<<curr->ptr->data << endl;
				cout << endl;
				curr = curr->next;
			}
		}
		cout << endl;
	}

	void clear() {
		if (!IsEmpty()) 
		{
			TableNode<T>* temp = new TableNode<T>;
			TableNode<T>* cur = new TableNode<T>;
			cur = head;
			for (int i = 0; i < size; i++) {
				temp = cur;
				cur = cur->next;
				delete temp;
			}
			size = 0;
			//cout << "Linked List cleared!" << endl;
			head = NULL;
			tail = NULL;
		}
	}
};


