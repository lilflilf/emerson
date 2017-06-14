#ifndef HMIADAPTOR_H
#define HMIADAPTOR_H

#include <QMetaType>
#include <QObject>
#include <QRegExpValidator>
#include "tablemodel.h"
#include "Interface/definition.h"
#include "Interface/Settings/OperatorLibrary.h"
#include "Interface/Maintenance/AdvancedMaintenance.h"
#include "Interface/Maintenance/Calibration.h"
#include "Interface/Maintenance/Maintenance.h"
#include "Interface/Maintenance/MaintenanceCounter.h"
#include "Interface/Maintenance/MaintenanceLog.h"
#include "Interface/Maintenance/ToolChange.h"
#include "Interface/interface.h"
#include "Interface/Settings/PermissionSetting.h"
#include "Interface/Settings/WeldDefaults.h"
#include "Interface/Settings/DataCommunication.h"
#include "Interface/MakeWeld/MakeWeldProcess.h"
#include <QMutex>
#include "Interface/ViewData/StatisticalTrend.h"
#include "Modules/M102IA.h"

#define TOPATH "C:/BransonData/Library/SpliceImage/"

//#define HMI_PRINT (qDebug() <<"HMI adapter:" << __FILE__ << __FUNCTION__ << __LINE__ << ": ")

class HmiAdaptor : public QObject
{
    Q_OBJECT

public:

    explicit HmiAdaptor(QObject *parent = 0);
    ~HmiAdaptor();
    Q_INVOKABLE void setTestSpliceId(int spliceId);
    Q_INVOKABLE int getTestSpliceId();

    Q_INVOKABLE void setEditWireId(int wireId);
    Q_INVOKABLE int getEditWireId();
    Q_INVOKABLE void setEditPartId(int partId);
    Q_INVOKABLE int getEditPartId();

    Q_INVOKABLE void quit();
    Q_INVOKABLE void openFileDialog();
    Q_INVOKABLE void advancedMaintenanceExecute(int code);
    Q_INVOKABLE void advancedMaintenanceRecall();
    Q_INVOKABLE void maintenanceCountExecute(QString code);
    Q_INVOKABLE QString maintenanceCountGetValue(int code, int index);
    Q_INVOKABLE QString maintenanceCountGetImage(int index);
    Q_INVOKABLE void maintenanceCountReset(QString code);
    Q_INVOKABLE void maintenanceCountSetLimit(QString code, QString value);
    Q_INVOKABLE void maintenanceCount80PercentAlarm(QString code, QString value);
    Q_INVOKABLE void maintenanceStart(int page);
    Q_INVOKABLE void maintenanceStop(int page);
    Q_INVOKABLE void maintenanceReset();
    Q_INVOKABLE QString getAdvancedMaintenanceValue(int index, QString key);
    Q_INVOKABLE void setAdvancedMaintenanceValue(int index, QString value);
    Q_INVOKABLE QString getMaintenanceVerson(int index);
    Q_INVOKABLE QString getSoftVerson(int index);
    Q_INVOKABLE bool login(QString passwd);
    Q_INVOKABLE bool borrowLogin(QString passwd, QString pageName);
    Q_INVOKABLE QStringList getCarTempLate();
    Q_INVOKABLE void addCarTempLate(QString name);
    Q_INVOKABLE void removeCarTemplate(QString name);
    Q_INVOKABLE int getCurrentOperatorId();
    Q_INVOKABLE QString getCurrentOperatorName();
    Q_INVOKABLE void calibrationMaintenanceExecute(int code);
    Q_INVOKABLE void hornCalibrationComplete(QString AmplitudeStr);
    Q_INVOKABLE int randPoint();
    Q_INVOKABLE QString copyFileToPath(QString source);

    Q_INVOKABLE int timeChangeToInt(QString time);

    Q_INVOKABLE void setProcess();
    Q_INVOKABLE void setOperateProcess(int spliceId, bool isText);
    Q_INVOKABLE void operateProcessExec(QString type);
    Q_INVOKABLE int  controlLimitProcess(QString type,QList<int> list,int redMax,int redMin);
    Q_INVOKABLE void teachModeProcess();
    Q_INVOKABLE void stopTeachMode();


    /********permissionsetting func**************/
    Q_INVOKABLE bool permissionsettingExecute(QString code);
    Q_INVOKABLE QStringList permissionsettingGetValue(QString code);
    Q_INVOKABLE bool needPassWord(QString pageName);
    Q_INVOKABLE bool permissionsettingGetChecked(QString stringIndex, int level);
    Q_INVOKABLE bool permissionsettingSetValue(QString name, bool level1, bool level2, bool level3, bool level4, bool level5);
    Q_INVOKABLE bool permissionsettingSetFourValue(QStringList fourName);
    Q_INVOKABLE bool stringRegexMatch(QString exp, QString value);
    Q_INVOKABLE bool keyNumStringMatch(QString minValue, QString maxValue, QString value);
    Q_INVOKABLE QString getStringUnit(QString value);
    Q_INVOKABLE QString getStringValue(QString value);
    Q_INVOKABLE bool comepareCurrentValue(QString minValue, QString maxValue, QString value);
    /********weldDefaults func**************/
    Q_INVOKABLE bool weldDefaultsExecute(QString code);
    Q_INVOKABLE bool weldDefaultsGetSwitch(QString index);
    Q_INVOKABLE QStringList weldDefaultsGetValue(int index);
    Q_INVOKABLE QString weldDefaultsGetNum(QString index);
    Q_INVOKABLE bool weldDefaultsSetValue(QList<bool> boolList, QStringList strList, int sampleIndex, QString coolingDur, QString coolingDel);
    Q_INVOKABLE bool weldDefaultsSetValue2(int index,int checkIndex);
    Q_INVOKABLE bool weldDefaultsGetValue2(int index,int checkIndex);
    Q_INVOKABLE bool weldDefaultsSetValue3(QStringList strList);
    Q_INVOKABLE bool weldDefaultFormulaUpdate();

    Q_INVOKABLE QString weldDefaultsGetCutterNum(QString key, QString index);
    Q_INVOKABLE void weldDefaultsSetCutterNum(QString key, QString index);


    /********DataCommunication func**************/
    Q_INVOKABLE bool dataCommunicationExecute(QString code);
    Q_INVOKABLE bool dataCommunicationGetSwitch(QString index);
    Q_INVOKABLE QStringList dataCommunicationGetValue(QString index);
    Q_INVOKABLE bool dataCommunicationSetValue(QList<bool> boolList, QStringList strList, QString ip, QString port);


    Q_INVOKABLE void statisticalTrendApply(int SpliceID, QString SpliceName, unsigned int time_from, unsigned int time_to);
    Q_INVOKABLE QList<int> getStatisticalTrendDataList(int index);
    Q_INVOKABLE QStringList getWeldActualParameterDataList(int index, int type);
    Q_INVOKABLE QStringList getCurrentStatisticsParameterList(int index);
    Q_INVOKABLE QString getAmplitudeToString(int value, int TypeEnum);
    Q_INVOKABLE QString getDefaultAmplitudeToString(int value, int TypeEnum);
    Q_INVOKABLE QString getTestQuantity(int value, bool bIsMax);
    Q_INVOKABLE QString getShrinkTemperatureToString(int value, bool bIsMax);
    Q_INVOKABLE QString getShrinkTimeToString(int value, bool bIsMax);

    Q_INVOKABLE void msgBoxClick(bool clickOK);
    Q_INVOKABLE void teachModeSaveSplice();
    Q_INVOKABLE void setAlarmModelList(bool bIsNeedReset);
    Q_INVOKABLE void viewLibraryMovePart(int id, QString name);
    Q_INVOKABLE void viewLibraryMoveSplice(int id, QString name);

    Q_INVOKABLE void importData(QString fileUrl);
    Q_INVOKABLE int importSplice(QString spliceStr);
    Q_INVOKABLE int importHarness(QString harnessStr);
    Q_INVOKABLE int importSequence(QString sequenceStr);
    Q_INVOKABLE int importWorkOrder(QString workOrderStr);

    Q_INVOKABLE void addInsulation(QString insualtionId, QString temp, QString time);
    Q_INVOKABLE void exportShrink(QString insualtionId, QString temp, QString time, QString fileUrl);
    Q_INVOKABLE void removeShrink(int selectIndex);
    Q_INVOKABLE int stringToInt(QString temp);

    Q_INVOKABLE void setWorkFlow(int workMode, int workId);
    Q_INVOKABLE QVariant getWorkFlow(QString workKey);
    Q_INVOKABLE void readWorkFlow();

    Q_INVOKABLE void setWorkValue(QString key, QString value);
    Q_INVOKABLE QVariant getWorkValue(QString workKey);
    Q_INVOKABLE QList<int> getWorkMissList();
    Q_INVOKABLE void setWorkMissList(int spliceId);


    Q_INVOKABLE QString getUserManualPath();
    Q_INVOKABLE QString getApplicationDirPathPath();
    Q_INVOKABLE QString getToolChangeFileName(QString filePath);
    Q_INVOKABLE void setLanguage(int row, int column);
    Q_INVOKABLE QString getLanguageImage();

    BransonMessageBox bransonMessageBox;
    InterfaceClass *interfaceClass;
    M102IA *m102ia;
    MakeWeldProcess *operateProcess;
    DBPresetTable *m_spliceAdaptor;
    VariantToString *m_variantToString;
    StringToVariant *m_stringToVariant;

    WorkOrderModel *workOrderModel;
    SplicesModel *spliceModel;
    PartModel *harnessModel;
    OperatorModel *operatorModel;
    WireModel *wireModel;
    WeldHistoryModel *weldHistoryModel;
    AlarmModel *alarmModel;
    MaintenanceLogModel *maintenanceLogModel;
    SequenceModel *sequenceModel;

    /********Maintenance**************/
    AdvancedMaintenance * advanceMaintenance;
    Calibration * calibration;
    MaintenanceCounter *maintenanceCount;
    MaintenanceLogElement *maintenanceLog;
    ToolChange *toolChange;

    /*********Setting*****************/
    PermissionSetting *permissionSetting;
    WeldDefaults *weldDefaults;
    DataCommunication *dataCommunication;

    QMutex mutex;
    StatisticalTrend *statisticalTrend;
    int taskBarHeight;
    void (*func_ptr)(void*);
    int testSpliceId;
    int editWireId;
    int editPartId;
    bool bIsPhysicalKey;
signals:
    void widthCalibrationFinish(const bool &_Result);
    void heightCalibrationFinish(const bool &_Result);
    void signalEnableDialog(bool okVisable, bool cancelVisable, QString okText, QString cancelText, QString typeIco,QString titleText,QString centerText,bool isQuit);
    void signalDisableDialog();
    void signalWeldCycleCompleted(bool result);
    void signalButtonStateChanged(QString buttonName,bool state);
    void signalMantenaneceCount(int count);
    void signalMovePart(int id, QString name);
    void signalMoveSplice(int id, QString name);

    void signalPhysicalKeySignal(bool status);
    void signalPhysicalKeyMessage();
public slots:
    void slotPhysicalKeySignal(bool &status);
    void slotWeldCycleCompleted(bool result);
    void slotEnableDialog(struct BransonMessageBox &MsgBox);
    void slotDisableDialog(struct BransonMessageBox &MsgBox);
    void slotButtonState(const unsigned long status);
    void slotGetAlarmFlag();
private:
    void reboot();
};

#endif // HMIADAPTOR_H
