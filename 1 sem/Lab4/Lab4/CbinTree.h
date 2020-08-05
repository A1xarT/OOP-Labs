#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class CTreeNode
{
public:

	CTreeNode(std::ifstream&);
	CTreeNode();
	CTreeNode* left;
	CTreeNode* right;
	int BookID;
	string Author;
	string Title;
	int Year;
	int Quantity;
};

class CBinTree
{
public:
	CTreeNode* root;
	int maxId;
	CBinTree();
	CBinTree(string);
	void showBooks();
	void showBooksRec(CTreeNode*, string);
	void addBook();
	void deleteBookInfo(int);
	CTreeNode* deleteBookInfo(CTreeNode*, int);
	void findByTitle(string);
	void findByTitleRec(CTreeNode*, string, int*, int, string);
	void InfoByAuthor(string);
	void InfoByAuthorRec(CTreeNode*, string, int*);
	void insert(CTreeNode*, CTreeNode*);
};