//
// Created by filipegaio on 28-10-2023.
//

#include "Uc.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Uc::Uc() { this->codeUc_ = "UC.00000"; } //Default constructor

Uc::Uc(std::string code) { this->codeUc_ = code; }

void Uc::setCode(std::string code) { this->codeUc_ = code; } //set UC code

string Uc::getCode() const { return this->codeUc_; } //returns UC's code

vector<Classs> Uc::getClassses() const {return this->classes_;} //returns UC's classes

void Uc::setClassses(vector<Classs> classes) {this->classes_ = classes;} //ter a vector os classes

void Uc::addClasss(const Classs& aClasss) { this->classes_.push_back(aClasss);} //adds a class

void Uc::updateClasss(const Classs& aClasss) { //replaces a certain class info with a given class (easier than making the for the entire UC classes)
    for (auto & classe : classes_){
        if (classe.getCode() == aClasss.getCode()){
            classe = aClasss;
            break;
        }
    }
}

int Uc::diffMaxClasssAttendance()
{
    int min = 40;
    int max = 0;
    for(const Classs& classs : this->classes_) //iterates over every class of the uc to check the max difference of number of students in it
    {
        if(classs.getStudents().size() < min)
            min = classs.getStudents().size();
        if(classs.getStudents().size() > max)
            max = classs.getStudents().size();
    }
    return max-min;
}


bool Uc::switchClass(Student& student, vector<Uc>& ucs, vector<Student>& students, Classs& classsAtual, string requiredClasss)
{
    //process a switch request between two classes of a certain UC
    Uc* temp = new Uc(*this);
    Student tempS = student; //creates a temp UC and student to check if entering the new Class and leaving from the last wont affect its balance
    for(Classs& class_ : temp->getClassses())
    {
        if(class_.getCode() == requiredClasss)
        {
            class_.addStudentToUc(tempS, this->codeUc_);
        }
        if(class_.getCode() == classsAtual.getCode())
        {
            class_.removeStudent(tempS, this->codeUc_);
        }
    }
    for(Classs &class_ : this->classes_)
    {
        if(class_.getCode() == requiredClasss)
        {
            if(this->diffMaxClasssAttendance() > 4) //for classes that dont have the balance
            {
                if(class_.canEnter() && !this->scheduleConflicts(true, class_, tempS, ucs) && (temp->diffMaxClasssAttendance() <= this->diffMaxClasssAttendance()))
                {
                    //If everything is acceptable for our students switch processes it
                    class_.addStudentToUc(student, this->codeUc_);
                    classsAtual.removeStudent(student, std::string());
                    student.remove(this->codeUc_);
                    modifyingStudents("switch", student.getNumber(), student.getName(), requiredClasss, this->codeUc_);
                    writeSwitch(student.getNumber(), this->codeUc_, requiredClasss, classsAtual.getCode());
                    return true;
                }
                else return false;
            }
            else //for balanced classes
            {
                if(class_.canEnter() && !scheduleConflicts(true, class_, tempS, ucs) && temp->diffMaxClasssAttendance() <= 4)
                {
                    //If everything is acceptable for our students switch processes it
                    class_.addStudentToUc(student, this->codeUc_);
                    classsAtual.removeStudent(student, std::string());
                    student.remove(this->codeUc_);
                    modifyingStudents("switch", student.getNumber(), student.getName(), requiredClasss, this->codeUc_);
                    writeSwitch(student.getNumber(), this->codeUc_, requiredClasss, classsAtual.getCode());

                    return true;
                }
                else return false;
            }
        }
    }
    return false;
}


bool Uc::addUc(Student& student, vector<Uc>& ucs)
{
    //Processes add student to a new UC
    int min = 41;
    Classs* atual;
    if (student.getIsIn().size() < 7){ //check if student is elegible
        for (Classs& classs : this->classes_){
            if ( classs.getStudents().size() < min){
                atual = &classs;
                min = classs.getStudents().size();
            }
        }
        if(atual->canEnter() && !scheduleConflicts(false, *atual , student, ucs)){ //try to add him to the least popualated class
            //Checks if student don't have conflicts by enetering and if class is ready to recieve him
            atual->addStudentToUc(student, this->getCode());
            modifyingStudents("add", student.getNumber(), student.getName(), atual->getCode(), this->codeUc_);
            return true;
        }
        for (Classs& classs : this->classes_){
            if(classs.canEnter() && !scheduleConflicts(false, classs , student, ucs)){
                //Checks if student don't have conflicts by enetering and if class is ready to recieve him
                classs.addStudentToUc(student, this->getCode());
                modifyingStudents("add", student.getNumber(), student.getName(), classs.getCode(), this->codeUc_);
                return true;
            }
        }

    }
    return false;
}

bool Uc::removeUc(Student& student, vector<Uc>& ucs, Classs atualClass)
{
    //process remove request
    Uc* temp = new Uc(*this);
    Student tempS = student;
    atualClass.removeStudent(tempS, this->codeUc_);
    temp->updateClasss(atualClass);
    if (temp->diffMaxClasssAttendance() <= this->diffMaxClasssAttendance()){ //checks if leaving wont ruin the balance
        for (Classs& classs : this->classes_){
            if ( classs.getCode() == atualClass.getCode()){
                classs.removeStudent(student, this->codeUc_); //process the remove
                modifyingStudents("remove", student.getNumber(), student.getName(), atualClass.getCode(), this->codeUc_);
                delete temp;
                return true;
            }
        }
    }
    delete temp;
    return false;

}

bool Uc::scheduleConflicts(bool switchRequest, const Classs& requiredClasss, Student student, vector<Uc>& ucs)
{
    //looks for schdule conflits
    string yourClasss;
    //checks type of request
    if(switchRequest)
    {
        for(auto& pair : student.getIsIn())
        {
            if(this->codeUc_ == pair.first)
                yourClasss = pair.second;
        }
        student.remove(this->getCode());

    }
    for(auto& pair : student.getIsIn()) //Checks for every class that the student is in if any classes collide
    {
        for(const Uc& uc_ : ucs)
        {
            if(pair.first == uc_.getCode())
            {
                for(const Classs& class_ : uc_.classes_)
                {
                    if(pair.second == class_.getCode())
                    {
                        for(const Aula& aula_ : class_.getSchedule())
                        {
                            for(const Aula& aula2_ : requiredClasss.getSchedule())
                            {
                                if((aula_.type == "TP" && aula2_.type == "TP" || aula_.type == "TP" && aula2_.type == "PL" || aula_.type == "PL" && aula2_.type == "TP" || aula_.type == "PL" && aula2_.type == "PL") && aula_.weekDay == aula2_.weekDay && ((aula_.start <= aula2_.start && aula_.end > aula2_.start) || (aula_.start >= aula2_.start && aula2_.end > aula_.start)))
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (switchRequest) student.enroll(this->codeUc_, yourClasss);
    return false;

}


void Uc::modifyingStudents(string type, int num, string nameStudent, string requiredClass, string requiredUc)
{
    if(type == "add")
    {
        fstream file("../schedule/students_classes_final.csv", ios::app);
        file << num << "," << nameStudent << "," << requiredUc << "," << requiredClass << endl;
        writeAdd(num, requiredUc, requiredClass);
    }
    else if(type == "remove")
    {
        fstream file("../schedule/students_classes_final.csv");
        string s, numS, nameS, ucS, classS;
        int count = 0;
        while(getline(file, s))
        {
            istringstream iss(s);
            getline(iss, numS, ',');
            getline(iss, nameS, ',');
            getline(iss, ucS, ',');
            getline(iss, classS, '\r');
            if(numS == to_string(num) && nameS == nameStudent && requiredUc == ucS)
                removeLine(count);
            ++count;
        }
        writeRemove(num, requiredUc, requiredClass);
    }
    else if (type == "switch") {
        ifstream inputFile("../schedule/students_classes_final.csv");
        ofstream tempFile("temp.csv");
        string line, numS, nameS, ucS, classS;

        int count = 0;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            getline(iss, numS, ',');
            getline(iss, nameS, ',');
            getline(iss, ucS, ',');
            getline(iss, classS, '\r');

            if (numS == std::to_string(num) && nameS == nameStudent && ucS == requiredUc) {
                // Modify the classS value here (classS = requiredClass;)
                classS = requiredClass;
            }

            // Reconstruct the modified line and write it to the temporary file
            tempFile << numS << "," << nameS << "," << ucS << "," << classS << std::endl;
        }

        inputFile.close();
        tempFile.close();

        // Remove the original file and rename the temporary file to the original file name
        remove("../schedule/students_classes_final.csv");
        rename("temp.csv", "../schedule/students_classes_final.csv");
    }
}
void Uc::removeLine(size_t lineToDelete)
{
    ifstream inputFile("../schedule/students_classes_final.csv");
    ofstream tempFile("temp.txt");
    string line;
    int currentLine = -1;

    while (getline(inputFile, line)) {
        currentLine++;
        if (currentLine != lineToDelete) {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    // Remove the original file and rename the temporary file to the original file name
    remove("../schedule/students_classes_final.csv");
    rename("temp.txt", "../schedule/students_classes_final.csv");
}

void Uc::writeAdd(int num, string requiredUc, string requiredClass)
{
    ofstream out("../schedule/operations.csv", ios::app);
    out << "add," << num << "," << requiredUc << "," << requiredClass << endl;
}

void Uc::writeRemove(int num, string requiredUc, string requiredClass)
{
    ofstream out("../schedule/operations.csv", ios::app);
    out << "remove," << num << "," << requiredUc << "," << requiredClass << endl;
}

void Uc::writeSwitch(int num, string uc, string requiredClass, string currentClass)
{
    ofstream out("../schedule/operations.csv", ios::app);
    out << "switch," << num << "," << uc << "," << currentClass << "," << requiredClass << endl;
}

void Uc::printClassSchedule(Classs aClasss) {
    cout << "UC: " << this->codeUc_ << " || ";
    aClasss.printAula();
}