#ifndef DATA_BASE_MANAGE_SOLUTION_H
#define DATA_BASE_MANAGE_SOLUTION_H

#include "data_base_common.h"

namespace dbm
{
    namespace dbms
    {
        enum class TYPE_FIELD
        {
            INT,
            DECIMAL,
            TINYINT,
            BOOL,
            FLOAT,
            TEXT,
            VARCHAR_255,
            VARCHAR_30,
            DATE,
            TIME,
            DATETIME,
            BLOB,
            LARGEBLOB
        };
        static const char *T_F[] =
        { "INT", "DECIMAL", "TINYINT", "BOOL" , "FLOAT", "TEXT", "VARCHAR(255)", "VARCHAR(30)", "DATE", "TIME", "DATETIME", "BLOB", "LARGEBLOB" };

        enum class ATTRIBUTES_CONSTRAINTS
        {
            NO_ATTR,
            PRIMARY_KEY,
            NOT_NULL,
            DEFAULT,
            AUTO_INCREMENT,
            UNIQUE
        };
        static const char *A_C[] =
        { "", "PRIMARY KEY", "NOT NULL", "DEFAULT", "AUTO_INCREMENT", "UNIQUE" };



        struct ColumnSettings
        {
            TYPE_FIELD m_type;
            ATTRIBUTES_CONSTRAINTS m_attr;
            QString m_columnName;
        };



        class DataBaseManageSol : public QObject
        {
            Q_OBJECT
        public:
            DataBaseManageSol();
            ~DataBaseManageSol();
            bool OpenDataBase(QSqlDatabase &aDataBase,
                              const QString &aFileName,
                              const QString &aDBType,
                              const QString &aHostName,
                              quint32 aPort,
                              const QString &aUserName,
                              const QString &aPassword);

            bool CloseDataBase(QSqlDatabase &aDataBase, const QString &aFileName);
            bool CreateTable(QSqlDatabase &aDataBase,
                             const QString &aTableName,
                             QVector<ColumnSettings> &aColumns);
            bool DeleteTable();
            bool CreateRow();
            bool DeleteRow();
        signals:
            void dataBaseOpened();
            void dataBaseClosed();
            void tableCreated();
            void tableDeleted();
        };
    }
}

#endif // DATA_BASE_MANAGE_SOLUTION_H
