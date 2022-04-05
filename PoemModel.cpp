#include "PoemModel.h"

PoemModel::PoemModel(QObject* parent):
    QAbstractTableModel(parent)
{
    setHeaderData(0, Qt::Horizontal, "title");
}

int PoemModel::rowCount(const QModelIndex& parent) const
{
    return poems.size();
}

QVariant PoemModel::data(const QModelIndex& index, int role) const
{
    PoemDataManager::Poem poem = poems[index.row()];
    
    if (role == Qt::ItemDataRole::DisplayRole) {
        switch (index.column()) {
        case 0:
            return poem.title;
        case 1:
            return poem.type;
        case 2:
            return poem.writer;
        case 3:
            return poem.content;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QVariant PoemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::ItemDataRole::DisplayRole)
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return tr("Title");
            case 1:
                return tr("Type");
            case 2:
                return tr("Author");
            case 3:
                return tr("Content");
            }
        }
        else return section+1;
    return QVariant();
}

Qt::ItemFlags PoemModel::flags(const QModelIndex& index) const
{
    return Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsEnabled;
}

void PoemModel::setPoems(QList<int> poemsID)
{
    beginResetModel();
    poems.clear();
    for (int i : poemsID) {
        PoemDataManager::Poem res = PoemDataManager::SearchPoemByID(i);
        if (!res.isNull)
            poems.append(res);
    }

    endResetModel();
}
