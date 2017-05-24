
#include "CzkSolveMvc.h"

#include "CHvdcDefs.h"
#include "CxbDefs.h"
#include "CxbDev3pVSrc.h"

#include "CxbRwOrderMvc.h"
#include "CxbParams.h"


void CzkSolveMvc::Init(CxbHvdcGrid* vGrid)
{
	pzkHvdc = vGrid;
	//
	pzkProfile = new CzkProfile();
	pzkProfile->Init();

	//
	pzkResult = new CzkResult();
	pzkResult->Init();

	//
	pzkSolves = new CzkSolves();
	pzkSolves->Init(pzkProfile, pzkHvdc);

/////////////////////////////////////////////
	pxbHvdc = pzkHvdc;
	pxbProfile = pzkProfile;
	pxbResult  = pzkResult;
	pxbSolves = pzkSolves;
}


void CzkSolveMvc::Test(int vGNDType)
{
	doPrepare_hRLC();

	//
	pxbOrder->GroundType = vGNDType;
	//
	//pxbSolves->Init(pxbProfile, pxbHvdc);

	//
	doNewSolves(vGNDType);

	//�ڵ���
	doNodeID();

	doStationSort();

	//��ʼ�������þ���
	doInitMatrix();

	doRun();

}


void CzkSolveMvc::doPrepare_hRLC()
{
	double vFreStart = pzkProfile->pzkOrder->FreStart;

	double vFreStep = pzkProfile->pzkOrder->FreStep;

	int vFreDim = pzkProfile->pzkOrder->FreDim;

	//���������豸�ĸ���г���迹��
	pzkHvdc->Prepare_hRLC(vFreStart, vFreStep, vFreDim);

}

void CzkSolveMvc::doRun()
{
	//������

	//���ǹ���(����ˮƽ)��DCFƫ�����͡�г������
	//doPrepare_U3p(pzkProfile->pzkOrder->CreateCaseID());

	int vDim = pzkProfile->pzkOrder->FreDim;

	double vFreStart = pzkProfile->pzkOrder->FreStart;

	double vFreStep = pzkProfile->pzkOrder->FreStep;

	//г������1-hMax()
	for (int i = 1; i <= vDim; i++)
		//int i = 1;
	{
		cout << "----Ƶ��:  " << vFreStart + vFreStep * i << "-----" << endl;

		pzkProfile->hOrder = i;
		pzkProfile->ReSetData();

		pzkSolves->Run();

	}

	//��¼���
	doRecordResult();

}

void CzkSolveMvc::doRecordResult()
{
	//������
	static int vN = 1;
	string vCaseID = pzkProfile->pzkOrder->CreateCaseID();

	//pzkResult->mcResultMap[vCaseID]=

	cout << "�迹ɨ��:";
	cout << vCaseID;
	cout << "%";
	cout << pzkProfile->pzkOrder->PdPer;

	cout << "======" << vN++;

	cout << endl;

}
