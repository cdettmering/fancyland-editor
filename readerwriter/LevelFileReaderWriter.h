#ifndef LEVELREADERWRITER_H
#define LEVELREADERWRITER_H

#include "file/LevelFile.h"
#include "ReaderWriter.h"

class LevelFileReaderWriter : public ReaderWriter<LevelFile>
{
public:
    LevelFileReaderWriter();
    ~LevelFileReaderWriter();
    bool read(const QString &file, LevelFile &object) const;
    bool write(const QString &file, const LevelFile &object) const;
    bool createDefaultFile(const QString &path) const;
    bool createDirectoryStructure(const QString &path, const QString &levelName) const;
};
#endif // LEVELREADERWRITER_H
