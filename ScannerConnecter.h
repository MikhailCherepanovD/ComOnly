#ifndef SCANNERCONNECTER_H
#define SCANNERCONNECTER_H
#include <QObject>
#include <QSharedPointer>
#include <QString>

//!
//! \brief Перечнисление возможных состояний сканера
//!  в процессе подключения/отключения
//!

//!
//! \brief Общий класс общения со сканером для Windows и Linux
//!
class ScannerConnecter : public QObject
{   //---- TODO: Переименовать в Connector
    Q_OBJECT
public:
    using ptr_t =  ScannerConnecter*;//QSharedPointer<ScannerConnecter>;
    ScannerConnecter(QObject* parent=nullptr);
    virtual ~ScannerConnecter();
    static ptr_t get(QObject *parent=nullptr);
    QString getStateStr();
public slots:
    //! \brief Обработка и декодирование строки в XML формате
    void processXmlScanData(QString xmlScanData);
signals:
    void sendDataLabelScanData(QString);
protected:
    enum class ScannerState{
        uninitialized,
        initialized,
        bindUnknown,
        opened,
        eventRegistered,
        eventUnregistered,
        closed,
        getScanners,
        failedInitializeComObject,
        failedCreationScannerIntarface,
        failedBindUnknown,
        failedScannerOpenning,
        failedGetScanners,
        failedRegisterEvent,
        failedUnRegisterEvent,
        failedClosed
    };
    ScannerState currentState;

};

#endif // SCANNERCONNECTER_H
