#ifndef SAMPLEINLINECOLORBOX_H
#define SAMPLEINLINECOLORBOX_H

#include <QColor>
#include <QBrush>
#include <QFont>
#include <QPainter>

#include <KTextEditor/InlineNoteInterface>


class SampleInlineColorBox : public KTextEditor::InlineNote
{
public:
    SampleInlineColorBox(int column, QColor color);
    virtual ~SampleInlineColorBox();

    int column() const override;
    qreal width(qreal height, const QFontMetricsF &fontMetrics) const override;
    void paint(qreal height, const QFontMetricsF &fontMetrics, const QFont &font, QPainter &painter) const override;

private:
    int m_column;
    QColor m_color;
};

#endif // SAMPLEINLINECOLORBOX_H
