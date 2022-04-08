#include "PoemDialog.h"
#include <qfile.h>


PoemDialog::PoemDialog(QWidget* parent):
	QDialog(parent)
{
	ui.setupUi(this);
}

void PoemDialog::showPoem(PoemDataManager::Poem poem,QWidget* parent)
{
	PoemDialog dialog(parent);
	dialog.ui.titleLabel->setText(QStringLiteral("<<%1>>").arg(poem.title));
	dialog.ui.writerLabel->setText(tr("Author:") + poem.writer);
	dialog.ui.typeLabel->setText(tr("Type:") + poem.type);
	dialog.ui.contentBrowser->setHtml(tr("<div align=\"center\"><font size=\"10\"><p>%1</p></font></div>").arg(poem.content.replace("\n", "<br>")));
	dialog.exec();
}
