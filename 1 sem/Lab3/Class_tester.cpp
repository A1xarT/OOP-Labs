#include "Classes.h"

int main() {
	cString s1("Data");
	cString s2 = s1;
	printf("\n Copy counstructor called");
	s2.Print();
	s1 = "Second";
	if (s1.Getlength() == 6)
		printf("\n Getlength() of 'Second' == 6");
	cString s23;
	if (s23.Isempty())
		printf("\n default constructored object is empty");
	cString s("abc");
	s.Empty();
	if (s.Getlength() == 0)
		printf("\n Empty method worked properly");
	s = "abc";
	s.Print();
	s.SetAt(1, 'M');
	printf("\n SetAt(1,'M') of abc called");
	s.Print();
	s1 = "abc";
	s2 = "abd";
	if (s1.Compare(s2) == -1)
		printf("\n abc - abd == 1");
	s1 = "abcdef";
	s2 = "cde"; 
	if (s1.Mid(2, 3) == s2)
		printf("\n Mid(2,3) of abcdef == cde ");
	s1 = "abcdef";
	s2 = "abc";
	if (s1.Left(3) == s2)
		printf("\n Left(3) of abcdef == abc");
	s1 = "abcdef";
	s2 = "def";
	if (s1.Right(3) == s2)
		printf("\n Right(3) of abcdef == def");
	s1 = "abcdef";
	if (s1.Find('c') == 2)
		printf("\n Find(c) of abcdef == 2");
	if (s1.Find("bcde") == 1)
		printf("\n Find(bcde) of abcdef == 1");
	s1 = "abc";
	if (s1[1] == 'b')
		printf("\n abc[1] == b");        
	s1 = "cat";           
	s2 = s1;
	s2.Print();
	printf("\n Operator '=' worked properly");
	s1 = "abc";
	s2 = "def";
	if ((s1 + s2) == "abcdef")
		printf("\n abc  + def == abcdef");
	s1 = "abc";
	s2 = "def";
	s1 += s2; 
	printf("\n Result of abc += def :");
	s1.Print();

	return 0;
}