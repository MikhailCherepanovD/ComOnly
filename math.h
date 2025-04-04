#ifndef MATH_H
#define MATH_H
#include <Unknwn.h>
#include <objbase.h>
#include <windows.h>
#include <guiddef.h>
extern const IID IID_IMath;
class Math : public IDispatch
{
public:
    //IUnknown
    STDMETHOD(QueryInterface( REFIID, void** ))override;
    STDMETHOD_(ULONG, AddRef())override;
    STDMETHOD_(ULONG,Release())override;
    //IDispatch:
    STDMETHOD(GetTypeInfoCount)(UINT* pctinfo)override;
    STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo)override;

    //! \brief Функция для сопоставления названий методов и их id для последующего вызова функцией invoke
    //! \brief Вызывается неявно системой управления COM объектами
    //!
    //! \param riid - всегда IID_NULL - не используется (in)
    //! \param rgszNames -  массив имен, переданных скриптом (in)
    //! \param cNames -  количство имен в rgszNames (in)
    //! \param lcid - id языка (in)
    //! \param rgDispId - массив, в который записываются соотвествующие id для каждого имени(память в нем уже выделена ОС) (out)
    STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
                             LCID lcid, DISPID* rgDispId)override;


    //! \brief Вызов методов объекта через его интерфейс.
    //! \brief Вызывается неявно системой управления COM объектами
    //!
    //! \param dispId - идентификатор диспетчеризации(id события из документации сканера) (in)
    //! \param riid - всегда IID_NULL (in) *не использую
    //! \param lcid -  id языка (in) *не использую
    //! \param wFlags - флаги, описывающите контекст вызова invoke (in) *не использую
    //! \param pDispParams - указатель на структуру параметров вызываемого метода (in)
    //! \param pVarResult - результат вызова метода (out) *не использую
    //! \param pExepInfo  - возникшие исключения (out) *не использую
    //! \param puArgErr  - индекс аргумента ошибки (out) *не использую
    STDMETHOD(Invoke)( DISPID dispId, REFIID riid, LCID lcid, WORD wFlags,
                       DISPPARAMS* pDispParams, VARIANT* pVarResult,EXCEPINFO* pExepInfo, UINT* puArgErr) override;
    //IMath
    //STDMETHOD(Add( long, long, long*));

private:
   // Новая переменная-член класса добавлена для подсчета
   // обращений извне к интерфейсу объекта
   DWORD m_lRef;

public:
   Math( );
};
#endif // MATH_H
