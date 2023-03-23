#include "include/data_base_request_solution.h"

dbm::dbrs::DataBaseRequestSol::DataBaseRequestSol()
{
    //set logger
    qInstallMessageHandler(dbm::dbls::messageHandler);
}

dbm::dbrs::DataBaseRequestSol::~DataBaseRequestSol()
{

}

bool dbm::dbrs::DataBaseRequestSol::RandomQuery(QSqlDatabase &aDataBase, const QString &aQuery)
{
    QSqlQuery query(aDataBase);

    if(!query.exec(aQuery))
    {
        qWarning(dbm::dbls::logWarning()) <<  query.lastError().text() << '\n' << query.lastQuery();
        return false;
    }

    qDebug(dbm::dbls::logDebug()) << "Random query successfully: " << query.lastQuery() << Qt::endl;
    emit querySuccessfully();
    return true;
}

QVector<QVariant> dbm::dbrs::DataBaseRequestSol::GetContentsOfTheColumn(QSqlDatabase &aDataBase,
                                                                        const QString &aTableName,
                                                                        const QString &aColumnName)
{
    QSqlQuery query(aDataBase);
    QString str = "SELECT " + aColumnName + " FROM " + aTableName;

    if(!query.exec(str))
    {
        qWarning(dbm::dbls::logWarning()) <<  query.lastError().text() << '\n' << query.lastQuery();
    }

    int fieldNo = query.record().indexOf(aColumnName);
    QVector<QVariant> contents;
    while (query.next())
    {
        contents.push_back(query.value(fieldNo));
    }

    emit querySuccessfully();
    return contents;
}
