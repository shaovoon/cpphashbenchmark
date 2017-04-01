// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ATLSTDSTR_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ATLSTDSTR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ATLSTDSTR_EXPORTS
#define ATLSTDSTR_API __declspec(dllexport)
#else
#define ATLSTDSTR_API __declspec(dllimport)
#endif

extern "C"
{
ATLSTDSTR_API void Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString);
ATLSTDSTR_API void Destroy();

ATLSTDSTR_API bool PopulateMap		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
ATLSTDSTR_API bool PopulateMultimap	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
ATLSTDSTR_API bool PopulateSet		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
ATLSTDSTR_API bool PopulateMultiset	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

ATLSTDSTR_API bool BenchmarkMap		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
ATLSTDSTR_API bool BenchmarkMultimap	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
ATLSTDSTR_API bool BenchmarkSet		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
ATLSTDSTR_API bool BenchmarkMultiset	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

ATLSTDSTR_API int GetIndex();

ATLSTDSTR_API bool SupportMap();
ATLSTDSTR_API bool SupportMultimap();
ATLSTDSTR_API bool SupportSet();
ATLSTDSTR_API bool SupportMultiset();
}
