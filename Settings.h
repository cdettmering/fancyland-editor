#ifndef SETTINGS_H
#define SETTINGS_H

#include <QColor>

class Settings
{
public:

    static void setItemBorderColor(const QColor &color);
    static QColor getItemBorderColor();

    static void setTerrainLineColor(const QColor &color);
    static QColor getTerrainLineColor();

    static void setTerrainAnchorColor(const QColor &color);
    static QColor getTerrainAnchorColor();

private:
    static const QString COLOR_PREFIX;
    static const QString ITEM_BORDER_COLOR;
    static const QString TERRAIN_LINE_COLOR;
    static const QString TERRAIN_ANCHOR_COLOR;
};

#endif // SETTINGS_H
