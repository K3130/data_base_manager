#ifndef DATA_BASE_LOG_SOLUTION_H
#define DATA_BASE_LOG_SOLUTION_H

#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QLoggingCategory>

namespace dbm
{
    namespace dbls
    {
        Q_DECLARE_LOGGING_CATEGORY(logDebug)
        Q_DECLARE_LOGGING_CATEGORY(logInfo)
        Q_DECLARE_LOGGING_CATEGORY(logWarning)
        Q_DECLARE_LOGGING_CATEGORY(logCritical)

        void messageHandler(QtMsgType aType,
                            const QMessageLogContext &aContext,
                            const QString &aMsg);
    }
}

#endif // DATA_BASE_LOG_SOLUTION_H
