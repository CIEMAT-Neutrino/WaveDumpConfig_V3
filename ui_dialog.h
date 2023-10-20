/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(817, 515);
        plainTextEdit = new QPlainTextEdit(Dialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 20, 741, 411));
        plainTextEdit->setReadOnly(true);
        plainTextEdit->setBackgroundVisible(false);
        plainTextEdit->setCenterOnScroll(false);
        plainTextEdit->setPlaceholderText(QString::fromUtf8(""));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(680, 450, 93, 28));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("Dialog", "# ----------------------------------------------------------------\n"
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
        pushButton->setText(QCoreApplication::translate("Dialog", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
