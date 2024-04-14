/**
 * @file
 * @brief This file contains the main function that initializes and runs the program.
 *
 * This file includes necessary header files and initializes the data structures.
 * It also contains the main function where the program execution begins.
 */

#include <vector> // Include vector header for using std::vector
#include "Student.h" // Include Student class header file
#include "Uc.h" // Include Uc class header file
#include "ClassesPerUcLoad.h" // Include header for loading classes per Uc from CSV
#include "PovoateClassesLoad.h" // Include header for populating Uc classes and students from CSV
#include "ClassesScheduleLoad.h" // Include header for loading classes schedule from CSV
#include "Menu.h" // Include header for the program menu

using namespace std;

/**
 * @brief The main function of the program.
 *
 * The program starts execution here. It initializes necessary data structures,
 * loads data from CSV files, and runs the program menu.
 *
 * @return 0 upon successful execution.
 */

int main() {
    vector<Uc> ucs = loadClassesPerUc(); // Vector to store CSV data (Ucs) Classes of Ucs
    vector<Student> students = PovoateClassesLoad(&ucs); //Vector to store all students and their info
    loadClassesSchedule(&ucs, &students); // Load classes schedule from CSV

    // Display the program menu
    menu(&ucs, &students);

    return 0; // Indicate successful execution
}
