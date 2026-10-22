#pragma once
#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "../SERVICE/JocService.h"
#include "JocTableModel.h"

class JocGUI : public QWidget {
private:
    JocService& srv;
    JocTableModel* model;
    
    // Elementele grafice
    QTableView* tabel;
    QLineEdit* txtId;
    QLineEdit* txtDim;
    QLineEdit* txtTabla;
    QLineEdit* txtJucator;
    QLineEdit* txtStare;
    QPushButton* btnAdauga;
    QPushButton* btnModifica;
    
    // Layout-ul pentru butoanele dinamice (tabla de joc)
    QGridLayout* layoutTabla;
    
    int idJocSelectat = -1; // retinem ce joc e selectat din tabel

    void initGUI();
    void connectSignals();
    void incarcaTabel();
    void deseneazaTablaDeJoc(int dim, const std::string& tabla);

public:
    JocGUI(JocService& srv);
};