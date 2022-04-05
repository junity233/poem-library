#pragma once
#include <qabstractitemmodel.h>
#include "PoemDataManager.h"

class PoemModel :
    public QAbstractTableModel
{
public:
    PoemModel(QObject* parent = Q_NULLPTR);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const { return 4; };
    virtual QVariant data(const QModelIndex& index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const;

    void setPoems(QList<int> poemsID);

private:
    QList<PoemDataManager::Poem> poems;
};

