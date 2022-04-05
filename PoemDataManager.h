#pragma once
#include <qsqldatabase.h>
#include <exception>

class PoemDataManager
{
public:

	struct Poem {
		int id;
		bool isNull;
		QString title;
		QString writer;
		QString type;
		QString content;
	};

	static bool Init(const QString& databasePath);

	static QList<int> SearchID(const QString& title = QString(), const QString& type = QString(), const QString& writer = QString(), const QString& content = QString());

	static Poem SearchPoemByID(int id);

	static int count();

	~PoemDataManager() { database.close(); };
	
private:
	QSqlDatabase database;
	static PoemDataManager* instance;

	PoemDataManager(const QString& databasePath);
};

