#pragma once

	typedef void (*InitializeFn)(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString);
	typedef void (*DestroyFn)();
	typedef bool (*PopulateFn)(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	typedef bool (*BenchmarkFn)(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	typedef int (*GetIndexFn)();
	typedef bool (*SupportFn)();


class LoadDll
{
public:
	LoadDll(void);
	~LoadDll(void);

	void SetDllPath(const std::wstring& szDllPath) { m_szDllPath = szDllPath; }
	bool IsReady() { return m_bReady; }

	void Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString);
	void Destroy();

	bool PopulateMap		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool PopulateMultimap	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool PopulateSet		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool PopulateMultiset	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

	bool BenchmarkMap		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool BenchmarkMultimap	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool BenchmarkSet		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool BenchmarkMultiset	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

	int GetIndex();

	bool SupportMap();
	bool SupportMultimap();
	bool SupportSet();
	bool SupportMultiset();

private:
	HMODULE m_hDll;
	std::wstring m_szDllPath;
	bool m_bReady;

	InitializeFn pfnInitialize;
	DestroyFn pfnDestroy;
	PopulateFn pfnPopulateMap;
	PopulateFn pfnPopulateMultimap;
	PopulateFn pfnPopulateSet;
	PopulateFn pfnPopulateMultiset;
	BenchmarkFn pfnBenchmarkMap;
	BenchmarkFn pfnBenchmarkMultimap;
	BenchmarkFn pfnBenchmarkSet;
	BenchmarkFn pfnBenchmarkMultiset;
	GetIndexFn pfnGetIndex;
	SupportFn pfnSupportMap;
	SupportFn pfnSupportMultimap;
	SupportFn pfnSupportSet;
	SupportFn pfnSupportMultiset;
};

