#ifndef WDCONFIGCLASS_H
#define WDCONFIGCLASS_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QProcess>
#include <QApplication>


#define NUM_CHANNELS 8

class WDConfigClass
{
public:

    QString FilepathWrite="/etc/wavedump/WaveDumpConfig.txt";
    QString FilepathRead = "/etc/wavedump/WaveDumpConfig.txt";
    enum TriggerType {ACQUISITION, ACQUISITION_and_TRGOUT, DISABLED};
    enum BaselineLevel {CERO,FIFTY,ONE_HUNDRED};
    struct GlobalParameters{
        int CommDevice;
        int RecordLength;
        int PostTrigger;
        bool PulsePolarity;
        TriggerType ExternalTrigger;
        int FPIO_Level;
        int OutputFileFormat;
        bool OutputHeader;
        bool TestPattern;

    };

    struct ChannelParameters{
        bool Enabled;
        int BaselineLevel;
        int Threshold;
        TriggerType ChannelTrigger;
    };
    struct TriggerMask{
        bool Ch0;
        bool Ch1;
        bool Ch2;
        bool Ch3;
        bool Ch4;
        bool Ch5;
        bool Ch6;
        bool Ch7;
    };

    struct TriggerGroups{
        bool Group0;
        bool Group1;
        bool Group2;
        bool Group3;
    };


    WDConfigClass();//Constructor
    ~WDConfigClass();

    bool ReadGlobalFromFile(QString filename);
    bool SaveGlobalToFile(QString filename);

    bool ReadChannelsFromFile(QString filename);
    bool SaveChannelsToFile(QString filename);

    bool SaveTriggerMaskToFile(QString filename);
    bool ReadTriggerMaskFromFile(QString filename);


    //We manage to read and save our private variables
    GlobalParameters ReadGlobalParameters();
    void SaveGlobalParameters(GlobalParameters MyGlobalParametersToSave);

    QVector<ChannelParameters> ReadChannelParameters();
    void SaveChannelParameters(QVector<ChannelParameters> MyChannelParametersToSave);

    TriggerMask ReadTriggerMaskParameters();
    void SaveTriggerMaskParameters(TriggerMask MyTriggerMaskParamToSave);


    bool ExecuteWaveDump(QString WaveDumpPath);


private:

    GlobalParameters MyGlobalParameters;
    QVector<ChannelParameters> MyChannelParametersVector;
    TriggerMask MyTriggerMask;
    TriggerGroups MyTriggerGroups;
    int NumberOfTriggerGroupsActive = 0;
    QProcess *process;

};

#endif // WDCONFIGCLASS_H
