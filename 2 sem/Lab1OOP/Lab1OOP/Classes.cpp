#include "Classes.h"

#define Default 0
using namespace std;

List::List() {
	head = nullptr;
	length = 0;
}

List::List(const List& other) {
	head = nullptr;
	length = 0;
	Node* node = other.head;
	while (node != nullptr) 
	{
		push_back(node->GetValue());
		node = node->GetNext();
	}
}

List::List(size_t _Count, int _Val) {
	head = nullptr;
	length = 0;
	size_t i = 0;
	while (i < _Count) {
		push_back(_Val);
		i++;
	}
}

List::~List() {
	clear();
}

Node::Node() {
	next = nullptr;
	value = Default;
}

Node::Node(int val) {
	next = nullptr;
	value = val;
}

void List::push_back(int value) {
	Node* node = new Node(value);
	if (head == nullptr) {
		head = node;
	}
	else {
		Node* last = head;
		while (last->GetNext() != nullptr) {
			last = last->GetNext();
		}
		last->SetNext(node);
	}
	length++;
}

void List::push_front(int value) {
	Node* node = new Node(value);
	if (head == nullptr) {
		head = node;
	}
	else {
		node->SetNext(head);
		head = node;
	}
	length++;
}

void List::pop_back() {
	if (head == nullptr) return;
	Node* node = head;
	if (node->GetNext() == nullptr) {
		delete node;
		head = nullptr;
		length--;
		return;
	}  
	while (node->GetNext()->GetNext() != nullptr) {
		node = node->GetNext();
	}
	delete node->GetNext();
	node->SetNext(nullptr);
	length--;
}

void List::pop_front() {
	if (head == nullptr) return;
	Node* node = head;
	if (node->GetNext() == nullptr) {
		delete node;
		head = nullptr;
	}
	else {
		node = node->GetNext();
		delete head;
		head = node;
	}
	length--;
}

Node& List::back() {
	Node* node = head;
	while (node->GetNext() != nullptr) {
		node = node->GetNext();
	}
	return *node;
}

const Node& List::back() const {
	Node* node = head;
	while (node->GetNext() != nullptr) {
		node = node->GetNext();
	}
	return *node;
}

Node& List::begin() {
	return *head;
}

const Node& List::begin() const {
	return *head;
}

void List::clear() {
	while(head != nullptr)
		pop_back();
}

bool List::empty() const {
	if (length == 0) return true;
	return false;
}
void List::erase(size_t pos) {
	if (pos >= length) abort();
	Node* node = head;
	if (pos == 0) {
		pop_front();
		return;
	}
	if (pos == length - 1) {
		pop_back();
		return;
	}
	size_t i = 1;
	while (i < pos) {
		node = node->GetNext();
		i++;
	}
	Node* tmp = node->GetNext();
	node->SetNext(node->GetNext()->GetNext());
	delete tmp;
	length--;
}

void List::erase(size_t first, size_t last) {
	if ((first < 0) || (last > length - 1)) abort();
	for (int i = 0; i <= last - first; i++)
		erase(first);
}

void List::insert(int val, unsigned pos, unsigned count) {
	if (pos >= length) abort();
	Node* node = head; int i = 1;
	if (pos == 0) {
		for (int k = 0; k < count; k++)
			push_front(val);
		return;
	}
	while (i < pos) {
		node = node->GetNext();
		i++;
	}
	for (int k = 0; k < count; k++) {
		Node* tmp = new Node(val);
		tmp->SetNext(node->GetNext());
		node->SetNext(tmp);
		length++;
	}

}

void List::insert(size_t pos, int* v, size_t count) {
	if (v == NULL) abort();
	int i;
	for (i = count - 1; i >= 0; i--) {
		insert(v[i], pos, 1);
	}
}

void List::sort() {
	if (head == nullptr) return;
	Node* left = head;
	Node* right = head->GetNext();
	Node* temp = new Node();
	while (left->GetNext()) {
		while (right) {
			if (left->GetValue() > right->GetValue()) {
				temp->SetValue(left->GetValue());
				left->SetValue(right->GetValue());
				right->SetValue(temp->GetValue());
			}
			right = right->GetNext();
		}
		left = left->GetNext();
		right = left->GetNext();
	}
	delete temp;
}

void List::unique() {
	if (head == nullptr) return;
	Node* node = head, * prev = nullptr;
	int pos = 0;
	int tmp = node->GetValue();
	while (node->GetNext() != nullptr) {
		prev = node;
		node = node->GetNext();
		pos++;
		if (node->GetValue() != tmp) {
			tmp = node->GetValue();
		}
		else {
			erase(pos);
			pos--;
			node = prev;
		}
	}
}

void List::merge(List& other) {
	this->sort();
	other.sort();
	Node* node1 = &begin();
	Node* node2 = &other.begin();
	int pos = 0;
	while ((node1 != nullptr)&&(node2 != nullptr)) {
		if (node1->GetValue() > node2->GetValue()) {
			insert(node2->GetValue(), pos, 1);
			node2 = node2->GetNext();
		}
		else {
			if (node1->GetValue() == node2->GetValue()) {
				node2 = node2->GetNext();
				continue;
			}
			else node1 = node1->GetNext();
		}
		pos++;
	}
	while (node2 != nullptr) {
		push_back(node2->GetValue());
		node2 = node2->GetNext();
	}
	other.clear();
}

void List::remove(int value) {
	int pos = 0;
	Node* node = head, *prev = nullptr;
	while (node != nullptr) {
		if (node->GetValue() == value) {
			if (pos == 0) {
				pop_front();
				node = head;
				continue;
			}
			erase(pos);
			pos--;
			node = prev;
		}
		pos++;
		prev = node;
		node = node->GetNext();
	}
}

void List::resize(size_t count, int value) {
	if (count < 0) abort();
	int i = 0, s = size();
	if (count < size()) {
		for (i; i < s - count; i++)
			pop_back();
	}
	else if (count > size()){
		for (i; i < count - s; i++)
			push_back(value);
	}
}

void List::resize(size_t count) {
	resize(count, Default);
}

void List::reverse() {
	Node* node = head;
	while (node != nullptr) {
		push_front(node->GetValue());
		node = node->GetNext();
	}
	erase(length / 2, length - 1);
}

void List::splice(size_t pos, List& other) {
	if (&other.begin() == nullptr) return;
	Node* node = &other.begin();
	while (node != nullptr) {
		insert(node->GetValue(), pos++, 1);
		node = node->GetNext();
	}
	other.clear();
}

void List::swap(List& other) {
	Node* tmp = head;
	int q_tmp = length;
	head = &other.begin();
	length = other.size();
	other.head = tmp;
	other.length = q_tmp;
}

bool List::operator==(const List& other) {
	if (size() != other.size()) return false;
	List A(*this) ,B(other);
	A.sort(); B.sort();
	Node* node1 = &A.begin(), * node2 = &B.begin();
	while (node1 != nullptr) {
		if (node1->GetValue() != node2->GetValue()) {
			A.clear(); B.clear();
			return false;
		}
		node1 = node1->GetNext();
		node2 = node2->GetNext();
	}
	A.clear(); B.clear();
	return true;
}

List& List::operator=(const List& other) {
	List *tmp = new List(other);
	this->clear();
	this->head = tmp->head;
	this->length = tmp->length;
	return *this;
}

List::operator int() const {
	int sum = 0;
	Node* node = head;
	while (node != nullptr) {
		sum += node->GetValue();
		node = node->GetNext();
	}
	return sum;
}

size_t List::size() const {
	return length;
}

void List::Print() {
	Node* node = head;
	if (node == nullptr) cout << "Empty";
	while (node != nullptr) {
		cout << node->GetValue() << " ";
		node = node->GetNext();
	}
	 cout << endl;
}

void Node::SetNext(Node* next) {
	this->next = next;
}

void Node::SetValue(int value) {
	this->value = value;
}

Node *Node::GetNext() {
	return next;
}
int Node::GetValue() {
	return value;
}