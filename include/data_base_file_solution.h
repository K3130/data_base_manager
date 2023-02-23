#ifndef DATA_BASE_FILE_SOLUTION_H
#define DATA_BASE_FILE_SOLUTION_H

#include "data_base_common.h"

namespace dbm
{
    namespace dbfs
    {
        class DataBaseFileSol
        {
        public:
            DataBaseFileSol();
            ~DataBaseFileSol();
            void CreateFileBD(const QString & aFileName);
            void DeleteFileBD(const QString & aFileName);
            void CopyFileBD(const QString & aSrc, const QString & aDst);
        private:
        };
    }
}

#endif // DATA_BASE_FILE_SOLUTION_H
