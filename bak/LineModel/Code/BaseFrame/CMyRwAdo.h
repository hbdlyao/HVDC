#pragma once


#include <string>

#include "CMyDefs.h"

#pragma comment(lib,"ws2_32.lib")
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF"), rename("BOF","adoBOF")

using namespace std;

/**
 * Ado���ݿ�
 */
class CRwAdo
{

protected:
	//���ݿ�ָ��
	_ConnectionPtr pConnection = nullptr;

	//��¼ָ��
	_RecordsetPtr pRecordset = nullptr;

	//����ָ��
	_CommandPtr pCommand = nullptr;

	//StrTable dbfTable;

	string strConnect = "strConnect";

	string UserID = "";
	string Password = "";


public:
	~CRwAdo();


	/**
	 * StrTable dbfTable;
	 */
	virtual void InitDbf(string vDbf, string vUserID, string vPassword, string vSecurity);

	virtual bool IsEOF();
	//
	virtual bool IsOpen();
	//
	virtual bool OpenDBF();
	virtual bool CloseDBF();

	//
	virtual bool OpenSQL(string vSQL);
	virtual bool ExecSQL(string vSQL);

	virtual bool CloseTBL();

	//
	virtual void GetFieldValue(string vFieldName, _variant_t & vValue);
	virtual void SetFieldValue(string vFieldName, _variant_t vValue);

	virtual int Record_RowCount();

	//
	virtual void Record_MoveNext();
	virtual void Record_Update();
	virtual void Record_AddNew();

	//
	virtual void BeginTrans();
	virtual void CommitTrans();
	virtual void RollbackTrans();
};


/**
 * Ado_MDB���ݿ�
 */
class CRwAdo_MDB : public CRwAdo
{
public:
	virtual void InitDbf(string vDbf, string vUserID, string vPassword, string vSecurity);

};

class CRwAdo_Access : public CRwAdo
{
public:
	virtual void InitDbf(string vDbf, string vUserID, string vPassword, string vSecurity);

};