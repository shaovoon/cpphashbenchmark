// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STLCSTR_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STLCSTR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STLCSTR_EXPORTS
#define STLCSTR_API __declspec(dllexport)
#else
#define STLCSTR_API __declspec(dllimport)
#endif

extern "C"
{
STLCSTR_API void Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString);
STLCSTR_API void Destroy();

STLCSTR_API bool PopulateMap		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
STLCSTR_API bool PopulateMultimap	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
STLCSTR_API bool PopulateSet		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
STLCSTR_API bool PopulateMultiset	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

STLCSTR_API bool BenchmarkMap		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
STLCSTR_API bool BenchmarkMultimap	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
STLCSTR_API bool BenchmarkSet		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
STLCSTR_API bool BenchmarkMultiset	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

STLCSTR_API int GetIndex();

STLCSTR_API bool SupportMap();
STLCSTR_API bool SupportMultimap();
STLCSTR_API bool SupportSet();
STLCSTR_API bool SupportMultiset();
}
