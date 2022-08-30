#include "db_worker.h"
#include <algorithm>
#include <string>
#include <QDebug>
#include <QPair>


using namespace std;


DBWorker::DBWorker(QTableView* acid_limit_table, QObject *parent)
    : QObject(parent) {


    data_base = QSqlDatabase::addDatabase("QSQLITE");
    data_base.setDatabaseName(db_name);

    if(!data_base.open()){
        qDebug() << "DBWorker Constructor error: DB did't opend";
    }

    query = new QSqlQuery(data_base);
    query->exec("CREATE TABLE IF NOT EXISTS " + table_name + " ("
                                                             "'formula' TEXT NOT NULL UNIQUE, "
                                                             "'equivalent' INTEGER NOT NULL, "
                                                             "PRIMARY KEY('formula') "
                                                             ");");

    model = new QSqlTableModel(this, data_base);
    model->setTable(table_name);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Кислотный\nостаток"));
    model->setHeaderData(1, Qt::Horizontal, tr("Эквивалент"));
    acid_limit_table->setModel(model);

};


bool DBWorker::DeleteEquivalent(const QString& formula){

    query->clear();

    if(!query->exec("DELETE FROM " + table_name + ""
                    " WHERE (formula = '" + formula + "')")) {

        return 0;
    }

    model->select();

    return 1;

}

bool DBWorker::AddNewEquivalent (const QString& formula, const size_t equivalent){

    query->clear();

    if(!query->exec("INSERT INTO " + table_name + ""
                    " VALUES ('" + formula + "' , "
                    "" + QString::number(equivalent) + ")")) {
        return 0;
    }

    model->select();

    return 1;

}


size_t DBWorker::FindEquivalent(const QString& formula) {

    size_t molecules = 0;

    size_t max_tail_after_taple = 2;

    QPair<size_t, QString> equivalent_taple = GetEquivalentFromDB(formula);

    if((formula.back().isDigit() && formula[formula.size() - max_tail_after_taple] == ')') ||
            equivalent_taple.second.front() != formula.back()) {

        molecules = formula.back().digitValue();
    }

    return molecules > 1 ? equivalent_taple.first * molecules : equivalent_taple.first;
}


QPair<size_t, QString> DBWorker::GetEquivalentFromDB(const QString& formula) {

    GetAllFromDB();

    bool contains = false;

    while (query->next()) {

        contains = formula.contains(query->value(0).toString());

        if(contains) {

            return {query->value(1).toInt(), query->value(0).toString()};

        }

    }

    return {0, ""};

}


bool DBWorker::GetAllFromDB() {

    query->clear();

    if(!query->exec("SELECT * FROM " + table_name + " ORDER BY formula DESC")) {

        return 0;
    }

    return 1;
}


size_t DBWorker::GetEquivalent(const QString& formula){

    query->clear();

    if(!query->exec("SELECT equivalent FROM " + table_name + ""
                    " WHERE formula = '" + formula + "'")) {

        return 0;
    }

    query->next();

    return query->value(0).toInt();
}


DBWorker::~DBWorker(){
    delete query;
}
