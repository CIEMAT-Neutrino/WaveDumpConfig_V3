/********************************************************************************
** Form generated from reading UI file 'helpwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPWINDOW_H
#define UI_HELPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_HelpWindow
{
public:
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *HelpWindow)
    {
        if (HelpWindow->objectName().isEmpty())
            HelpWindow->setObjectName(QString::fromUtf8("HelpWindow"));
        HelpWindow->resize(807, 458);
        plainTextEdit = new QPlainTextEdit(HelpWindow);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 20, 741, 411));
        plainTextEdit->setReadOnly(true);
        plainTextEdit->setBackgroundVisible(false);
        plainTextEdit->setCenterOnScroll(false);
        plainTextEdit->setPlaceholderText(QString::fromUtf8(""));

        retranslateUi(HelpWindow);

        QMetaObject::connectSlotsByName(HelpWindow);
    } // setupUi

    void retranslateUi(QDialog *HelpWindow)
    {
        HelpWindow->setWindowTitle(QCoreApplication::translate("HelpWindow", "Help", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("HelpWindow", "# ----------------------------------------------------------------\n"
"# Settings common to all channels\n"
"# ----------------------------------------------------------------\n"
"# RECORD_LENGTH = number of samples in the acquisition window\n"
"# POST_TRIGGER: post trigger size in percent of the whole acquisition window\n"
"#PULSE_POLARITY: input signal polarity.\n"
"# EXTERNAL_TRIGGER: external trigger input settings. When enabled, the ext. trg. can be either  propagated (ACQUISITION_AND_TRGOUT) or not (ACQUISITION_ONLY) through the TRGOUT.\n"
"# FPIO_LEVEL: type of the front panel I/O LEMO connectors \n"
"# OUTPUT_FILE_FORMAT: output file can be either ASCII (column of decimal numbers) or binary (2 bytes per sample, except for Mod 721 and Mod 731 that is 1 byte per sample).\n"
"# OUTPUT_FILE_HEADER: if enabled, the header is included in the output file data.\n"
"# TEST_PATTERN: if enabled, data from ADC are replaced by test pattern (triangular wave)\n"
"\n"
"# -----------------------------------------------"
                        "-----------------\n"
"# Individual Settings \n"
"# ----------------------------------------------------------------\n"
"# ENABLE_INPUT: enable/disable one channel.\n"
"#BASELINE_LEVEL: baseline position in percent of the Full Scale. \n"
"# POSITIVE PULSE POLARITY (Full Scale = from 0 to + Vpp)\n"
" 0: analog input dynamic range = from 0 to +Vpp \n"
" 50: analog input dynamic range = from +Vpp/2 to +Vpp \n"
"100: analog input dynamic range = null (usually not used)*\n"
"# NEGATIVE PULSE POLARITY (Full Scale = from -Vpp to 0) \n"
" 0: analog input dynamic range = from -Vpp to 0 \n"
" 50: analog input dynamic range = from -Vpp/2 to 0 \n"
" 100: analog input dynamic range = null (usually not used)*\n"
" options: 0 to 100.\n"
"# TRIGGER_THRESHOLD: threshold for the channel auto trigger (ADC counts)\n"
" options 0 to 2^N-1 (N=Number of bit of the ADC). The threshold is relative to the baseline:\n"
" POSITIVE PULSE POLARITY: threshold = baseline + TRIGGER_THRESHOLD\n"
" NEGATIVE PULSE POLARITY: threshold = baseline -"
                        " TRIGGER_THRESHOLD\n"
"# CHANNEL_TRIGGER: channel auto trigger settings. When enabled, the ch. auto trg. can be either propagated (ACQUISITION_AND_TRGOUT) or not (ACQUISITION_ONLY) through the TRGOUT.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpWindow: public Ui_HelpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPWINDOW_H
