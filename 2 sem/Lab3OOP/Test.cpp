#define _CRT_SECURE_NO_WARNINGS
#include "List.h"
#include "CFile.h"
int main()
{
	List<CFile> *Catalog = new List<CFile>, *RecycleBin = new List<CFile>;
	Catalog->load("Info.csv");
	cout << "Catalog->load(\"Info.csv\") called" << endl;
	Catalog->Print();
	Catalog->pop_front();
	Catalog->push_front(CFile("Pic", "20/11/2019", 10));
	cout << "pop_front() and push_front(CFile(\"Pic\", ..)) called" << endl;
	Catalog->Print();
	Catalog->remove(CFile("Pic", "20/10/1000", 110));
	cout << "remove(CFile(\"Pic\", ..)) called" << endl;
	Catalog->Print();
	Catalog->RenameFile("One", "Note");
	cout << "RenameFile(\"One\", \"Note\") called" << endl;
	Catalog->Print();
	Catalog->DeleteOlders("01/01/2016");
	cout << "DeleteOlders(\"10/12/2018\") called" << endl;
	Catalog->Print();
	cout << "Catalog->find(CFile(\"Three\", \"03/03/03\", 20)) :" << endl << (*Catalog->find(CFile("Three", "03/03/03", 20))).data << endl;
	Catalog->load("Info.csv");
	cout << "Catalog->load(\"Info.csv\") called" << endl;
	Catalog->Print();
	Catalog->splice(Catalog->begin(), *RecycleBin);
	Catalog->splice(Catalog->end(), *RecycleBin);
	cout << "splice(Catalog->begin(), *RecycleBin) called" << endl;
	cout << "splice(Catalog->end(), *RecycleBin) called" << endl;
	cout << "--- Catalog ---" << endl;
	Catalog->Print();
	cout << "--- Recycle Bin ---" << endl;
	RecycleBin->Print();
	cout << "Catalog->size() == " << Catalog->size() << endl;
	Catalog->clear();
	cout << "Catalog->clear() called" << endl;
	cout << "Catalog->size() == " << Catalog->size() << endl;
	cout << "Catalog->empty() == " << Catalog->empty() << endl;
	return 0;
}