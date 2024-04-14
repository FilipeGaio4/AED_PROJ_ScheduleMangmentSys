//
// Created by filipegaio on 04-11-2023.
//

/**
 * @file
 * @brief This file defines a struct called Opperation.
 *
 */

#ifndef PROJ2023_OPPERATION_H
#define PROJ2023_OPPERATION_H

#include <string>

using namespace std;

/**
 * @brief This struct facilitates the carriage of information of a certain Opperation after it is accepted.
 *
 * This struct has 5 attributes, type of the opp (type), the mecanographic number of the student (meca),
 * the UC Code (UcCode), the class where the student originally is (clasOrigin) and the class where stdent will end up(classFinal).
 */

struct Opperation {
    string type; /**< @brief Type can be "add", "remove" or "switch". */
    string meca; /**< @brief Student's unique identification number. */
    string ucCode; /**< @brief UC's unique identification number. */
    string classOrigin; /**< @brief Student's class of origin (It might be "" if it is an add opperation). */
    string classFinal; /**< @brief Student's final's class (It might be "" if it is an add remove opperation). */

};

#endif //PROJ2023_OPPERATION_H
