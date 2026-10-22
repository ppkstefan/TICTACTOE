//
// Created by PPK on 6/27/2026.
//

#include "JocRepo.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

JocRepo::JocRepo(const std::string& filename) : filename{ filename } {
    loadFromFile(); // Incarcam datele imediat ce se creeaza repo-ul
}

void JocRepo::loadFromFile() {
    jocuri.clear();
    std::ifstream fin(filename);
    if (!fin.is_open()) return; // Daca nu exista fisierul, pornim cu lista goala

    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        int id, dim;
        std::string tabla, stare, cuvant;
        char jucator;

        // Citim datele simple
        ss >> id >> dim >> tabla >> jucator;

        // EVITAM CAPCANA: Citim restul liniei pentru starea "In derulare"
        stare = "";
        while (ss >> cuvant) {
            stare += cuvant + " ";
        }
        if (!stare.empty()) stare.pop_back(); // Scoatem ultimul spatiu in plus

        jocuri.push_back(Joc(id, dim, tabla, jucator, stare));
    }
    fin.close();
}

void JocRepo::saveToFile() {
    std::ofstream fout(filename);
    for (const auto& j : jocuri) {
        fout << j.getId() << " " << j.getDim() << " "
             << j.getTabla() << " " << j.getJucator() << " " << j.getStare() << "\n";
    }
    fout.close();
}

std::vector<Joc> JocRepo::getAll() {
    return jocuri;
}

void JocRepo::adauga(const Joc& j) {
    // Verificam sa nu existe deja un joc cu acelasi ID
    for (const auto& joc : jocuri) {
        if (joc.getId() == j.getId()) {
            throw std::runtime_error("ID deja existent in baza de date!");
        }
    }
    jocuri.push_back(j);
    saveToFile(); // Actualizam fisierul
}

void JocRepo::modifica(const Joc& j) {
    bool gasit = false;
    for (auto& joc : jocuri) {
        if (joc.getId() == j.getId()) {
            joc = j; // Actualizam obiectul prin atribuire
            gasit = true;
            break;
        }
    }
    if (!gasit) {
        throw std::runtime_error("Jocul nu exista!");
    }
    saveToFile(); // Actualizam fisierul
}