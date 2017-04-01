#include "StdAfx.h"
#include "AtlHashBenchmark.h"
#include <mmsystem.h>
#include <cstdio>
#include <strsafe.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "strsafe.lib")

AtlHashBenchmark::AtlHashBenchmark(void)
{
	m_szMapName = L"ATL Hash Map (CString)";
	m_szMultimapName = L"ATL Hash Multimap (CString)";
	m_szSetName = L"ATL Hash Set (CString)";
	m_szMultisetName = L"ATL Hash Multiset (CString)";
}

AtlHashBenchmark::~AtlHashBenchmark(void)
{
	Destroy();
}

void AtlHashBenchmark::Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString)
{
	m_pvecEngDict = pvecEngDictCString;
}

void AtlHashBenchmark::Destroy()
{
	if(m_map.GetCount()>0) m_map.RemoveAll();
}

bool AtlHashBenchmark::PopulateMap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(m_map.GetCount()>0)
		m_map.RemoveAll();

	if(!m_pvecEngDict||m_pvecEngDict->size()<=0)
		return false;

	if(pName==NULL)
	{
		if(pLen) *pLen = m_szMapName.length();
		return false;
	}

	StringCchCopy(pName, *pLen, m_szMapName.c_str() );
	if(pLen)
	{
		if(*pLen > m_szMapName.length())
			*pLen = m_szMapName.length();
	}

	DWORD dwStartTime = timeGetTime();

	for(size_t i=0; i<m_pvecEngDict->size(); ++i)
	{
		POSITION pos = m_map.SetAt((*m_pvecEngDict)[i], std::rand());
		if(i%10000 == 0 && pProgress)
		{
			*pProgress = i * 1.0f / m_pvecEngDict->size() * HUNDRED_PERCENT;
		}
	}

	DWORD dwEndTime = timeGetTime();

	if(pProgress) 
		*pProgress = HUNDRED_PERCENT;

	if(pTimeTaken)
		*pTimeTaken = dwEndTime - dwStartTime;

	return true;
}

bool AtlHashBenchmark::PopulateMultimap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

bool AtlHashBenchmark::PopulateSet(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

bool AtlHashBenchmark::PopulateMultiset(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

bool AtlHashBenchmark::BenchmarkMap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pName==NULL)
	{
		if(pLen) *pLen = m_szMapName.length();
		return false;
	}

	StringCchCopy(pName, *pLen, m_szMapName.c_str() );
	if(pLen)
	{
		if(*pLen > m_szMapName.length())
			*pLen = m_szMapName.length();
	}

	DWORD dwStartTime = timeGetTime();

	srand(nRandomSeed);

	for(size_t i=0; i<nTotal; ++i)
	{
		int val = 0;
		int index = rand();
		bool b = m_map.Lookup((*m_pvecEngDict)[index], val);
		//CString szFormat;
		//szFormat.Format(L"Found : %s", b ? L"true" : L"false");
		//OutputDebugStringW(szFormat);

		if(i%10000 == 0 && pProgress)
		{
			*pProgress = i * 1.0f / nTotal * HUNDRED_PERCENT;
		}
	}

	DWORD dwEndTime = timeGetTime();

	if(pProgress) 
		*pProgress = HUNDRED_PERCENT;

	if(pTimeTaken)
		*pTimeTaken = dwEndTime - dwStartTime;

	return true;
}

bool AtlHashBenchmark::BenchmarkMultimap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

bool AtlHashBenchmark::BenchmarkSet(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

bool AtlHashBenchmark::BenchmarkMultiset(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

