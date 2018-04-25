#ifndef SAMPLEINLINETEXTNOTE_H
#define SAMPLEINLINETEXTNOTE_H

#include <QColor>
#include <QBrush>
#include <QFont>
#include <QPainter>

#include <KTextEditor/InlineNoteInterface>


class SampleInlineTextNote : public KTextEditor::InlineNote
{
    constexpr static qreal MARGIN = 6.0;

public:
    SampleInlineTextNote(int column, QString text, QColor textColor, QBrush backgroundBrush, bool renderBackground, qreal cornerRadius);
    virtual ~SampleInlineTextNote();

    int column() const override;
    qreal width(qreal height, const QFontMetricsF &fontMetrics) const override;
    void paint(qreal height, const QFontMetricsF &fontMetrics, const QFont &font, QPainter &painter) const override;

    void setText(QString text);

private:
    int m_column;
    QString m_text;

    QColor m_textColor;
    QBrush m_backgroundBrush;
    bool m_renderBackground;
    qreal m_cornerRadius;
};

#endif // SAMPLEINLINETEXTNOTE_H
