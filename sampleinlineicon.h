#ifndef SAMPLEINLINEICON_H
#define SAMPLEINLINEICON_H

#include <QIcon>
#include <QFont>
#include <QPainter>

#include <KTextEditor/InlineNoteInterface>


class SampleInlineIcon : public KTextEditor::InlineNote
{
public:
    SampleInlineIcon(int column, QIcon icon);
    virtual ~SampleInlineIcon();

    int column() const override;
    qreal width(qreal height, const QFontMetricsF &fontMetrics) const override;
    void paint(qreal height, const QFontMetricsF &fontMetrics, const QFont &font, QPainter &painter) const override;

private:
    int m_column;
    QIcon m_icon;
};

#endif // SAMPLEINLINEICON_H
