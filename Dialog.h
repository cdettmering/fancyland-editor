#ifndef DIALOG_H
#define DIALOG_H

#include "Sprite.h"

class Dialog
{
public:
    static QList<Sprite> selectSprites();
    static QString selectDirectory();
};

#endif // DIALOG_H
