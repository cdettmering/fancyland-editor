#ifndef ENEMYMAPFILEREADERWRITER_H
#define ENEMYMAPFILEREADERWRITER_H

#include "ReaderWriter.h"
#include "../file/EnemyMapFile.h"

class EnemyMapFileReaderWriter : public ReaderWriter<EnemyMapFile>
{
public:
    EnemyMapFileReaderWriter();
    ~EnemyMapFileReaderWriter();
    bool read(const QString &file, EnemyMapFile &object) const;
    bool write(const QString &file, const EnemyMapFile &object) const;
    bool createDefaultFile(const QString &path) const;
};

#endif // ENEMYMAPFILEREADERWRITER_H
