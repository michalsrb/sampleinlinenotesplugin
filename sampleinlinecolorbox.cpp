#include "sampleinlinecolorbox.h"


SampleInlineColorBox::SampleInlineColorBox(int column, QColor color)
    : m_column(column)
    , m_color(color)
{}

SampleInlineColorBox::~SampleInlineColorBox()
{}

int SampleInlineColorBox::column() const
{
    return m_column;
}

qreal SampleInlineColorBox::width(qreal height, const QFontMetricsF &fontMetrics) const
{
    return height;
}

void SampleInlineColorBox::paint(qreal height, const QFontMetricsF &fontMetrics, const QFont &font, QPainter &painter) const
{
    QPen pen(Qt::SolidLine);
    pen.setColor(Qt::black);
    painter.setBrush(QBrush(m_color));

    QRectF rectangle(1, 1, height - 2, height - 2);
    painter.drawRect(rectangle);
}
