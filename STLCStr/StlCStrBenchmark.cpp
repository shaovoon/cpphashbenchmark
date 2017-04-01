#include "StdAfx.h"
#include "StlCStrBenchmark.h"
#include <mmsystem.h>
#include <cstdio>
#include <strsafe.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "strsafe.lib")

StlCStrBenchmark::StlCStrBenchmark(void)
{
	m_szMapName = L"STL Map (CString)";
	m_szMultimapName = L"STL Multimap (CString)";
	m_szSetName = L"STL Set (CString)";
	m_szMultisetName = L"STL Multiset (CString)";
}

StlCStrBenchmark::~StlCStrBenchmark(void)
{
	Destroy();
}

void StlCStrBenchmark::Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString)
{
	m_pvecEngDict = pvecEngDictCString;
}

void StlCStrBenchmark::Destroy()
{
	if(m_map.size()>0) m_map.clear();
	if(m_multimap.size()>0) m_multimap.clear();
	if(m_set.size()>0) m_set.clear();
	if(m_multiset.size()>0) m_multiset.clear();
}

bool StlCStrBenchmark::PopulateMap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(m_map.size()>0)
		m_map.clear();

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
		m_map.insert(std::make_pair((*m_pvecEngDict)[i], std::rand()));
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

bool StlCStrBenchmark::PopulateMultimap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(m_multimap.size()>0)
		m_multimap.clear();

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
			m_multimap.insert(std::make_pair((*m_pvecEngDict)[i], std::rand()));
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

bool StlCStrBenchmark::PopulateSet(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(m_set.size()>0)
		m_set.clear();

	if(m_pvecEngDict->size()<=0)
		return false;

	if(pName==NULL)
	{
		if(pLen) *pLen = m_szSetName.length();
		return false;
	}

	StringCchCopy(pName, *pLen, m_szSetName.c_str() );
	if(pLen)
	{
		if(*pLen > m_szSetName.length())
			*pLen = m_szSetName.length();
	}

	DWORD dwStartTime = timeGetTime();

	for(size_t i=0; i<m_pvecEngDict->size(); ++i)
	{
		m_set.insert((*m_pvecEngDict)[i]);
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

bool StlCStrBenchmark::PopulateMultiset(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(m_multiset.size()>0)
		m_multiset.clear();

	if(m_pvecEngDict->size()<=0)
		return false;

	if(pName==NULL)
	{
		if(pLen) *pLen = m_szMultisetName.length();
		return false;
	}

	StringCchCopy(pName, *pLen, m_szMultisetName.c_str() );
	if(pLen)
	{
		if(*pLen > m_szMultisetName.length())
			*pLen = m_szMultisetName.length();
	}

	DWORD dwStartTime = timeGetTime();

	size_t outerloop = 2;
	size_t innerloop = m_pvecEngDict->size()/outerloop;

	for(size_t j=0; j<outerloop; ++j)
	{
		for(size_t i=0; i<innerloop; ++i)
		{
			m_multiset.insert((*m_pvecEngDict)[i]);
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

bool StlCStrBenchmark::BenchmarkMap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
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
		auto it = m_map.find((*m_pvecEngDict)[rand()]);
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

bool StlCStrBenchmark::BenchmarkMultimap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
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
		auto pairIt = m_multimap.equal_range((*m_pvecEngDict)[rand()]);
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

bool StlCStrBenchmark::BenchmarkSet(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pName==NULL)
	{
		if(pLen) *pLen = m_szSetName.length();
		return false;
	}

	StringCchCopy(pName, *pLen, m_szSetName.c_str() );
	if(pLen)
	{
		if(*pLen > m_szSetName.length())
			*pLen = m_szSetName.length();
	}

	DWORD dwStartTime = timeGetTime();

	srand(nRandomSeed);

	for(size_t i=0; i<nTotal; ++i)
	{
		auto it = m_set.find((*m_pvecEngDict)[rand()]);
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

bool StlCStrBenchmark::BenchmarkMultiset(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(pName==NULL)
	{
		if(pLen) *pLen = m_szMultisetName.length();
		return false;
	}

	StringCchCopy(pName, *pLen, m_szMultisetName.c_str() );
	if(pLen)
	{
		if(*pLen > m_szMultisetName.length())
			*pLen = m_szMultisetName.length();
	}

	DWORD dwStartTime = timeGetTime();

	srand(nRandomSeed);

	for(size_t i=0; i<nTotal; ++i)
	{
		auto pairIt = m_multiset.equal_range((*m_pvecEngDict)[rand()]);
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

