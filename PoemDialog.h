#pragma once
#include <qdialog.h>
#include "ui_PoemDialog.h"
#include "PoemDataManager.h"
class PoemDialog :
    public QDialog
{
    Q_OBJECT
public:
    PoemDialog(QWidget* parent = Q_NULLPTR);

    static void showPoem(PoemDataManager::Poem poem, QWidget* parent = Q_NULLPTR);

private:
    Ui::PoemDialog ui;
    static QString contentTemplate;
};

