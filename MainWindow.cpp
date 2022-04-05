#include "MainWindow.h"
#include "PoemDialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    PoemDataManager::Init("culture.db");

    model = new PoemModel(this);
    poemNumLabel = new QLabel(this);
    pageLabel = new QLabel(this);

    ui.tableView->setModel(model);
    ui.statusBar->addWidget(poemNumLabel);
    ui.statusBar->addWidget(pageLabel);

    Init();
}

void MainWindow::onQueryButtonClicked()
{
    poems = PoemDataManager::SearchID(ui.titleEdit->text(), ui.typeCombo->currentText(), ui.authorEdit->text(), ui.contentEdit->text());
    pageNum = 0;
    ui.pageNumSpin->setMaximum(pageSum());
    UpdatePage();
}

void MainWindow::onViewButtonClicked()
{
    int idx = pageNum * poemNumOfPage + ui.tableView->currentIndex().row();
    PoemDataManager::Poem poem = PoemDataManager::SearchPoemByID(poems[idx]);

    PoemDialog::showPoem(poem, this);
}

void MainWindow::onPerPageButtonClicked()
{
    if (pageNum > 0)
        pageNum--;
    UpdatePage();
}

void MainWindow::onNextPageButtonClicked()
{
    if((pageNum+1)*poemNumOfPage<=poems.size())
        pageNum++;
    UpdatePage();
}

void MainWindow::onJumpToButtonClicked()
{
    pageNum = ui.pageNumSpin->value() - 1;
    UpdatePage();
}

void MainWindow::onComfireButtonClicked()
{
    pageNum = 0;
    poemNumOfPage = ui.poemNumPerPageSpin->value();
    UpdatePage();
}

void MainWindow::Init() {
    poems = PoemDataManager::SearchID();

    UpdatePage();
}

void MainWindow::UpdatePage() {
    QList<int> poemsOfPage;

    for (int i = 0; i < poemNumOfPage && (i + poemNumOfPage * pageNum) < poems.size(); i++) {
        poemsOfPage.append(poems[i + poemNumOfPage * pageNum]);
    }

    pageLabel->setText(tr("%1 / %2 Page").arg(pageNum + 1).arg(pageSum()));
    poemNumLabel->setText(tr("%1 records in total").arg(poems.size()));

    model->setPoems(poemsOfPage);
}

int MainWindow::pageSum() const
{
    return poems.size() / poemNumOfPage + (poems.size() % poemNumOfPage != 0);
}
