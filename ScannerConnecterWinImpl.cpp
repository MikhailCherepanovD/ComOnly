#include "ScannerConnecterWinImpl.h"
#include <Math.h>
ScannerConnecterWinImpl::ScannerConnecterWinImpl(QObject* parent):
    ScannerConnecter{parent},
    scannerInterface_{NULL},
    appHandle_{0},
    scannersNumber_{0},
    scannersInfoXml_{0},
    scannersArray_{NULL},
    outXml_{0}
{
    // Строка подписки на событие
    inXml_ = "<inArgs>"
        "<cmdArgs><arg-int>"
        "1"
        "</arg-int><arg-int>"
        "1"
        "</arg-int></cmdArgs></inArgs>";

    qDebug()<< "Scanner state is: "+ getStateStr();
    comObjectInitialize();
    qDebug()<< "Scanner state is: "+ getStateStr();

    if(currentState!=ScannerState::initialized){
        //TODO: понять что будем делать при ошибках
        return;
    }

    bindUnknownIntarface();
    qDebug()<< "Scanner state is: "+ getStateStr();
    if(currentState!=ScannerState::bindUnknown){
        //TODO: понять что будем делать при ошибках
        return;
    }

    openScannerConnection();
    qDebug()<< "Scanner state is: "+ getStateStr();

    if(currentState!=ScannerState::opened){
        //TODO: понять что будем делать при ошибках
        return;
    }

    registerEvent();
    qDebug()<< "Scanner state is: "+ getStateStr();

    if(currentState!=ScannerState::eventRegistered){
        //TODO: понять что будем делать при ошибках
        return;
    }
}




ScannerConnecterWinImpl::~ScannerConnecterWinImpl(){
    //Удалаяем событие с регистрации
    LONG status = -1;
    CComBSTR inXmlC = inXml_.c_str();
    CComBSTR outXmlC;
    HRESULT hr = scannerInterface_->ExecCommand(UNREGISTER_FOR_EVENTS, &inXmlC, &outXml_, &status);
    if ((hr == S_OK) && (status == STATUS_SUCCESS)){
        currentState = ScannerState::eventUnregistered;
    }
    else{
        currentState = ScannerState::failedUnRegisterEvent;
    }
    qDebug()<< "Scanner state is: "+ getStateStr();

    // Закрываем соединение
    status = -1;
    hr = scannerInterface_->Close(0, &status);
    if ((hr == S_OK) && (status == STATUS_SUCCESS)){
        currentState = ScannerState::closed;
    }
    else{
        currentState = ScannerState::failedClosed;
    }
    qDebug()<< "Scanner state is: "+ getStateStr();

    //Отвязываемся от COM объекта
    if(scannerInterface_){
        if(cookie_ != 0 && eventSink_){
//            BOOL stat = AfxConnectionUnadvise(scannerInterface_, DIID__ICoreScannerEvents, eventSinkUnknown_, FALSE, cookie_);
//            qDebug()<<"AfxConnectionUnadvise status"<<stat;
            delete eventSink_;
            eventSink_=0;
            cookie_=0;
            scannerInterface_->Release();
        }
    }
    CoUninitialize();
    currentState = ScannerState::uninitialized;
    qDebug()<< "Scanner state is: "+ getStateStr();
}



void ScannerConnecterWinImpl::comObjectInitialize(){
    CoInitialize(NULL); // Разрешает создание COM объектов
    HRESULT hr = CoCreateInstance(CLSID_CCoreScanner, NULL, CLSCTX_ALL, IID_ICoreScanner, ((void**)&scannerInterface_));
    if(FAILED(hr)){
        currentState = ScannerState::failedInitializeComObject;
    }
    else if(!scannerInterface_){
        currentState = ScannerState::failedCreationScannerIntarface;
    }
    else{
        currentState = ScannerState::initialized;
    }

}

void printHResultError(HRESULT hr) {
    LPVOID lpMsgBuf;
    DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;

    FormatMessageA(
        flags,
        nullptr,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&lpMsgBuf,
        0,
        nullptr
    );

    qDebug() << QString("HRESULT: 0x%1").arg(hr, 8, 16, QLatin1Char('0'));

    if (lpMsgBuf) {
        qDebug() << "System message:" << QString::fromLocal8Bit((char*)lpMsgBuf).trimmed();
        LocalFree(lpMsgBuf);
    } else {
        qDebug() << "Не удалось получить системное сообщение.";
    }

    // Доп. расшифровка для часто встречающихся HRESULT'ов
    switch (hr) {
        case E_POINTER:      qDebug() << "Описание: Неверный (нулевой) указатель."; break;
        case E_FAIL:         qDebug() << "Описание: Общее сбойное завершение операции."; break;
        case E_NOINTERFACE:  qDebug() << "Описание: Интерфейс не поддерживается."; break;
        case E_ACCESSDENIED: qDebug() << "Описание: Доступ запрещён."; break;
        case E_OUTOFMEMORY:  qDebug() << "Описание: Недостаточно памяти."; break;
        default:             qDebug() << "Описание: Неизвестный HRESULT или без расшифровки."; break;
    }
}
//eventSink_ = new EventSink();
//eventSinkUnknown_ = eventSink_->GetIDispatch(FALSE);//указатель на интерфейс IDispatch  от объекта EventSink
//qDebug()<<"eventSinkUnknown = eventSink->GetIDispatch(FALSE); done";
//IDispatch - Интерфейс в COM, который позволяет вызывать методы и получать свойства объектов динамически

//    math_ = new Math();
//    IUnknown* pUnk = static_cast<IUnknown*>(math_);
//    math_->AddRef();
//    BOOL stat = AfxConnectionAdvise(scannerInterface_, DIID__ICoreScannerEvents,pUnk /*eventSinkUnknown_*/, FALSE, &cookie_);// подключили scanner_interface к scanner_event_sink_unknown
//    qDebug()<<" BOOL stat = AfxConnectionAdvise(scannerInterface, DIID__ICoreScannerEvents, eventSinkUnknown, FALSE, &cookie); done";
//    if(stat != 0){
//        currentState = ScannerState::bindUnknown;
//    }else{
//        currentState = ScannerState::failedBindUnknown;
//    }




//void ScannerConnecterWinImpl::bindUnknownIntarface(){
//    eventSink_ = new EventSink();
//    eventSinkUnknown_ = eventSink_->GetIDispatch(FALSE);//указатель на интерфейс IDispatch  от объекта EventSink
//    IConnectionPointContainer* pConnectionPointContainer = nullptr;
//    HRESULT hr = scannerInterface_->QueryInterface(IID_IConnectionPointContainer,(void**)&pConnectionPointContainer);
//    if(FAILED(hr)){
//       currentState = ScannerState::failedBindUnknown;
//       return;
//    }
//    IConnectionPoint* pConnectionPoint = nullptr;
//    hr = pConnectionPointContainer->FindConnectionPoint(DIID__ICoreScannerEvents, &pConnectionPoint);
//    if (FAILED(hr)) {
//        qDebug()<<"err1";
//        currentState = ScannerState::failedBindUnknown;
//        return;
//    }
//    hr = pConnectionPoint->Advise(eventSinkUnknown_, &cookie_);
//    printHResultError(hr);
//    if (FAILED(hr)) {
//        qDebug()<<"err2";
//        currentState = ScannerState::failedBindUnknown;
//        return;
//    }
//    currentState = ScannerState::bindUnknown;
//}

void ScannerConnecterWinImpl::bindUnknownIntarface(){
    math_ = new Math();
    IDispatch* mathUnknown = nullptr;
    HRESULT hrQueryInterface = math_->QueryInterface(IID_IDispatch,(void**)&mathUnknown);
    if(FAILED(hrQueryInterface)){
       currentState = ScannerState::failedBindUnknown;
       qDebug()<<"math_->QueryInterface";
       return;
    }

    IConnectionPointContainer* pConnectionPointContainer = nullptr;
    HRESULT hr = scannerInterface_->QueryInterface(IID_IConnectionPointContainer,(void**)&pConnectionPointContainer);

    if(FAILED(hr)){
       currentState = ScannerState::failedBindUnknown;
       qDebug()<<"Failed  scannerInterface_->QueryInterface";
       return;
    }

    IConnectionPoint* pConnectionPoint = nullptr; // точка подключения к интерфейсу
    hr = pConnectionPointContainer->FindConnectionPoint(DIID__ICoreScannerEvents, &pConnectionPoint); //DIID исходящего интерфейса, возвращает указатель на точку подключения

    if (FAILED(hr)) {
        qDebug()<<"Failed pConnectionPointContainer->FindConnectionPoint";

        currentState = ScannerState::failedBindUnknown;
        return;
    }
    hr = pConnectionPoint->Advise(pConnectionPointContainer, &cookie_);

    if (FAILED(hr)) {
        qDebug()<<"Failed  pConnectionPoint->Advise";
        qDebug()<<"HRESULT facility: " <<HRESULT_FACILITY(hr);// Возвращает идентификаторы средств: 4 - FACILITY_ITF
        qDebug()<<"HRESULT code:" <<HRESULT_CODE(hr); //514
        bool f = hr == CONNECT_E_CANNOTCONNECT; //	The sink does not support the interface required by this connection point.
        // Advice documentation: https://learn.microsoft.com/en-us/windows/win32/api/ocidl/nf-ocidl-iconnectionpoint-advise
        qDebug()<<"hr == :" <<f;
        currentState = ScannerState::failedBindUnknown;
        return;
    }
    currentState = ScannerState::bindUnknown;
}


void ScannerConnecterWinImpl::openScannerConnection(){
    const SHORT numberOfScannerTypes = 1;
    SHORT scannerTypes[numberOfScannerTypes];
    LONG status = -1;
    SAFEARRAYBOUND bound[numberOfScannerTypes];
    bound[0].lLbound = 0;
    bound[0].cElements = numberOfScannerTypes;
    scannerTypes[0] = SCANNER_TYPES_ALL;
    SAFEARRAY* scannerTypesArray = SafeArrayCreate(VT_I2, 1, bound);
    for (long i = 0; i < numberOfScannerTypes; i++){
        SafeArrayPutElement(scannerTypesArray, &i, &scannerTypes[i]);
    }
    HRESULT hr = scannerInterface_->Open(
        appHandle_,            // Application handle
        scannerTypesArray,     // Array of scanner types
        numberOfScannerTypes,  // Length of scanner types array
        &status);              // Command execution success/failure return status

    if(hr == S_OK && status == STATUS_SUCCESS){
        currentState = ScannerState::opened;
    }
    else{
        currentState = ScannerState::failedScannerOpenning;
    }
    SafeArrayDestroy(scannerTypesArray);
}



void ScannerConnecterWinImpl::registerEvent(){
    CComBSTR inXmlC = inXml_.c_str();
    CComBSTR outXmlC;
    LONG status=-1;
    HRESULT hr = scannerInterface_->ExecCommand(REGISTER_FOR_EVENTS, &inXmlC, &outXml_, &status); // добавлили обработчик

    if(hr == S_OK && status == STATUS_SUCCESS){
        currentState = ScannerState::eventRegistered;
    }else{
        currentState = ScannerState::failedRegisterEvent;
    }
    qDebug()<<getStateStr();
}
