#include "EventSink.h"
#include <atlbase.h>
#include "_core_scanner_i.c"
#include <iostream>
#include <string>
#include "afxdisp.h"  // MFC Automation classes
#include <QByteArray>
#include <QString>
#include <QDebug>


using namespace std;
//EventSink* ScannerEventSink;
IMPLEMENT_DYNAMIC(EventSink, CCmdTarget)
EventSink::EventSink() {
    // регистрирует объект как COM + OLE - автоматизация
    EnableAutomation();
}

EventSink::~EventSink(){}

BEGIN_MESSAGE_MAP(EventSink, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(EventSink, CCmdTarget)
    DISP_FUNCTION_ID(EventSink, "ScanDataEvent", 3, EventSink::OnScanDataEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(EventSink, CCmdTarget)
    INTERFACE_PART(EventSink, DIID__ICoreScannerEvents, Dispatch) //(DIID -  id класса)
END_INTERFACE_MAP()

void EventSink::OnScanDataEvent(short eventType, BSTR scanDataBSTR)
{
    wstring scanDataWstr(scanDataBSTR, SysStringLen(scanDataBSTR));
    QString scanDataQStr = QString::fromStdWString(scanDataWstr);
    qDebug()<<"Was scanned";
}















