#ifndef DATA_BASE_REQUEST_SOLUTION_H
#define DATA_BASE_REQUEST_SOLUTION_H

#include "data_base_common.h"

namespace dbm
{
    namespace dbrs
    {
        class DataBaseRequestSol : public QObject
        {
            Q_OBJECT
        public:
            DataBaseRequestSol();
            ~DataBaseRequestSol();
            bool RandomQuery(QSqlDatabase &aDataBase, const QString &aQuery);

            QVector<QVariant> GetContentsOfTheColumn(QSqlDatabase &aDataBase,
                                                     const QString &aTableName,
                                                     const QString &aColumnName);
        signals:
            void querySuccessfully();
        };
    }
}

#endif // DATA_BASE_REQUEST_SOLUTION_H
