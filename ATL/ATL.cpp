// STL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ATL.h"
#include "AtlBenchmark.h"

AtlBenchmark* g_pBench=NULL;

extern "C" ATL_API void Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString)
{
	g_pBench = new AtlBenchmark();
	g_pBench->Initialize(pvecEngDict, pvecEngDictCString);
}

extern "C" ATL_API void Destroy()
{
	if(g_pBench) 
	{
		g_pBench->Destroy();
		delete g_pBench;
		g_pBench = NULL;
	}
}

extern "C" ATL_API bool PopulateMap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(g_pBench) 
		return g_pBench->PopulateMap(pTimeTaken, pProgress, pName, pLen);

	return false;
}

extern "C" ATL_API bool PopulateMultimap(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(g_pBench) 
		return g_pBench->PopulateMultimap(pTimeTaken, pProgress, pName, pLen);

	return false;
}

extern "C" ATL_API bool PopulateSet(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(g_pBench) 
		return g_pBench->PopulateSet(pTimeTaken, pProgress, pName, pLen);

	return false;
}

extern "C" ATL_API bool PopulateMultiset(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(g_pBench) 
		return g_pBench->PopulateMultiset(pTimeTaken, pProgress, pName, pLen);

	return false;
}

extern "C" ATL_API bool BenchmarkMap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(g_pBench) 
		return g_pBench->BenchmarkMap(nRandomSeed, nTotal, pTimeTaken, pProgress, pName, pLen);

	return false;
}

extern "C" ATL_API bool BenchmarkMultimap(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(g_pBench) 
		return g_pBench->BenchmarkMultimap(nRandomSeed, nTotal, pTimeTaken, pProgress, pName, pLen);

	return false;
}

extern "C" ATL_API bool BenchmarkSet(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(g_pBench) 
		return g_pBench->BenchmarkSet(nRandomSeed, nTotal, pTimeTaken, pProgress, pName, pLen);

	return false;
}

extern "C" ATL_API bool BenchmarkMultiset(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen)
{
	if(g_pBench) 
		return g_pBench->BenchmarkMultiset(nRandomSeed, nTotal, pTimeTaken, pProgress, pName, pLen);

	return false;
}

extern "C" ATL_API int GetIndex()
{
	if(g_pBench) 
		return g_pBench->GetIndex();

	return -1;
}

extern "C" ATL_API bool SupportMap()
{
	if(g_pBench) 
		return g_pBench->SupportMap();

	return false;
}

extern "C" ATL_API bool SupportMultimap()
{
	if(g_pBench) 
		return g_pBench->SupportMultimap();

	return false;
}

extern "C" ATL_API bool SupportSet()
{
	if(g_pBench) 
		return g_pBench->SupportSet();

	return false;
}

extern "C" ATL_API bool SupportMultiset()
{
	if(g_pBench) 
		return g_pBench->SupportMultiset();

	return false;
}
