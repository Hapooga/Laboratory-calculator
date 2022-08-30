#ifndef DB_WORKER_H
#define DB_WORKER_H

#include <QtSql>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>

#include <map>
#include <string>

class DBWorker : public QObject {

     Q_OBJECT

public:

    explicit DBWorker(QTableView* acid_limit_table, QObject *parent = 0);

    bool DeleteEquivalent(const QString& formula);

    bool AddNewEquivalent (const QString& formula, const size_t equivalent);

    size_t FindEquivalent(const QString& formula);

    size_t GetEquivalent(const QString& formula);

    ~DBWorker();

private:

    QPair<size_t, QString> GetEquivalentFromDB(const QString& formula);

    bool GetAllFromDB();

private:

    const QString table_name = "equivalent_table";
    const QString db_name = "EquivalentTableDB.sqlite";

    QSqlQuery *query;
    QSqlTableModel* model;
    QSqlDatabase data_base;

};

#endif // DB_WORKER_H
