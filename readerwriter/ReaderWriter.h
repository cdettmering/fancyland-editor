#ifndef READERWRITER_H
#define READERWRITER_H

#include <QString>

template <class T>
class ReaderWriter
{
public:
    ReaderWriter() {}
    virtual ~ReaderWriter() {}
    virtual bool read(const QString &file, T &object) const = 0;
    virtual bool write(const QString &file, const T &object) const = 0;
    virtual bool createDefaultFile(const QString &path) const = 0;
};
#endif // READERWRITER_H
