#include "JocTableModel.h"

int JocTableModel::rowCount(const QModelIndex& parent) const {
    return jocuri.size();
}

int JocTableModel::columnCount(const QModelIndex& parent) const {
    return 5; // Id, Dim, Tabla, Jucator, Stare
}

QVariant JocTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        Joc j = jocuri[index.row()];
        switch (index.column()) {
            case 0: return QString::number(j.getId());
            case 1: return QString::number(j.getDim());
            case 2: return QString::fromStdString(j.getTabla());
            case 3: return QString(j.getJucator());
            case 4: return QString::fromStdString(j.getStare());
            default: break;
        }
    }
    return QVariant();
}

QVariant JocTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "ID";
            case 1: return "Dim";
            case 2: return "Tabla";
            case 3: return "Jucator";
            case 4: return "Stare";
            default: break;
        }
    }
    return QVariant();
}

void JocTableModel::setJocuri(const std::vector<Joc>& noiJocuri) {
    beginResetModel();
    jocuri = noiJocuri;
    endResetModel();
}