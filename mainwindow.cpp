#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::ReadConfigParametersFile();
    MyWDConfigClass = new WDConfigClass;
    MyWDConfigClass->ReadGlobalFromFile(PathWaveDumpConfig);
    MainWindow::LoadGlobalParamatersToForm(MyWDConfigClass->ReadGlobalParameters());
    MyWDConfigClass->ReadChannelsFromFile(PathWaveDumpConfig);
    MainWindow::LoadChannelParamatersToForm(MyWDConfigClass->ReadChannelParameters());

    MyWDConfigClass->ReadTriggerMaskFromFile(PathWaveDumpConfig);
    MainWindow::LoadTriggerMaskToForm(MyWDConfigClass->ReadTriggerMaskParameters());
}

MainWindow::~MainWindow()
{
    delete ui;
}

WDConfigClass::GlobalParameters MainWindow::SaveGlobalParametersFromForm()
{
    WDConfigClass::GlobalParameters TempGlobal;

    TempGlobal.CommDevice = ui->comboBoxCommDevice->currentIndex();
    TempGlobal.RecordLength = ui->spinBoxRecordLength->value();
    TempGlobal.PostTrigger = ui->spinBoxPostTrigger->value();
    TempGlobal.PulsePolarity=ui->comboBoxPulsePolarity->currentIndex();
    TempGlobal.ExternalTrigger = (WDConfigClass::TriggerType)ui->comboBoxExternalTrigger->currentIndex();
    TempGlobal.FPIO_Level = ui->comboBoxFPIO_Level->currentIndex();
    TempGlobal.OutputFileFormat = ui->comboBoxOutputFileFormat->currentIndex();
    TempGlobal.OutputHeader = ui->comboBoxFileHeader->currentIndex();
    TempGlobal.TestPattern = ui->comboBoxTestPattern->currentIndex();


    return TempGlobal;
}

bool MainWindow::LoadGlobalParamatersToForm(WDConfigClass::GlobalParameters MyGlobalsToForm)
{
    ui->comboBoxCommDevice->setCurrentIndex(MyGlobalsToForm.CommDevice);
    ui->spinBoxRecordLength->setValue(MyGlobalsToForm.RecordLength);
    ui->spinBoxPostTrigger->setValue(MyGlobalsToForm.PostTrigger);
    ui->comboBoxPulsePolarity->setCurrentIndex(MyGlobalsToForm.PulsePolarity);
    ui->comboBoxExternalTrigger->setCurrentIndex(MyGlobalsToForm.ExternalTrigger);
    ui->comboBoxFPIO_Level->setCurrentIndex(MyGlobalsToForm.FPIO_Level);
    ui->comboBoxOutputFileFormat->setCurrentIndex(MyGlobalsToForm.OutputFileFormat);
    ui->comboBoxFileHeader->setCurrentIndex(MyGlobalsToForm.OutputHeader);
    ui->comboBoxTestPattern->setCurrentIndex(MyGlobalsToForm.TestPattern);


    return true;
}

QVector<WDConfigClass::ChannelParameters> MainWindow::SaveChannelParametersFromForm()
{
    QVector<WDConfigClass::ChannelParameters> TempChannelParametersVector;
    WDConfigClass::ChannelParameters TempChannelParam;

    TempChannelParam.Enabled = ui->radioButtonCh0Enable->isChecked();
    TempChannelParam.BaselineLevel = ui->spinBoxBaselineCh0->value();
    TempChannelParam.Threshold=ui->spinBoxThresholdCh0->value();
    TempChannelParam.ChannelTrigger=(WDConfigClass::TriggerType)ui->comboBoxExternalTriggerCh0->currentIndex();

    TempChannelParametersVector.append(TempChannelParam);

    TempChannelParam.Enabled = ui->radioButtonCh1Enable->isChecked();
    TempChannelParam.BaselineLevel = ui->spinBoxBaselineCh1->value();
    TempChannelParam.Threshold=ui->spinBoxThresholdCh1->value();
    TempChannelParam.ChannelTrigger=(WDConfigClass::TriggerType)ui->comboBoxExternalTriggerCh1->currentIndex();

    TempChannelParametersVector.append(TempChannelParam);

    TempChannelParam.Enabled = ui->radioButtonCh2Enable->isChecked();
    TempChannelParam.BaselineLevel = ui->spinBoxBaselineCh2->value();
    TempChannelParam.Threshold=ui->spinBoxThresholdCh2->value();
    TempChannelParam.ChannelTrigger=(WDConfigClass::TriggerType)ui->comboBoxExternalTriggerCh2->currentIndex();


    TempChannelParametersVector.append(TempChannelParam);

    TempChannelParam.Enabled = ui->radioButtonCh3Enable->isChecked();
    TempChannelParam.BaselineLevel = ui->spinBoxBaselineCh3->value();
    TempChannelParam.Threshold=ui->spinBoxThresholdCh3->value();
    TempChannelParam.ChannelTrigger=(WDConfigClass::TriggerType)ui->comboBoxExternalTriggerCh3->currentIndex();

    TempChannelParametersVector.append(TempChannelParam);

    TempChannelParam.Enabled = ui->radioButtonCh4Enable->isChecked();
    TempChannelParam.BaselineLevel = ui->spinBoxBaselineCh4->value();
    TempChannelParam.Threshold=ui->spinBoxThresholdCh4->value();
    TempChannelParam.ChannelTrigger=(WDConfigClass::TriggerType)ui->comboBoxExternalTriggerCh4->currentIndex();

    TempChannelParametersVector.append(TempChannelParam);

    TempChannelParam.Enabled = ui->radioButtonCh5Enable->isChecked();
    TempChannelParam.BaselineLevel = ui->spinBoxBaselineCh5->value();
    TempChannelParam.Threshold=ui->spinBoxThresholdCh5->value();
    TempChannelParam.ChannelTrigger=(WDConfigClass::TriggerType)ui->comboBoxExternalTriggerCh5->currentIndex();

    TempChannelParametersVector.append(TempChannelParam);

    TempChannelParam.Enabled = ui->radioButtonCh6Enable->isChecked();
    TempChannelParam.BaselineLevel = ui->spinBoxBaselineCh6->value();
    TempChannelParam.Threshold=ui->spinBoxThresholdCh6->value();
    TempChannelParam.ChannelTrigger=(WDConfigClass::TriggerType)ui->comboBoxExternalTriggerCh6->currentIndex();

    TempChannelParametersVector.append(TempChannelParam);

    TempChannelParam.Enabled = ui->radioButtonCh7Enable->isChecked();
    TempChannelParam.BaselineLevel = ui->spinBoxBaselineCh7->value();
    TempChannelParam.Threshold=ui->spinBoxThresholdCh7->value();
    TempChannelParam.ChannelTrigger=(WDConfigClass::TriggerType)ui->comboBoxExternalTriggerCh7->currentIndex();

    TempChannelParametersVector.append(TempChannelParam);

    return TempChannelParametersVector;
}

bool MainWindow::LoadChannelParamatersToForm(QVector<WDConfigClass::ChannelParameters> MyChannelParamToForm)
{
    ui->radioButtonCh0Enable->setChecked(MyChannelParamToForm[0].Enabled);
    ui->spinBoxBaselineCh0->setValue(MyChannelParamToForm[0].BaselineLevel);
    ui->spinBoxThresholdCh0->setValue(MyChannelParamToForm[0].Threshold);
    ui->comboBoxExternalTriggerCh0->setCurrentIndex(MyChannelParamToForm[0].ChannelTrigger);

    ui->radioButtonCh1Enable->setChecked(MyChannelParamToForm[1].Enabled);
    ui->spinBoxBaselineCh1->setValue(MyChannelParamToForm[1].BaselineLevel);
    ui->spinBoxThresholdCh1->setValue(MyChannelParamToForm[1].Threshold);
    ui->comboBoxExternalTriggerCh1->setCurrentIndex(MyChannelParamToForm[1].ChannelTrigger);

    ui->radioButtonCh2Enable->setChecked(MyChannelParamToForm[2].Enabled);
    ui->spinBoxBaselineCh2->setValue(MyChannelParamToForm[2].BaselineLevel);
    ui->spinBoxThresholdCh2->setValue(MyChannelParamToForm[2].Threshold);
    ui->comboBoxExternalTriggerCh2->setCurrentIndex(MyChannelParamToForm[2].ChannelTrigger);

    ui->radioButtonCh3Enable->setChecked(MyChannelParamToForm[3].Enabled);
    ui->spinBoxBaselineCh3->setValue(MyChannelParamToForm[3].BaselineLevel);
    ui->spinBoxThresholdCh3->setValue(MyChannelParamToForm[3].Threshold);
    ui->comboBoxExternalTriggerCh3->setCurrentIndex(MyChannelParamToForm[3].ChannelTrigger);

    ui->radioButtonCh4Enable->setChecked(MyChannelParamToForm[4].Enabled);
    ui->spinBoxBaselineCh4->setValue(MyChannelParamToForm[4].BaselineLevel);
    ui->spinBoxThresholdCh4->setValue(MyChannelParamToForm[4].Threshold);
    ui->comboBoxExternalTriggerCh4->setCurrentIndex(MyChannelParamToForm[4].ChannelTrigger);

    ui->radioButtonCh5Enable->setChecked(MyChannelParamToForm[5].Enabled);
    ui->spinBoxBaselineCh5->setValue(MyChannelParamToForm[5].BaselineLevel);
    ui->spinBoxThresholdCh5->setValue(MyChannelParamToForm[5].Threshold);
    ui->comboBoxExternalTriggerCh5->setCurrentIndex(MyChannelParamToForm[5].ChannelTrigger);

    ui->radioButtonCh6Enable->setChecked(MyChannelParamToForm[6].Enabled);
    ui->spinBoxBaselineCh6->setValue(MyChannelParamToForm[6].BaselineLevel);
    ui->spinBoxThresholdCh6->setValue(MyChannelParamToForm[6].Threshold);
    ui->comboBoxExternalTriggerCh6->setCurrentIndex(MyChannelParamToForm[6].ChannelTrigger);

    ui->radioButtonCh7Enable->setChecked(MyChannelParamToForm[7].Enabled);
    ui->spinBoxBaselineCh7->setValue(MyChannelParamToForm[7].BaselineLevel);
    ui->spinBoxThresholdCh7->setValue(MyChannelParamToForm[7].Threshold);
    ui->comboBoxExternalTriggerCh7->setCurrentIndex(MyChannelParamToForm[7].ChannelTrigger);


    return true;
}

WDConfigClass::TriggerMask MainWindow::SaveTriggerMaskFromForm()
{
    WDConfigClass::TriggerMask TempTriggerMask;
    TempTriggerMask.Ch0 = ui->radioButton_CoinCh0->isChecked();
    TempTriggerMask.Ch1 = ui->radioButton_CoinCh1->isChecked();
    TempTriggerMask.Ch2 = ui->radioButton_CoinCh2->isChecked();
    TempTriggerMask.Ch3 = ui->radioButton_CoinCh3->isChecked();
    TempTriggerMask.Ch4 = ui->radioButton_CoinCh4->isChecked();
    TempTriggerMask.Ch5 = ui->radioButton_CoinCh5->isChecked();
    TempTriggerMask.Ch6 = ui->radioButton_CoinCh6->isChecked();
    TempTriggerMask.Ch7 = ui->radioButton_CoinCh7->isChecked();

    return TempTriggerMask;
}

bool MainWindow::LoadTriggerMaskToForm(WDConfigClass::TriggerMask MyTriggerMaskToForm)
{
    ui->radioButton_CoinCh0->setChecked(MyTriggerMaskToForm.Ch0);
    ui->radioButton_CoinCh1->setChecked(MyTriggerMaskToForm.Ch1);
    ui->radioButton_CoinCh2->setChecked(MyTriggerMaskToForm.Ch2);
    ui->radioButton_CoinCh3->setChecked(MyTriggerMaskToForm.Ch3);
    ui->radioButton_CoinCh4->setChecked(MyTriggerMaskToForm.Ch4);
    ui->radioButton_CoinCh5->setChecked(MyTriggerMaskToForm.Ch5);
    ui->radioButton_CoinCh6->setChecked(MyTriggerMaskToForm.Ch6);
    ui->radioButton_CoinCh7->setChecked(MyTriggerMaskToForm.Ch7);

    return true;

}

bool MainWindow::ReadConfigParametersFile()
{
    QString TempString;


//Abrimos el fichero y leemos línea a línes
    QFile file(ConfigFileName);


    if (!file.open(QIODevice::ReadWrite))
        QMessageBox::information(nullptr,"info",file.errorString() + " For Reading WaveDump File Values");
    else
    {
        QTextStream stream(&file);
        QString line;
        //int endl;

        do {
            line = stream.readLine();
        // Parseamos la tensión del canal buscando la etiqueta correspondiente
            if (line.contains("#")){

                //Do Nothing
            }
            else{

                  if (line.contains("PathWaveDumpConfig"))
                    {

                      TempString = line.remove("PathWaveDumpConfig ");
                      MainWindow::PathWaveDumpConfig = TempString;
                    }

                }//else
          } while (!line.isNull());
          file.close();
    }

return true;

    return true;
}


void MainWindow::on_pushButtonHelp_clicked()
{
 HelpWindow HelpWin;
 HelpWin.exec();
}

void MainWindow::on_groupBox_12_clicked()
{ 

}


void MainWindow::on_pushButton_clicked()
{
    //We first save the screen configuration to File

    MyWDConfigClass->SaveGlobalParameters(MainWindow::SaveGlobalParametersFromForm());
    MyWDConfigClass->SaveGlobalToFile(PathWaveDumpConfig);

    MyWDConfigClass->SaveTriggerMaskParameters(MainWindow::SaveTriggerMaskFromForm());
    MyWDConfigClass->SaveTriggerMaskToFile(PathWaveDumpConfig);

    MyWDConfigClass->SaveChannelParameters(MainWindow::SaveChannelParametersFromForm());
    MyWDConfigClass->SaveChannelsToFile(PathWaveDumpConfig);

    //////////////////////////////////////////////////////////////////

    //QString WaveDumpPath = "C:\\Users\\Sergio\\Desktop\\Teletrabajo\\QtProjects\\WaveDump\\bin";
    QString WaveDumpPath = "WaveDump\\Release";
    MyWDConfigClass->ExecuteWaveDump(WaveDumpPath);

}

void MainWindow::on_pushButtonSaveConfig_clicked()
{
    MyWDConfigClass->SaveGlobalParameters(MainWindow::SaveGlobalParametersFromForm());
    MyWDConfigClass->SaveGlobalToFile(PathWaveDumpConfig);

    MyWDConfigClass->SaveTriggerMaskParameters(MainWindow::SaveTriggerMaskFromForm());
    MyWDConfigClass->SaveTriggerMaskToFile(PathWaveDumpConfig);

    MyWDConfigClass->SaveChannelParameters(MainWindow::SaveChannelParametersFromForm());
    MyWDConfigClass->SaveChannelsToFile(PathWaveDumpConfig);


}

void MainWindow::on_pushButtonLoadConfig_clicked()
{
    MyWDConfigClass->ReadGlobalFromFile(PathWaveDumpConfig);
    MainWindow::LoadGlobalParamatersToForm(MyWDConfigClass->ReadGlobalParameters());
    MyWDConfigClass->ReadChannelsFromFile(PathWaveDumpConfig);
    MainWindow::LoadChannelParamatersToForm(MyWDConfigClass->ReadChannelParameters());

    MyWDConfigClass->ReadTriggerMaskFromFile(PathWaveDumpConfig);
    MainWindow::LoadTriggerMaskToForm(MyWDConfigClass->ReadTriggerMaskParameters());
}

void MainWindow::on_radioButton_CoinCh0_toggled(bool checked)
{
   if (checked){
        ui->radioButtonCh0Enable->setChecked(checked);
        ui->comboBoxExternalTriggerCh0->setCurrentIndex(WDConfigClass::TriggerType::ACQUISITION);
   }
}

void MainWindow::on_radioButton_CoinCh1_toggled(bool checked)
{
    if (checked){
         ui->radioButtonCh1Enable->setChecked(checked);
         ui->comboBoxExternalTriggerCh1->setCurrentIndex(WDConfigClass::TriggerType::ACQUISITION);
    }
}

void MainWindow::on_radioButton_CoinCh2_toggled(bool checked)
{
    if (checked){
         ui->radioButtonCh2Enable->setChecked(checked);
         ui->comboBoxExternalTriggerCh2->setCurrentIndex(WDConfigClass::TriggerType::ACQUISITION);
    }
}

void MainWindow::on_radioButton_CoinCh3_toggled(bool checked)
{
    if (checked){
         ui->radioButtonCh3Enable->setChecked(checked);
         ui->comboBoxExternalTriggerCh3->setCurrentIndex(WDConfigClass::TriggerType::ACQUISITION);
    }
}

void MainWindow::on_radioButton_CoinCh4_toggled(bool checked)
{
    if (checked){
         ui->radioButtonCh4Enable->setChecked(checked);
         ui->comboBoxExternalTriggerCh4->setCurrentIndex(WDConfigClass::TriggerType::ACQUISITION);
    }
}

void MainWindow::on_radioButton_CoinCh5_toggled(bool checked)
{
    if (checked){
         ui->radioButtonCh5Enable->setChecked(checked);
         ui->comboBoxExternalTriggerCh5->setCurrentIndex(WDConfigClass::TriggerType::ACQUISITION);
    }
}

void MainWindow::on_radioButton_CoinCh6_toggled(bool checked)
{
    if (checked){
         ui->radioButtonCh6Enable->setChecked(checked);
         ui->comboBoxExternalTriggerCh6->setCurrentIndex(WDConfigClass::TriggerType::ACQUISITION);
    }
}

void MainWindow::on_radioButton_CoinCh7_toggled(bool checked)
{
    if (checked){
         ui->radioButtonCh7Enable->setChecked(checked);
         ui->comboBoxExternalTriggerCh7->setCurrentIndex(WDConfigClass::TriggerType::ACQUISITION);
    }
}
