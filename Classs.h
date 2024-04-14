//
// Created by filipegaio on 28-10-2023.
//

/**
 * @file
 * @brief This file is the header of the Class Classs that contain it's atrributes and declaration of it's functions.
 *
 *
 */

#ifndef CLASSS_H
#define CLASSS_H

#include <string>
#include <vector>
#include <iostream>
#include "Student.h"
#include "Aula.h"

using namespace std;

/**
 * @class Classs
 * @brief The Class Classs contains it's atrributes and declaration of it's functions (It's called Classs with triple 's' due to conflicts between the keyword class.
 *
 *
 */


class Classs {
private:
    string codeCl_; /**< @brief Unique code for identifying the class. */
    vector<Student> students_; /**< @brief Vector containing the enrolled students in the class. */
    vector<Aula> aulas_; /**< @brief Vector containing lecture schedules for the class. */
    static const int Cap = 40; /**< @brief Arbitrary maximum capacity of the class (can be changed if needed). */

public:
    /**
     * @brief Default constructor for the Classs class.
     */
    Classs();

    /**
     * @brief Parameterized constructor for the Classs class.
     * @param code Unique code for identifying the class.
     */
    Classs(string code);

    // Classs Setter and Getter
    /**
     * @brief Sets the unique code for the class.
     * @param code Unique code for identifying the class.
     */
    void setCode(string code);

    /**
     * @brief Gets the unique code of the class.
     * @return The unique code of the class.
     */
    string getCode() const;

    /**
     * @brief Gets the vector of enrolled students in the class.
     * @return Vector containing the enrolled students in the class.
     */
    vector<Student> getStudents() const;

    /**
     * @brief Gets the vector of Lectures in the class.
     * @return Vector containing the Lectures in the class.
     */
    vector<Aula> getSchedule() const;

    /**
     * @brief Adds a student to the class.
     * @param students Vector of students to be enrolled in the class.
     */
    void setStudents(vector<Student> students);

    /**
     * @brief Adds a student to a certain class of a course.
     * @param student Student object representing the student to be added.
     * @param ucCode Unique code for identifying the course.
     */
    void addStudentToUc(Student &student, string ucCode);

    /**
     * @brief Removes a student from the class.
     * @param student Student object representing the student to be removed.
     * @param ucCode Unique code for identifying the course.
     */
    void removeStudent(Student &student, string ucCode);

    // Class functions to manage lectures
    /**
     * @brief Adds a lecture event to the class schedule.
     * @param aula Aula object representing the lecture event to be added.
     */
    void addAula(Aula aula);

    /**
     * @brief Prints the schedule for the class.
     */
    void printAula();

    /**
     * @brief Checks if a student can enter the class based on its capacity.
     * @return True if the student can enter, false otherwise.
     */
    bool canEnter();

    /**
     * @brief Checks for schedule conflicts with another class.
     * @param requiredClasss Classs object representing the required class to check for conflicts.
     * @return True if there are schedule conflicts, false otherwise.
     */
    bool scheduleConflicts(Classs requiredClasss);
};





#endif //PROJ2023_CLASSS_H
