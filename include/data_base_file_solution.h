#ifndef DATA_BASE_FILE_SOLUTION_H
#define DATA_BASE_FILE_SOLUTION_H

#include "data_base_common.h"

namespace dbm
{
    namespace dbfs
    {
        class DataBaseFileSol : public QObject
        {
            Q_OBJECT
        public:
            DataBaseFileSol();
            ~DataBaseFileSol();
            bool CreateFileBD(QSqlDatabase &aDataBase,
                              const QString &aFileName,
                              const QString &aDBType,
                              const QString &aHostName,
                              quint32 aPort,
                              const QString &aUserName,
                              const QString &aPassWord);

            bool DeleteFileBD(const QString &aFileName);
            bool CopyFileBD(const QString &aSrcFIle, const QString &aDstFile);
        signals:
            void fileCreated();
            void fileDeleted();
            void fileCopyed();
        };
    }
}

#endif // DATA_BASE_FILE_SOLUTION_H
