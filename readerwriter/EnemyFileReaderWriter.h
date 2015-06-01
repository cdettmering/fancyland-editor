#ifndef ENEMYFILEREADERWRITER_H
#define ENEMYFILEREADERWRITER_H

#include "ReaderWriter.h"
#include "../file/EnemyFile.h"

class EnemyFileReaderWriter : public ReaderWriter<EnemyFile>
{
public:
    EnemyFileReaderWriter();
    ~EnemyFileReaderWriter();
    bool read(const QString &file, EnemyFile &object) const;
    bool write(const QString &file, const EnemyFile &object) const;
    bool createDefaultFile(const QString &path) const;
};
#endif // ENEMYFILEREADERWRITER_H
