#ifndef DB_WORKER_H
#define DB_WORKER_H

#include <QtSql>
#include <QSqlQuery>

#include <map>
#include <string>

class DBWorker{
public:

    static DBWorker& Instence();

    std::pair<size_t, std::string> GetEquivalentFromBuffer(const QString& formula) const;

    bool DeleteEquivalent(const QString& formula);

    bool AddNewEquivalent (const QString& formula, const size_t equivalent);

    bool GetAllInfoFromDB();

    QSqlQueryModel* GetModal() const;

    size_t GetEquivalent(const QString& formula);

    bool ReloadTableBuffer();

    DBWorker(const DBWorker& other) = delete;

    DBWorker& operator = (const DBWorker& other) = delete;

    ~DBWorker();

private:

    DBWorker();

    const QString table_name = "equivalent_table";
    const QString db_name = "EquivalentTableDB.sqlite";
    QSqlQueryModel* modal;
    QSqlDatabase data_base;
    QString query_string;
    std::vector<std::pair<std::string, size_t>> taple_buffer;
};

#endif // DB_WORKER_H
