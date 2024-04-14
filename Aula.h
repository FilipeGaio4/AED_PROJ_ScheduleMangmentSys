//
// Created by filipegaio on 04-11-2023.
//

/**
 * @file
 * @brief This file holds a struct Aula
 *
 *
 */


#ifndef PROJ2023_AULA_H
#define PROJ2023_AULA_H

#include <string>

using namespace std;
/**
 * @brief This struct facilitates the carriage of information of a certain Lecture of a certain Class
 *
 * This struct has 4 attributes, weekDay, the hour of begging, the ending hour and it's type (T if the Class is theorical, TP if it is practical-theoric and PL if it is Practical Laboratory
 */
struct Aula {
    string weekDay;
    double start;
    double end;
    string type;

/**
 * @brief OverLoad to de == Opp.
 *
 * OverLoad will help the code to be cleaner and easier to check if the Lectures are the equal eg (this==other).
 *
 * @param this The first element we want to compare.
 * @param other The second element that we want to compare.
 * @return The return will be true if they have all attributes the same and false otherwise.
 */

    bool operator==(const Aula& other) const {
        return weekDay == other.weekDay && start == other.start && end == other.end && type == other.type;
    }
};

#endif //PROJ2023_AULA_H
