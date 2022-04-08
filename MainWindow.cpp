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
    QModelIndex index = ui.tableView->currentIndex();
    if (index.isValid())
        viewPoem(index.row());
}

void MainWindow::onPerPageButtonClicked()
{
    if (pageNum > 0)
        pageNum--;
    UpdatePage();
}

void MainWindow::onNextPageButtonClicked()
{
    if(pageNum<pageSum())
        pageNum++;
    UpdatePage();
}

void MainWindow::onJumpToButtonClicked()
{
    if (poems.size() == 0)
        return;
    pageNum = ui.pageNumSpin->value() - 1;
    UpdatePage();
}

void MainWindow::onComfireButtonClicked()
{
    pageNum = 0;
    poemNumOfPage = ui.poemNumPerPageSpin->value();
    UpdatePage();
}

void MainWindow::onPoemTableViewDoubleClicked(const QModelIndex& index)
{
    viewPoem(index.row());
}

void MainWindow::onPageNumSpinEditingFinished()
{

    if (poems.size() == 0)
        return;
    pageNum = ui.pageNumSpin->value()-1;
    UpdatePage();
}

void MainWindow::Init() {
    poems = PoemDataManager::SearchID();
    ui.pageNumSpin->setMaximum(poems.size());

    UpdatePage();
}

void MainWindow::UpdatePage() {
    QList<int> poemsOfPage;

    for (int i = 0; i < poemNumOfPage && (i + poemNumOfPage * pageNum) < poems.size(); i++) {
        poemsOfPage.append(poems[i + poemNumOfPage * pageNum]);
    }

    pageLabel->setText(tr("%1 / %2 Page").arg(pageNum + 1).arg(pageSum()));
    poemNumLabel->setText(tr("%1 records in total").arg(poems.size()));
    ui.pageNumSpin->setValue(pageNum + 1);

    model->setPoems(poemsOfPage);
}

int MainWindow::pageSum() const
{
    return poems.size() / poemNumOfPage + (poems.size() % poemNumOfPage != 0);
}

void MainWindow::viewPoem(int pageIndex)
{
    int idx = pageNum * poemNumOfPage + pageIndex;
    PoemDataManager::Poem poem = PoemDataManager::SearchPoemByID(poems[idx]);

    PoemDialog::showPoem(poem, this);
}
