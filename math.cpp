#include "math.h"
#include <QDebug>
#include "_core_scanner_i.c"
const IID IID_IMath =
{ 0x12345678, 0x1234, 0x1234, { 0x12, 0x34, 0x56, 0x78, 0x90, 0xab } };

Math::Math( )
{
   m_lRef = 1;
}

STDMETHODIMP Math::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown)
    {
        *ppv = (IUnknown*)this;
    }
    else if(riid == IID_IDispatch){
        *ppv = (IDispatch*)this;
    }
    else{
        //*ppv = nullptr;
        //return E_NOINTERFACE;
        *ppv = this;
    }
    AddRef();
    return S_OK;
}
STDMETHODIMP_(ULONG) Math::Release( )
{
   InterlockedDecrement( &m_lRef );
   if ( m_lRef == 0 )
   {
      delete this;
      return 0;
   }
   else
      return m_lRef;
}

STDMETHODIMP_(ULONG) Math::AddRef( )
{
   InterlockedIncrement( &m_lRef );
   return m_lRef;
}

//IDISPATH
STDMETHODIMP Math::GetTypeInfoCount(UINT* pctinfo){
    *pctinfo = 0;
    return S_OK;
}
STDMETHODIMP Math::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo){
    return E_NOTIMPL;
}

STDMETHODIMP Math::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
                                 LCID lcid, DISPID* rgDispId){
     return E_NOTIMPL;
}

STDMETHODIMP Math::Invoke(DISPID dispId, REFIID riid, LCID lcid, WORD wFlags,
                   DISPPARAMS* pDispParams, VARIANT* pVarResult,EXCEPINFO* pExepInfo, UINT* puArgErr){
    if (dispId == 3) { // ID события ScanDataEvent
        qDebug() << "Scanned:";
    }
    return S_OK;
}


//STDMETHODIMP Math::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
//                                 LCID lcid, DISPID* rgDispId){
//    if(cNames==0 || rgszNames==0 || rgDispId){
//        return DISP_E_UNKNOWNNAME;
//    }

//    if (riid != IID_NULL){
//        return DISP_E_UNKNOWNINTERFACE;
//    }

//    // Пример: поддерживаем только метод "Add"
//    if (_wcsicmp(rgszNames[0], L"Add") == 0)   //_wcsicmp -  функция сравнения строк
//    {
//        rgDispId[0] = 3; // назначаем DISPID
//        return S_OK;
//    }

//    return DISP_E_UNKNOWNNAME;
//}

//STDMETHODIMP Math::Invoke(DISPID dispId, REFIID riid, LCID lcid, WORD wFlags,
//                   DISPPARAMS* pDispParams, VARIANT* pVarResult,EXCEPINFO* pExepInfo, UINT* puArgErr){
//    if (dispId == 3) { // ID события ScanDataEvent
//        if (pDispParams->cArgs >= 2) {
//            //short eventType = pDispParams->rgvarg[1].iVal;
//            //BSTR scanData = pDispParams->rgvarg[0].bstrVal;
//            long res;
//            Add(10, 10, &res);
//        }
//        return S_OK;
//    }
//    return DISP_E_MEMBERNOTFOUND;
//}

////MATH
//STDMETHODIMP Math::Add( long Op1, long Op2, long *pResult )
//{
//   *pResult = Op1 + Op2;
//   qDebug()<<"in add";
//   return S_OK;
//}


