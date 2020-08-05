#pragma once
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include "Iterator.h"
#include <regex>
using namespace std;
template <class T>
class List {

	struct ListNode {
		T data;
		ListNode* next;
		ListNode() {
			next = NULL;
		}
		ListNode(T dat) {
			data = dat;
		}
		void Print() {
			cout << data;
		}
	};

public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	//constructors / destructors
	List();
	~List();

	//methods
	iterator begin();//Returns an iterator addressing the first element 
	iterator end();//Returns an iterator that addresses the location 
   //succeeding the last element

	bool load(const char* filename);
	void clear();//Erases all the elements of a list.
	bool empty();//Tests if a list is empty.

	iterator find(const node_type& val);//Returns an iterator to the 
// first element in a list that 
//match a specified value.

	void pop_front();//Deletes the element at the beginning of a list.

	void push_front(const node_type val);//Adds an element to the beginning 
  //of a list.
	void remove(const node_type val);//Erases first element in a list that 
   //match a specified value.


	int size();//Returns the number of elements in a list.

	void splice(iterator _Where, List<T>& _Right);//Removes element from //the target list and inserts it in first
// position of the argument list.
	void Print();//Dumps list into the screen
	void RenameFile(const char* OldName, const char* NewName); //Renames the file what's name set as first parameter
	void DeleteOlders(const char* RedDate); //Deletes all elements created earlier than RedDate
private:
	node_type* head;
	iterator* first, * last;
};

template <class T> List<T>::List() {
	this->head = nullptr;
	this->first = nullptr;
	this->last = nullptr;
}

template <class T> List<T>::~List() {
	clear();
}

template <class T> void List<T>::push_front(const node_type val) {
	if (find(val) != nullptr) {		// if file with the same name already exists we replace it with a new one
		remove(*find(val));
		push_front(val);
		return;
	}
	if (head == nullptr) 
	{
		head = new node_type(val);
		head->next = nullptr;
		first = new iterator(head);
		last = new iterator(head);
		return;
	}
	else 
	{
		node_type* tmp = new ListNode(val);
		tmp->next = head;
		head = tmp;
		delete first;
		first = new iterator(head);
	}
}

template <class T> void List<T>::pop_front() {
	if (head == nullptr) return;
	node_type *tmp = head->next;
	delete head;
	head = tmp;
	delete first;
	first = new iterator(head);
	if (head == nullptr) {
		delete last;
		last = new iterator(head);
	}
}

template <class T> typename List<T>::iterator List <T>::begin() {
	if (first == nullptr) return nullptr;	
	return *first;
}

template <class T> typename List<T>::iterator List <T>::end() {
	if (last == nullptr) return nullptr;
	return *last;
}

template <class T> void List<T>::clear() {
	while (head != nullptr)
		pop_front();
}

template <class T> bool List<T>::empty() {
	if (head == nullptr) return true;
	return false;
}

template <class T> typename List<T>::iterator List <T>::find(const node_type& val) {
	iterator it = begin();
	while (it != nullptr) {
		if ((*it).data == val.data)
			break;
		it++;
	}
	return it;
}

template <class T> void List<T>::remove(const node_type val) {
	if (find(val) == nullptr) return;
	if (head->data == val.data) pop_front();
	else
	{
		node_type* tmp = head;
		while (tmp->next != nullptr) {
			if (tmp->next->data == val.data)
				break;
			tmp = tmp->next;
		}
		if (tmp->next) {
			if (*last == iterator(tmp->next)) {
				delete last;
				last = new iterator(tmp);
			}
			node_type* toDelete = tmp->next;
			tmp->next = tmp->next->next;
			delete toDelete;
		}
	}
}

template <class T> void List<T>::splice(iterator _Where, List<T>& _Right) {
	if (_Where == nullptr || find(*_Where) == nullptr || &_Right == nullptr) return;
	iterator it = find(*_Where);
	_Right.push_front(*it);
	remove(*it);
}

template <class T> bool List<T>::load(const char* filename) {
	if (!filename) abort();
	ifstream fin;
	fin.open(filename);
	if (fin.eof()) {
		fin.close();
		return false;
	}
	string line, tmp;
	list <string>* row = new list <string>{};
	list <string>::iterator it;
	int j, iter, size;
	char *name1, *name2;
	while (!fin.eof()) {
		j = iter = 0;
		fin >> line;
		while (j != line.size()) {
			if (line[j] == ';') {
				tmp = line.substr(iter, j - iter);
				row->push_back(tmp);
				j = j + 1;
				iter = j;
				continue;
			}
			j++;
		}
		tmp = line.substr(iter);
		row->push_back(tmp);
		it = (*row).begin();
		name1 = new char [(*it).length() + 1];
		strcpy(name1, (*it).c_str());
		it++;
		name2 = new char[(*it).length() + 1];
		strcpy(name2, (*it).c_str());
		it++;
		size = stoi(*it);
		it++;
		this->push_front(T(name1, name2, size));
		row->clear();
		if (fin.eof()) break;
	}
	fin.close();
	return true;
}

template <class T> int List<T>::size() {
	int size = 0;
	node_type *tmp = head;
	while (tmp != nullptr) {
		size++;
		tmp = tmp->next;
	}
	return size;
}

template <class T> void List<T>::Print() {
	node_type* tmp = head;
	if (tmp == nullptr)	cout << "Empty" << endl;
	else cout << endl << " | List of files |" << endl;
	while (tmp != nullptr) {
		cout << tmp->data << endl;
		tmp = tmp->next;
	}
}

template <class T> void List<T>::RenameFile(const char* OldName, const char* NewName) {
	if (!OldName || !NewName) abort();
	iterator it = find(node_type(T(OldName, "01/01/01", 1)));
	if (it != nullptr)
		(*it).data.rename(NewName);
}

template <class T> void List<T>::DeleteOlders(const char* RedDate) {
	string str = RedDate;
	regex regular("^0*([1-9]|[1-2][0-9]|3[0-1])\/0*([1-9]|1[0-2])\/\\d+$");
	if (!regex_match(str.c_str(), regular))
		abort();
	iterator it = this->begin();
	iterator it2;
	while(it != nullptr)
	{
		it2 = it;
		it++;
		if ((*it2).data.isOlder(RedDate))
			remove(*it2);
	}
}