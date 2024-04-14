//
// Created by filipegaio on 28-10-2023.
//

/**
 * @file
 * @brief This file is responsible to read the csv that hold information about each Student and the UC's and classes where he is and store them in an adequate place.
 *
 */

#ifndef PROJ2023_POVOATECLASSESLOAD_H
#define PROJ2023_POVOATECLASSESLOAD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Classs.h"
#include "Uc.h"

//This function will read data from csv and store every student and every class they're in

/**
 * @brief This function will read data from csv and store every student and every class they're in
 *
 */

vector<Student> PovoateClassesLoad(vector<Uc> *ucsImport) {

    vector<Student> students; // Vector to store CSV data (Students) just to start
    ifstream file("../schedule/students_classes_final.csv"); // Open the CSV file
    string line;

    bool first = true;
    while (getline(file, line)) {
        if (line != "\r"){
            istringstream ss(line);
            string nome, num, ucCode, classsCode;
            int numero;
            bool existeAluno = false;

            if (!first) {
                getline(ss, num, ',');
                getline(ss, nome, ','); // Read number as a string and then convert
                getline(ss, ucCode, ',');
                getline(ss, classsCode, '\r');
                numero = stoi(num);
                int i;
                for (i = 0; i < students.size(); i++){
                    if (students[i].getNumber() == numero){
                        existeAluno = true;
                        break;
                    }
                }
                if (!existeAluno){
                    Student student(numero, nome);
                    for (Uc &uc: *ucsImport) {
                        if (uc.getCode() == ucCode) {
                            for (Classs &c: uc.getClassses()) {
                                if (c.getCode() == classsCode) {
                                    c.addStudentToUc(student, ucCode);
                                    uc.updateClasss(c);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    students.push_back(student);
                }
                else{
                    for (Uc &uc: *ucsImport) {
                        if (uc.getCode() == ucCode) {
                            for (Classs &c: uc.getClassses()) {
                                if (c.getCode() == classsCode) {
                                    c.addStudentToUc(students[i], ucCode);
                                    uc.updateClasss(c);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            } else first = false;
        }
    }
    file.close();
    return students;
}


#endif //PROJ2023_POVOATECLASSESLOAD_H
