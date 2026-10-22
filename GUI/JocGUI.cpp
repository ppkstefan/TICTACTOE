#include "JocGUI.h"
#include <QMessageBox>
#include <QLabel>
#include <QFormLayout>

JocGUI::JocGUI(JocService& srv) : srv{ srv } {
    initGUI();
    model = new JocTableModel();
    tabel->setModel(model);
    
    incarcaTabel();
    connectSignals();
}

void JocGUI::initGUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    
    // --- Partea Stanga: Tabel si Formular ---
    QVBoxLayout* leftLayout = new QVBoxLayout();
    
    tabel = new QTableView();
    // Setari pentru a selecta toata linia, nu doar o celula
    tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabel->setSelectionMode(QAbstractItemView::SingleSelection);
    leftLayout->addWidget(tabel);
    
    QFormLayout* formLayout = new QFormLayout();
    txtId = new QLineEdit();
    txtDim = new QLineEdit();
    txtTabla = new QLineEdit();
    txtJucator = new QLineEdit();
    txtStare = new QLineEdit();
    
    formLayout->addRow("ID Joc:", txtId);
    formLayout->addRow("Dimensiune:", txtDim);
    formLayout->addRow("Tabla (ex: X-O...):", txtTabla);
    formLayout->addRow("Jucator (X/O):", txtJucator);
    formLayout->addRow("Stare:", txtStare);
    leftLayout->addLayout(formLayout);
    
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnAdauga = new QPushButton("Adauga Joc Nou");
    btnModifica = new QPushButton("Modifica Joc");
    btnLayout->addWidget(btnAdauga);
    btnLayout->addWidget(btnModifica);
    leftLayout->addLayout(btnLayout);
    
    mainLayout->addLayout(leftLayout);
    
    // --- Partea Dreapta: Tabla dinamica ---
    QVBoxLayout* rightLayout = new QVBoxLayout();
    QLabel* lblTabla = new QLabel("Tabla de joc activa:");
    rightLayout->addWidget(lblTabla);
    
    // Cream un widget simplu care sa tina QGridLayout-ul pentru a-l putea curata usor
    QWidget* tablaWidget = new QWidget();
    layoutTabla = new QGridLayout(tablaWidget);
    rightLayout->addWidget(tablaWidget);
    rightLayout->addStretch(); // impinge elementele in sus
    
    mainLayout->addLayout(rightLayout);
}

void JocGUI::incarcaTabel() {
    // Apelam service-ul care ne da jocurile deja sortate (Cerinta 1)
    model->setJocuri(srv.getAllSorted());
}

void JocGUI::deseneazaTablaDeJoc(int dim, const std::string& tablaStr) {
    // 1. Curatam vechile butoane de pe ecran
    QLayoutItem* item;
    while ((item = layoutTabla->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // 2. Generam butoanele noi
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int pozitiePeString = i * dim + j;
            QString textPeButon = QString(tablaStr[pozitiePeString]);
            
            QPushButton* btn = new QPushButton(textPeButon);
            btn->setFixedSize(50, 50); // butoane patrate

            // 3. Conectam click-ul pe buton
            QObject::connect(btn, &QPushButton::clicked, [this, pozitiePeString]() {
                if (idJocSelectat != -1) {
                    try {
                        srv.mutareJoc(idJocSelectat, pozitiePeString);
                        incarcaTabel(); // refresh la tabel ca s-a schimbat starea si tabla
                        
                        // Refacem selectia in tabel pentru a vedea modificarile pe tabla
                        for (int rand = 0; rand < model->rowCount(); rand++) {
                            if (model->data(model->index(rand, 0)).toInt() == idJocSelectat) {
                                tabel->selectRow(rand); // Aceasta va declansa automat redesenarea tablei
                                break;
                            }
                        }
                    } catch (const std::exception& e) {
                        QMessageBox::warning(this, "Eroare Mutare", e.what());
                    }
                }
            });
            layoutTabla->addWidget(btn, i, j);
        }
    }
}

void JocGUI::connectSignals() {
    // Selectia din tabel -> populeaza formularul si deseneaza tabla
    QObject::connect(tabel->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        if (tabel->selectionModel()->selectedIndexes().isEmpty()) return;
        
        int row = tabel->selectionModel()->selectedIndexes().at(0).row();
        
        int id = model->data(model->index(row, 0)).toInt();
        int dim = model->data(model->index(row, 1)).toInt();
        QString tabla = model->data(model->index(row, 2)).toString();
        QString jucator = model->data(model->index(row, 3)).toString();
        QString stare = model->data(model->index(row, 4)).toString();
        
        txtId->setText(QString::number(id));
        txtDim->setText(QString::number(dim));
        txtTabla->setText(tabla);
        txtJucator->setText(jucator);
        txtStare->setText(stare);
        
        idJocSelectat = id;
        deseneazaTablaDeJoc(dim, tabla.toStdString());
    });

    // Buton Adauga
    QObject::connect(btnAdauga, &QPushButton::clicked, [this]() {
        try {
            int id = txtId->text().toInt();
            int dim = txtDim->text().toInt();
            std::string tabla = txtTabla->text().toStdString();
            char jucator = txtJucator->text().toStdString()[0];
            
            srv.adaugaJoc(id, dim, tabla, jucator);
            incarcaTabel();
            QMessageBox::information(this, "Succes", "Joc adaugat cu succes in starea Neinceput!");
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Eroare", e.what());
        }
    });

    // Buton Modifica
    QObject::connect(btnModifica, &QPushButton::clicked, [this]() {
        try {
            int id = txtId->text().toInt();
            int dim = txtDim->text().toInt();
            std::string tabla = txtTabla->text().toStdString();
            char jucator = txtJucator->text().toStdString()[0];
            std::string stare = txtStare->text().toStdString();
            
            srv.modificaJoc(id, dim, tabla, jucator, stare);
            incarcaTabel();
            
            if (id == idJocSelectat) {
                deseneazaTablaDeJoc(dim, tabla); // update vizual daca fix el e selectat
            }
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Eroare", e.what());
        }
    });
}