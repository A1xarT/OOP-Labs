/*******************************************
*file: CFile.h
*purpose: class used to manage files
*author: Ilya Lyubchich
*written: 05/05/2020
*last modified: 05/05/05
*requirements: set date of creation in "date/month/year" format
*********************************************/
#pragma once
#include <iostream>

using namespace std;

class CFile {
public:
	CFile();
	CFile(char* filename, char* creation_date, int size);
	CFile(const char* filename, const  char* creation_date, int size);
	~CFile() {};
	char* get_filename();
	char* get_creation_date();
	int get_size();
	void set_filename(char* name);
	void set_filename(const char* name);
	void set_creation_date(char* name);
	void set_creation_date(const char* name);
	void set_size(int size);
	bool isOlder(const char* creation_date);
	void rename(const char * name);
	friend ostream& operator<<(ostream& stream, CFile& obj);
	bool operator ==(const CFile& obj);
private:
	char* _filename;
	char* _creation_date;
	int _size;
};
