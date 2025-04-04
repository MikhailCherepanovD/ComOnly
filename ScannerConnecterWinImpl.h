#ifndef SCANNERCONNECTERWINIMPL_H
#define SCANNERCONNECTERWINIMPL_H
#define _AFXDLL // для корректного подключения MFC
#include "target.h"
#include <afxctl.h>
#include "_core_scanner_i.c"
#include "_core_scanner.h"
#include "common_defs.h"
#include "EventSink.h"
#include "Math.h"
#include "ScannerConnecter.h"
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <vector>
#include <conio.h>
#include <QDebug>
#include <QString>

class ScannerConnecterWinImpl: public ScannerConnecter
{
public:
    explicit ScannerConnecterWinImpl(QObject* parent);
    ~ScannerConnecterWinImpl();
private:
    void comObjectInitialize();
    void openScannerConnection();
    void bindUnknownIntarface();
    void getScanners();
    void registerEvent();
private:
    // Переменные для общения с COM объектом сканера
    ICoreScanner* scannerInterface_; // Интерфейс для взаимодействия со сканером
    LONG appHandle_; //Дескрипотор подключаемого приложения
    SHORT scannersNumber_; // Количество подключенных сканеров
    BSTR scannersInfoXml_; //BSTR - строковый тип, используемый в COM. Информация о подключенных сканерах.
    SAFEARRAY* scannersArray_; // Массив идентификаторов сканеров.
    LPUNKNOWN eventSinkUnknown_; //LPUNKNOWN — это указатель на интерфейс IUnknown, который является базовым интерфейсом для всех COM-объектов.
    DWORD cookie_;
    std::string inXml_;
    BSTR outXml_;
    EventSink* eventSink_;
    Math* math_;
    LPDISPATCH mathUnknown_;
};
#endif // SCANNERCONNECTERWINIMPL_H
