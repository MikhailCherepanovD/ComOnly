#include "ScannerConnecter.h"

#ifdef Q_OS_WIN32
    #include "ScannerConnecterWinImpl.h"
#else
    #include "linux/ScannerConnecterLinuxImpl.h"
#endif

ScannerConnecter::ScannerConnecter(QObject* parent):
    QObject(parent),
    currentState(ScannerState::uninitialized){

}

ScannerConnecter::~ScannerConnecter(){}

//static функция
ScannerConnecter::ptr_t ScannerConnecter::get(QObject *parent){
#ifdef Q_OS_WIN32
    return new ScannerConnecterWinImpl(parent);//QSharedPointer<ScannerConnecterWinImpl>::create();
#else
    // Ну пока тут возвращать нечего
    return QSharedPointer<ScannerConnecter>::create();
#endif
}

QString ScannerConnecter::getStateStr() {
    switch (currentState) {
        case ScannerState::uninitialized:
            return "uninitialized";
        case ScannerState::initialized:
            return "initialized";
        case ScannerState::opened:
            return "opened";
        case ScannerState::bindUnknown:
            return "bindUnknown";
        case ScannerState::eventRegistered:
            return "eventRegistered";
        case ScannerState::eventUnregistered:
            return "eventUnregistered";
        case ScannerState::closed:
            return "closed";
        case ScannerState::getScanners:
            return "getScanners";
        case ScannerState::failedInitializeComObject:
            return "failedInitializeComObject";
        case ScannerState::failedCreationScannerIntarface:
            return "failedCreationScannerIntarface";
        case ScannerState::failedBindUnknown:
            return "failedBindUnknown";
        case ScannerState::failedScannerOpenning:
            return "failedScannerOpenning";
        case ScannerState::failedGetScanners:
            return "failedGetScanners";
        case ScannerState::failedRegisterEvent:
            return "failedRegisterEvent";
        case ScannerState::failedUnRegisterEvent:
            return "failedUnRegisterEvent";
        case ScannerState::failedClosed:
            return "failedClosed";
        default:
            return "unknown";
    }
}

//слоты
void ScannerConnecter::processXmlScanData(QString xmlScanData){

}
