#include "CBinTree.h"

void DeleteBook(CBinTree& tree) {
	cout << "Enter the book inventory number" << endl;
	int tmp;
	cin >> tmp;
	tree.deleteBookInfo(tmp);
}
void ShowByAuthor(CBinTree& tree) {
	cout << "Enter the book Author" << endl;
	string tmp = "";
	cin.ignore(9000, '\n');
	getline(cin, tmp);
	tree.InfoByAuthor(tmp);
}
void ShowByTitle(CBinTree& tree) {
	cout << "Enter the title name" << endl;
	string tmp = "";
	cin.ignore(9000, '\n');
	getline(cin, tmp);
	tree.findByTitle(tmp);
}

bool menu(CBinTree& tree) {
	cout << "\n\t\t\ Welcome to our library" << endl << endl;
	cout << "        Please choose option and press ENTER" << endl;
	cout << "\t1. Add a new book to library" << endl;
	cout << "\t2. Delete a book by inventory number" << endl;
	cout << "\t3. Show available books by Author" << endl;
	cout << "\t4. Check the book in library" << endl;
	cout << "\t5. Show all books" << endl;
	cout << "\t6. Exit\n";
	cout << "Your choice: ";

	int choice = 0;
	scanf_s("%d", &choice);

	switch (choice) {
	case 1: tree.addBook(); break;
	case 2: DeleteBook(tree); break;
	case 3: ShowByAuthor(tree); break;
	case 4: ShowByTitle(tree); break;
	case 5: tree.showBooks(); break;
	case 6: return false;
	default: abort();
	}
	return true;
}


int main()
{
	CBinTree* tree = new CBinTree("library.csv");
	while (menu(*tree)) {
		system("cls");
	}
	system("pause");
	return 0;
}

