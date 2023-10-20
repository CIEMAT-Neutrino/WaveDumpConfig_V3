#include "wdconfigclass.h"

WDConfigClass::WDConfigClass()
{
    process = new QProcess();
}

WDConfigClass::~WDConfigClass()
{
    process->kill();
}

bool WDConfigClass::ReadGlobalFromFile(QString filename)
{

    QString TempString;


//Abrimos el fichero y leemos línea a línes
    QFile file(filename);

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

                        if (line.contains("OPEN USB"))
                          {
                            MyGlobalParameters.CommDevice = 0;
                          }
                        else if (line.contains("OPEN PCI 0 0 0"))
                          {
                            MyGlobalParameters.CommDevice = 1;
                        }
                        else if (line.contains("RECORD_LENGTH"))
                        {
                          TempString = line.mid(13, '\n');
                          MyGlobalParameters.RecordLength = TempString.toInt();
                        }
                        else if (line.contains("POST_TRIGGER"))
                        {
                          TempString = line.mid(12, '\n');
                          MyGlobalParameters.PostTrigger = TempString.toInt();
                        }
                        else if (line.contains("PULSE_POLARITY"))
                        {
                            if (line.contains("POSITIVE"))
                                    MyGlobalParameters.PulsePolarity = true;
                            if (line.contains("NEGATIVE"))
                                    MyGlobalParameters.PulsePolarity = false;
                        }
                        else if (line.contains("EXTERNAL_TRIGGER"))
                        {
                            if (line.contains("DISABLED"))
                                    MyGlobalParameters.ExternalTrigger = WDConfigClass::DISABLED;
                            if (line.contains("ACQUISITION_ONLY"))
                                    MyGlobalParameters.ExternalTrigger = WDConfigClass::ACQUISITION;
                            if (line.contains("ACQUISITION_AND_TRGOUT"))
                                    MyGlobalParameters.ExternalTrigger = WDConfigClass::ACQUISITION_and_TRGOUT;
                        }
                        else if (line.contains("FPIO_LEVEL"))
                        {
                            if (line.contains("NIM"))
                                    MyGlobalParameters.FPIO_Level = false;
                            if (line.contains("TTL"))
                                    MyGlobalParameters.FPIO_Level = true;
                        }
                        else if (line.contains("OUTPUT_FILE_FORMAT"))
                        {
                            if (line.contains("BINARY"))
                                    MyGlobalParameters.OutputFileFormat = true;
                            if (line.contains("ASCII"))
                                    MyGlobalParameters.OutputFileFormat= false;
                        }
                        else if (line.contains("OUTPUT_FILE_HEADER"))
                        {
                            if (line.contains("YES"))
                                    MyGlobalParameters.OutputHeader = true;
                            if (line.contains("NO"))
                                    MyGlobalParameters.OutputHeader= false;
                        }
                        else if (line.contains("TEST_PATTERN"))
                        {
                            if (line.contains("YES"))
                                    MyGlobalParameters.TestPattern = true;
                            if (line.contains("NO"))
                                    MyGlobalParameters.TestPattern= false;
                        }
                       /* else if(line.contains("BASELINE_LEVEL"))
                        {
                            TempString = line.mid(14, '\n');
                            if (TempString == "0")
                                MyGlobalParameters.GlobalBaseline = BaselineLevel::CERO;
                            if (TempString == "50")
                                MyGlobalParameters.GlobalBaseline = BaselineLevel::FIFTY;
                            if (TempString == "100")
                                MyGlobalParameters.GlobalBaseline = BaselineLevel::ONE_HUNDRED;
                        }*/

                    }//else
              } while (!line.isNull());
              file.close();
        }

    return true;

}

bool WDConfigClass::SaveGlobalToFile(QString filename)
{

    QFile file(filename);
    bool result;

    if (!file.open(QIODevice::ReadWrite |QIODevice::Truncate )){
        QMessageBox::information(nullptr,"info",file.errorString()+" For Writing HV Values");
        result = 0;
    }
    else {
           QTextStream stream(&file);

            qDebug() <<"Writing Values to File";
            stream << "[COMMON]\n";
            if (MyGlobalParameters.CommDevice == 0)
                stream << "OPEN USB 0 0\n";
            if (MyGlobalParameters.CommDevice == 1)
                stream << "OPEN PCI 0 0 0\n";

            stream << "RECORD_LENGTH " + QString::number(MyGlobalParameters.RecordLength) + "\n";
            stream << "POST_TRIGGER  " + QString::number(MyGlobalParameters.PostTrigger)+ "\n";
            if(MyGlobalParameters.PulsePolarity == false)
                stream << "PULSE_POLARITY  NEGATIVE\n";
            if(MyGlobalParameters.PulsePolarity == true)
                stream << "PULSE_POLARITY  POSITIVE\n";
            if(MyGlobalParameters.ExternalTrigger == TriggerType::DISABLED)
                stream << "EXTERNAL_TRIGGER   DISABLED\n";
            if(MyGlobalParameters.ExternalTrigger == TriggerType::ACQUISITION)
                stream << "EXTERNAL_TRIGGER   ACQUISITION_ONLY\n";
            if(MyGlobalParameters.ExternalTrigger == TriggerType::ACQUISITION_and_TRGOUT)
                stream << "EXTERNAL_TRIGGER   ACQUISITION_AND_TRGOUT\n";
            if(MyGlobalParameters.FPIO_Level == true)
                stream << "FPIO_LEVEL  TTL\n";
            if(MyGlobalParameters.FPIO_Level == false)
                stream << "FPIO_LEVEL  NIM\n";
            if(MyGlobalParameters.OutputFileFormat == false)
                stream << "OUTPUT_FILE_FORMAT  ASCII\n";
            if(MyGlobalParameters.OutputFileFormat == true)
                stream << "OUTPUT_FILE_FORMAT  BINARY\n";
            if(MyGlobalParameters.OutputHeader == true)
                stream << "OUTPUT_FILE_HEADER  YES\n";
            if(MyGlobalParameters.OutputHeader == false)
                stream << "OUTPUT_FILE_HEADER  NO\n";
            if(MyGlobalParameters.TestPattern == true)
                stream << "TEST_PATTERN  YES\n";
            if(MyGlobalParameters.TestPattern == false)
                stream << "TEST_PATTERN  NO\n";
            //stream << "WRITE_REGISTER 811C 00010000 00300000\n";
            stream << "WRITE_REGISTER 811C 00400000 00600000\n";
          }

        file.close();
        qDebug() << "Writing finished";
        result = true;

return result;


}

bool WDConfigClass::ReadChannelsFromFile(QString filename)
{
        enum ConfigStatus {CH0, CH1, CH2, CH3, CH4, CH5, CH6, CH7};
        ChannelParameters TempChannelParams;
        ConfigStatus MyConfigStatus;

        QString TempString;


    //Abrimos el fichero y leemos línea a línes
        QFile file(filename);

            if (!file.open(QIODevice::ReadWrite))
                QMessageBox::information(nullptr,"info",file.errorString() + " For Reading HV Values");
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

                            if (line.contains("[0]"))
                                MyConfigStatus = ConfigStatus::CH0;
                            if (line.contains("[1]")){
                                  MyConfigStatus = ConfigStatus::CH1;
                                  //We supose Ch0 is read and we add to the global parameters vector
                                  MyChannelParametersVector.append(TempChannelParams);
                            }
                            if (line.contains("[2]")){
                                  MyConfigStatus = ConfigStatus::CH2;
                                  //We supose Ch0 is read and we add to the global parameters vector
                                  MyChannelParametersVector.append(TempChannelParams);
                            }
                            if (line.contains("[3]")){
                                  MyConfigStatus = ConfigStatus::CH3;
                                  //We supose Ch0 is read and we add to the global parameters vector
                                  MyChannelParametersVector.append(TempChannelParams);
                            }
                            if (line.contains("[4]")){
                                  MyConfigStatus = ConfigStatus::CH4;
                                  //We supose Ch0 is read and we add to the global parameters vector
                                  MyChannelParametersVector.append(TempChannelParams);
                            }
                            if (line.contains("[5]")){
                                  MyConfigStatus = ConfigStatus::CH5;
                                  //We supose Ch0 is read and we add to the global parameters vector
                                  MyChannelParametersVector.append(TempChannelParams);
                            }
                            if (line.contains("[6]")){
                                  MyConfigStatus = ConfigStatus::CH6;
                                  //We supose Ch0 is read and we add to the global parameters vector
                                  MyChannelParametersVector.append(TempChannelParams);
                            }
                            if (line.contains("[7]")){
                                  MyConfigStatus = ConfigStatus::CH7;
                                  //We supose Ch0 is read and we add to the global parameters vector
                                  MyChannelParametersVector.append(TempChannelParams);
                            }

                            //Configuramos cada canal
                            if (MyConfigStatus == ConfigStatus::CH0){
                                if (line.contains("ENABLE_INPUT")){
                                    if (line.contains("YES"))TempChannelParams.Enabled=true;
                                    if (line.contains("NO"))TempChannelParams.Enabled=false;
                                }
                                if (line.contains("BASELINE_LEVEL")){
                                    TempString = line.mid(15, '\n');
                                    TempChannelParams.BaselineLevel = TempString.toInt();
                                }
                                if (line.contains("TRIGGER_THRESHOLD")){
                                    TempString = line.mid(17, '\n');
                                    TempChannelParams.Threshold = TempString.toInt();
                                }
                                 if (line.contains("CHANNEL_TRIGGER"))
                                {
                                    if (line.contains("DISABLED"))
                                            TempChannelParams.ChannelTrigger = WDConfigClass::DISABLED;
                                    if (line.contains("ACQUISITION_ONLY"))
                                            TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION;
                                    if (line.contains("ACQUISITION_AND_TRGOUT"))
                                            TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION_and_TRGOUT;
                                }
                            }
                            if (MyConfigStatus == ConfigStatus::CH1){
                                if (line.contains("ENABLE_INPUT")){
                                    if (line.contains("YES"))TempChannelParams.Enabled=true;
                                    if (line.contains("NO"))TempChannelParams.Enabled=false;
                                }
                                if (line.contains("BASELINE_LEVEL")){
                                    TempString = line.mid(14, '\n');
                                    TempChannelParams.BaselineLevel = TempString.toInt();
                                }
                                if (line.contains("TRIGGER_THRESHOLD")){
                                    TempString = line.mid(17, '\n');
                                    TempChannelParams.Threshold = TempString.toInt();
                                }
                                if (line.contains("CHANNEL_TRIGGER"))
                               {
                                   if (line.contains("DISABLED"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::DISABLED;
                                   if (line.contains("ACQUISITION_ONLY"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION;
                                   if (line.contains("ACQUISITION_AND_TRGOUT"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION_and_TRGOUT;
                               }
                            }
                            if (MyConfigStatus == ConfigStatus::CH2){
                                if (line.contains("ENABLE_INPUT")){
                                    if (line.contains("YES"))TempChannelParams.Enabled=true;
                                    if (line.contains("NO"))TempChannelParams.Enabled=false;
                                }
                                if (line.contains("BASELINE_LEVEL")){
                                    TempString = line.mid(14, '\n');
                                    TempChannelParams.BaselineLevel = TempString.toInt();
                                }
                                if (line.contains("TRIGGER_THRESHOLD")){
                                    TempString = line.mid(17, '\n');
                                    TempChannelParams.Threshold = TempString.toInt();
                                }
                                if (line.contains("CHANNEL_TRIGGER"))
                               {
                                   if (line.contains("DISABLED"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::DISABLED;
                                   if (line.contains("ACQUISITION_ONLY"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION;
                                   if (line.contains("ACQUISITION_AND_TRGOUT"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION_and_TRGOUT;
                               }
                            }
                            if (MyConfigStatus == ConfigStatus::CH3){
                                if (line.contains("ENABLE_INPUT")){
                                    if (line.contains("YES"))TempChannelParams.Enabled=true;
                                    if (line.contains("NO"))TempChannelParams.Enabled=false;
                                }
                                if (line.contains("BASELINE_LEVEL")){
                                    TempString = line.mid(14, '\n');
                                    TempChannelParams.BaselineLevel = TempString.toInt();
                                }
                                if (line.contains("TRIGGER_THRESHOLD")){
                                    TempString = line.mid(17, '\n');
                                    TempChannelParams.Threshold = TempString.toInt();
                                }
                                if (line.contains("CHANNEL_TRIGGER"))
                               {
                                   if (line.contains("DISABLED"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::DISABLED;
                                   if (line.contains("ACQUISITION_ONLY"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION;
                                   if (line.contains("ACQUISITION_AND_TRGOUT"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION_and_TRGOUT;
                               }
                            }
                            if (MyConfigStatus == ConfigStatus::CH4){
                                if (line.contains("ENABLE_INPUT")){
                                    if (line.contains("YES"))TempChannelParams.Enabled=true;
                                    if (line.contains("NO"))TempChannelParams.Enabled=false;
                                }
                                if (line.contains("BASELINE_LEVEL")){
                                    TempString = line.mid(14, '\n');
                                    TempChannelParams.BaselineLevel = TempString.toInt();
                                }
                                if (line.contains("TRIGGER_THRESHOLD")){
                                    TempString = line.mid(17, '\n');
                                    TempChannelParams.Threshold = TempString.toInt();
                                }
                                if (line.contains("CHANNEL_TRIGGER"))
                               {
                                   if (line.contains("DISABLED"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::DISABLED;
                                   if (line.contains("ACQUISITION_ONLY"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION;
                                   if (line.contains("ACQUISITION_AND_TRGOUT"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION_and_TRGOUT;
                               }
                            }
                            if (MyConfigStatus == ConfigStatus::CH5){
                                if (line.contains("ENABLE_INPUT")){
                                    if (line.contains("YES"))TempChannelParams.Enabled=true;
                                    if (line.contains("NO"))TempChannelParams.Enabled=false;
                                }
                                if (line.contains("BASELINE_LEVEL")){
                                    TempString = line.mid(14, '\n');
                                    TempChannelParams.Threshold = TempString.toInt();
                                }
                                if (line.contains("TRIGGER_THRESHOLD")){
                                    TempString = line.mid(17, '\n');
                                    TempChannelParams.BaselineLevel = TempString.toInt();
                                }
                                if (line.contains("CHANNEL_TRIGGER"))
                               {
                                   if (line.contains("DISABLED"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::DISABLED;
                                   if (line.contains("ACQUISITION_ONLY"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION;
                                   if (line.contains("ACQUISITION_AND_TRGOUT"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION_and_TRGOUT;
                               }
                            }
                            if (MyConfigStatus == ConfigStatus::CH6){
                                if (line.contains("ENABLE_INPUT")){
                                    if (line.contains("YES"))TempChannelParams.Enabled=true;
                                    if (line.contains("NO"))TempChannelParams.Enabled=false;
                                }
                                if (line.contains("BASELINE_LEVEL")){
                                    TempString = line.mid(14, '\n');
                                    TempChannelParams.BaselineLevel = TempString.toInt();
                                }
                                if (line.contains("TRIGGER_THRESHOLD")){
                                    TempString = line.mid(17, '\n');
                                    TempChannelParams.Threshold = TempString.toInt();
                                }
                                if (line.contains("CHANNEL_TRIGGER"))
                               {
                                   if (line.contains("DISABLED"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::DISABLED;
                                   if (line.contains("ACQUISITION_ONLY"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION;
                                   if (line.contains("ACQUISITION_AND_TRGOUT"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION_and_TRGOUT;
                               }
                            }
                            if (MyConfigStatus == ConfigStatus::CH7){
                                if (line.contains("ENABLE_INPUT")){
                                    if (line.contains("YES"))TempChannelParams.Enabled=true;
                                    if (line.contains("NO"))TempChannelParams.Enabled=false;
                                }
                                if (line.contains("BASELINE_LEVEL")){
                                    TempString = line.mid(14, '\n');
                                    TempChannelParams.BaselineLevel = TempString.toInt();
                                }
                                if (line.contains("TRIGGER_THRESHOLD")){
                                    TempString = line.mid(17, '\n');
                                    TempChannelParams.Threshold = TempString.toInt();

                                }
                                if (line.contains("CHANNEL_TRIGGER"))
                               {
                                   if (line.contains("DISABLED"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::DISABLED;
                                   if (line.contains("ACQUISITION_ONLY"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION;
                                   if (line.contains("ACQUISITION_AND_TRGOUT"))
                                           TempChannelParams.ChannelTrigger = WDConfigClass::ACQUISITION_and_TRGOUT;
                               }
                                MyChannelParametersVector.append(TempChannelParams);
                            }



                        }//else
                  } while (!line.isNull());
                  file.close();
            }

        return true;


}

bool WDConfigClass::SaveChannelsToFile(QString filename)
{
    QFile file(filename);
    bool result;


    if (!file.open(QIODevice::ReadWrite |QIODevice::Append )){
        QMessageBox::information(nullptr,"info",file.errorString()+" For Writing HV Values");
        result = false;
    }
    else {
           QTextStream stream(&file);
            for(int i=0; i<NUM_CHANNELS; i++)
            {
                qDebug() << "Writing Channel " + QString::number(i) +" to File";
                stream << "[" + QString::number(i) + "]\n";

                if (MyChannelParametersVector[i].Enabled) stream << "ENABLE_INPUT YES\n";
                else stream << "ENABLE_INPUT NO\n";
                stream << "BASELINE_LEVEL " + QString::number(MyChannelParametersVector[i].BaselineLevel) + "\n";
                stream << "TRIGGER_THRESHOLD " + QString::number(MyChannelParametersVector[i].Threshold) + "\n";
                if(MyChannelParametersVector[i].ChannelTrigger == TriggerType::DISABLED) stream << "CHANNEL_TRIGGER  DISABLED\n";
                else if(MyChannelParametersVector[i].ChannelTrigger == TriggerType::ACQUISITION) stream << "CHANNEL_TRIGGER  ACQUISITION_ONLY\n";
                else if(MyChannelParametersVector[i].ChannelTrigger == TriggerType::ACQUISITION_and_TRGOUT) stream << "CHANNEL_TRIGGER  ACQUISITION_AND_TRGOUT\n";
            }

          }

        file.close();
        qDebug() << "Writing Channels finished";
        result = true;

        return result;
}

bool WDConfigClass::SaveTriggerMaskToFile(QString filename)
{
    QFile file(filename);
    bool result;
    NumberOfTriggerGroupsActive = 0;
    int NumberOfChannelsInTrigger = 0;


    if (!file.open(QIODevice::ReadWrite |QIODevice::Append )){
        QMessageBox::information(nullptr,"info",file.errorString()+" For Writing HV Values");
        result = false;
    }//if
    else {
           QTextStream stream(&file);

        qDebug() << "Writing Trigger Mask Configuration to File";
        if (MyTriggerMask.Ch0 == true)
                NumberOfChannelsInTrigger = NumberOfChannelsInTrigger+1;
        if (MyTriggerMask.Ch1 == true)
                NumberOfChannelsInTrigger = NumberOfChannelsInTrigger+2;
        if (MyTriggerMask.Ch2 == true)
                NumberOfChannelsInTrigger = NumberOfChannelsInTrigger+4;
        if (MyTriggerMask.Ch3 == true)
                NumberOfChannelsInTrigger = NumberOfChannelsInTrigger+8;
        if (MyTriggerMask.Ch4 == true)
                NumberOfChannelsInTrigger = NumberOfChannelsInTrigger+16;
        if (MyTriggerMask.Ch5 == true)
                NumberOfChannelsInTrigger = NumberOfChannelsInTrigger+32;
        if (MyTriggerMask.Ch6 == true)
                NumberOfChannelsInTrigger = NumberOfChannelsInTrigger+64;
        if (MyTriggerMask.Ch7 == true)
                NumberOfChannelsInTrigger = NumberOfChannelsInTrigger+128;

        stream << "#CHANNELS_TRIGGER_MASK " + QString::number(NumberOfChannelsInTrigger) + "\n";

        if ((MyTriggerMask.Ch0 == true) && (MyTriggerMask.Ch1 == true)) stream << "WRITE_REGISTER 1084 0000 0003\n";
        if ((MyTriggerMask.Ch2 == true) && (MyTriggerMask.Ch3 == true)) stream << "WRITE_REGISTER 1284 0000 0003\n";
        if ((MyTriggerMask.Ch4 == true) && (MyTriggerMask.Ch5 == true)) stream << "WRITE_REGISTER 1484 0000 0003\n";
        if ((MyTriggerMask.Ch6 == true) && (MyTriggerMask.Ch7 == true)) stream << "WRITE_REGISTER 1684 0000 0003\n";

        if ((MyTriggerMask.Ch0 == true) || (MyTriggerMask.Ch1 == true)){
            MyTriggerGroups.Group0 = true;
            NumberOfTriggerGroupsActive++;
        }
        else MyTriggerGroups.Group0 = false;
        if ((MyTriggerMask.Ch2 == true) || (MyTriggerMask.Ch3 == true)){
            MyTriggerGroups.Group1 = true;
            NumberOfTriggerGroupsActive++;
        }
        else MyTriggerGroups.Group1 = false;
        if ((MyTriggerMask.Ch4 == true) || (MyTriggerMask.Ch5 == true)){
            MyTriggerGroups.Group2 = true;
            NumberOfTriggerGroupsActive++;
        }
        else MyTriggerGroups.Group2 = false;
        if ((MyTriggerMask.Ch6 == true) || (MyTriggerMask.Ch7 == true)){
            MyTriggerGroups.Group3 = true;
            NumberOfTriggerGroupsActive++;
        }
        else MyTriggerGroups.Group3 = false;
        if(NumberOfTriggerGroupsActive == 2){
            if ((MyTriggerGroups.Group0 == true) && (MyTriggerGroups.Group1== true)) stream << "WRITE_REGISTER 810C 81000003 FFFFFFFF\n";
            if ((MyTriggerGroups.Group0 == true) && (MyTriggerGroups.Group2== true)) stream << "WRITE_REGISTER 810C 81000005 FFFFFFFF\n";
            if ((MyTriggerGroups.Group0 == true) && (MyTriggerGroups.Group3== true)) stream << "WRITE_REGISTER 810C 81000009 FFFFFFFF\n";
            if ((MyTriggerGroups.Group1 == true) && (MyTriggerGroups.Group2== true)) stream << "WRITE_REGISTER 810C 81000006 FFFFFFFF\n";
            if ((MyTriggerGroups.Group1 == true) && (MyTriggerGroups.Group3== true)) stream << "WRITE_REGISTER 810C 8100000A FFFFFFFF\n";
            if ((MyTriggerGroups.Group2 == true) && (MyTriggerGroups.Group3== true)) stream << "WRITE_REGISTER 810C 8100000C FFFFFFFF\n";
        }
        if(NumberOfTriggerGroupsActive == 3){
            if ((MyTriggerGroups.Group0 == true) && (MyTriggerGroups.Group1== true) && (MyTriggerGroups.Group2== true)) stream << "WRITE_REGISTER 810C 82000007 FFFFFFFF\n";
            if ((MyTriggerGroups.Group0 == true) && (MyTriggerGroups.Group1== true) && (MyTriggerGroups.Group3== true)) stream << "WRITE_REGISTER 810C 8200000B FFFFFFFF\n";
            if ((MyTriggerGroups.Group0 == true) && (MyTriggerGroups.Group2== true) && (MyTriggerGroups.Group3== true)) stream << "WRITE_REGISTER 810C 8200000D FFFFFFFF\n";
        }
        if(NumberOfTriggerGroupsActive == 4){
            stream << "WRITE_REGISTER 810C 8300000F FFFFFFFF\n";
        }


          }//else

        file.close();
        qDebug() << "Writing Trigger Mask Configuration finished";
        result = true;

        return result;

}

bool WDConfigClass::ReadTriggerMaskFromFile(QString filename)
{
    int NumberOfChannelsInTrigger;
     /*ProductResult= NumberOfChannelsInTrigger & 1;
     ProductResult= NumberOfChannelsInTrigger & 2;
     ProductResult= NumberOfChannelsInTrigger & 4;
     ProductResult= NumberOfChannelsInTrigger & 8;*/
    QString TempString;


//Abrimos el fichero y leemos línea a línes
    QFile file(filename);

        if (!file.open(QIODevice::ReadWrite))
            QMessageBox::information(nullptr,"info",file.errorString() + " For Reading WaveDump File Values");
        else
        {
            QTextStream stream(&file);
            QString line;
            //int endl;

            do {
                line = stream.readLine();
            // Parseamos buscando la etiqueta correspondiente

                if (line.contains("#CHANNELS_TRIGGER_MASK"))
                  {
                    TempString = line.mid(22, '\n');
                    NumberOfChannelsInTrigger = TempString.toInt();
                    if ((NumberOfChannelsInTrigger & 1)==1)MyTriggerMask.Ch0 = true;
                    if ((NumberOfChannelsInTrigger & 2)==2)MyTriggerMask.Ch1 = true;
                    if ((NumberOfChannelsInTrigger & 4)==4)MyTriggerMask.Ch2 = true;
                    if ((NumberOfChannelsInTrigger & 8)==8)MyTriggerMask.Ch3 = true;
                    if ((NumberOfChannelsInTrigger & 16)==16)MyTriggerMask.Ch4 = true;
                    if ((NumberOfChannelsInTrigger & 32)==32)MyTriggerMask.Ch5 = true;
                    if ((NumberOfChannelsInTrigger & 64)==64)MyTriggerMask.Ch6 = true;
                    if ((NumberOfChannelsInTrigger & 128)==128)MyTriggerMask.Ch7 = true;
                  }

              } while (!line.isNull());
              file.close();
        }

    return true;
}

WDConfigClass::GlobalParameters WDConfigClass::ReadGlobalParameters()
{
    return MyGlobalParameters;
}

void WDConfigClass::SaveGlobalParameters(WDConfigClass::GlobalParameters MyGlobalParametersToSave)
{
    MyGlobalParameters = MyGlobalParametersToSave;
}

QVector<WDConfigClass::ChannelParameters> WDConfigClass::ReadChannelParameters()
{
    return MyChannelParametersVector;
}

void WDConfigClass::SaveChannelParameters(QVector<WDConfigClass::ChannelParameters> MyChannelParametersToSave)
{
    MyChannelParametersVector = MyChannelParametersToSave;
}

WDConfigClass::TriggerMask WDConfigClass::ReadTriggerMaskParameters()
{
    return MyTriggerMask;
}

void WDConfigClass::SaveTriggerMaskParameters(WDConfigClass::TriggerMask MyTriggerMaskParamToSave)
{
    MyTriggerMask = MyTriggerMaskParamToSave;
}

bool WDConfigClass::ExecuteWaveDump(QString WaveDumpPath)
{


    /*QDir::setCurrent(WaveDumpPath);
    system("wavedump");*/

    //QString l(QDir::homePath());

    QString l("/data/WaveDumpData");
    QString exec = "gnome-terminal";
    //QString exec = "wavedump";
    QStringList params;
    //params << "-e"<< "sh /home/lab/run.sh" ;
    params << "-e"<< "wavedump";
    //params << "-e"<< "~/Documentos/wavedump-3.10.0/Setup/WaveDumpConfig.txt" ;
    process->setWorkingDirectory(l);
    //process->start(exec, params, QProcess::Unbuffered | QProcess::ReadWrite);
    process->start(exec, params);
    QApplication::processEvents();


    // Wait for finished
    //process->waitForStarted();
    //QProcess MyProcess;;


    //QString WorkingDirectory = "C:\\Users\\Sergio\\Desktop\\Teletrabajo\\QtProjects\\WaveDump\\bin";


   //MyProcess.startDetached("WaveDump.exe");
   /*MyProcess.start("WaveDump.exe");
    if(MyProcess.open()){
        qDebug() << "Starting";
        QByteArray Out = MyProcess.readAllStandardOutput();
        MyProcess.close();

    }
    MyProcess.waitForFinished(-1);
        qDebug() << "finish";*/
    return true;
}
