#include <QApplication>
#include "REPO/JocRepo.h"
#include "SERVICE/JocService.h"
#include "GUI/JocGUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Daca fisierul nu exista in folderul curent al executabilului,
    // se va crea la prima adaugare.
    JocRepo repo{"jocuri.txt"};
    JocService srv{repo};
    JocGUI gui{srv};

    gui.setWindowTitle("Tic Tac Toe Manager");
    gui.resize(800, 400);
    gui.show();

    return a.exec();
}