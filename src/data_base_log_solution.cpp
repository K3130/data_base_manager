#include "include/data_base_log_solution.h"

namespace dbm
{
    namespace dbls
    {
        Q_LOGGING_CATEGORY(logDebug,    "Debug")
        Q_LOGGING_CATEGORY(logInfo,     "Info")
        Q_LOGGING_CATEGORY(logWarning,  "Warning")
        Q_LOGGING_CATEGORY(logCritical, "Critical")

        void messageHandler(QtMsgType aType, const QMessageLogContext &aContext, const QString &aMsg)
        {
            QFile logFile(QDir::toNativeSeparators(QDir::currentPath() + "/DB_log.txt"));
            logFile.open(QFile::Append | QFile::Text);
            QTextStream out(&logFile);
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
            switch (aType)
            {
                case QtInfoMsg:     out << "INF "; break;
                case QtDebugMsg:    out << "DBG "; break;
                case QtWarningMsg:  out << "WRN "; break;
                case QtCriticalMsg: out << "CRT "; break;
                case QtFatalMsg:    out << "FTL "; break;
            }

            out << aContext.category << ": " << aMsg << Qt::endl;
            out.flush();
        }
    }
}
