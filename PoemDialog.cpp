#include "PoemDialog.h"
#include <qfile.h>

QString PoemDialog::contentTemplate = "<!DOCTYPE HTML PUBLIC \" -//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
"<html>"
"    <head>"
"        <meta name=\"qrichtext\" content=\"1\" />"
"        <style type=\"text / css\">"
"            p, li { white-space: pre-wrap; }"
"        </style>"
"    </head>"
"    <body style=\" font - family:'SimSun'; font - size:9pt; font - weight:400; font - style:normal; \">"
"        <p align=\"center\" style=\" - qt - paragraph - type:empty; margin - top:0px; margin - bottom:0px; margin - left:0px; margin - right:0px; -qt - block - indent:0; text - indent:0px; \">"
"%1"
"        </p>"
"    </body>"
"</html>";

PoemDialog::PoemDialog(QWidget* parent):
	QDialog(parent)
{
	ui.setupUi(this);
}

void PoemDialog::showPoem(PoemDataManager::Poem poem,QWidget* parent)
{
	PoemDialog dialog(parent);
	dialog.ui.titleLabel->setText(poem.title);
	dialog.ui.writerLabel->setText(tr("Author:") + poem.writer);
	dialog.ui.typeLabel->setText(tr("Type:") + poem.type);
	dialog.ui.contentBrowser->setHtml(contentTemplate.arg(poem.content.replace("\n", "<br>")));
	dialog.exec();
}
