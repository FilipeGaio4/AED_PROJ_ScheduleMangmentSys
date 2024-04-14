//
// Created by filipegaio on 01-11-2023.
//

/**
 * @file
 * @brief This file holds some functions that will make code cleaner and easier to understand.
 *
 */

#ifndef PROJ2023_AUXILIARFUNCTIONS_H
#define PROJ2023_AUXILIARFUNCTIONS_H


#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "Student.h"
#include "Classs.h"
#include "Uc.h"
#include "Opperation.h"

using namespace std;

/**
 * @brief This functions prints to the terminal the Schedule of a certain student,
 *
 *
 * @param isInUcCl A vector that holds pairs for every Uc, Class that the student is part of.
 * @param ucs A vector with all ucs and respective information (Holds the information about the schedule of each class).
 */

void printSchedule(const vector<pair<string, string>>& isInUcCl, vector<Uc> *ucs){
    for (const auto& ucUl : isInUcCl){ //for loop trough classes that the student is enrroled and print them
        for (auto uc : *ucs){
            if (ucUl.first == uc.getCode()){
                for ( const auto& cl : uc.getClassses()){
                    if (ucUl.second == cl.getCode()){
                        uc.printClassSchedule(cl);
                        break;
                    }
                }
                break;
            }
        }
    }
}

/**
 * @brief The function will check for overlapped Classes.
 *
 * The function will check all of the student's class and check is is there a overlap between them. Notice, however that this overlaps are viable, meaning that are only overlapped with Theorical Lectures.
 *
 * @param student The student that we want to analyse it's schedule.
 * @param ucs A vector with all ucs and respective information (Holds the information about the schedule of each class).
 * @return Returns a vector with the pairs of overlapped classes (Pair<Aula, pair<UcCode, ClassCode>>).
 */

vector<pair<Aula, pair<string, string>>> overlappedClasses(const Student& student, vector<Uc> &ucs) {
    list<pair<Aula, pair<string, string>>> studentsClasses; //list to hold studentClasses, efficient to push_back
    vector<pair<Aula, pair<string, string>>> overlapped;
    for (const Uc& uc : ucs){ //for loop to add all classes of a certain student to a vector sutdentsClasses
        for (const Classs& classs : uc.getClassses()){
            for ( const auto& p : student.getIsIn()){
                if (uc.getCode() == p.first && classs.getCode() == p.second){
                    for (const Aula& aula : classs.getSchedule()){
                        pair<Aula, pair<string, string>> tmp = make_pair(aula, make_pair(uc.getCode(),classs.getCode()));
                        studentsClasses.push_back(tmp);
                    }
                }
            }
        }
    }
    for (const auto& p: studentsClasses){ //for loop through the created vector to see if there is over lapped classes
        for (const auto& p1: studentsClasses){
            if (p.second != p1.second){
                if(p.first.weekDay == p1.first.weekDay && ((p.first.start <= p1.first.start && p.first.end > p1.first.start) || (p.first.start >= p1.first.start && p1.first.end > p.first.start)))
                {
                    bool first = false;
                    bool second = false;
                    //verificar se tanto o pair p como o pair 1 ainda não estão no vetor overlapped
                    for (const auto& patual : overlapped){
                        if (patual == p) first = true;
                        if (patual == p1) second = true;
                    }
                    if (!first) overlapped.push_back(p);
                    if (!second) overlapped.push_back(p1);
                }
            }
        }
    }
    return overlapped;
}

/**
 * @brief The function will read the csv that contains the recent opperations that wew made trough a request and store them in a stack that will be returned.
 *
 * Time Complexity : O(n) being n the number of lines in the csv
 *
 * @return Returns a stack with all those Requests.
 */
//Funtion to read csv of opps and create a stack
stack<Opperation> loadRequests(){

    //Stack to store requests
    stack<Opperation> requests;
    ifstream file("../schedule/operations.csv"); // Open the CSV file
    string line;

    bool first = true;
    while (getline(file, line)) {
        if (line != "\r") {
            istringstream ss(line);
            string type, meca, ucCode, originClass, finalClass;
            int numero;
            bool existeAluno = false;

            if (!first) {
                getline(ss, type, ','); // "add" or "remove" or "switch"
                getline(ss, meca, ',');  //mecanographic number
                getline(ss, ucCode, ','); //UC code
                if (type == "add"){
                    getline(ss, finalClass, ',');
                    originClass = "";
                }
                else if (type == "remove"){
                    getline(ss, originClass, ',');
                    finalClass = "";
                }
                else if (type == "switch"){
                    getline(ss, originClass, ',');
                    getline(ss, finalClass, ',');
                }
                Opperation op = {type, meca, ucCode, originClass, finalClass}; //create an object of type opperation with the values read from scv
                requests.push(op); //and add it to this vector
            }
            first = false;
        }
    }

    return requests;

}

/**
 * @brief If the undo request is successful we must erase the line in the csv that holds the undid request.
 *
 * The function will read the csv and make the needed changes according to the needs.
 *
 */

void undoSuccessful() {
    ifstream inputFile("../schedule/operations.csv");
    vector<string> lines;
    string line;

    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    lines.pop_back();
    lines.pop_back();

    inputFile.close();

    std::ofstream outputFile("../schedule/operations.csv");

    for (const auto& l : lines) {
        outputFile << l << std::endl;
    }

    outputFile.close();

}


#endif //PROJ2023_AUXILIARFUNCTIONS_H
