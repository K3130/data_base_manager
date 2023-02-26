#include "../include/data_base_file_solution.h"

dbm::dbfs::DataBaseFileSol::DataBaseFileSol()
{
    //set logger
    qInstallMessageHandler(dbm::dbls::messageHandler);
}

dbm::dbfs::DataBaseFileSol::~DataBaseFileSol()
{

}

bool dbm::dbfs::DataBaseFileSol::CreateFileBD(const QString &aFileName, const QString &aDBType)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(aDBType);
    db.setDatabaseName(aFileName);
    if( !db.open() )
    {
        qWarning(dbm::dbls::logWarning()) << db.lastError().text();
        return false;
    }
    db.close();
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
