//
// Created by filipegaio on 27-10-2023.
//
#include "Student.h"

//Implements Student.h

Student::Student() {
    this->name_ = "Default";
    this->number_ = 999999999;
}

Student::Student(int number, string name) {
    this->number_ = number;
    this->name_ = name;
}

void Student::setNumber(int number) { this->number_ = number; }

void Student::setName(string name) { this->name_ = name; }

int Student::getNumber() const { return this->number_; }

string Student::getName() const { return this->name_; }

vector<pair<string ,string>> Student::getIsIn() const { return this->isIn_UcCl; }

void Student::enroll(const string& uc, const string& cl) {
    isIn_UcCl.emplace_back(uc, cl); //emplace back is the same as psh back but more eficient when we want to push back pairs
}

void Student::clearIsIn() {this->isIn_UcCl.clear();}

void Student::printStudent() const{
    cout << "Nome: " << this->name_ << ", Número mecanográfico: " << this->number_ << endl;
}

void Student::printStudentIsIn() const {
    cout << "\nEstá incrito em: " << endl;
    for (auto uccl : this->isIn_UcCl){
        cout << "\tUC : " << uccl.first << " || Turma : " << uccl.second << endl;
    }
}

void Student::remove(string ucCode)
{
    for(auto it = this->isIn_UcCl.begin(); it != this->isIn_UcCl.end(); it++)
    {
        if(it->first == ucCode){
            isIn_UcCl.erase(it);
            break;
        }
    }
}


