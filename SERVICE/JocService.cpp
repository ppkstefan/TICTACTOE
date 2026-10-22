#include "JocService.h"
#include <stdexcept>
#include <algorithm>

void JocService::valideazaDate(int dim, const std::string& tabla, char jucator, const std::string& stare) {
    // Validare dimensiune
    if (dim != 3 && dim != 4 && dim != 5) {
        throw std::runtime_error("Dimensiunea trebuie sa fie 3, 4 sau 5!");
    }
    // Validare lungime tabla
    if (tabla.length() != dim * dim) {
        throw std::runtime_error("Tabla trebuie sa aiba exact dim x dim caractere!");
    }
    // Validare caractere tabla
    for (char c : tabla) {
        if (c != 'X' && c != 'O' && c != '-') {
            throw std::runtime_error("Tabla poate contine doar caracterele X, O sau - !");
        }
    }
    // Validare jucator
    if (jucator != 'X' && jucator != 'O') {
        throw std::runtime_error("Jucatorul curent trebuie sa fie X sau O!");
    }
    // Validare stare
    if (stare != "Neinceput" && stare != "In derulare" && stare != "Terminat") {
        throw std::runtime_error("Starea este invalida!");
    }
}

std::vector<Joc> JocService::getAllSorted() {
    std::vector<Joc> toate = repo.getAll();
    
    // Sortam alfabetic dupa starea jocului, conform cerintei din fisier
    std::sort(toate.begin(), toate.end(), [](const Joc& j1, const Joc& j2) {
        return j1.getStare() < j2.getStare();
    });
    
    return toate;
}

void JocService::adaugaJoc(int id, int dim, const std::string& tabla, char jucator) {
    // Fortam starea "Neinceput" conform cerintei 2
    valideazaDate(dim, tabla, jucator, "Neinceput");
    Joc j(id, dim, tabla, jucator, "Neinceput");
    repo.adauga(j);
}

void JocService::modificaJoc(int id, int dim, const std::string& tabla, char jucator, const std::string& stare) {
    // Aici permitem orice stare, de la "Neinceput" pana la "Terminat"
    valideazaDate(dim, tabla, jucator, stare);
    Joc j(id, dim, tabla, jucator, stare);
    repo.modifica(j);
}

void JocService::mutareJoc(int id, int pozitiePeTabla) {
    // Gasim jocul
    std::vector<Joc> toate = repo.getAll();
    auto it = std::find_if(toate.begin(), toate.end(), [id](const Joc& joc) {
        return joc.getId() == id;
    });

    if (it == toate.end()) throw std::runtime_error("Jocul nu a fost gasit!");
    Joc j = *it;

    if (j.getStare() == "Terminat") throw std::runtime_error("Jocul este deja terminat!");

    std::string tablaCurenta = j.getTabla();
    if (tablaCurenta[pozitiePeTabla] != '-') {
        throw std::runtime_error("Aceasta casuta este deja ocupata!");
    }

    // Facem mutarea
    tablaCurenta[pozitiePeTabla] = j.getJucator();
    j.setTabla(tablaCurenta);

    // Schimbam jucatorul
    char jucatorUrmator = (j.getJucator() == 'X') ? 'O' : 'X';
    j.setJucator(jucatorUrmator);

    // Daca jocul tocmai a inceput sau se joaca, starea e "In derulare"
    // (Aici poti adauga si algoritm de verificare daca cineva a castigat, setand "Terminat")
    j.setStare("In derulare");

    // Salvam direct modificarea in repo
    repo.modifica(j);
}