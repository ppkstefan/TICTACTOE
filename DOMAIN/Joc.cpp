//
// Created by PPK on 6/27/2026.
//

#include "Joc.h"


// Implementarea constructorului
Joc::Joc(int id, int dim, const std::string& tabla, char jucator, const std::string& stare)
    : id{ id }, dim{ dim }, tabla{ tabla }, jucator{ jucator }, stare{ stare } {
}

// Implementarea metodelor Getter
int Joc::getId() const {
    return id;
}

int Joc::getDim() const {
    return dim;
}

std::string Joc::getTabla() const {
    return tabla;
}

char Joc::getJucator() const {
    return jucator;
}

std::string Joc::getStare() const {
    return stare;
}

// Implementarea metodelor Setter
void Joc::setDim(int newDim) {
    dim = newDim;
}

void Joc::setTabla(const std::string& newTabla) {
    tabla = newTabla;
}

void Joc::setJucator(char newJucator) {
    jucator = newJucator;
}

void Joc::setStare(const std::string& newStare) {
    stare = newStare;
}