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
    ui.deliveryCombo->setCurrentIndex(0);
    ui.encryptCombo->setCurrentIndex(0);
    ui.roundsCount->setValue(1);
    ui.formatCombo->setCurrentIndex(0);
    ui.exportLine->setText("");
    ui.executeCombo->setCurrentIndex(0);
    ui.callsCombo->setCurrentIndex(0);
    ui.processLine->setText("");

}

void Mallet_GUI::on_fileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose File");
    ui.fileLine->clear();
    ui.fileLine->setText(filename);
}


void Mallet_GUI::on_deliveryCombo_currentIndexChanged()
{
    if (ui.deliveryCombo->currentIndex() == 3)
    {
        ui.httpLabel->setEnabled(true);
        ui.httpLine->setEnabled(true);
    }
    else {
        ui.httpLabel->setEnabled(false);
        ui.httpLine->setEnabled(false);
    }
}


void Mallet_GUI::on_formatCombo_currentIndexChanged() {
    if (ui.formatCombo->currentIndex() == 1)
    {
        ui.exportLabel->setEnabled(true);
        ui.exportLine->setEnabled(true);
    }
    else {
        ui.exportLabel->setEnabled(false);
        ui.exportLine->setEnabled(false);
    }
}

void Mallet_GUI::on_executeCombo_currentIndexChanged()
{
    if (ui.executeCombo->currentIndex() == 0)
    {
        ui.processLabel->setEnabled(false);
        ui.processLine->setEnabled(false);
    }
    else {
        ui.processLabel->setEnabled(true);
        ui.processLine->setEnabled(true);
    }
}

void Mallet_GUI::on_runButton_clicked()
{
    // What a beautiful way to parse user options!

    struct UserOptions sMenuOptions;
 
    sMenuOptions.sPayloadName = (ui.fileLine->text()).toStdString();
    sMenuOptions.cPlacement = (ui.deliveryCombo->currentIndex()+1);
    sMenuOptions.cAlgorithm = (ui.encryptCombo->currentIndex() + 1);
    sMenuOptions.nRounds = ui.roundsCount->value();
    sMenuOptions.cFormat = (ui.formatCombo->currentIndex() + 1);
    sMenuOptions.sExport = (ui.exportLine->text()).toStdString();
    sMenuOptions.cExecute = (ui.executeCombo->currentIndex() + 1);
    sMenuOptions.cCalls = (ui.callsCombo->currentIndex() + 1);
    sMenuOptions.sProcess = (ui.processLine->text()).toStdString();

    Mallet(sMenuOptions);

}