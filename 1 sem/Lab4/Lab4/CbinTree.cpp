#define _CRT_SECURE_NO_WARNINGS
#include "CBinTree.h"
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
#include <sstream>
#include <cstdlib> 

CBinTree::CBinTree(string filename) {
	this->maxId = 0;
	ifstream file(filename);
	if (!file) abort();
	vector <CTreeNode*> nodes;
	while (!file.eof()) {
		CTreeNode* tmp = new CTreeNode(file);
		nodes.push_back(tmp);
		this->maxId++;
	}
	root = nodes[(nodes.size()-1)/2];
	nodes.erase(nodes.begin() + (nodes.size()-1) / 2);
	vector<CTreeNode*>::iterator it;
	for (it = nodes.begin(); it != nodes.end()-1; it++) {
		insert(root, *it);
	}
}
CBinTree::CBinTree() {
	root = NULL;
	this->maxId = 0;
}
CTreeNode::CTreeNode() {
	left = NULL;
	right = NULL;
	BookID = 0;
	Author = "";
	Title = "";
	Year = 0;
	Quantity = 0;
}
CTreeNode::CTreeNode(ifstream& file) {
	this->left = NULL;
	this->right = NULL;
	string tmp;
	getline(file, tmp);
	string token;
	stringstream splitStr(tmp);
	if(getline(splitStr, token, ','))
		this->BookID = stoi(token.substr(1, token.length()));
	if (getline(splitStr, token, ','))
		this->Author = token;
	if (getline(splitStr, token, ','))
		this->Title = token;
	if (getline(splitStr, token, ','))
		this->Year = stoi(token);
	if (getline(splitStr, token, ','))
		this->Quantity = stoi(token);
}
void CBinTree::showBooks() {
	showBooksRec(root, "");
	system("pause");
}
void CBinTree::showBooksRec(CTreeNode* root, string name) {
	if (root == NULL)
		return;
	
	cout << root->BookID << " " << root->Author << " " << '"' << root->Title << '"' << " " << root->Year << " " << root->Quantity << endl;
	showBooksRec(root->left, name);
	showBooksRec(root->right, name);
}
void CBinTree::findByTitle(string title) {
	int res = 0;
	findByTitleRec(root, title, &res, 0, "");
	if(res == 1)
		cout << "This book is available" << endl;
	else
		cout << "Unfortunately, we don't have this book" << endl;
	system("pause");
}
void CBinTree::findByTitleRec(CTreeNode* r, string name, int* result, int code, string author) {
	if (r == NULL)
		return;
	if (!(r->Title.compare(name)))
	{
		if (r->Quantity > 0) {
			*result = 1;
			if ((code > 0) && (!(r->Author.compare(author)))) {
				r->Quantity += code;
				*result = 2;
			}
		}
		return;
	}
	findByTitleRec(r->left, name, result, code, author);
	findByTitleRec(r->right, name, result, code, author);
}
void CBinTree::addBook() {
	int year = 0, quantity = 0;
	string author, title;
	CTreeNode* node = new CTreeNode();
	printf("\n Write the name of Author: ");
	std::cin.ignore();
	std::getline(std::cin, author);
	printf("\n Write the title: ");
	std::getline(std::cin, title);
	printf("\n Write the year edition: ");
	scanf("%d", &year);
	printf("\n Write the quantity: ");
	scanf("%d", &quantity);
	if (quantity < 1) abort();

	int res = 0;
	findByTitleRec(root, title, &res, quantity, author);
	if (res == 2) return;						// checking for the same book of the same author to add 
												// - only quantity will be changed
	node->BookID = this->maxId++;
	node->Author = author;
	node->Title = title;
	node->Year = year;
	node->Quantity = quantity;
	if (root != NULL)
		insert(root, node);
	else
		root = node;
}


void CBinTree::insert(CTreeNode* rt, CTreeNode* node) {
	if (rt->BookID > node->BookID) {
		if (rt->left != NULL) insert(rt->left, node);
		else rt->left = node;
	}
	else
		if (node->BookID > rt->BookID) {
			if (rt->right != NULL) insert(rt->right, node);
			else rt->right = node;
		}
}
void CBinTree::deleteBookInfo(int id) {
	root = deleteBookInfo(root, id);
}
CTreeNode* CBinTree::deleteBookInfo(CTreeNode* rt, int BookID) {
	if (rt == NULL)
		return rt;

	if (BookID == rt->BookID) {

		CTreeNode* tmp;
		if (rt->right == NULL)
			tmp = rt->left;
		else {

			CTreeNode* ptr = rt->right;
			if (ptr->left == NULL) {
				ptr->left = rt->left;
				tmp = ptr;
			}
			else {

				CTreeNode* pmin = ptr->left;
				while (pmin->left != NULL) {
					ptr = pmin;
					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = rt->left;
				pmin->right = rt->right;
				tmp = pmin;
			}
		}

		delete rt;
		return tmp;
	}
	else if (BookID < rt->BookID)
		rt->left = deleteBookInfo(rt->left, BookID);
	else
		rt->right = deleteBookInfo(rt->right, BookID);
	return rt;
}
void CBinTree::InfoByAuthor(string author) {
	int res = 0;
	InfoByAuthorRec(root, author, &res);
	if (res == 0)
		cout << "Unfortunately we don't have any information about this author" << endl;
	system("pause");
}
void CBinTree::InfoByAuthorRec(CTreeNode* r, string name, int* result) {
	if (r == NULL)
	{
		return;
	}
	if (!(r->Author.compare(name)))
	{
		if (r->Quantity > 0) {
			*result = 1;
			cout << r->Title << " is available !"<< endl;
		}
	}
	InfoByAuthorRec(r->left, name, result);
	InfoByAuthorRec(r->right, name, result);
}