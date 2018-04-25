#include "sampleinlinetextnote.h"


SampleInlineTextNote::SampleInlineTextNote(int column, QString text, QColor textColor, QBrush backgroundBrush, bool renderBackground, qreal cornerRadius)
    : m_column(column)
    , m_text(text)
    , m_textColor(textColor)
    , m_backgroundBrush(backgroundBrush)
    , m_renderBackground(renderBackground)
    , m_cornerRadius(cornerRadius)
{}

SampleInlineTextNote::~SampleInlineTextNote()
{}

int SampleInlineTextNote::column() const
{
    return m_column;
}

qreal SampleInlineTextNote::width(qreal height, const QFontMetricsF &fontMetrics) const
{
    return fontMetrics.boundingRect(m_text).width() + MARGIN * 2.0;
}

void SampleInlineTextNote::paint(qreal height, const QFontMetricsF &fontMetrics, const QFont &font, QPainter &painter) const
{
    qreal textWidth = width(height, fontMetrics);

    if (m_renderBackground) {
        QRectF rectangle(MARGIN / 2.0, 0, textWidth - MARGIN, height);
        painter.setPen(Qt::NoPen);
        painter.setBrush(m_backgroundBrush);
        if (m_cornerRadius > 0) {
            painter.drawRoundedRect(rectangle, m_cornerRadius, m_cornerRadius);
        } else {
            painter.drawRect(rectangle);
        }
    }

    QPen pen(Qt::SolidLine);
    pen.setColor(m_textColor);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(MARGIN, fontMetrics.ascent(), m_text);
}

void SampleInlineTextNote::setText(QString text)
{
    m_text = text;
}
