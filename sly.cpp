#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Person
{
private:
    char* Name;
    char* Gender;
public:
    Person(char* name, char* gender)
    {
        Name = new char[strlen(name) + 1];
        Gender = new char[strlen(gender) + 1];
        strcpy(Name, name);
        strcpy(Gender, gender);
    }
    Person(const Person& other)
    {
        if (&other != this)
        {
            this->Name = new char[strlen(other.Name) + 1];
            this->Gender = new char[strlen(other.Gender) + 1];
            strcpy(this->Name, other.Name);
            strcpy(this->Gender, other.Gender);
        }
    }
    Person& operator=(const Person& other)
    {
        if (&other != this)
        {
            delete[] Gender;
            delete[] Name;
            this->Name = new char[strlen(other.Name) + 1];
            this->Gender = new char[strlen(other.Gender) + 1];
            strcpy(this->Name, other.Name);
            strcpy(this->Gender, other.Gender);
        }
        return *this;
    }
    char* getGender()
    {
        return this->Gender;
    }
    char* getName()
    {
        return this->Name;
    }
    virtual ~Person() 
    {
        delete[] Gender;
        delete[] Name;
        cout << "~Person()" << endl;
    }
    virtual void printInfo()
    {
        cout << this->getName() << " " << this->getGender() << endl;
    }

    friend ostream& operator<<(ostream& output, Person& person);
    friend istream& operator>>(istream& input, Person& person);
};

ostream& operator<<(ostream& output, Person& person)
{
    output << person.Name << " " << person.Gender;
    return output;
}

istream& operator>>(istream& input, Person& person)
{
    char tepName[100];
    char tepGender[10];
    input >> tepName;
    input >> tepGender;
    delete[] person.Name;
    delete[] person.Gender;

    person.Name = new char[strlen(tepName) + 1];
    person.Gender = new char[strlen(tepGender) + 1];
    strcpy(person.Name, tepName);
    strcpy(person.Gender, tepGender);
    return input;
}

class Student :public Person
{
    friend class Teacher;
private:
    string StudentId;
    double Score;
public:
    Student(char* name, char* gender, string studentId, double score)
        :Person(name, gender), StudentId(studentId), Score(score) { }
    ~Student()
    {
        cout << "~Student()" << endl;
    }
    void printInfo() override
    {
        cout << this->StudentId << " " << this->getName() << " ";
        cout << this->getGender() << ": " << this->Score << endl;
    }
    string getStudentId()
    {
        return this->StudentId;
    }
    double getScore()
    {
        return this->Score;
    }
};

class Teacher :public Person
{
private:
    string TeacherId;
    int Teach_year;
public:
    Teacher(char* name, char* gender, string teacherId, int year)
        :Person(name, gender), TeacherId(teacherId), Teach_year(year) { }
    ~Teacher()
    {
        cout << "~Teacher()" << endl;
    }
    void printInfo() override
    {
        cout << this->TeacherId << " " << this->getName() << " ";
        cout << this->getGender() << ": " << this->Teach_year << endl;
    }
    void getStudentInfo(Student& student)
    {
        cout << student.getStudentId() << " " << student.getName() << " ";
        cout << student.getGender() << ": " << student.getScore() << endl;
    }
};

int main()
{
    char name[] = "Lucy";
    char gender[] = "nv";
    Student student(name, gender, "S2026001", 95);
    Teacher teacher(name, gender, "T2026001", 15);
    Person* personptr = &student;
    personptr->printInfo();
    personptr = &teacher;
    personptr->printInfo();

    char namee[] = "Bob";
    char genderr[] = "nan";
    Person* p = new Student(namee, genderr, "S2026002", 85);
    p->printInfo();
    Person* q = new Teacher(namee, genderr, "T2026002", 10);
    q->printInfo();
    delete p;
    delete q;
}

