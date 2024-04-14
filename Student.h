//
// Created by filipegaio on 27-10-2023.
//

/**
 * @file
 * @brief This file is the header of the Student class, containing its attributes and declarations of its functions.
 *
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @class Student
 * @brief The Student class represents a student.
 *
 * The Student class includes attributes for student number, name, and a vector
 * to keep track of the courses (UC) and classes the student is enrolled in.
 */
class Student {
private:
    int number_; /**< @brief Student's unique identification number. */
    string name_; /**< @brief Student's name. */
    vector<pair<string, string>> isIn_UcCl; /**< @brief Vector of pairs containing UC and class codes where the student is enrolled. */

public:
    /**
     * @brief OverLoad of < opperator to be able to sort the students by numbers in a set.
     */
    bool operator<(const Student& other) const {
        return number_ < other.number_;
    }

    /**
     * @brief Default constructor for the Student class.
     */
    Student();

    /**
     * @brief Parameterized constructor for the Student class.
     * @param number Student's unique identification number.
     * @param name Student's name.
     */
    Student(int number, string name);

    // Student Setters
    /**
     * @brief Sets the student's unique identification number.
     * @param number Student's unique identification number.
     */
    void setNumber(int number);

    /**
     * @brief Sets the student's name.
     * @param name Student's name.
     */
    void setName(string name);

    // Student Getters
    /**
     * @brief Gets the student's unique identification number.
     * @return Student's unique identification number.
     */
    int getNumber() const;

    /**
     * @brief Gets the student's name.
     * @return Student's name.
     */
    string getName() const;

    /**
     * @brief Gets the vector of pairs containing UC and class codes where the student is enrolled.
     * @return Vector of pairs containing UC and class codes.
     */
    vector<pair<string, string>> getIsIn() const;

    // Student Functions
    /**
     * @brief Enrolls the student in a specific UC and class.
     * @param Uc UC code where the student is enrolled.
     * @param cl Class code where the student is enrolled.
     */
    void enroll(const string& Uc, const string& cl);

    /**
     * @brief Clears the list of UCs and classes where the student is enrolled.
     */
    void clearIsIn();

    /**
     * @brief Prints the student's name and number to the terminal.
     */
    void printStudent() const;

    /**
     * @brief Prints the list of UCs and classes where the student is enrolled to the terminal.
     */
    void printStudentIsIn() const;

    /**
     * @brief Prints the student's schedule to the terminal.
     */
    void printSchedule() const;

    /**
     * @brief Removes the student from a specific UC and class.
     * @param ucCode UC code from which the student needs to be removed.
     */
    void remove(string ucCode);
};

#endif // STUDENT_H
