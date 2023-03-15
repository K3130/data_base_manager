#include "../include/data_base_file_solution.h"

dbm::dbfs::DataBaseFileSol::DataBaseFileSol()
{
    //set logger
    qInstallMessageHandler(dbm::dbls::messageHandler);
}

dbm::dbfs::DataBaseFileSol::~DataBaseFileSol()
{

}

bool dbm::dbfs::DataBaseFileSol::CreateFileBD(QSqlDatabase &aDataBase,
                                              const QString &aFileName,
                                              const QString &aDBType,
                                              const QString &aHostName,
                                              quint32 aPort,
                                              const QString &aUserName,
                                              const QString &aPassword)
{
    aDataBase = QSqlDatabase::addDatabase(aDBType, "...");
    aDataBase.setDatabaseName(aFileName);
    aDataBase.setHostName(aHostName);
    aDataBase.setPort(aPort);
    aDataBase.setUserName(aUserName);
    aDataBase.setPassword(aPassword);
    if( !aDataBase.open() )
    {
        qWarning(dbm::dbls::logWarning()) << aDataBase.lastError().text();
        return false;
    }
    aDataBase = QSqlDatabase();
    aDataBase.close();
    QSqlDatabase::removeDatabase(aFileName);
    qDebug(dbm::dbls::logDebug()) << "File: " << aFileName << " Created!" << Qt::endl;
    emit fileCreated();
    return true;
}

bool dbm::dbfs::DataBaseFileSol::DeleteFileBD(const QString &aFileName)
{
    QFile file (aFileName);
    if ( !file.remove() )
    {
        qWarning(dbm::dbls::logWarning()) << file.errorString();
        return false;
    }
    qDebug(dbm::dbls::logDebug()) << "File: " << aFileName << " Deleted!" << Qt::endl;
    emit fileDeleted();
    return true;
}

bool dbm::dbfs::DataBaseFileSol::CopyFileBD(const QString &aSrcFile, const QString &aDstFile)
{
    QFile file;
    if( !file.copy(aSrcFile, aDstFile))
    {
        qWarning(dbm::dbls::logWarning()) << file.errorString();
        return false;
    }
    qDebug(dbm::dbls::logDebug()) << "File: " << aSrcFile << " copy to: " << aDstFile << Qt::endl;
    emit fileCopyed();
    return true;
}
