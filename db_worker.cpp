#include "db_worker.h"
#include <algorithm>
#include <string>
#include <QDebug>

using namespace std;

DBWorker& DBWorker::Instence() {
    static DBWorker db_worker;
    return db_worker;
}

pair<size_t, string> DBWorker::GetEquivalentFromBuffer(const QString& formula) const{

    string formula_with_taple = formula.toStdString();

    reverse(formula_with_taple.begin(), formula_with_taple.end());

    size_t max_tail_after_taple = 2;

    for(auto const& [taple, equivalent] : taple_buffer) {

        size_t taple_end = formula_with_taple.find(taple);

        if(taple_end <= max_tail_after_taple){

            return {equivalent, taple};

        }
    }

    return {0, ""};
}

bool DBWorker::DeleteEquivalent(const QString& formula){

    if(!data_base.open()){

        return 0;
    }

    query_string =
            "DELETE FROM " + table_name + ""
            " WHERE (formula = '" + formula + "')";

    QSqlQuery query(data_base);

    if(!query.exec(query_string)) {

        return 0;

    } else {

        return 1;
    }

}

bool DBWorker::AddNewEquivalent (const QString& formula, const size_t equivalent){

    if(!data_base.open()){

        return 0;
    }

    query_string = "INSERT INTO " + table_name + ""
                   " VALUES ('" + formula + "' , "
                   "" + QString::number(equivalent) + ")";

    QSqlQuery query(data_base);

    if(!query.exec(query_string)) {

        return 0;

    } else {

        return 1;
    }
}

bool DBWorker::GetAllInfoFromDB(){

    if(!data_base.open()){

        return 0;
    }
    query_string = "SELECT * FROM " + table_name;

    QSqlQuery query(data_base);

    if(!query.exec(query_string)) {

        return 0;

    } else {

        if(modal){

            delete modal;
        }

        modal = new QSqlQueryModel();
        modal->setQuery(std::move(query));

        return 1;
    }
}

QSqlQueryModel* DBWorker::GetModal() const {
    return modal;
}

size_t DBWorker::GetEquivalent(const QString& formula){

    if(!data_base.open()){

        return 0;
    }

    query_string = "SELECT equivalent FROM " + table_name + ""
                   " WHERE formula = '" + formula + "'";

    QSqlQuery query(data_base);

    if(!query.exec(query_string)) {

        return 0;
    }

    query.next();

    return query.value(0).toInt();
}

bool DBWorker::ReloadTableBuffer() {

    if(!data_base.open()){

        return 0;

    }

    query_string = "SELECT * FROM " + table_name;

    QSqlQuery query(data_base);

    if(!query.exec(query_string)) {

        return 0;
    }

    string taple;

    while(query.next()){

        taple = query.value(0).toString().toStdString();

        reverse(taple.begin(), taple.end());

        taple_buffer.push_back(make_pair(taple ,query.value(1).toInt()));

    }

    sort(taple_buffer.begin(), taple_buffer.end(), []
                (const pair<string, size_t>& left, const pair<string, size_t>& right){
        return left.first.size() > right.first.size();
    });

    return 1;
}

DBWorker::DBWorker() : data_base(QSqlDatabase::addDatabase("QSQLITE")) {

    data_base.setDatabaseName(db_name);

    if(!data_base.open()){

        qDebug() << "Constructor error: DB did't opend";
    }

    query_string = "CREATE TABLE IF NOT EXISTS " + table_name + " ("
                   "'formula' TEXT NOT NULL UNIQUE, "
                   "'equivalent' INTEGER NOT NULL, "
                   "PRIMARY KEY('formula') "
                   ");";

    QSqlQuery query(data_base);

    if(!query.exec(query_string)) {

        qDebug() << "Constructor error: Table did't created";

    }

    if(!ReloadTableBuffer()){

        qDebug() << "Constructor error: DB buffer did't reloaded";

    }
};

DBWorker::~DBWorker(){
    data_base.close();
    delete modal;
}
