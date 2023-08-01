#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_newNeuroBot.h"
#include <QCloseEvent>
class newNeuroBot : public QMainWindow
{
    Q_OBJECT

public:
    newNeuroBot(QWidget *parent = nullptr);
    ~newNeuroBot();

private slots: 
    int predict();
    int onModelName();
    int onModelPath();
    int onPicturePath();
    int onDeviceName();
    int getModelPath();
    int getPicPath();

private:
    Ui::newNeuroBotClass ui;
protected:
    void closeEvent(QCloseEvent* event);
};
