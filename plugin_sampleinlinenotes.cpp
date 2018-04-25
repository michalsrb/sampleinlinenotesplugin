//
// Description: Plugin for presenting InlineNoteInterface
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

#include "plugin_sampleinlinenotes.h"

#include <QFile>
#include <QFileInfo>
#include <QPainter>
#include <QFont>

#include <klocalizedstring.h>
#include <kcolorscheme.h>
#include <kpluginfactory.h>
#include <kpluginloader.h>
#include <kaboutdata.h>

#include <ktexteditor/view.h>
#include <ktexteditor/document.h>
#include <ktexteditor/editor.h>


K_PLUGIN_FACTORY_WITH_JSON (KatePluginSampleInlineNotesFactory, "sampleinlinenotes.json", registerPlugin<KatePluginSampleInlineNotes>();)


TestTxtInlineNoteProvider::TestTxtInlineNoteProvider()
    : m_note_a      (20, QString::fromUtf8("Note A"), Qt::white, QBrush(QColor(0x3a496c)), true, 4.0)
    , m_note_b      (0,  QString::fromUtf8("Note B"), Qt::white, QBrush(QColor(0x3a496c)), true, 4.0)
    , m_note_c      (48, QString::fromUtf8("Note C"), Qt::white, QBrush(QColor(0x3a496c)), true, 4.0)
    , m_note_d      (0,  QString::fromUtf8("Note D"), Qt::white, QBrush(QColor(0x3a496c)), true, 4.0)
    , m_note_e      (20, QString::fromUtf8("Note E"), Qt::white, QBrush(QColor(0x3a496c)), true, 4.0)
    , m_note_f      (40, QString::fromUtf8("Note F"), Qt::white, QBrush(QColor(0x3a496c)), true, 4.0)
    , m_note_counter(36, QString::fromUtf8("Counter"), Qt::white, QBrush(QColor(0x3a496c)), true, 4.0)
    , m_note_icon(14, QIcon::fromTheme(QStringLiteral("debug-step-into")))
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    m_timer.start(1000);
}

TestTxtInlineNoteProvider::~TestTxtInlineNoteProvider()
{}

void TestTxtInlineNoteProvider::timerTimeout()
{
    m_counter++;
    m_note_counter.setText(QString::asprintf("Counter: %d", m_counter));

    emit lineChanged(0); // 0 is the one with the counter
}

QVector<const KTextEditor::InlineNote *> TestTxtInlineNoteProvider::inlineNotes(int line)
{
    switch (line) {
        case 0: return { &m_note_a };
        case 2: return { &m_note_b };
        case 4: return { &m_note_c };
        case 6: return { &m_note_d, &m_note_e, &m_note_f };
        case 8: return { &m_note_counter };
        case 10: return { &m_note_icon };
        default: return {};
    }
}


TestQmlInlineNoteProvider::TestQmlInlineNoteProvider()
    : m_note_color(25, QColor(0x1d99f3))
{}

TestQmlInlineNoteProvider::~TestQmlInlineNoteProvider()
{}

QVector<const KTextEditor::InlineNote *> TestQmlInlineNoteProvider::inlineNotes(int line) {
    switch (line) {
        case 3: return { &m_note_color };
        default: return {};
    }
}


TestCppInlineNoteProvider::TestCppInlineNoteProvider()
    : m_block_end_if(       17, QString::fromUtf8("\u21E6 if"),                            QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_block_end_switch(    9, QString::fromUtf8("\u21E6 switch"),                        QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_block_end_for(       5, QString::fromUtf8("\u21E6 for"),                           QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_block_end_fn(        1, QString::fromUtf8("\u21E6 main"),                          QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_macro_end(           7, QString::fromUtf8("HAS_FEATURE"),                          QColor(0x60c060), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_transform_param_0(  19, QString::fromUtf8("first1: "),                             QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_transform_param_1(  30, QString::fromUtf8("last1: "),                              QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_transform_param_2(  39, QString::fromUtf8("d_first: "),                            QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_transform_param_3(  19, QString::fromUtf8("unary_op: "),                           QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_transform_auto_type(26, QString::fromUtf8("\u25C2 unsigned char"),                 QColor(0x6060c0), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_lambda_return_type( 29, QString::fromUtf8("-> unsigned char"),                     QColor(0x6060c0), QBrush(QColor(0xf0f0f0)), true, 4.0)
    , m_field_size_0(       17, QString::fromUtf8("size: 3 \u2199padding: 1"),            QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 0.0)
    , m_field_size_1(       17, QString::fromUtf8("size: 4"),                              QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 0.0)
    , m_field_size_2(       17, QString::fromUtf8("size: 2 \u2199padding: 2"),             QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 0.0)
    , m_field_size_3(       17, QString::fromUtf8("size: 4"),                              QColor(0x606060), QBrush(QColor(0xf0f0f0)), true, 0.0)
{}

TestCppInlineNoteProvider::~TestCppInlineNoteProvider()
{}

QVector<const KTextEditor::InlineNote *> TestCppInlineNoteProvider::inlineNotes(int line) {
    switch (line) {
        case 13: return { &m_block_end_if };
        case 15: return { &m_block_end_switch };
        case 16: return { &m_block_end_for };
        case 17: return { &m_macro_end };
        case 20: return { &m_transform_param_0, &m_transform_param_1, &m_transform_param_2 };
        case 21: return { &m_transform_param_3, &m_transform_auto_type, &m_lambda_return_type };
        case 24: return { &m_field_size_0 };
        case 25: return { &m_field_size_1 };
        case 26: return { &m_field_size_2 };
        case 27: return { &m_field_size_3 };
        case 29: return { &m_block_end_fn };
        default: return {};
    }
}


KatePluginSampleInlineNotes::KatePluginSampleInlineNotes(QObject* parent, const VariantList&)
    : KTextEditor::Plugin(parent)
{
    auto kateApplication = KTextEditor::Editor::instance()->application();
    connect(kateApplication, SIGNAL(documentCreated(KTextEditor::Document*)), this, SLOT(documentCreated(KTextEditor::Document*)));

    registerProvidersToAllDocuments();
}

KatePluginSampleInlineNotes::~KatePluginSampleInlineNotes()
{
    unregisterProvidersFromAllDocuments();
}

QObject* KatePluginSampleInlineNotes::createView(KTextEditor::MainWindow* mainWindow)
{
    return nullptr;
}

void KatePluginSampleInlineNotes::documentCreated(KTextEditor::Document *document)
{
    registerProviderToDocument(document);
    watchDocument(document);
}

void KatePluginSampleInlineNotes::documentDeleted(KTextEditor::Document *document)
{
    m_documentToProviderMap.remove(document);
}

void KatePluginSampleInlineNotes::registerProvidersToAllDocuments()
{
    auto kateApplication = KTextEditor::Editor::instance()->application();
    foreach (KTextEditor::Document *document, kateApplication->documents()) {
        registerProviderToDocument(document);
        watchDocument(document);
    }
}

void KatePluginSampleInlineNotes::unregisterProvidersFromAllDocuments()
{
    auto kateApplication = KTextEditor::Editor::instance()->application();
    foreach (KTextEditor::Document *document, kateApplication->documents()) {
        auto provider = m_documentToProviderMap.value(document);
        if (!provider) {
            continue;
        }
        KTextEditor::InlineNoteInterface* iface = qobject_cast<KTextEditor::InlineNoteInterface*>(document);
        if (iface) {
            iface->unregisterInlineNoteProvider(provider);
        }
    }
    m_documentToProviderMap.clear();
}

void KatePluginSampleInlineNotes::registerProviderToDocument(KTextEditor::Document *document)
{
    KTextEditor::InlineNoteInterface* iface = qobject_cast<KTextEditor::InlineNoteInterface*>(document);

    if (!iface) {
        return;
    }

    // Find which provider should be used based on the document name.
    // We are expecting to be used with files from the "samples" directory.
    KTextEditor::InlineNoteProvider* provider = nullptr;
    QString name = document->documentName();
    if (name == QStringLiteral("test.txt")) {
        provider = &m_testTxtInlineNoteProvider;
    } else if (name == QStringLiteral("test.qml")) {
        provider = &m_testQmlInlineNoteProvider;
    } else if (name == QStringLiteral("test.cpp")) {
        provider = &m_testCppInlineNoteProvider;
    } else {
        return; // Not a file from our samples.
    }

    m_documentToProviderMap.insert(document, provider);
    iface->registerInlineNoteProvider(provider);
}

void KatePluginSampleInlineNotes::watchDocument(KTextEditor::Document *document)
{
    connect(document, &KTextEditor::Document::documentNameChanged, [=]() {
        KTextEditor::InlineNoteInterface* iface = qobject_cast<KTextEditor::InlineNoteInterface*>(document);
        if (!iface) {
            return;
        }

        auto oldProvider = m_documentToProviderMap.value(document);
        if (oldProvider) {
            iface->unregisterInlineNoteProvider(oldProvider);
        }

        registerProviderToDocument(document);
    });
}


#include "plugin_sampleinlinenotes.moc"
