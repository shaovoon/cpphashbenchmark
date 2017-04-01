#include "StdAfx.h"
#include "AtlBenchmark.h"
#include <mmsystem.h>
#include <cstdio>
#include <strsafe.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "strsafe.lib")

AtlBenchmark::AtlBenchmark(void)
{
	m_szMapName = L"ATL RB Map (CString)";
	m_szMultimapName = L"ATL RB Multimap (CString)";
	m_szSetName = L"ATL Set (CString)";
	m_szMultisetName = L"ATL Multiset (CString)";
}

AtlBenchmark::~AtlBenchmark(void)
{
	Destroy();
}

void AtlBenchmark::Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString)
{
	m_pvecEngDict = pvecEngDictCString;
}

void AtlBenchmark::Destroy()
{
	if(m_map.GetCount()>0) m_map.RemoveAll();
	if(m_multimap.GetCount()>0) m_multimap.RemoveAll();
}

bool AtlBenchmark::PopulateMap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
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

bool AtlBenchmark::PopulateMultimap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(m_multimap.GetCount()>0)
		m_multimap.RemoveAll();

	if(m_pvecEngDict->size()<=0)
		return false;

	if(pName==NULL)
	{
		if(pLen) *pLen = m_szMultimapName.length();
		return false;
	}

	StringCchCopy(pName, *pLen, m_szMultimapName.c_str() );
	if(pLen)
	{
		if(*pLen > m_szMultimapName.length())
			*pLen = m_szMultimapName.length();
	}


	DWORD dwStartTime = timeGetTime();

	size_t outerloop = 2;
	size_t innerloop = m_pvecEngDict->size()/outerloop;

	for(size_t j=0; j<outerloop; ++j)
	{
		for(size_t i=0; i<innerloop; ++i)
		{
			m_multimap.Insert((*m_pvecEngDict)[i], std::rand());
			if(i%10000 == 0 && pProgress)
			{
				*pProgress = ((j*innerloop)+i)*HUNDRED_PERCENT / m_pvecEngDict->size();
			}
		}
	}

	DWORD dwEndTime = timeGetTime();

	if(pProgress) 
		*pProgress = HUNDRED_PERCENT;

	if(pTimeTaken)
		*pTimeTaken = dwEndTime - dwStartTime;

	return true;
}

bool AtlBenchmark::PopulateSet(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

bool AtlBenchmark::PopulateMultiset(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

bool AtlBenchmark::BenchmarkMap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
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
		bool b = m_map.Lookup((*m_pvecEngDict)[rand()], val);
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

bool AtlBenchmark::BenchmarkMultimap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pName==NULL)
	{
		if(pLen) *pLen = m_szMultimapName.length();
		return false;
	}

	StringCchCopy(pName, *pLen, m_szMultimapName.c_str() );
	if(pLen)
	{
		if(*pLen > m_szMultimapName.length())
			*pLen = m_szMultimapName.length();
	}

	DWORD dwStartTime = timeGetTime();

	srand(nRandomSeed);

	for(size_t i=0; i<nTotal; ++i)
	{
		POSITION pos = m_multimap.FindFirstWithKey((*m_pvecEngDict)[rand()]);
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

bool AtlBenchmark::BenchmarkSet(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

bool AtlBenchmark::BenchmarkMultiset(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	return false;
}

