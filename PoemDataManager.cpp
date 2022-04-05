#include "PoemDataManager.h"
#include <qsqldriver.h>
#include <qsqlquery.h>
#include <qvariant.h>
#include <qsqlerror.h>
#include <qdebug.h>
#include <qset.h>
#include <qmessagebox.h>

PoemDataManager* PoemDataManager::instance = nullptr;

PoemDataManager::PoemDataManager(const QString& databasePath)
{
	if (QSqlDatabase::contains("poems_database")) {
		this->database = QSqlDatabase::database("poems_database");
	}
	else {
		this->database = QSqlDatabase::addDatabase("QSQLITE");
		this->database.setDatabaseName(databasePath);
	}
}

bool PoemDataManager::Init(const QString& databasePath)
{
	if (instance != nullptr)
		return false;

	instance = new PoemDataManager(databasePath);

	instance->database.open();
	if (!instance->database.isOpen())
	{
		delete instance;
		instance = nullptr;
		return false;
	}

	return true;
}

QList<int>PoemDataManager::SearchID(const QString& title, const QString& type, const QString& writer, const QString& content)
{
	QList<int> res;
	QSqlQuery query;
	//QString sql = "Select id,title,writer,type,content from \"poems\" where content like '%" + str + "%';";
	QString sql = "Select id from \"poems\" ";
	QStringList exps;

	if (!title.isEmpty()) {
		exps += "title like \"%" + title + "%\"";
	}
	if (!type.isEmpty()&&type!=QStringLiteral("È«²¿")) {
		exps += "type = \"" + type + '\"';
	}
	if (!writer.isEmpty()) {
		exps += "writer = \"" + writer + '\"';
	}
	if (!content.isEmpty()) {
		exps += "content like \"%" + content + "%\"";
	}

	if (!exps.empty()) {
		sql += "where " + exps[0];
		for (int i = 1; i < exps.size(); i++)
			sql.append(" AND " + exps[i]);
	}

	sql = sql + ';';
	if (query.exec(sql)) {
		while (query.next()) {
			res.append(query.value("id").toInt());
		}
		return res;
	}
	else {
		QMessageBox::warning(nullptr, "Error", QString("SQL Error:%1").arg(query.lastError().text()));
	}
}

PoemDataManager::Poem PoemDataManager::SearchPoemByID(int id)
{
	Poem res;
	QSqlQuery query;
	QString sql = QString("select id,title,writer,type,content from \"poems\" where id == %1;").arg(id);

	if (query.exec(sql)) {
		if (query.next()) {
			res.isNull = false;
			res.id = query.value("id").toInt();
			res.content = query.value("content").toString();
			res.title = query.value("title").toString();
			res.writer = query.value("writer").toString();
			res.type = query.value("type").toString();
			return res;
		}
		res.isNull = true;
		return res;
	}
	else {
		qDebug() << "Execute sql failed:" + query.lastError().text();
		throw "Execute sql failed:" + query.lastError().text();
	}
}

int PoemDataManager::count()
{
	QSqlQuery query;
	QString sql = "select count(*) from \"poems\";";

	if (query.exec(sql)) {
		query.next();
		return query.value(0).toInt();
	}
	else{
		return -1;
	}
}
