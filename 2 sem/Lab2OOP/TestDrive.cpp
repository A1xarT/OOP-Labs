#include "Classes.h"


using namespace std;

int main()
{
	Employee *First = new Employee("Alexander", "Petrov", 18, 1);
	Employee E1("Ivan", "Ivanov", 40, 20);
	E1.SetDepartment("IT");
	E1.SetSalary(900);
	Employee E2("Maxim", "Doll", 19, 21);
	E2.SetDepartment("IT");
	First->SetDepartment("IT");
	First->SetSalary(1500);
	First = First;
	Employee Second(*First);
	delete First;
	cout << " Display() called" << endl;
	Second.Display(1);
	Manager* M = new Manager("Gennady", "Kontaldo", 40, 11);
	M->SetDepartment("IT");
	M->SetSalary(3000);
	M = M;
	M->AddSubordinate(&Second);
	cout << " DisplaySubordinates() called" << endl;
	M->DisplaySubordinates();
	Database* Data = new Database();
	Data->LoadFromFile("input.csv");
	cout << "\n LoadFromFile() called" << endl;
	Data->DisplayAll();
	Data->HireEmployee(&Second);
	Data->HireEmployee(&E1);
	Data->HireEmployee(&E2);
	Data->HireEmployee(M);
	Data->ArrangeSubordinates();
	cout << "\n ArrangeSubordinates() called" << endl;
	Data->DisplayAll();
	cout << "\n Data->DisplayDepartmentEmployees('IT') called" << endl;
	Data->DisplayDepartmentEmployees("IT");
	Employee ToHire("Jack", "Dagger", 25, 6);
	ToHire.SetDepartment("IT");
	cout << "\n Data->HireEmployee(&ToHire) called" << endl;
	Data->HireEmployee(&ToHire);
	cout << "\n Data->DisplayDepartmentEmployees('IT') called" << endl;
	Data->DisplayDepartmentEmployees("IT");
	cout << "\n Data->FireEmployee(id of ToHire) called" << endl;
	Data->FireEmployee(6);
	cout << "\n Data->DisplayDepartmentEmployees('IT') called" << endl;
	Data->DisplayDepartmentEmployees("IT");
	cout << "\n Data->ShowRecordSet(Data->SQL('age', 'le', '21')) called" << endl;
	Data->ShowRecordSet(Data->SQL("age", "le", "21"));
	cout << "\n Data->DisplayAll() called" << endl;
	Data->DisplayAll();
	return 0;
}