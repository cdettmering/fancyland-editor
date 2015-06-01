#ifndef TERRAINFILEREADERWRITER_H
#define TERRAINFILEREADERWRITER_H

#include "ReaderWriter.h"
#include "file/TerrainFile.h"

class TerrainFileReaderWriter : public ReaderWriter<TerrainFile>
{
public:
    TerrainFileReaderWriter();
    ~TerrainFileReaderWriter();
    bool read(const QString &file, TerrainFile &object) const;
    bool write(const QString &file, const TerrainFile &object) const;
    bool createDefaultFile(const QString &path) const;
};
#endif // TERRAINFILEREADERWRITER_H
