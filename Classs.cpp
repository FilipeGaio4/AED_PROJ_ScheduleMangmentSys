//
// Created by filipegaio on 28-10-2023.
//

#include "Classs.h"

using namespace std;

Classs::Classs() {
    this->codeCl_ = "CL.00000";
    this->students_.clear();
}

Classs::Classs(std::string code) {
    this->codeCl_ = code;
}

void Classs::setCode(std::string code) {this->codeCl_ = code;}

string Classs::getCode() const {return this->codeCl_;}

vector<Student> Classs::getStudents() const {return this->students_;}

vector<Aula> Classs::getSchedule() const {return this->aulas_;}

void Classs::setStudents(vector<Student> students) {this->students_ = students;}

void Classs::addStudentToUc(Student &student, string ucCode) {
    student.enroll(ucCode, this->codeCl_);
    Student temp = student;
    temp.clearIsIn();
    this->students_.push_back(student);
}


void Classs::removeStudent(Student &student, string ucCode) {
    for(auto it = students_.begin(); it != students_.end(); it++)
    {
        if(it->getNumber() == student.getNumber())
        {
            students_.erase(it);
            break;
        }
    }
    student.remove(ucCode);
}

void Classs::addAula(Aula aula) {this->aulas_.push_back(aula);}

void Classs::printAula() {
    cout << "Turma: " << this->codeCl_ << endl;
    for (auto a : this->aulas_){
        cout <<"\t_______________" << endl << "\tWeek Day: " << a.weekDay << endl << "\tStart at: " << a.start << endl << "\tEnds at: " << a.end << endl << "\tType: " << a.type << endl ;
    }
}

bool Classs::canEnter() {return this->students_.size() < Cap;}

bool Classs::scheduleConflicts(Classs requiredClasss)
{
    for(Aula aula_ : this->aulas_)
    {
        for(Aula aula2_ : requiredClasss.aulas_)
        {
            if((aula_.type == "TP" && aula2_.type == "TP" || aula_.type == "TP" && aula2_.type == "PL" || aula_.type == "PL" && aula2_.type == "TP" || aula_.type == "PL" && aula2_.type == "PL") && aula_.weekDay == aula2_.weekDay && ((aula_.start <= aula2_.start && aula_.end > aula2_.start) || (aula_.start >= aula2_.start && aula2_.end > aula_.start)))
            {
                return true;
            }
        }
    }
    return false;
}

