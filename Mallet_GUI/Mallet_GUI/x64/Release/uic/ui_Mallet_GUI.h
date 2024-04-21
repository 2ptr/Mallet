/********************************************************************************
** Form generated from reading UI file 'Mallet_GUI.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MALLET_GUI_H
#define UI_MALLET_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mallet_GUIClass
{
public:
    QTabWidget *tabWidget;
    QWidget *CustomShellcode;
    QFormLayout *formLayout;
    QLineEdit *fileLine;
    QPushButton *fileButton;
    QPushButton *runButton;
    QGroupBox *optionsBox;
    QFormLayout *formLayout_2;
    QLabel *deliveryLabel;
    QLabel *httpLabel_2;
    QComboBox *deliveryCombo;
    QLabel *httpLabel;
    QLineEdit *httpLine;
    QLabel *encLabel_2;
    QComboBox *encryptCombo;
    QLabel *roundsLabel;
    QSpinBox *roundsCount;
    QLabel *exportLabel_2;
    QComboBox *formatCombo;
    QLabel *exportLabel;
    QLineEdit *exportLine;
    QLabel *processLabel_2;
    QComboBox *executeCombo;
    QLabel *processLabel;
    QLineEdit *processLine;
    QLabel *callsLabel;
    QComboBox *callsCombo;
    QLabel *executeLabel;
    QLabel *formatLabel;
    QLabel *encLabel;
    QLabel *label;
    QPushButton *quickModeButton;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *Mallet_GUIClass)
    {
        if (Mallet_GUIClass->objectName().isEmpty())
            Mallet_GUIClass->setObjectName("Mallet_GUIClass");
        Mallet_GUIClass->resize(663, 500);
        QIcon icon;
        icon.addFile(QString::fromUtf8("mallet_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        Mallet_GUIClass->setWindowIcon(icon);
        tabWidget = new QTabWidget(Mallet_GUIClass);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 260, 251, 121));
        CustomShellcode = new QWidget();
        CustomShellcode->setObjectName("CustomShellcode");
        formLayout = new QFormLayout(CustomShellcode);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName("formLayout");
        fileLine = new QLineEdit(CustomShellcode);
        fileLine->setObjectName("fileLine");

        formLayout->setWidget(0, QFormLayout::SpanningRole, fileLine);

        fileButton = new QPushButton(CustomShellcode);
        fileButton->setObjectName("fileButton");

        formLayout->setWidget(1, QFormLayout::FieldRole, fileButton);

        tabWidget->addTab(CustomShellcode, QString());
        runButton = new QPushButton(Mallet_GUIClass);
        runButton->setObjectName("runButton");
        runButton->setGeometry(QRect(80, 440, 131, 31));
        optionsBox = new QGroupBox(Mallet_GUIClass);
        optionsBox->setObjectName("optionsBox");
        optionsBox->setGeometry(QRect(290, 20, 361, 461));
        QFont font;
        font.setBold(false);
        optionsBox->setFont(font);
        formLayout_2 = new QFormLayout(optionsBox);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName("formLayout_2");
        deliveryLabel = new QLabel(optionsBox);
        deliveryLabel->setObjectName("deliveryLabel");
        QFont font1;
        font1.setBold(true);
        deliveryLabel->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, deliveryLabel);

        httpLabel_2 = new QLabel(optionsBox);
        httpLabel_2->setObjectName("httpLabel_2");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, httpLabel_2);

        deliveryCombo = new QComboBox(optionsBox);
        deliveryCombo->addItem(QString());
        deliveryCombo->addItem(QString());
        deliveryCombo->addItem(QString());
        deliveryCombo->addItem(QString());
        deliveryCombo->setObjectName("deliveryCombo");
        deliveryCombo->setFont(font);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, deliveryCombo);

        httpLabel = new QLabel(optionsBox);
        httpLabel->setObjectName("httpLabel");
        httpLabel->setEnabled(false);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, httpLabel);

        httpLine = new QLineEdit(optionsBox);
        httpLine->setObjectName("httpLine");
        httpLine->setEnabled(false);
        httpLine->setReadOnly(false);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, httpLine);

        encLabel_2 = new QLabel(optionsBox);
        encLabel_2->setObjectName("encLabel_2");

        formLayout_2->setWidget(5, QFormLayout::LabelRole, encLabel_2);

        encryptCombo = new QComboBox(optionsBox);
        encryptCombo->addItem(QString());
        encryptCombo->addItem(QString());
        encryptCombo->addItem(QString());
        encryptCombo->setObjectName("encryptCombo");
        encryptCombo->setFont(font);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, encryptCombo);

        roundsLabel = new QLabel(optionsBox);
        roundsLabel->setObjectName("roundsLabel");

        formLayout_2->setWidget(6, QFormLayout::LabelRole, roundsLabel);

        roundsCount = new QSpinBox(optionsBox);
        roundsCount->setObjectName("roundsCount");

        formLayout_2->setWidget(6, QFormLayout::FieldRole, roundsCount);

        exportLabel_2 = new QLabel(optionsBox);
        exportLabel_2->setObjectName("exportLabel_2");

        formLayout_2->setWidget(9, QFormLayout::LabelRole, exportLabel_2);

        formatCombo = new QComboBox(optionsBox);
        formatCombo->addItem(QString());
        formatCombo->addItem(QString());
        formatCombo->setObjectName("formatCombo");

        formLayout_2->setWidget(9, QFormLayout::FieldRole, formatCombo);

        exportLabel = new QLabel(optionsBox);
        exportLabel->setObjectName("exportLabel");
        exportLabel->setEnabled(false);

        formLayout_2->setWidget(10, QFormLayout::LabelRole, exportLabel);

        exportLine = new QLineEdit(optionsBox);
        exportLine->setObjectName("exportLine");
        exportLine->setEnabled(false);

        formLayout_2->setWidget(10, QFormLayout::FieldRole, exportLine);

        processLabel_2 = new QLabel(optionsBox);
        processLabel_2->setObjectName("processLabel_2");

        formLayout_2->setWidget(13, QFormLayout::LabelRole, processLabel_2);

        executeCombo = new QComboBox(optionsBox);
        executeCombo->addItem(QString());
        executeCombo->addItem(QString());
        executeCombo->addItem(QString());
        executeCombo->addItem(QString());
        executeCombo->setObjectName("executeCombo");
        QFont font2;
        font2.setBold(false);
        font2.setKerning(true);
        executeCombo->setFont(font2);

        formLayout_2->setWidget(13, QFormLayout::FieldRole, executeCombo);

        processLabel = new QLabel(optionsBox);
        processLabel->setObjectName("processLabel");
        processLabel->setEnabled(false);

        formLayout_2->setWidget(15, QFormLayout::LabelRole, processLabel);

        processLine = new QLineEdit(optionsBox);
        processLine->setObjectName("processLine");
        processLine->setEnabled(false);

        formLayout_2->setWidget(15, QFormLayout::FieldRole, processLine);

        callsLabel = new QLabel(optionsBox);
        callsLabel->setObjectName("callsLabel");

        formLayout_2->setWidget(14, QFormLayout::LabelRole, callsLabel);

        callsCombo = new QComboBox(optionsBox);
        callsCombo->addItem(QString());
        callsCombo->addItem(QString());
        callsCombo->addItem(QString());
        callsCombo->setObjectName("callsCombo");
        callsCombo->setFont(font2);

        formLayout_2->setWidget(14, QFormLayout::FieldRole, callsCombo);

        executeLabel = new QLabel(optionsBox);
        executeLabel->setObjectName("executeLabel");
        executeLabel->setFont(font1);

        formLayout_2->setWidget(12, QFormLayout::LabelRole, executeLabel);

        formatLabel = new QLabel(optionsBox);
        formatLabel->setObjectName("formatLabel");
        formatLabel->setFont(font1);

        formLayout_2->setWidget(8, QFormLayout::LabelRole, formatLabel);

        encLabel = new QLabel(optionsBox);
        encLabel->setObjectName("encLabel");
        encLabel->setFont(font1);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, encLabel);

        label = new QLabel(Mallet_GUIClass);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 30, 191, 151));
        label->setPixmap(QPixmap(QString::fromUtf8("mallet_splash.png")));
        label->setScaledContents(true);
        quickModeButton = new QPushButton(Mallet_GUIClass);
        quickModeButton->setObjectName("quickModeButton");
        quickModeButton->setGeometry(QRect(80, 400, 131, 31));
        label_2 = new QLabel(Mallet_GUIClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 200, 49, 16));
        label_3 = new QLabel(Mallet_GUIClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(90, 220, 121, 16));

        retranslateUi(Mallet_GUIClass);

        tabWidget->setCurrentIndex(0);
        executeCombo->setCurrentIndex(0);
        callsCombo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Mallet_GUIClass);
    } // setupUi

    void retranslateUi(QWidget *Mallet_GUIClass)
    {
        Mallet_GUIClass->setWindowTitle(QCoreApplication::translate("Mallet_GUIClass", "Mallet", nullptr));
        fileButton->setText(QCoreApplication::translate("Mallet_GUIClass", "Select File", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(CustomShellcode), QCoreApplication::translate("Mallet_GUIClass", "Shellcode File", nullptr));
        runButton->setText(QCoreApplication::translate("Mallet_GUIClass", "Generate Dropper", nullptr));
        optionsBox->setTitle(QCoreApplication::translate("Mallet_GUIClass", "Payload Options", nullptr));
        deliveryLabel->setText(QCoreApplication::translate("Mallet_GUIClass", "Delivery", nullptr));
        httpLabel_2->setText(QCoreApplication::translate("Mallet_GUIClass", "Method", nullptr));
        deliveryCombo->setItemText(0, QCoreApplication::translate("Mallet_GUIClass", "Static - .text", nullptr));
        deliveryCombo->setItemText(1, QCoreApplication::translate("Mallet_GUIClass", "Static - .data", nullptr));
        deliveryCombo->setItemText(2, QCoreApplication::translate("Mallet_GUIClass", "Static - .rsrc", nullptr));
        deliveryCombo->setItemText(3, QCoreApplication::translate("Mallet_GUIClass", "HTTP Stager", nullptr));

        httpLabel->setText(QCoreApplication::translate("Mallet_GUIClass", "HTTP Stager URL", nullptr));
        httpLine->setText(QString());
        httpLine->setPlaceholderText(QCoreApplication::translate("Mallet_GUIClass", "http://attacker.com/payload.raw", nullptr));
        encLabel_2->setText(QCoreApplication::translate("Mallet_GUIClass", "Algorithm", nullptr));
        encryptCombo->setItemText(0, QCoreApplication::translate("Mallet_GUIClass", "AES-256 (TinyAES)", nullptr));
        encryptCombo->setItemText(1, QCoreApplication::translate("Mallet_GUIClass", "RC4", nullptr));
        encryptCombo->setItemText(2, QCoreApplication::translate("Mallet_GUIClass", "XOR", nullptr));

        roundsLabel->setText(QCoreApplication::translate("Mallet_GUIClass", "Rounds", nullptr));
        exportLabel_2->setText(QCoreApplication::translate("Mallet_GUIClass", "File Format", nullptr));
        formatCombo->setItemText(0, QCoreApplication::translate("Mallet_GUIClass", ".exe", nullptr));
        formatCombo->setItemText(1, QCoreApplication::translate("Mallet_GUIClass", ".dll", nullptr));

        exportLabel->setText(QCoreApplication::translate("Mallet_GUIClass", "Export name for .dll", nullptr));
        exportLine->setText(QString());
        exportLine->setPlaceholderText(QCoreApplication::translate("Mallet_GUIClass", "EvilFunction", nullptr));
        processLabel_2->setText(QCoreApplication::translate("Mallet_GUIClass", "Method", nullptr));
        executeCombo->setItemText(0, QCoreApplication::translate("Mallet_GUIClass", "Local Thread", nullptr));
        executeCombo->setItemText(1, QCoreApplication::translate("Mallet_GUIClass", "Remote Process Injection", nullptr));
        executeCombo->setItemText(2, QCoreApplication::translate("Mallet_GUIClass", "Remote DLL Injection", nullptr));
        executeCombo->setItemText(3, QCoreApplication::translate("Mallet_GUIClass", "Remote Thread Hijack", nullptr));

        processLabel->setText(QCoreApplication::translate("Mallet_GUIClass", "Target Process", nullptr));
        processLine->setText(QString());
        processLine->setPlaceholderText(QCoreApplication::translate("Mallet_GUIClass", "notepad.exe", nullptr));
        callsLabel->setText(QCoreApplication::translate("Mallet_GUIClass", "System Calls", nullptr));
        callsCombo->setItemText(0, QCoreApplication::translate("Mallet_GUIClass", "Win32 API", nullptr));
        callsCombo->setItemText(1, QCoreApplication::translate("Mallet_GUIClass", "NT API", nullptr));
        callsCombo->setItemText(2, QCoreApplication::translate("Mallet_GUIClass", "Syscalls", nullptr));

        executeLabel->setText(QCoreApplication::translate("Mallet_GUIClass", "Execution", nullptr));
        formatLabel->setText(QCoreApplication::translate("Mallet_GUIClass", "Format", nullptr));
        encLabel->setText(QCoreApplication::translate("Mallet_GUIClass", "Encryption", nullptr));
        label->setText(QString());
        quickModeButton->setText(QCoreApplication::translate("Mallet_GUIClass", "Quick Mode", nullptr));
        label_2->setText(QCoreApplication::translate("Mallet_GUIClass", "v 0.2", nullptr));
        label_3->setText(QCoreApplication::translate("Mallet_GUIClass", "Written by twopoint", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mallet_GUIClass: public Ui_Mallet_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MALLET_GUI_H
