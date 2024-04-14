//
// Created by filipegaio on 28-10-2023.
//

/**
 * @file
 * @brief This file is the header of the Uc class, containing its attributes and declarations of its functions.
 *
 */

#ifndef UC_H
#define UC_H

#include <string>
#include <vector>
#include "Classs.h"

using namespace std;

/**
 * @class Uc
 * @brief The Uc class represents a course (Unidade Curricular).
 *
 * The Uc class includes attributes for UC code and a vector to keep track of the classes
 * associated with the UC. It also provides methods to manage classes and student enrollments.
 */
class Uc {
private:
    string codeUc_; /**< @brief Unique code for identifying the UC. */
    vector<Classs> classes_; /**< @brief Vector of Classs objects representing the classes associated with the UC. */

public:
    /**
     * @brief Default constructor for the Uc class.
     */
    Uc();

    /**
     * @brief Parameterized constructor for the Uc class.
     * @param code Unique code for identifying the UC.
     */
    Uc(string code);

    // Uc Setter and Getter
    /**
     * @brief Sets the unique code for the UC.
     * @param code Unique code for identifying the UC.
     */
    void setCode(string code);

    /**
     * @brief Gets the unique code of the UC.
     * @return The unique code of the UC.
     */
    string getCode() const;

    /**
     * @brief Gets the vector of Classs objects associated with the UC.
     * @return Vector of Classs objects representing the classes associated with the UC.
     */
    vector<Classs> getClassses() const;

    // Uc functions to manage classes and students
    /**
     * @brief Sets the vector of Classs objects associated with the UC.
     * @param classes Vector of Classs objects representing the classes associated with the UC.
     */
    void setClassses(vector<Classs> classes);

    /**
     * @brief Adds a class to the UC.
     * @param aClasss Classs object representing the class to be added.
     */
    void addClasss(const Classs& aClasss);

    /**
     * @brief Updates a specific class inside a UC.
     * @param aClasss Classs object representing the updated class.
     */
    void updateClasss(const Classs& aClasss);

    /**
     * @brief Calculates the difference between the maximum class attendance and the lest class attendance in this UC.
     * @return Difference between the maximum class attendance and the minimum class attendance.
     */
    int diffMaxClasssAttendance();

    /**
     * @brief Switches a student to a different class within the UC.
     * @param you Student object representing the student requesting the switch.
     * @param ucs Vector of Uc objects representing all UCs.
     * @param students Vector of Student objects representing all students.
     * @param classsAtual Current Classs object of the student.
     * @param requiredClasss Required class code for the switch.
     * @return True if the switch is successful, false otherwise.
     */
    bool switchClass(Student& you, vector<Uc>& ucs, vector<Student>& students, Classs& classsAtual, string requiredClasss);

    /**
     * @brief Prints the schedule of a specific class to the terminal.
     * @param aClasss Classs object representing the class whose schedule needs to be printed.
     */
    void printClassSchedule(Classs aClasss);

    /**
     * @brief Checks for schedule conflicts within the UC.
     *
     * Time Complexity : O(uc * cl * p * a²) being uc the number of ucs, cl the number os classes p the number of classes that the student is in and a the lectures of that class
     *
     * @param switchRequest True if the request is for switching classes, false otherwise.
     * @param requiredClasss Classs object representing the required class.
     * @param student Student object for whom the check is performed.
     * @param ucs Vector of Uc objects representing all UCs.
     * @return True if there are schedule conflicts, false otherwise.
     */
    bool scheduleConflicts(bool switchRequest, const Classs& requiredClasss, Student student, vector<Uc>& ucs);

    /**
     * @brief Adds a student to the UC the most appropriate class.
     * @param student Student object representing the student to be added.
     * @param ucs Vector of Uc objects representing all UCs.
     * @return True if the student is successfully added, false otherwise.
     */
    bool addUc(Student& student, vector<Uc>& ucs);

    /**
     * @brief Removes a student from the UC.
     * @param student Student object representing the student to be removed.
     * @param ucs Vector of Uc objects representing all UCs.
     * @param atualClass Current Classs object of the student.
     * @return True if the student is successfully removed, false otherwise.
     */
    bool removeUc(Student& student, vector<Uc>& ucs, Classs atualClass);

    /**
     * @brief Modifies student csv information based on the provided parameters.
     *
     * Time Complexity : O(n) being n the number of lines in the csv
     *
     * @param type Type of modification (add, switch, remove).
     * @param num Student number.
     * @param nameStudent Student name.
     * @param requiredClass Required class code.
     * @param requiredUc Required UC code.
     */
    void modifyingStudents(string type, int num, string nameStudent, string requiredClass, string requiredUc);

    /**
     * @brief Removes a specific line from a file from the csv.
     * @param lineToDelete Line number to be removed.
     */
    void removeLine(size_t lineToDelete);

    /**
     * @brief Writes an addition operation to the csv Opperations file.
     * @param num Student number.
     * @param requiredUc Required UC code.
     * @param requiredClass Required class code.
     */
    void writeAdd(int num, string requiredUc, string requiredClass);

    /**
     * @brief Writes a switch operation to the csv Opperations file.
     * @param num Student number.
     * @param uc UC code.
     * @param requiredClass Required class code.
     * @param currentClass Current class code.
     */
    void writeSwitch(int num, string uc, string requiredClass, string currentClass);

    /**
     * @brief Writes a removal operation to the csv Opperations file.
     * @param num Student number.
     * @param requiredUc Required UC code.
     * @param requiredClass Required class code.
     */
    void writeRemove(int num, string requiredUc, string requiredClass);
};

#endif // UC_H

