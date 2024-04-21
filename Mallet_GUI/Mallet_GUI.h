#pragma once

#include <QtWidgets/QWidget>
#include "ui_Mallet_GUI.h"

class Mallet_GUI : public QWidget
{
    Q_OBJECT

public:
    Mallet_GUI(QWidget *parent = nullptr);
    ~Mallet_GUI();

private:
    Ui::Mallet_GUIClass ui;

private slots:
    void on_runButton_clicked();
    void on_quickModeButton_clicked();
    void on_fileButton_clicked();
};
