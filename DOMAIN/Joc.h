//
// Created by PPK on 6/27/2026.
//

#ifndef TICTACTOE_JOC_H
#define TICTACTOE_JOC_H


#pragma once
#include <string>

class Joc {
private:
    int id;
    int dim;
    std::string tabla;
    char jucator;
    std::string stare;

public:
    // Constructorul de baza
    Joc(int id, int dim, const std::string& tabla, char jucator, const std::string& stare);

    // --- Getters ---
    int getId() const;
    int getDim() const;
    std::string getTabla() const;
    char getJucator() const;
    std::string getStare() const;

    // --- Setters ---
    // ID-ul nu are setter pentru ca, de regula, identificatorul unic nu se modifica
    void setDim(int newDim);
    void setTabla(const std::string& newTabla);
    void setJucator(char newJucator);
    void setStare(const std::string& newStare);
};


#endif //TICTACTOE_JOC_H