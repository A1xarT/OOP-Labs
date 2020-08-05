#include "CFile.h"
#include "Iterator.h"
#include <string>
#include <list>
#include <regex>

char* CFile::get_creation_date() {
	return this->_creation_date;
}
char* CFile::get_filename() {
	return this->_filename;
}

int CFile::get_size() {
	return this->_size;
}

void CFile::set_creation_date(char* name) {
	string str = name;
	regex regular("^0*([1-9]|[1-2][0-9]|3[0-1])\/0*([1-9]|1[0-2])\/\\d+$");
	if (!regex_match(str.c_str(), regular))
		abort();
	this->_creation_date = name;
}

void CFile::set_creation_date(const char* name) {
	string str = name;
	regex regular("^0*([1-9]|[1-2][0-9]|3[0-1])\/0*([1-9]|1[0-2])\/\\d+$");
	if (!regex_match(str.c_str(), regular))
		abort();
	this->_creation_date =(char*)name;
}

void CFile::set_filename(char* name) {
	this->_filename = name;
}

void CFile::set_filename(const char* name) {
	this->_filename = (char*)name;
}

void CFile::set_size(int size) {
	this->_size = size;
}

ostream& operator<<(ostream& stream, CFile& obj) {
	if (&obj == nullptr) return stream;
	if (obj.get_filename() != nullptr)
		stream << " File name: " << obj.get_filename() << endl;
	if (obj.get_creation_date() != nullptr)
		stream << " Creation date: " << obj.get_creation_date() << endl;
	 stream << " Size: " << obj.get_size() << endl;
	return stream;
}

CFile::CFile() {
	this->set_size(0);
	this->_creation_date = nullptr;
	this->_filename =  nullptr;
}

CFile::CFile(char* filename, char* creation_date, int size) {
	this->set_size(size);
	this->set_filename(filename);
	this->set_creation_date(creation_date);
}

CFile::CFile(const char* filename, const char* creation_date, int size)
{
	this->set_size(size);
	this->set_filename((char*)filename);
	this->set_creation_date((char*)creation_date);
}

void CFile::rename(const char * name) {
	this->set_filename((char*)name);
}

bool CFile::isOlder(const char* creation_date) {
	string str = creation_date;
	regex regular("^0*([1-9]|[1-2][0-9]|3[0-1])\/0*([1-9]|1[0-2])\/\\d+$");
	string delim = "\/";
	if (!regex_match(str.c_str(), regular))
		abort();
	str = creation_date;
	list <int> lst1, lst2;
	while(lst1.size() < 2) {
		lst1.push_front(stoi(str.substr(0, str.find(delim))));
		str = str.substr(str.find(delim) + 1, str.size() - str.find(delim));
	}
	lst1.push_front(stoi(str.substr(0, str.find(delim))));
	str = this->get_creation_date();
	while (lst2.size() < 2) {
		lst2.push_front(stoi(str.substr(0, str.find(delim))));
		str = str.substr(str.find(delim) + 1, str.size() - str.find(delim));
	}
	lst2.push_front(stoi(str.substr(0, str.find(delim))));
	int k = 0;
	list<int>::iterator it1 = lst1.begin();
	list<int>::iterator it2 = lst2.begin();
	if (*it2 < *it1) {
		return true;
	}
	else if (*it2 == *it1) {
		it1++; it2++;
		if (*it2 < *it1)
			return true;
		else if (*(++it2) < *(++it1))
			return true;
	}
	return false;
}

bool CFile::operator ==(const CFile& obj) {
	if (!obj._creation_date || !obj._filename || !obj._size) return false;
	if (strcmp(obj._filename, _filename) == 0) return true;
	return false;
}