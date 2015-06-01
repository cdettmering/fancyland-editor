#ifndef LAYERFILEREADERWRITER_H
#define LAYERFILEREADERWRITER_H

#include "ReaderWriter.h"
#include "../file/LayerFile.h"

class LayerFileReaderWriter : public ReaderWriter<LayerFile>
{
public:
    LayerFileReaderWriter();
    ~LayerFileReaderWriter();
    bool read(const QString &file, LayerFile &object) const;
    bool write(const QString &file, const LayerFile &object) const;
    bool createDefaultFile(const QString &path) const;
};
#endif // LAYERFILEREADERWRITER_H
