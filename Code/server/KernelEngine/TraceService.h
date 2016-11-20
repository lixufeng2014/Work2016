#ifndef TRACE_SERVICE_HEAD_FILE
#define TRACE_SERVICE_HEAD_FILE

#pragma once

#include "KernelEngineHead.h"

//////////////////////////////////////////////////////////////////////////

//׷�ٷ���
class KERNEL_ENGINE_CLASS CTraceService
{
	//��������
protected:
	//���캯��
	CTraceService();

	//��������
public:
	//���÷���
	static bool SetTraceService(IUnknownEx * pIUnknownEx);
	//��ȡ����
	static VOID * GetTraceService(const IID & Guid, DWORD dwQueryVer);
	//��ȡ����
	static VOID * GetTraceServiceManager(const IID & Guid, DWORD dwQueryVer);

	//״̬����
public:
	//׷��״̬
	static bool IsEnableTrace(enTraceLevel TraceLevel);
	//׷�ٿ���
	static bool EnableTrace(enTraceLevel TraceLevel, bool bEnableTrace);

	//���ܺ���
public:
	//׷����Ϣ
	static bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
};

//////////////////////////////////////////////////////////////////////////

//׷�ٷ���
class KERNEL_ENGINE_CLASS CRichEditTrace : public CRichEditCtrl, public ITraceService
{
	//��������
protected:
	LONG							m_lMaxLineCount;					//�������
	LONG							m_lReserveLineCount;				//��������
	BYTE							m_cbBuffer[MAX_ASYNCHRONISM_DATA];	//��ʱ����

	//�������
protected:
	CDataQueue						m_DataQueue;						//���ݶ���
	CCriticalSection				m_CriticalSection;					//ͬ������

	//��������
public:
	//���캯��
	CRichEditTrace();
	//��������
	virtual ~CRichEditTrace();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID __cdecl Release() { return; }
	//�ӿڲ�ѯ
	virtual VOID * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//��Ϣ�ӿ�
public:
	//׷����Ϣ
	virtual bool __cdecl TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);

	//���غ���
protected:
	//�󶨺���
	virtual VOID PreSubclassWindow();

	//���ܺ���
public:
	//������Ϣ
	bool LoadMessage(LPCTSTR pszFileName);
	//������Ϣ
	bool SaveMessage(LPCTSTR pszFileName);
	//���ò���
	bool SetParameter(LONG lMaxLineCount, LONG lReserveLineCount);

	//��������
private:
	//���÷���
	VOID InitializeService();
	//��ȡ��ɫ
	COLORREF GetTraceColor(enTraceLevel TraceLevel);
	//�����ִ�
	bool InsertString(LPCTSTR pszString, CHARFORMAT2 & CharFormat);

	//�ص�����
private:
	//���ػص�
	static DWORD CALLBACK LoadCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);
	//����ص�
	static DWORD CALLBACK SaveCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);

	//�˵�����
protected:
	//ɾ����Ϣ
	VOID OnClearAll();
	//ȫ��ѡ��
	VOID OnSelectAll();
	//�����ַ�
	VOID OnCopyString();
	//������Ϣ
	VOID OnSaveString();
	//ɾ���ַ�
	VOID OnDeleteString();

	//��Ϣӳ��
protected:
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�Ҽ���Ϣ
	VOID OnRButtonDown(UINT nFlags, CPoint point);
	//׷����Ϣ
	LRESULT OnTraceServiceMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif