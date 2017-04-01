#include "StdAfx.h"
#include "LoadDll.h"



LoadDll::LoadDll(void)
{
	m_hDll = NULL;
	m_szDllPath = L"";
	m_bReady = false;

	pfnInitialize = NULL;
	pfnDestroy = NULL;
	pfnPopulateMap = NULL;
	pfnPopulateMultimap = NULL;
	pfnPopulateSet = NULL;
	pfnPopulateMultiset = NULL;
	pfnBenchmarkMap = NULL;
	pfnBenchmarkMultimap = NULL;
	pfnBenchmarkSet = NULL;
	pfnBenchmarkMultiset = NULL;
	pfnGetIndex = NULL;
	pfnSupportMap = NULL;
	pfnSupportMultimap = NULL;
	pfnSupportSet = NULL;
	pfnSupportMultiset = NULL;

}


LoadDll::~LoadDll(void)
{
	Destroy();
}

void LoadDll::Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString)
{
	if(m_hDll)
	{
		FreeLibrary(m_hDll);
		m_hDll=NULL;
	}

	if(m_szDllPath.empty())
	{
		m_bReady = false;
		return;
	}

	m_hDll = LoadLibrary(m_szDllPath.c_str());

	if(m_hDll==NULL)
	{
		m_bReady = false;
		return;
	}

	m_bReady = false;
	pfnInitialize = (InitializeFn) GetProcAddress(m_hDll, "Initialize");

	if(!pfnInitialize)
		return;

	pfnDestroy = (DestroyFn) GetProcAddress(m_hDll, "Destroy");

	if(!pfnDestroy)
		return;

	pfnPopulateMap = (PopulateFn) GetProcAddress(m_hDll, "PopulateMap");

	if(!pfnPopulateMap)
		return;

	pfnPopulateMultimap = (PopulateFn) GetProcAddress(m_hDll, "PopulateMultimap");

	if(!pfnPopulateMultimap)
		return;

	pfnPopulateSet = (PopulateFn) GetProcAddress(m_hDll, "PopulateSet");

	if(!pfnPopulateSet)
		return;

	pfnPopulateMultiset = (PopulateFn) GetProcAddress(m_hDll, "PopulateMultiset");

	if(!pfnPopulateMultiset)
		return;

	pfnBenchmarkMap = (BenchmarkFn) GetProcAddress(m_hDll, "BenchmarkMap");

	if(!pfnBenchmarkMap)
		return;

	pfnBenchmarkMultimap = (BenchmarkFn) GetProcAddress(m_hDll, "BenchmarkMultimap");

	if(!pfnBenchmarkMultimap)
		return;

	pfnBenchmarkSet = (BenchmarkFn) GetProcAddress(m_hDll, "BenchmarkSet");

	if(!pfnBenchmarkSet)
		return;

	pfnBenchmarkMultiset = (BenchmarkFn) GetProcAddress(m_hDll, "BenchmarkMultiset");

	if(!pfnBenchmarkMultiset)
		return;

	pfnGetIndex = (GetIndexFn) GetProcAddress(m_hDll, "GetIndex");

	if(!pfnGetIndex)
		return;

	pfnSupportMap = (SupportFn) GetProcAddress(m_hDll, "SupportMap");

	if(!pfnSupportMap)
		return;

	pfnSupportMultimap = (SupportFn) GetProcAddress(m_hDll, "SupportMultimap");

	if(!pfnSupportMultimap)
		return;

	pfnSupportSet = (SupportFn) GetProcAddress(m_hDll, "SupportSet");

	if(!pfnSupportSet)
		return;

	pfnSupportMultiset = (SupportFn) GetProcAddress(m_hDll, "SupportMultiset");

	if(!pfnSupportMultiset)
		return;

	if(pfnInitialize)
		pfnInitialize(pvecEngDict, pvecEngDictCString);

	m_bReady = true;
}

void LoadDll::Destroy()
{
	if(pfnDestroy)
		pfnDestroy();


	if(m_hDll)
	{
		FreeLibrary(m_hDll);
	}

	m_hDll=NULL;

	m_bReady = false;

	pfnInitialize = NULL;
	pfnDestroy = NULL;
	pfnPopulateMap = NULL;
	pfnPopulateMultimap = NULL;
	pfnPopulateSet = NULL;
	pfnPopulateMultiset = NULL;
	pfnBenchmarkMap = NULL;
	pfnBenchmarkMultimap = NULL;
	pfnBenchmarkSet = NULL;
	pfnBenchmarkMultiset = NULL;
	pfnGetIndex = NULL;

}

bool LoadDll::PopulateMap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pfnPopulateMap)
		return pfnPopulateMap(pTimeTaken, pProgress, pName, pLen);

	return false;
}

bool LoadDll::PopulateMultimap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pfnPopulateMultimap)
		return pfnPopulateMultimap(pTimeTaken, pProgress, pName, pLen);

	return false;
}

bool LoadDll::PopulateSet(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pfnPopulateSet)
		return pfnPopulateSet(pTimeTaken, pProgress, pName, pLen);

	return false;
}

bool LoadDll::PopulateMultiset(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pfnPopulateMultiset)
		return pfnPopulateMultiset(pTimeTaken, pProgress, pName, pLen);

	return false;
}

bool LoadDll::BenchmarkMap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pfnBenchmarkMap)
		return pfnBenchmarkMap(nRandomSeed, nTotal, pTimeTaken, pProgress, pName, pLen);

	return false;
}

bool LoadDll::BenchmarkMultimap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pfnBenchmarkMultimap)
		return pfnBenchmarkMultimap(nRandomSeed, nTotal, pTimeTaken, pProgress, pName, pLen);

	return false;
}

bool LoadDll::BenchmarkSet(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pfnBenchmarkSet)
		return pfnBenchmarkSet(nRandomSeed, nTotal, pTimeTaken, pProgress, pName, pLen);

	return false;
}

bool LoadDll::BenchmarkMultiset(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pfnBenchmarkMultiset)
		return pfnBenchmarkMultiset(nRandomSeed, nTotal, pTimeTaken, pProgress, pName, pLen);

	return false;
}

int LoadDll::GetIndex()
{
	if(pfnGetIndex)
		return pfnGetIndex();

	return -1;
}

bool LoadDll::SupportMap()
{
	if(pfnSupportMap)
		return pfnSupportMap();

	return false;
}

bool LoadDll::SupportMultimap()
{
	if(pfnSupportMultimap)
		return pfnSupportMultimap();

	return false;
}

bool LoadDll::SupportSet()
{
	if(pfnSupportSet)
		return pfnSupportSet();

	return false;
}

bool LoadDll::SupportMultiset()
{
	if(pfnSupportMultiset)
		return pfnSupportMultiset();

	return false;
}
