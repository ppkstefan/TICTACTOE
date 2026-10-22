//
// Created by PPK on 6/27/2026.
//

#ifndef TICTACTOE_JOCSERVICE_H
#define TICTACTOE_JOCSERVICE_H


#pragma once
#include "../REPO/JocRepo.h"
#include <string>
#include <vector>

class JocService {
private:
    JocRepo& repo;

    // Functie privata pentru reutilizarea codului de validare
    void valideazaDate(int dim, const std::string& tabla, char jucator, const std::string& stare);

public:
    JocService(JocRepo& r) : repo{ r } {}

    // Returneaza lista gata sortata dupa stare (Cerinta 1)
    std::vector<Joc> getAllSorted();

    // Creare joc (Cerinta 2)
    void adaugaJoc(int id, int dim, const std::string& tabla, char jucator);

    // Modificare joc existent (Cerinta 3)
    void modificaJoc(int id, int dim, const std::string& tabla, char jucator, const std::string& stare);

    // Efectueaza o mutare direct pe string-ul tablei (Cerinta 5)
    void mutareJoc(int id, int pozitiePeTabla);
};

#endif //TICTACTOE_JOCSERVICE_H