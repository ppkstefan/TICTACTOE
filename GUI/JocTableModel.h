#pragma once
#include <QAbstractTableModel>
#include "../DOMAIN/Joc.h"
#include <vector>

class JocTableModel : public QAbstractTableModel {
private:
    std::vector<Joc> jocuri;

public:
    // Suprascriem metodele obligatorii
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Metoda custom pentru a da refresh la datele din tabel
    void setJocuri(const std::vector<Joc>& noiJocuri);
};