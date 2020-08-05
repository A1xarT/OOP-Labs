#pragma once
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <typeinfo>


class Person {
public:
	Person() {};
	Person(std::string _f_name, std::string _l_name, int _age) : age(_age), f_name(_f_name), l_name(_l_name) {};
	virtual void Display(bool dep) = 0;
	int GetAge();
protected:
	std::string f_name;//first name
	std::string l_name;//last name
	int age = -1;
};

class Employee : public Person {
public:
	Employee() {};
	Employee(std::string _f_name, std::string _l_name, int _age, int _id) : Person(_f_name, _l_name, _age), id(_id) {};
	Employee(const Employee& e);
	Employee& operator=(const Employee& e);
	void SetSalary(int s);	
	void SetDepartment(std::string dept);
	void SetId(int n);
	int GetId();
	std::string GetDepartment() const;
	virtual void Display(bool dep);
	//Add here whatever you need
	int GetSalary()const;
	std::string GetType()const;

protected:
	std::string department = "";
	std::string obj_type = "Employee";
	int salary = 0;
	int id = -1;
};

class Manager : public Employee {
public:
	Manager() { obj_type = "Manager"; };	
	Manager(std::string _f_name, std::string _l_name, int _age, int _id) :
		Employee(_f_name, _l_name, _age, _id) {
		obj_type = "Manager";
	};
	Manager(const Manager& m);
	Manager& operator=(const Manager& m);
	virtual void Display(bool dep);
	//add an employee to the subordinates std::list
	Person* AddSubordinate(Person* p);
	void DisplaySubordinates();
	//Add here whatever you need
	bool DeleteSubordinate(int id);

private:
	std::list <Person*> subordinates;//spysok pidleglih
};

class Database {

public:
	Database() {};
	~Database() {};//no need in destructor
	//creates “flat” database
	bool LoadFromFile(const char* file);
	//arranges "flat" database after loading from the file
	void ArrangeSubordinates();
	//hire a new employee
	Person* HireEmployee(Person* p);
	void DisplayDepartmentEmployees(std::string _department);
	//fire the employee
	bool FireEmployee(int id);
	void DisplayAll();
	std::vector<Person*> SQL(const char* field, const char* cond, const char* value);
	void ShowRecordSet(std::vector<Person*> rs);
		//Add here whatever you need

private:
	std::vector<Person*> employees;
};

