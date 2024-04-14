//
// Created by filipegaio on 28-10-2023.
//

/**
 * @file
 * @brief This file is responsible to read the csv that hold information about each UC and their classes and store them in an adequate place.
 *
 */

#ifndef PROJ2023_CLASSESPERUCLOAD_H
#define PROJ2023_CLASSESPERUCLOAD_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Classs.h"
#include "Uc.h"

using namespace std;



/**
 * @brief This function will read data from csv and store every class of every Uc
 *
 */

vector<Uc> loadClassesPerUc() {

    vector<Uc> ucs; // Vector to store CSV data (Ucs)

    ifstream file("../schedule/classes_per_uc.csv"); // Open the CSV file
    string line;

    bool first = true;
    while (getline(file, line)) {
        istringstream ss(line);
        bool existeUc = false;
        string ucCode, classsCode;

        if (!first) {
            getline(ss, ucCode, ',');
            getline(ss, classsCode, '\r');
            for (Uc &uc: ucs) {
                if (uc.getCode() == ucCode) {
                    uc.addClasss(Classs(classsCode));
                    existeUc = true;
                    break;
                }
            }
            if (!existeUc) {
                Uc uc = Uc(ucCode);
                Classs classs = Classs(classsCode);
                uc.addClasss(classs);
                ucs.push_back(uc);
            }

        }
        first = false;
    }
    return ucs;
}

#endif //PROJ2023_CLASSESPERUCLOAD_H