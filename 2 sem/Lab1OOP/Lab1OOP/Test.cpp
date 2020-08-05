#include "Classes.h"

using namespace std;

int main() {
	List A(3,1);
	List B(A);
	List C;
	C.push_back(1);
	C.insert(1, 0, 2);
	List D = B;
	D = D;
	if (D == C) cout << "Copying and comparing operators worked properly\n";
	D.pop_back();
	D.pop_front();
	D.push_back(10);
	if (11 == int(D)) cout << "Sum of {1,10} == 11 \n";
	if (A.back().GetValue() == A.begin().GetValue()) cout << "A.back() == A.begin() in A = {1,1,1} \n";
	cout << "A: " << endl;
	A.Print();
	A.clear();
	cout << "A.clear() was called" << endl;
	if (A.empty()) cout << "A.empty() is true. Let's see what A.Print() will say => \n =>";
	A.Print();
	cout << "B: " << endl;
	B.Print();
	B.erase(0);
	B.erase(0, 1);
	cout << "B.erase(0) and B.erase(0, 1) were called" << endl;
	B.Print();
	int mas[2] = { 1, 1 };
	D.Print();
	cout << "Inserting {1, 1} " << endl;
	D.insert(0, mas, 2);
	D.Print();
	A.clear();
	B.clear();
	for (int i = 1; i < 5; i++) {
		A.push_back(2-i);
		B.push_front(4-i);
	}
	cout << "Merging 2 lists\n";
	A.Print();
	B.Print();
	A.merge(B);
	A.Print();
	C.clear();
	for (int i = 0; i < 3; i++)
		C.push_front(1);
	C.push_front(3);
	cout << endl;
	C.Print();
	cout << "Removing all nodes with value = 1\n";
	C.remove(1); 
	C.Print();
	cout << "resize(4) called\n";
	C.resize(4);
	cout << "resize(6, 2) called\n";
	C.Print();
	C.resize(6, 2);
	C.Print();
	C.reverse();
	cout << "Reverse called \n";
	C.Print();
	printf("Size = %d\n", C.size());
	C.sort(); C.unique();
	printf("sort() and unique() called \n");
	C.Print();
	cout << "Size = " << C.size() << endl;
	cout << "C: " << endl;
	C.Print();
	cout << "D: " << endl;
	D.Print();
	cout << "C.splice(1, D) called " << endl;
	C.splice(1, D);
	cout << "C: " << endl;
	C.Print();
	cout << "D: " << endl;
	D.Print();
	D.swap(C);
	cout << "C and D were swapped" << endl;
	cout << "C: " << endl;
	C.Print();
	cout << "D: " << endl;
	D.Print();
}