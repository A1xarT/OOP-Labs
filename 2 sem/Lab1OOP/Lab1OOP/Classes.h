#pragma once
#include <string.h>
#include <iostream>

class Node {
public:
	Node();
	Node(int val);
	Node* GetNext();
	int GetValue();
	void SetNext(Node* const next);
	void SetValue(int value);
private:
	Node* next = nullptr;
	int value;
};

class List {
public:
	List();
	List(size_t _Count, int _Val);
	List(const List& other);
	~List();
	Node& back();
	const Node& back() const;
	Node& begin();
	const Node& begin() const;
	void clear();
	void push_back(int value);
	void push_front(int value);
	void pop_back();
	void pop_front();
	bool empty() const;
	void erase(size_t pos);
	void erase(size_t first, size_t last);
	void insert(int val, unsigned pos, unsigned count);
	void insert(size_t pos, int* v, size_t count);
	void sort();
	void unique();
	size_t size() const;
	void merge(List& other);
	void remove(int value);
	void resize(size_t count);
	void resize(size_t count, int value);
	void reverse();
	void splice(size_t pos, List& other);
	void swap(List& other);
	bool operator==(const List& other);
	List& operator=(const List& other);
	operator int() const;

	void Print();
private:
	Node* head;
	int length;
};
