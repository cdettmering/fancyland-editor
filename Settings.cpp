#include "Settings.h"

#include <QSettings>

const QString Settings::COLOR_PREFIX = "colors";
const QString Settings::ITEM_BORDER_COLOR = COLOR_PREFIX + QString("itemborder");
const QString Settings::TERRAIN_LINE_COLOR = COLOR_PREFIX + QString("terrainline");
const QString Settings::TERRAIN_ANCHOR_COLOR = COLOR_PREFIX + QString("terrainanchor");

void Settings::setItemBorderColor(const QColor &color)
{
    QSettings settings;
    settings.setValue(ITEM_BORDER_COLOR, color);
}

QColor Settings::getItemBorderColor()
{
    QSettings settings;
    return settings.value(ITEM_BORDER_COLOR, QColor(Qt::black)).value<QColor>();
}

void Settings::setTerrainLineColor(const QColor &color)
{
    QSettings settings;
    settings.setValue(TERRAIN_LINE_COLOR, color);
}

QColor Settings::getTerrainLineColor()
{
    QSettings settings;
    return settings.value(TERRAIN_LINE_COLOR, QColor(Qt::black)).value<QColor>();
}

void Settings::setTerrainAnchorColor(const QColor &color)
{
    QSettings settings;
    settings.setValue(TERRAIN_ANCHOR_COLOR, color);
}

QColor Settings::getTerrainAnchorColor()
{
    QSettings settings;
    return settings.value(TERRAIN_ANCHOR_COLOR, QColor(Qt::black)).value<QColor>();
}
