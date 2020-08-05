#include "Classes.h"
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

int Person::GetAge() {
	return age;
}

void Employee::Display(bool dep) {
	if(dep == 1)
	cout << " Employment type: " + obj_type << endl << " id: " << GetId() << endl << " " + f_name + " " + l_name << " age: " 
		<< age << " salary: " << GetSalary() << endl << " department: " + GetDepartment() << endl;
	else
		cout << "\n\t Employment type: " + obj_type << endl << "\t id: " << GetId() << endl << "\t " + f_name + " " + l_name << " age: "
		<< age << " salary: " << GetSalary() << endl;	
		 
}

void Employee::SetId(int n) {
	id = n;
}

void Employee::SetSalary(int s) {
	salary = s;
}

void Employee::SetDepartment(string dept) {
	department = dept;
}

int Employee::GetId() {
	return id;
}

int Employee::GetSalary() const{
	return salary;
}

string Employee::GetDepartment() const{
	if (department == "") return "none";
	return department;
}

string Employee::GetType()const {
	return obj_type;
}

Employee::Employee(const Employee& e) {
	f_name = e.f_name;
	l_name = e.l_name;
	age = e.age;
	id = e.id;
	salary = e.GetSalary();
	department = e.GetDepartment();
}

Employee& Employee::operator=(const Employee& e) {
	Employee *tmp = new Employee(e);
	delete this;
	return *tmp;
}


void Manager::Display(bool dep){
	Employee::Display(1);
	if (dep == 0) {
		cout << " Subordinates: ";
		DisplaySubordinates();
	}
}

Person* Manager::AddSubordinate(Person* p) {
	if (p == nullptr) return nullptr;
	if (subordinates.end() != find(subordinates.begin(), subordinates.end(), p))
		return nullptr;
	Employee * A = dynamic_cast<Employee*>(p);
	if (A->GetDepartment() != this->GetDepartment())
		A->SetDepartment(this->GetDepartment());
	subordinates.push_back(p);
	return p;
}

void Manager::DisplaySubordinates() {
	if (subordinates.size() == 0)
		cout << " none " << endl;
	for (Person* n : subordinates)
		n->Display(0);
}

Manager::Manager(const Manager& m) {
	f_name = m.f_name;
	l_name = m.l_name;
	age = m.age;
	id = m.id;
	salary = m.GetSalary();
	department = m.GetDepartment();
	for (Person* p : m.subordinates)
		subordinates.push_back(p);
}

Manager& Manager::operator=(const Manager& m) {
	Manager* tmp = new Manager(m);
	delete this;
	return *tmp;
}

bool Database::LoadFromFile(const char* file) {
	ifstream fin;
	fin.open(file);
	if (fin.eof()) {
		fin.close();
		return false;
	}
	string line, tmp, f_name, l_name, department;
	list <string>* row = new list <string>{};
	list <string>::iterator it;
	int j, iter, flag, id, age, salary;
	while (!fin.eof()) {
		j = iter = 0;
		fin >> line;
		if (fin.eof()) break;
		while (j != line.size()) {
			if (line[j] == ';') {
				tmp = line.substr(iter, j - iter);
				row->push_back(tmp);
				j = j + 1;
				iter = j;
				continue;
			}
			j++;
		}
		tmp = line.substr(iter);
		row->push_back(tmp);
		it = (*row).begin();
		flag = stoi(*it); it++;
		id = stoi(*it); it++;
		f_name = *it; it++;
		l_name = *it; it++;
		int age = stoi(*it); it++;
		department = *it; it++;
		salary = stoi(*it); it++;
		if(flag == 0){
			Employee* AnotherOne = new Employee(f_name, l_name, age, id);
			AnotherOne->SetDepartment(department);
			AnotherOne->SetSalary(salary);
			employees.push_back(AnotherOne);
		}
		else {
			Manager* AnotherOne = new Manager(f_name, l_name, age, id);
			AnotherOne->SetDepartment(department);
			AnotherOne->SetSalary(salary);
			employees.push_back(AnotherOne);
		}
		row->clear();
	}
	fin.close();
	return true;
}

void Database::ArrangeSubordinates() {
	for (Person* p : employees) {
		if (dynamic_cast<Employee*>(p)->GetType() == "Manager") {
			for (Person* pn : employees) {
				if (dynamic_cast<Employee*>(pn)->GetType() == "Employee") {
					if (dynamic_cast<Employee*>(p)->GetDepartment() == dynamic_cast<Employee*>(pn)->GetDepartment())
						if (&p != &pn) {
							dynamic_cast<Manager*>(dynamic_cast<Employee*>(p))->AddSubordinate(dynamic_cast<Employee*>(pn));
						}
				}
			}
		}
	}
}

Person* Database::HireEmployee(Person* p) {
	if (p == nullptr) abort();
	if (employees.end() != find(employees.begin(), employees.end(), p))
		return nullptr;
	employees.push_back(p);
	ArrangeSubordinates();
	return employees.back();
}

bool Manager::DeleteSubordinate(int id) {
	bool flag = false;
	for (Person* p : subordinates) {
		if (dynamic_cast<Employee*>(p)->GetId() == id) {
			subordinates.remove(p);
			flag = true;
			break;
		}
	}
	return flag;
}

bool Database::FireEmployee(int id) {
	bool flag = false;
	int it = 0;
	for (Person* p : employees) {
		if (dynamic_cast<Employee*>(p)->GetId() == id) {
			employees.erase(employees.begin() + it);
			flag = true;
		}
		it++;
	}
	if (!flag) return flag;
	for (Person* p : employees) {
		if (dynamic_cast<Employee*>(p)->GetType() == "Manager") {
			dynamic_cast<Manager*>(dynamic_cast<Employee*>(p))->DeleteSubordinate(id);
		}
	}
	return flag;
}

void Database::DisplayDepartmentEmployees(string _department) {
	for (Person* p : employees) {
		if (dynamic_cast<Employee*>(p)->GetDepartment() == _department)
			p->Display(1);
	}
}

vector<Person*> Database::SQL(const char* field, const char* cond, const char* value) {
	vector<Person*>* vec = new vector <Person*>{};
	if (!strlen(value)) return *vec;
	if ((field == nullptr) || (cond == nullptr) || (value == nullptr)) return *vec;
	if (!strcmp(field, "age")) {
		if (!strcmp(cond, "le")) {
			for (Person* p : employees)
				if (dynamic_cast<Employee*>(p)->GetAge() <= stoi(value))
					vec->push_back(p);
		}
		else if (!strcmp(cond, "ge")) {
			for (Person* p : employees)
				if (dynamic_cast<Employee*>(p)->GetAge() >= stoi(value))
					vec->push_back(p);
			}
	}
	else
		if (!strcmp(field, "salary")) {
			if (!strcmp(cond, "le")) {
				for (Person* p : employees)
					if (dynamic_cast<Employee*>(p)->GetSalary() <= stoi(value))
						vec->push_back(p);
			}
			else if (!strcmp(cond, "ge")) {
				for (Person* p : employees)
					if (dynamic_cast<Employee*>(p)->GetSalary() >= stoi(value))
						vec->push_back(p);
			}
		}
	return *vec;
}

void Database::ShowRecordSet(std::vector<Person*> rs) {
	for (Person* p : rs) {
		if (dynamic_cast<Employee*>(p)->GetType() == "Employee")
			dynamic_cast<Employee*>(p)->Display(1);
		else
			dynamic_cast<Manager*>(dynamic_cast<Employee*>(p))->Display(0);
	}
}

void Database::DisplayAll() {
	for (Person* p : employees) {
		if (dynamic_cast<Employee*>(p)->GetType() == "Manager") {
			dynamic_cast<Employee*>(p)->Display(0);
		}
		else
			dynamic_cast<Employee*>(p)->Display(1);
	}
}

