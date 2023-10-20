#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QProcess>
#include<QString>
#include<QDebug>
#include <QFileDialog>
#include "wdconfigclass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    WDConfigClass::GlobalParameters SaveGlobalParametersFromForm();
    bool LoadGlobalParamatersToForm(WDConfigClass::GlobalParameters MyGlobalsToForm);

    QVector<WDConfigClass::ChannelParameters> SaveChannelParametersFromForm();
    bool LoadChannelParamatersToForm(QVector<WDConfigClass::ChannelParameters> MyChannelParamToForm);

    WDConfigClass::TriggerMask SaveTriggerMaskFromForm();
    bool LoadTriggerMaskToForm(WDConfigClass::TriggerMask MyTriggerMaskToForm);

    bool ReadConfigParametersFile();

private slots:
    void on_pushButtonHelp_clicked();

    void on_groupBox_12_clicked();

    void on_pushButton_clicked();

    void on_pushButtonSaveConfig_clicked();

    void on_pushButtonLoadConfig_clicked();

    void on_radioButton_CoinCh0_toggled(bool checked);

    void on_radioButton_CoinCh1_toggled(bool checked);

    void on_radioButton_CoinCh2_toggled(bool checked);

    void on_radioButton_CoinCh3_toggled(bool checked);

    void on_radioButton_CoinCh4_toggled(bool checked);

    void on_radioButton_CoinCh5_toggled(bool checked);

    void on_radioButton_CoinCh6_toggled(bool checked);

    void on_radioButton_CoinCh7_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    WDConfigClass * MyWDConfigClass;
    QString PathWaveDumpConfig = "/etc/wavedump/WaveDumpConfig.txt";
    //QString PathWaveDumpConfig = "/home/lab/Documentos/wavedump-3.10.0/Setup/WaveDumpConfig.txt";
    QString ConfigFileName = "ConfigParameters.TXT";
};
#endif // MAINWINDOW_H
