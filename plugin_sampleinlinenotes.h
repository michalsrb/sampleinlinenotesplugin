//
// Description: Plugin for testing InlineNoteInterface
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Library General Public
//  License version 2 as published by the Free Software Foundation.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Library General Public License for more details.
//
//  You should have received a copy of the GNU Library General Public License
//  along with this library; see the file COPYING.LIB.  If not, write to
//  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
//  Boston, MA 02110-1301, USA.

#ifndef PLUGIN_SAMPLEINLINENOTES_H
#define PLUGIN_SAMPLEINLINENOTES_H

#include <QtCore/QTimer>
#include <QtCore/QMap>

#include <KTextEditor/Application>
#include <KTextEditor/MainWindow>
#include <KTextEditor/Plugin>
#include <KXMLGUIClient>
#include <KActionMenu>
#include <KTextEditor/SessionConfigInterface>
#include <KTextEditor/Editor>

#include <ktexteditor/inlinenoteinterface.h>

#include "sampleinlinecolorbox.h"
#include "sampleinlineicon.h"
#include "sampleinlinetextnote.h"


class KHistoryComboBox;
class QTextEdit;
class QTreeWidget;

typedef QList<QVariant> VariantList;


/**
 * \brief InlineNoteProvider for test.txt
 */
class TestTxtInlineNoteProvider : public KTextEditor::InlineNoteProvider
{
    Q_OBJECT

public:
    TestTxtInlineNoteProvider();
    virtual ~TestTxtInlineNoteProvider();

    QVector<const KTextEditor::InlineNote *> inlineNotes(int line) override;

private Q_SLOTS:
    void timerTimeout();

private:
    SampleInlineTextNote m_note_a, m_note_b, m_note_c, m_note_d, m_note_e, m_note_f;
    SampleInlineTextNote m_note_counter;
    SampleInlineIcon m_note_icon;

    int m_counter = 0;
    QTimer m_timer;
};

/**
 * \brief InlineNoteProvider for test.qml
 */
class TestQmlInlineNoteProvider : public KTextEditor::InlineNoteProvider
{
    Q_OBJECT

public:
    TestQmlInlineNoteProvider();
    virtual ~TestQmlInlineNoteProvider();

    QVector<const KTextEditor::InlineNote *> inlineNotes(int line) override;

private:
    SampleInlineColorBox m_note_color;
};

/**
 * \brief InlineNoteProvider for test.cpp
 */
class TestCppInlineNoteProvider : public KTextEditor::InlineNoteProvider
{
    Q_OBJECT

public:
    TestCppInlineNoteProvider();
    virtual ~TestCppInlineNoteProvider();

    QVector<const KTextEditor::InlineNote *> inlineNotes(int line) override;

private:
    SampleInlineTextNote m_block_end_if, m_block_end_switch, m_block_end_for, m_block_end_fn, m_macro_end;
    SampleInlineTextNote m_transform_param_0, m_transform_param_1, m_transform_param_2, m_transform_param_3;
    SampleInlineTextNote m_transform_auto_type;
    SampleInlineTextNote m_lambda_return_type;
    SampleInlineTextNote m_field_size_0, m_field_size_1, m_field_size_2, m_field_size_3;
};

/**
 * \brief Assings InlineNoteProviders based on document name.
 */
class KatePluginSampleInlineNotes : public KTextEditor::Plugin
{
    Q_OBJECT

public:
    explicit KatePluginSampleInlineNotes(QObject* parent = nullptr, const VariantList& = VariantList());
    ~KatePluginSampleInlineNotes() override;

    QObject* createView(KTextEditor::MainWindow* mainWindow) override;

private Q_SLOTS:
    void documentCreated(KTextEditor::Document *document);
    void documentDeleted(KTextEditor::Document *document);

private:
    void registerProvidersToAllDocuments();
    void unregisterProvidersFromAllDocuments();
    void registerProviderToDocument(KTextEditor::Document *document);
    void watchDocument(KTextEditor::Document *document);

    QMap<KTextEditor::Document*, KTextEditor::InlineNoteProvider*> m_documentToProviderMap;

    TestTxtInlineNoteProvider m_testTxtInlineNoteProvider;
    TestQmlInlineNoteProvider m_testQmlInlineNoteProvider;
    TestCppInlineNoteProvider m_testCppInlineNoteProvider;
};

#endif
