#pragma once
#include "../DOMAIN/Joc.h"
#include <vector>
#include <string>

class JocRepo {
private:
    std::string filename;
    std::vector<Joc> jocuri;
    
    void loadFromFile();
    void saveToFile();

public:
    // Constructorul primeste calea catre fisierul text
    JocRepo(const std::string& filename);
    
    // Returneaza toate jocurile
    std::vector<Joc> getAll();
    
    // Adauga un joc nou in memorie si in fisier
    void adauga(const Joc& j);
    
    // Modifica un joc existent (dupa ID) in memorie si in fisier
    void modifica(const Joc& j);
};