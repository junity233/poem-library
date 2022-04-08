#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "PoemDataManager.h"
#include "PoemModel.h"
#include <qlabel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void onQueryButtonClicked();
    void onViewButtonClicked();
    void onPerPageButtonClicked();
    void onNextPageButtonClicked();
    void onJumpToButtonClicked();
    void onComfireButtonClicked();
    void onPoemTableViewDoubleClicked(const QModelIndex &);
    void onPageNumSpinEditingFinished();

private:
    Ui::MainWindowClass ui;
    PoemModel* model;
    QList<int> poems;
    int pageNum = 0;
    int poemNumOfPage = 10;

    QLabel* poemNumLabel;
    QLabel* pageLabel;

    void Init();
    void UpdatePage();
    int pageSum() const;
    void viewPoem(int pageIndex);
};
