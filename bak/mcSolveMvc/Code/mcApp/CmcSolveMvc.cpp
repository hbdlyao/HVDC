///////////////////////////////////////////////////////////
//  CmcSolveMvc.cpp
//  Implementation of the Class CmcSolveMvc
//  Created on:      23-4��-2017 16:46:17
//  Original author: Administrator
///////////////////////////////////////////////////////////

#include "CmcParams.h"
#include "CHvdcFunc.h"

#include "CmcSolveMvc.h"
#include "CmcSolvesNormal.h"

#include "CmcRwOrderMvc.h"
#include "CmcRwResultMvc.h"

#include <iostream>


CmcSolveMvc::~CmcSolveMvc()
{
	Release();
}

void CmcSolveMvc::Release()
{
	pmcSolves->Clear();
	delete pmcSolves;
	pmcSolves = nullptr;

	pmcProfile->Clear();
	delete pmcProfile;
	pmcProfile = nullptr;

	pmcResult->Clear();
	delete pmcResult;
	pmcResult = nullptr;
}

void CmcSolveMvc::Clear()
{
	pmcSolves->Clear();

	pmcProfile->Clear();

	pmcResult->Clear();
}


void CmcSolveMvc::Init(CmcHvdcGrid* vGrid)
{
	pmcHvdc = vGrid;
	//
	pmcProfile = new CmcProfile();
	pmcProfile->Init();

	//
	pmcResult = new CmcResult();
	pmcResult->Init();

	//
	pmcSolves = new CmcSolves();
	pmcSolves->Init(pmcProfile, pmcHvdc);

}

void CmcSolveMvc::InitOrder(CmcOrder* vOrder)
{
	CalName = vOrder->CalName;

	pmcOrder = vOrder;

	pmcProfile->InitOrder(pmcOrder);
	pmcSolves->InitOrder(pmcOrder);
	
}

//************************************
// *�Ϸ���������·��г����������*
// �Ķ�����:  SaveResults
// �Ķ���:    �޿���
// �Ķ�����:  �޸�
// �Ķ�����:  1.��Ϊʹ��vRwMvc.OnSave����
// �Ķ�ʱ��:  2017/05/23
//************************************
void CmcSolveMvc::SaveResults()
{
	CmcRwResultMvc vRwMvc;

	vRwMvc.InitAdo(CmcParams::dbfFile);
	vRwMvc.Init(pmcResult);

	vRwMvc.OnSave(CmcParams::dbfFile);
}


void CmcSolveMvc::Test(int vGNDType)
{
	pmcOrder->GroundType = vGNDType;

	//pmcSolves->Init(pmcProfile, pmcHvdc);
	//
	doNewSolves(vGNDType);

	//�ڵ���
	doNodeID();

	//����վ����
	doStationSort();

	//��¼��վ������Ľڵ���
	//doRecordMeasureNode();

	//�����ֵ
	doPrepareNormal();

	//doRun();
}


//************************************
// *�Ϸ���������·��г����������*
// �Ķ�����:  Run
// �Ķ���:    �޿���
// �Ķ�����:  �޸�
// �Ķ�����:  1.���Ӳ�����Ϣ�����
// �Ķ�ʱ��:  2017/05/23
//************************************
void CmcSolveMvc::Run()
{
	cout << "Run---mc---" << endl;

	//�๤������
	doInitRun();

	//
	doRun_Ground(pmcOrder->Flag_Ground);

	//
	cout << endl;
}


int CmcSolveMvc::StaCount()
{
	return CmcParams::mcStationCount;
}

//************************************
// *�Ϸ���������·��г����������*
// �Ķ�����:  doRecordResult
// �Ķ���:    �޿���
// �Ķ�����:  �޸�
// �Ķ�����:  1.�޸Ĳ�����Ϣ�������ʽ
// �Ķ�ʱ��:  2017/05/23
//************************************
void CmcSolveMvc::doRecordResult()
{
	string vCaseID = pmcOrder->CreateCaseID();
	pmcResult->Record(CalName, vCaseID, pmcProfile->pmcStaData, pmcProfile->pmcStaDataN);

	//������
	static int vN = 1;
	cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	cout << "����·:";
	cout << vCaseID;
	cout << "%";
	cout.width(3);
	cout << pmcOrder->PdPer;

	cout << "======";
	cout.width(6);
	cout << vN++;

}


void CmcSolveMvc::doNodeID()
{
	pmcSolves->NodeID();
}


void CmcSolveMvc::doStationSort()
{
	pmcSolves->StationSort();
}


void CmcSolveMvc::doNewSolves(int vGNDType)
{
	pmcSolves->Clear();
	pmcSolves->NewSolves(vGNDType);
}


void CmcSolveMvc::doInitRun()
{
	//pmcSolves->Init(pmcProfile, pmcHvdc);
	//
	int vStaCount = StaCount();
	int vCaseCount = pmcOrder->CaseCount();

	pmcResult->Clear();
	pmcResult->Init(vStaCount, vCaseCount, pmcOrder->PdSize);
}


void CmcSolveMvc::doPrepareNormal()
{
	pmcSolves->PrepareNormal();
}

void CmcSolveMvc::doRun()
{
	pmcProfile->ResetData();
	//
	pmcSolves->Run();
	//��¼���
	doRecordResult();

}


void CmcSolveMvc::doRun_Ground(string vFlag)
{
	int vN = static_cast<int> (vFlag.size());

	//�������/��������/˫��/˫������
	for (int i = 0; i < vN; i++)
	{
		if (vFlag[i] == '1') //"1111"
		{
			pmcOrder->GroundType = GndTypeArr[i];

			//���ݽӵ��������� mcCalculate,���豸һһ��Ӧ
			doNewSolves(GndTypeArr[i]);

			//�ڵ���
			doNodeID();

			//����վ����
			doStationSort();

			//�����ֵ
			doPrepareNormal();

			//
			doRun_Rd(pmcOrder->Flag_Rd);

		}//if

	}//for
}


void CmcSolveMvc::doRun_Rd(string vFlag)
{
	int vN = static_cast<int> (vFlag.size());

	//���衢����
	for (int i = 0; i < vN; i++)
	{
		if (vFlag[i] == '1') //
		{
			pmcOrder->RdLevel = RdLevelArr[i];

			doRun_Ud(pmcOrder->Flag_Ud);

		}//if vFlag

	}//for
}


void CmcSolveMvc::doRun_Ud(string vFlag){

	int vN = static_cast<int> (vFlag.size());
	int vStaCount = StaCount();

	//ȫѹ/80%/70%
	for (int i = 0; i < vN; i++)
	{
		if (vFlag[i] == '1')
		{
			pmcOrder->UdLevel = UdLevelArr[i];

			if (pmcOrder->IsUacSwap)
				doRun_UacSwap(pmcOrder->Flag_Uac, 0, vStaCount);
			else
				doRun_Uac(pmcOrder->Flag_Uac);

		}//if

	}//for
}

void CmcSolveMvc::doRun_Uac(string vFlag){

	int vN = static_cast<int> (vFlag.size());
	int vStaCount = StaCount();

	//���/�/��С/��С
	for (int i = 0; i < vN; i++)
		if (vFlag[i] == '1')
		{
			for (int j = 0; j < vStaCount; j++)
				pmcOrder->UacLevel[j] = UacLevelArr[i];
			//
			doRun_Pd();
		}//if
}


void CmcSolveMvc::doRun_UacSwap(string vFlag, int vIndex, int vStaCount){

	int vN = static_cast<int> (vFlag.size());

	//vIndex��0��ʼ,��vIndex==vStaCount,˵�����еĻ���վ��������Uac
	if (vIndex == vStaCount)
		doRun_Pd();
	else
	{//���/�/��С/��С
		for (int i = 0; i < vN; i++)
			if (vFlag[i] == '1')
			{
				pmcOrder->UacLevel[vIndex] = UacLevelArr[i];

				doRun_UacSwap(vFlag, vIndex + 1, vStaCount);
			}//if

	}//else
}

void CmcSolveMvc::doRun_Pd()
{

	int vPdSize;

	vPdSize = pmcOrder->PdSize;

	for (int i = 0; i < vPdSize; i++)
	{
		pmcOrder->UpdatePdPercent(i);
		pmcOrder->IsUdCustomPre = false;

		if (pmcOrder->IsUdCustom) //ָ��Ud
			doRun_UdCustom(i);
		else
			doRun();

	}//for
}

void CmcSolveMvc::doRun_UdCustom(int vPdIndex)
{

	if (pmcOrder->UdCustomMap.count(vPdIndex) == 0)
		doRun();
	else
	{
		pmcOrder->IsUdCustomPre = true;
		pmcOrder->UdCustom = pmcOrder->UdCustomMap[vPdIndex];
		doRun();
	}
}

void CmcSolveMvcNormal::Init(CmcHvdcGrid * vGrid)
{
	pmcHvdc = vGrid;
	//
	pmcProfile = new CmcProfile();
	pmcProfile->Init();

	//
	pmcResult = new CmcResult();
	pmcResult->Init();

	//
	pmcSolves = new CmcSolvesNormal();
	pmcSolves->Init(pmcProfile, pmcHvdc);

}

void CmcSolveMvcNormal::Run()
{
	//pmcSolves->Init(pmcProfile, pmcHvdc);

	pmcOrder->InitNormal();

	//
	CmcSolveMvc::Run();
}

void CmcSolveMvcNormal::doRecordResult(){

	dynamic_cast<CmcSolvesNormal*>(pmcSolves)->SaveNorml();

	//������
	static int vN = 1;
	string vCaseID = pmcOrder->CreateCaseID();

	cout << "����·�:";
	cout << vCaseID;
	cout << "%";
	cout << pmcOrder->PdPer;

	cout << "======" << vN++;
}