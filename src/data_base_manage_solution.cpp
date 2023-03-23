#include "include/data_base_manage_solution.h"


QString convertTypeFieldToString(int aVal)
{
    QString enumToStr(dbm::dbms::T_F[aVal]);
    return enumToStr;
}


QString convertAttrConstToString(int aVal)
{
    QString enumToStr(dbm::dbms::A_C[aVal]);
    return enumToStr;
}



dbm::dbms::DataBaseManageSol::DataBaseManageSol()
{
    //set logger
    qInstallMessageHandler(dbm::dbls::messageHandler);
}

dbm::dbms::DataBaseManageSol::~DataBaseManageSol()
{

}

bool dbm::dbms::DataBaseManageSol::OpenDataBase(QSqlDatabase &aDataBase,
                                                const QString &aFileName,
                                                const QString &aDBType,
                                                const QString &aHostName,
                                                quint32 aPort,
                                                const QString &aUserName,
                                                const QString &aPassword)
{
    aDataBase = QSqlDatabase::addDatabase(aDBType);
    aDataBase.setDatabaseName(aFileName);
    aDataBase.setHostName(aHostName);
    aDataBase.setPort(aPort);
    aDataBase.setUserName(aUserName);
    aDataBase.setPassword(aPassword);
    if(!aDataBase.open())
    {
        qWarning(dbm::dbls::logWarning()) << aDataBase.lastError().text();
        return false;
    }
    qDebug(dbm::dbls::logDebug()) << "Data file: " << aFileName << " Opened!" << Qt::endl;
    emit dataBaseOpened();
    return true;
}

bool dbm::dbms::DataBaseManageSol::CloseDataBase(QSqlDatabase &aDataBase, const QString &aFileName)
{
    aDataBase.close();
    QSqlDatabase::removeDatabase(aFileName);
    qDebug(dbm::dbls::logDebug()) << "Data file: " << aFileName << " Closed!" << Qt::endl;
    emit dataBaseClosed();
    return true;
}

bool dbm::dbms::DataBaseManageSol::CreateTable(QSqlDatabase &aDataBase,
                                               const QString &aTableName,
                                               const QVector<ColumnSettings> &aColumns)

{
    QSqlQuery query(aDataBase);

    QString str = "CREATE TABLE " + aTableName + " (";

    for (size_t i = 0; i < aColumns.size(); i++)
    {
        str += "    ";
        str += aColumns[i].m_columnName + "    "
                + convertTypeFieldToString((int)aColumns[i].m_type) + "     "
                + convertAttrConstToString((int)aColumns[i].m_attr) + ",";
    }

    str.chop(1);
    str += ");";

    if(!query.exec(str))
    {
        qWarning(dbm::dbls::logWarning()) <<  query.lastError().text() << '\n' << query.lastQuery();
        return false;
    }
    qDebug(dbm::dbls::logDebug()) << "Table created: " << aTableName << Qt::endl;
    emit tableCreated();
    return true;
}

bool dbm::dbms::DataBaseManageSol::DeleteTable(QSqlDatabase &aDataBase, const QString &aTableName)
{
    QSqlQuery query(aDataBase);
    QString str = "DROP TABLE " + aTableName;

    if(!query.exec(str))
    {
        qWarning(dbm::dbls::logWarning()) <<  query.lastError().text() << '\n' << query.lastQuery();
        return false;
    }
    qDebug(dbm::dbls::logDebug()) << "Table delete: " << aTableName << Qt::endl;
    emit tableDeleted();
    return true;
}

bool dbm::dbms::DataBaseManageSol::InsertRow(QSqlDatabase &aDataBase,
                                             const QString &aTableName,
                                             const QVector<QString> &aColumns,
                                             const QVector<QVariant> &aValues)
{
    if (aColumns.size() != aValues.size())
    {
        qWarning(dbm::dbls::logWarning()) <<  "Quantities and values are not equal!";
        return false;
    }

    QSqlQuery query(aDataBase);

    QString str = "INSERT INTO " + aTableName + "(";

    for (size_t i = 0; i < aColumns.size(); i++)
    {
        str += " ";
        str += aColumns[i] + ",";
    }
    str.chop(1);
    str += ") ";
    str += "   VALUES(";

    for (size_t i = 0; i < aColumns.size(); i++)
    {
        str += ":" + aColumns[i]  + ",";
    }
    str.chop(1);
    str += ")";

    query.prepare(str);

    for (size_t i = 0; i < aColumns.size(); i++)
    {
        query.bindValue(":" + aColumns[i], aValues[i]);
    }

    if(!query.exec())
    {
        qWarning(dbm::dbls::logWarning()) <<  query.lastError().text() << '\n' << query.lastQuery();
        return false;
    }
    qDebug(dbm::dbls::logDebug()) << "Insert row: " << aTableName << Qt::endl;

    return true;
}

bool dbm::dbms::DataBaseManageSol::DeleteRowById(QSqlDatabase &aDataBase,
                                                 const QString &aTableName,
                                                 quint32 aID)
{
    QSqlQuery query(aDataBase);

    QString str = "DELETE FROM " + aTableName + " WHERE id=" + QString::number(aID);

    if(!query.exec(str))
    {
        qWarning(dbm::dbls::logWarning()) <<  query.lastError().text() << '\n' << query.lastQuery();
        return false;
    }

    qDebug(dbm::dbls::logDebug()) << "Delete row by id = " + QString::number(aID) << aTableName << Qt::endl;

    return true;
}
