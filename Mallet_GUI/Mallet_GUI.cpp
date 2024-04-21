#include "Mallet_GUI.h"
#include "Common.h"
#include <qfiledialog.h>

Mallet_GUI::Mallet_GUI(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

Mallet_GUI::~Mallet_GUI()
{}

void Mallet_GUI::on_quickModeButton_clicked()
{
    // Quick mode preset
    ui.placementCombo->setCurrentIndex(0);
    ui.encLine->setText("1");
    ui.formatCombo->setCurrentIndex(0);
    ui.exportLine->setText("");
    ui.executeCombo->setCurrentIndex(0);
    ui.processLine->setText("");

}

void Mallet_GUI::on_fileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose File");
    ui.fileLine->clear();
    ui.fileLine->setText(filename);
}

void Mallet_GUI::on_runButton_clicked()
{
    // What a beautiful way to parse user options!

    struct UserOptions sMenuOptions;
    sMenuOptions.cPayloadMode = (ui.tabWidget->currentIndex()+1);
    if (sMenuOptions.cPayloadMode == 1)
    {
        if (ui.shellRadio->isChecked())
        {
            sMenuOptions.cTemplate = 1;
        }
        else {
            sMenuOptions.cTemplate = 2;
        }
    }
    sMenuOptions.sListenerIP = (ui.ipLine->text()).toStdString();
    sMenuOptions.sListenerPort = (ui.portLine->text()).toStdString();
    sMenuOptions.sPayloadName = (ui.fileLine->text()).toStdString();
    sMenuOptions.cPlacement = (ui.placementCombo->currentIndex()+1);
    sMenuOptions.sCipher = (ui.encLine->text()).toStdString();
    sMenuOptions.nRounds = strlen(sMenuOptions.sCipher.data());
    sMenuOptions.cFormat = (ui.formatCombo->currentIndex() + 1);
    sMenuOptions.sExport = (ui.exportLine->text()).toStdString();
    sMenuOptions.cExecute = (ui.executeCombo->currentIndex() + 1);
    sMenuOptions.sProcess = (ui.processLine->text()).toStdString();

    Mallet(sMenuOptions);

}