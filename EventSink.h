/*******************************************************************************************
* @file event_sink.h
* @version 1.0.0.1
* @date 2020-05-21
* @copyright ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
********************************************************************************************/

#define _AFXDLL
#pragma once
#include <QObject>
#include "afxctl.h"
#include "afxwin.h"
#include "afxcmn.h"


//!
//! \brief Класс обработчик ScannerCore events
//!
class EventSink : public CCmdTarget
{
    DECLARE_DYNAMIC(EventSink)
public:
    EventSink();
    virtual ~EventSink();
    void OnScanDataEvent(short event_type, BSTR scan_data);
protected:
    DECLARE_MESSAGE_MAP()
    DECLARE_DISPATCH_MAP()
    DECLARE_INTERFACE_MAP()
private:
};

