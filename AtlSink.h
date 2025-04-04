//#ifndef ATLSINK_H
//#define ATLSINK_H

//#include <atlbase.h>
//#include <atlcom.h>
//#include <atlctl.h>
//#include <QString>
//#include <QDebug>

//// Заменить на актуальный LIBID и версию, если есть
//// GUID должен быть у интерфейса событий сканера
//// Например:
//#include "_core_scanner_i.c"

//class ATL_NO_VTABLE EventSink :
//    public CComObjectRootEx<CComSingleThreadModel>,
//    public IDispEventImpl<1, EventSink, &DIID__ICoreScannerEvents, &LIBID_CoreScanner, 1, 0>
//{
//public:
//    BEGIN_COM_MAP(EventSink)
//    END_COM_MAP()

//    BEGIN_SINK_MAP(EventSink)
//        SINK_ENTRY(1, 3, OnScanDataEvent) // 3 — DISPID ScanDataEvent
//    END_SINK_MAP()

//    void __stdcall OnScanDataEvent(short eventType, BSTR scanDataBSTR)
//    {
//        QString scanData = QString::fromWCharArray(scanDataBSTR, SysStringLen(scanDataBSTR));
//        qDebug() << "Was scanned:" << scanData;
//    }

//    void Advise(IDispatch* source)
//    {
//        m_source = source;
//        AtlAdvise(m_source, static_cast<ID ispatch*>(this), __uuidof(DIID_ICoreScannerEvents), &m_cookie);
//    }

//    void Unadvise()
//    {
//        if (m_cookie)
//        {
//            AtlUnadvise(m_source, __uuidof(DIID_ICoreScannerEvents), m_cookie);
//            m_cookie = 0;
//        }
//    }

//private:
//    CComPtr<IDispatch> m_source;
//    DWORD m_cookie = 0;
//};
//#endif // ATLSINK_H
