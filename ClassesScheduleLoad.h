//
// Created by filipegaio on 29-10-2023.
//

/**
 * @file
 * @brief This file is responsible to read the csv that hold information about each class and their schedule and store them in an adequate place.
 *
 */

#ifndef PROJ2023_CLASSESSCHEDULELOAD_H
#define PROJ2023_CLASSESSCHEDULELOAD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Classs.h"
#include "Uc.h"

using namespace std;

/**
 * @brief This function will read data from csv and store every class's schedule
 *
 * @param students A vector with all students and respective information
 * @param ucs A vector with all ucs and respective information (Will hold the information about the schedule of each class).
 * @return Will return the altered ucs vector.

 */
//This function will read data from csv and store every Schedule of every class

vector<Uc> loadClassesSchedule(vector<Uc> *ucsImport, vector<Student> *studentsStudents) {


    ifstream file("../schedule/classes.csv"); // Open the CSV file
    string line;

    bool first = true;
    while (getline(file, line)) {
        istringstream ss(line);
        string ucCode, classsCode, weekday, startHour, duration, type;

        if (!first) {
            getline(ss, classsCode, ',');
            getline(ss, ucCode, ',');
            getline(ss, weekday, ',');
            getline(ss, startHour, ',');
            getline(ss, duration, ',');
            getline(ss, type, '\r');
            double start = stod(startHour);
            double end = stod(duration);
            end += start;
            Aula aula = {weekday, start, end, type};
            for (Uc &uc: *ucsImport) {
                if (uc.getCode() == ucCode) {
                    for (Classs &c: uc.getClassses()) {
                        if (c.getCode() == classsCode) {
                            c.addAula(aula);
                            uc.updateClasss(c);
                            break;
                        }
                    }
                    break;
                }
            }

        }
        first = false;
    }
    return *ucsImport;
}

#endif //PROJ2023_CLASSESSCHEDULELOAD_H
