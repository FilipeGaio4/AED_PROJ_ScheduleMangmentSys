//
// Created by filip on 30/10/2023.
//

/**
 * @file
 * @brief Header file containing menu-related functions for managing students, classes, and UCs.
 *
 * This file defines functions to display menu options, process user input, and manage various operations related to students, classes, and UCs.
 */

#ifndef PROJ2023_MENU_H
#define PROJ2023_MENU_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <set>
#include <queue>
#include "Student.h"
#include "Classs.h"
#include "Uc.h"
#include "AuxiliarFunctions.h"

using namespace std;

/**
 * @brief Displays a sorted list of all students based on user's choice of ordering.
 *
 * This function allows the user to choose the sorting criteria for students (by number or name)
 * and displays the sorted list along with additional information if requested.
 * Time Complexity : O(log n) being n the number of lines in the csv
 * it mught be aventually O(k log n) being n the number of lines in the csv and k the number os classes the student is in to check it's year
 *
 * @param ucs Pointer to the vector of Uc objects.
 * @param students Pointer to the vector of Student objects.
 */

void verTodosEstudantes(vector<Uc> *ucs, vector<Student> *students) {
    //prints all students

    string orderChoice;
    string yearChoice;
    string contentChoice;

    cout << "Escolha a ordenação dos estudantes:\n";
    cout << "1 - Ordenar por número\n";
    cout << "2 - Ordenar por nome\n";
    cout << "Digite sua escolha: ";
    cin >> orderChoice;

    //User can choose the ordering system of the print
    set<Student> sortedStudents;
    sortedStudents.clear();
     //access user's choice
    if (orderChoice == "1") {
        // Sort students by number and insert into the set
        sortedStudents.insert(students->begin(), students->end());
    } else if (orderChoice == "2") {
        // Sort students by name and insert into the set
        sort(students->begin(), students->end(), [](const Student& a, const Student& b) {
            return a.getName() < b.getName();
        });
    } else {
        cout << "Escolha inválida.";
        return;
    }

    //content choice means if we want just students or students and theis classes
    //order choice means if user want to sort them by number or name
    //year choice means that the user wants to see the students of that specific year
    //more printing options
    do {
        cout << "\n\nEscolha o conteúdo que quer ver:\n";
        cout << "1 - Ver apenas os estudantes\n";
        cout << "2 - Ver os estudantes e as cadeiras que frequenta\n";
        cout << "0 - Voltar para o menu inicial\n";
        cout << "Digite sua escolha: ";
        cin >> contentChoice;
        //Allows user to filter by year
        if (contentChoice == "1" && orderChoice == "1") {
            cout << "\nEscolha o ano que quer ver:\n";
            cout << "1 - Primeiro ano\n";
            cout << "2 - Segundo ano\n";
            cout << "3 - Terceiro ano\n";
            cout << "0 - Todos os anos\n";
            cout << "Digite sua escolha: ";
            cin >> yearChoice;

            if (!(yearChoice == "0" || yearChoice == "1" || yearChoice == "2" || yearChoice == "3" )){
                cout << "Escolha inválida.";
                return;
            }
            for (const Student& s : sortedStudents) {
                if (yearChoice == "0"){
                    s.printStudent();
                }
                else {
                    for(auto ucCl : s.getIsIn()){
                        string str = "";
                        str += (ucCl.second[0]);
                        if (str == yearChoice){
                            s.printStudent();
                            break;
                        }
                    }
                }
            }
        } else if (contentChoice == "2" && orderChoice == "1") {

            for (const Student& s : sortedStudents) {
                s.printStudent();
                s.printStudentIsIn();
                cout << "\n";
            }
        }else if (contentChoice == "1" && orderChoice == "2") {
            cout << "\nEscolha o ano que quer ver:\n";
            cout << "1 - Primeiro ano\n";
            cout << "2 - Segundo ano\n";
            cout << "3 - Terceiro ano\n";
            cout << "0 - Todos os anos\n";
            cout << "Digite sua escolha: ";
            cin >> yearChoice; //impleemtnara

            if (!(yearChoice == "0" || yearChoice == "1" || yearChoice == "2" || yearChoice == "3" )){
                cout << "Escolha inválida.";
                return;
            }

            for (const Student& s : *students) {
                if (yearChoice == "0"){
                    s.printStudent();
                }
                else {
                    for(auto ucCl : s.getIsIn()){
                        string str = "";
                        str += (ucCl.second[0]);
                        if (str == yearChoice){
                            s.printStudent();
                            break;
                        }
                    }
                }
            }
        }else if (contentChoice == "2" && orderChoice == "2") {
            for (const Student& s : *students) {
                s.printStudent();
                s.printStudentIsIn();
                cout << "\n";
            }
        } else if (contentChoice == "0") {
            cout << "A voltar para o menu inicial. Obrigado!\n";
            return;
        } else {
            cout << "Escolha inválida. Por favor, tente novamente.\n";
        }

    } while (contentChoice != "0");
}

/**
 * @brief Displays all UCs, their classes, and the students enrolled in each class.
 *
 * This function prints information about all UCs, their classes, and the students enrolled in each class.
 * Time Complexity : O(uc * cl * s) being uc the number of ucs, cl the number os classes and s the number of students
 *
 * @param ucs Pointer to the vector of Uc objects.
 * @param students Pointer to the vector of Student objects.
 */

void verUcClassStudent(vector<Uc> *ucs, vector<Student> *students){
    //print all classes and students enrroled
    for (const Uc& uc: *ucs) {
        cout << "____________________________" << endl << "UC: " << uc.getCode() << endl;
        for (const Classs& c: uc.getClassses()) {
            cout << "____________________________" << endl << "\tClass: " << c.getCode() << endl ;
            for (const Student& s: c.getStudents()){
                cout << "\t\t\tNome: " << s.getName() << ", Número: " << s.getNumber() << endl;
            }
        }
    }
}

/**
 * @brief Displays all classes of a specific UC based on user input.
 *
 * This function prompts the user to input a UC code and displays all classes within that UC.
 * Time Complexity : O(uc * cl * sa) being uc the number of ucs, cl the number os classes and a the number of lectures in a class
 *
 * @param ucs Pointer to the vector of Uc objects.
 * @param students Pointer to the vector of Student objects.
 */

void verTodasClasses(vector<Uc> *ucs, vector<Student> *students) {
    //prints every class schdule of a certain UC
    string choice;
    bool existe = false;
    do {
        cout << "\n\n\nDigite o código da UC:\nExemplo: L.EIC001 \nOu digite '0' para regressar ao menu: \n";
        cin >> choice;
        for (const Uc& uc : *ucs){ //find the required UC
            if (choice == uc.getCode()) {
                existe = true;
                cout << "UC : " << uc.getCode() << endl;
                for (Classs classs: uc.getClassses()) { //iterate over every class of the UC
                    cout << "______________________" << endl;
                    classs.printAula(); //print its schedule
                }
            }
        }
        if (choice == "0" || existe){
            existe = true;
        }
        else{
            cout << "Escolha inválida. Por favor, tente novamente." << endl;
        }
    } while (!existe);
}

/**
 * @brief Displays detailed information about a specific student based on their student number.
 *
 * This function prompts the user to input a student number and displays information about that specific student,
 * including their schedule and enrolled classes.
 * Time Complexity : O(log s) being s the number of students then depending on the choice of the user in might iterate over a vector O(n) being n the number os classes that the student is in
 *
 * @param ucs Pointer to the vector of Uc objects.
 * @param students Pointer to the vector of Student objects.
 */

void infoSobreEstudante(vector<Uc> *ucs, vector<Student> *students) {
    // Código para exibir informações sobre um estudante específico
    bool existe = false;
    int meca;
    cout << "\nDigite o número mecanográfico do estudante:"; // ou 0 para voltar atras
    if (cin >> meca){
        set<Student> sortedStudents; //set of students to make search O(log n)
        sortedStudents.clear();
        sortedStudents.insert(students->begin(), students->end());
        auto it = find_if(sortedStudents.begin(), sortedStudents.end(), [meca](const Student& student) {
            return student.getNumber() == meca;
        });
        if (it != sortedStudents.end()) { //if student was found
            const Student& s = *it;
            existe = true;
            string choice;
            //present more choices to user
            do {
                cout << endl;
                s.printStudent();
                cout << "\nOpções:" << endl;
                cout << "1 - Ver horário do estudante" << endl;
                cout << "2 - Ver cadeiras que frequenta" << endl;
                cout << "0 - Voltar ao menu principal" << endl;
                cout << "Escolha uma opção: ";

                if (cin >> choice) {
                    if (choice == "1") {
                        //Print student's schedule
                        printSchedule(s.getIsIn(), ucs);
                        int cont = 0;
                        for (auto p : overlappedClasses(s, *ucs)){ //check for overlapped classes
                            if (cont == 0)cout << "\nAulas sobrepostas:\n";
                            cont ++;
                            cout << "\tUC : " << p.second.first << "  ||  Turma: " << p.second.second << endl;
                            cout << "\tDia da semana: " << p.first.weekDay << " , Início: " << p.first.start << ",Fim: " << p.first.end << ",Tipo: " << p.first.type << endl << endl;
                        }
                    } else if (choice == "2") {
                        //print UC and Classes that is enrolled in
                        s.printStudentIsIn();
                    } else if (choice == "0") {
                        cout << "A voltar ao menu inicial. Obrigado!\n" << endl;
                    } else {
                        cout << "Escolha inválida. Por favor, tente novamente." << endl;
                    }
                } else {
                    cout << "Escolha inválida. Por favor, digite um número." << endl;
                    cin.clear();
                }

            } while (choice != "0");
        }
        if (!existe) cout << "Não existe nenhum aluno com esse número mecanográfico.\n";
    }
    else{
        cout << "\nDigite um número mecanográfico válido." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        infoSobreEstudante(ucs, students);
    }
}

/**
 * @brief Processes a student's request (add, remove, switch) for a specific UC and class.
 *
 * This function allows the user to add, remove, or switch classes within a specific UC and to add and remove a specific UC.
 * Time Complexity : O(uc * cl * s) being uc the number of ucs, cl the number os classes and s the number of students in the worst case that is switch
 *
 * @param ucs Pointer to the vector of Uc objects.
 * @param students Pointer to the vector of Student objects.
 */

void processarRequisicao(vector<Uc> *ucs, vector<Student> *students) {
    // Código para processar uma requisição
    bool existe = false; //boolean to check if the student we're looking for exists
    bool sucess = false; //boolean to access the success of the request
    bool sucessButNotPossible = false; //boolean that accesses if the request was made but denied by the system (p.e. class was full)
    bool contin = false; //boolean to avoid printing extra warnings when the inputs are not valid
    int meca;
    cout << "\nDigite o número mecanográfico do estudante ou digite 0 para regressar ao menu principal: ";
    if (cin >> meca){
        if (meca == 0);
        else{
            for (Student& s : *students){ //find the desired student
                if (s.getNumber() == meca){
                    existe = true;
                    string choice;
                    cout << endl;
                    s.printStudent();
                    cout << endl;
                    string requestType, targetUc, atualClass, finalClass;

                    // Collect information from the user
                    cout << "Introduzir o tipo de requisição (add, remove, switch): ";
                    cin >> requestType;
                    if (requestType == "add"){
                        cout << "Introduz a UC em que te queres inscrever: ";
                        cin >> targetUc;
                        for (Uc& uc : *ucs){ //find the desired UC
                            if (uc.getCode() == targetUc){
                                bool alreadyInUc = false;
                                for (const auto& p : s.getIsIn()){ //Check if student isn't already there, bc student can't be in two or more classes in the UC
                                    if (targetUc == p.first) alreadyInUc = true;
                                }
                                if (!alreadyInUc){
                                    if (uc.addUc(s, *ucs)){ //process the add request
                                        sucess = true;
                                    }
                                    else sucessButNotPossible = true;
                                }
                                else {
                                    cout << "O estudante já está nessa UC, selecione outra opção:\n";
                                    processarRequisicao(ucs, students);
                                    contin = true;
                                }

                            }
                        }
                    }
                    else if (requestType == "remove"){
                        cout << "Introduz a UC que queres anular: ";
                        cin >> targetUc;
                        for (Uc& uc : *ucs){ //find the desired UC
                            if (uc.getCode() == targetUc){
                                bool InUc = false;
                                string clCode;
                                Classs atualClasss;
                                for (const auto& p : s.getIsIn()){ //Check if student is in the UC we want to remove it from
                                    if (targetUc == p.first) {
                                        clCode = p.second;
                                        InUc = true;
                                    }
                                }
                                if (InUc){
                                    for (const Classs& classs : uc.getClassses()){
                                        if (classs.getCode() == clCode) atualClasss = classs;

                                    }
                                    if (uc.removeUc(s, *ucs, atualClasss)){ //Process the remove request
                                        sucess = true;
                                    }
                                    else sucessButNotPossible = true;
                                }
                                else {
                                    cout << "O estudante não está nessa UC, selecione outra opção:\n";
                                    processarRequisicao(ucs, students);
                                    contin = true;
                                }

                            }
                        }
                    }
                    else if (requestType == "switch"){
                        cout << "Introduz a UC a que queres mudar de turma: ";
                        cin >> targetUc;
                        for ( Uc& uc : *ucs ){ //find the desired UC
                            if (uc.getCode() == targetUc){
                                cout << "Introduz a tua turma atual: ";
                                cin >> atualClass;
                                for (Classs &clatual : uc.getClassses()){ //Find the actual class and check if the student is there
                                    if (clatual.getCode() == atualClass){
                                        for (auto p : s.getIsIn()){
                                            if ( targetUc == p.first && atualClass == p.second){ // Checks if student is in targerUc in class atualClass
                                                cout << "Introduz a tua turma para que quer ir: ";
                                                cin >> finalClass;
                                                for (Classs clfinal : uc.getClassses()){ //finds the class that the students wants to go
                                                    if (clfinal.getCode() == finalClass){ //checks if he isn't already there
                                                        if (finalClass == atualClass) cout << "O estudante já está nessa turma." << endl;
                                                        else{
                                                            if (uc.switchClass(s, *ucs, *students, clatual, finalClass)){ //Process the request
                                                                sucess = true;
                                                            }
                                                            else sucessButNotPossible = true;
                                                        }
                                                    }
                                                }
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                    else { //O user não escolher "add" ou "remove" ou "switch"
                        cout << "\nSeleciona um tipo válido.\n";
                        sucess = true;
                        processarRequisicao(ucs, students);
                        contin = true;
                    }
                }
            }
            if (contin){} //avoid printing extra errors
            else if (!existe) { //Checks if student was found
                cout << "\nNão existe nenhum aluno com esse número mecanográfico.\n";
                processarRequisicao(ucs, students);
                contin = true;
            }
            else if (sucessButNotPossible){ //checks if the request was made but not accepted
                cout << "\nNão foi possível processar a requisição.\nOu a turma está cheia, ou a transferência causa discrepância na distribuição dos alunos, ou o os horários não são compatíveis, ou o aluno não é elegível para entrar na turma.\n";
            }
            else if (!sucess) { //Checks if the request wasn't made
                cout << "\nAlgo correu mal, verifique se existe a UC ou a turma/s que introduziu.\n";
                processarRequisicao(ucs, students);
                contin = true;
            }
            else if (sucess){ //checks full sucess of the request
                cout << "\nA sua requisição foi efetuada com sucesso!\n";
            }
        }
    }
    else{
        cout << "\nDigite um número mecanográfico válido." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        processarRequisicao(ucs, students);
        contin = true;
    }
}

/**
 * @brief Undoes the last successful request made by a student.
 *
 * This function allows the user to undo the last successful add, remove, or switch request made by the user.
 * Time Complexity : O(uc * cl * s) being uc the number of ucs, cl the number os classes and s the number of students
 *
 * @param ucs Pointer to the vector of Uc objects.
 * @param students Pointer to the vector of Student objects.
 */

void undoRequisicao(vector<Uc> *ucs, vector<Student> *students){
    //Undo the last request
    stack<Opperation> requests = loadRequests();
    queue<Opperation> queueRequests;
    Opperation Request = requests.top();
    queueRequests.push(Request);
    bool success = false;
    cout << "\nA última requisição executada foi: " << endl;
    string undoChoice;
    Opperation lastRequest = queueRequests.front();
    if (lastRequest.type == "add"){
        cout << "Adicionar o Estudante número: " << lastRequest.meca << " à turma " << lastRequest.classFinal <<
            " da UC " << lastRequest.ucCode << endl;
        cout << "Pretende fazer undo? (s/n)" << endl;
        cin >> undoChoice;
        if (undoChoice == "s"){
            for (Student& student : *students){ //find the desired student
                if (student.getNumber() == stoi(lastRequest.meca)){
                    for (Uc& uc : *ucs){ //find the desired UC
                        if (uc.getCode() == lastRequest.ucCode){
                            for (Classs classs : uc.getClassses()){ //find the desired class
                                if (classs.getCode() == lastRequest.classFinal){
                                    if (uc.removeUc(student, *ucs, classs)){ //try to undo request
                                        success = true;
                                    }
                                }
                            }
                        }
                    }

                }
            }
        }
        else{
            cout << "A voltar para o menu principal" << endl;
        }

    }
    else if (lastRequest.type == "remove"){
        cout << "Remover o Estudante número: " << lastRequest.meca << " da turma " << lastRequest.classOrigin <<
            " da UC " << lastRequest.ucCode << endl;
        cout << "Pretende fazer undo? (s/n)" << endl;
        cin >> undoChoice;
        if (undoChoice == "s"){
            for (Student& student : *students){ //find desired student
                if (student.getNumber() == stoi(lastRequest.meca)){
                    for (Uc& uc : *ucs){ //find desired UC
                        if (uc.getCode() == lastRequest.ucCode){
                            for (Classs classs : uc.getClassses()){ //find desired Class
                                if (classs.getCode() == lastRequest.classOrigin){
                                    if (uc.addUc(student, *ucs)){ //try to undo request
                                        success = true;
                                    }
                                }
                            }
                        }
                    }

                }
            }
        }
        else{
            cout << "A voltar para o menu principal" << endl;
        }

    }
    else if (lastRequest.type == "switch"){
        cout << "O Estudante número: " << lastRequest.meca << " trocou da turma " << lastRequest.classOrigin <<
            " para a turma " << lastRequest.classFinal << " da UC " << lastRequest.ucCode << endl;
        cout << "Pretende fazer undo? (s/n)" << endl;
        cin >> undoChoice;
        if (undoChoice == "s"){
            for (Student& student : *students){ //find desired student
                if (student.getNumber() == stoi(lastRequest.meca)){
                    for (Uc& uc : *ucs){ //find desired UC
                        if (uc.getCode() == lastRequest.ucCode){
                            for (Classs &classs : uc.getClassses()){ //find desired Class
                                if (classs.getCode() == lastRequest.classFinal){
                                    if (uc.switchClass(student, *ucs, *students, classs, lastRequest.classOrigin)){ //try to undo request
                                        success = true;
                                        break;
                                    }

                                }
                            }
                            break;
                        }
                    }
                    break;

                }
            }
        }
        else{
            cout << "A voltar para o menu principal" << endl;
        }

    }
    if (success) { //access the success of the undo
        cout << "Undo efetuado com sucesso!\n";
        queueRequests.pop();
        undoSuccessful(); //removes the opperation from the csv that holds the opperations
    }
    else {
        cout << "Não foi possível realizar o undo.\nOu a turma está cheia, ou a transferência causa discrepância na distribuição dos alunos, ou o os horários não são compatíveis, ou o aluno não é elegível para entrar na turma.\n";
        queueRequests.pop();
    }
}

/**
 * @brief Displays a list of all successful requests made by students.
 *
 * This function displays a list of all successful add, remove, and switch requests made by students using a stack.
 * Time Complexity : O(n) being n the number of requests in the stack
 *
 * @param ucs Pointer to the vector of Uc objects.
 * @param students Pointer to the vector of Student objects.
 */

void verRequisicao(vector<Uc> *ucs, vector<Student> *students){
    //print the resquests that were successul string from the last one and until the oldest one
    stack<Opperation> requests = loadRequests();
    if (requests.empty()) { //checks if there is any request that was made
        cout << "Não há requisições efetuadas com êxito." << endl;
    } else {
        while (!requests.empty()) { //prints the requests
            if (requests.top().type == "add"){
                cout << "\nAdicionar o Estudante número: " << requests.top().meca << " à turma " << requests.top().classFinal <<
                     " da UC " << requests.top().ucCode << endl;

            }
            else if (requests.top().type == "remove"){
                cout << "\nRemover o Estudante número: " << requests.top().meca << " da turma " << requests.top().classOrigin <<
                     " da UC " << requests.top().ucCode << endl;
            }
            else{
                cout << "\nO Estudante número: " << requests.top().meca << " trocou da turma " << requests.top().classOrigin <<
                     " para a turma " << requests.top().classFinal << " da UC " << requests.top().ucCode << endl;
            }
            requests.pop(); //pops the top of the stack element so we can access the next one
        }
    }
}

/**
 * @brief Main menu function for user interaction and navigation.
 *
 * This function displays the main menu options, processes user input, and performs corresponding actions.
 * Time Complexity : O(1) this function only evaluate the value of input and calls another functions
 *
 * @param ucs Pointer to the vector of Uc objects.
 * @param students Pointer to the vector of Student objects.
 * @return 0 upon successful execution.
 */

int menu(vector<Uc> *ucs, vector<Student> *students) {
    //Main menu of te whole program
    string choice;

    do {
        // Show options
        cout << "\n\nBem-vindo ao Menu de consulta e gestão de Alunos, Turmas e UCs da FEUP\n" << endl;
        cout << "Menu:\n" << endl;
        cout << "1 - Ver todos os estudantes" << endl;
        cout << "2 - Ver todos as UC's e turmas que as compões juntamente com os alunos inscritos" << endl;
        cout << "3 - Ver o horário todas as turmas de uma UC" << endl;
        cout << "4 - Informações sobre um estudante específico" << endl;
        cout << "5 - Processar uma requisição" << endl;
        cout << "6 - Fazer undo à última requisição efetuada com êxito" << endl;
        cout << "7 - Ver a lista de requisições efetuadas com êxito" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite sua escolha: ";
        cin >> choice;
        // Executar ações com base na escolha do usuário

        //Access the users choice
        if (choice == "1") {
            verTodosEstudantes(ucs, students);
        } else if (choice == "2") {
            verUcClassStudent(ucs, students);
        }else if (choice == "3") {
            verTodasClasses(ucs, students);
        } else if (choice == "4") {
            infoSobreEstudante(ucs, students);
        } else if (choice == "5") {
            processarRequisicao(ucs, students);
        }else if (choice == "6") {
            undoRequisicao(ucs, students);
        }else if (choice == "7") {
            verRequisicao(ucs, students);
        } else if (choice == "0") {
            cout << "A encerrar o programa. Obrigado!" << endl;
        } else { //Access if the input if valid
            cout << "\n\nEscolha inválida. Por favor, tente novamente." << endl;
            cout << "Digite um número entre 0 - 7." << endl;
        }



    } while (choice != "0");

    return 0;
}


#endif //PROJ2023_MENU_H
