#include "sampleinlineicon.h"


SampleInlineIcon::SampleInlineIcon(int column, QIcon icon)
    : m_column(column)
    , m_icon(icon)
{}

SampleInlineIcon::~SampleInlineIcon()
{}

int SampleInlineIcon::column() const
{
    return m_column;
}

qreal SampleInlineIcon::width(qreal height, const QFontMetricsF &fontMetrics) const
{
    return height;
}

void SampleInlineIcon::paint(qreal height, const QFontMetricsF &fontMetrics, const QFont &font, QPainter &painter) const
{
    m_icon.paint(&painter, 0, 0, height, height);
}
