
// HashContainerBenchmarkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HashContainerBenchmark.h"
#include "HashContainerBenchmarkDlg.h"
#include "afxdialogex.h"
#include <strsafe.h>
#include <algorithm>

#pragma comment(lib, "strsafe.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct tagThreadData
{
	tagThreadData()
	{
		pvecDlls = NULL;
		pnDoneCnt = NULL;
		pnCurrentProgress = NULL;
		pbIsMapPopulated = NULL;
		pbIsMultiMapPopulated = NULL;
		pbIsSetPopulated = NULL;
		pbIsMultiSetPopulated = NULL;
		pvecTimeTaken = NULL;
		pvecTestName = NULL;
		hMutex = NULL;
		postback = NULL;
		nRandSeed = 0;
		nTotalSearch = 0;
	}

	std::vector<LoadDll*>* pvecDlls;
	volatile UINT* pnDoneCnt;
	volatile UINT* pnCurrentProgress;
	bool* pbIsMapPopulated;
	bool* pbIsMultiMapPopulated;
	bool* pbIsSetPopulated;
	bool* pbIsMultiSetPopulated;
	std::vector<UINT>* pvecTimeTaken;
	std::vector<std::wstring>* pvecTestName;
	HANDLE hMutex;
	CWnd* postback;
	UINT nRandSeed;
	UINT nTotalSearch;
} ThreadData, *PThreadData;

void BenchmarkMapThread(void * args)
{
	PThreadData pData = (PThreadData)(args);

	WaitForSingleObject(pData->hMutex, INFINITE);

	if(*pData->pbIsMapPopulated==false)
	{
		for(size_t i=0; i<pData->pvecDlls->size(); ++i)
		{
			if(pData->pvecDlls->at(i)->SupportMap()==false)
				continue;
			UINT timeTaken=0;
			UINT progress=0;
			wchar_t buf[MAX_PATH];
			ZeroMemory(buf, sizeof(buf));
			USHORT len = MAX_PATH;
			pData->pvecDlls->at(i)->PopulateMap(&timeTaken, &progress, buf, &len);;
		}
		if(pData->pvecDlls->size()>0)
			*pData->pbIsMapPopulated = true;
	}

	pData->pvecTimeTaken->clear();
	pData->pvecTestName->clear();

	for(size_t i=0; i<pData->pvecDlls->size(); ++i)
	{
		if(pData->pvecDlls->at(i)->SupportMap()==false)
			continue;
		*pData->pnDoneCnt = i;
		UINT timeTaken=0;
		wchar_t buf[MAX_PATH];
		ZeroMemory(buf, sizeof(buf));
		USHORT len = MAX_PATH;
		pData->pvecDlls->at(i)->BenchmarkMap(pData->nRandSeed, pData->nTotalSearch, &timeTaken, pData->pnCurrentProgress, buf, &len);
		pData->pvecTimeTaken->push_back(timeTaken);
		pData->pvecTestName->push_back(buf);
	}
	*pData->pnDoneCnt = pData->pvecDlls->size();

	pData->postback->PostMessage(WM_BENCHMARK_DONE, 0, 0);

	delete pData;

	Sleep(100);
	ReleaseMutex(pData->hMutex);
}

void BenchmarkMultiMapThread(void * args)
{
	PThreadData pData = (PThreadData)(args);

	WaitForSingleObject(pData->hMutex, INFINITE);

	if(*pData->pbIsMultiMapPopulated==false)
	{
		for(size_t i=0; i<pData->pvecDlls->size(); ++i)
		{
			if(pData->pvecDlls->at(i)->SupportMultimap()==false)
				continue;
			UINT timeTaken=0;
			UINT progress=0;
			wchar_t buf[MAX_PATH];
			ZeroMemory(buf, sizeof(buf));
			USHORT len = MAX_PATH;
			pData->pvecDlls->at(i)->PopulateMultimap(&timeTaken, &progress, buf, &len);;
		}
		if(pData->pvecDlls->size()>0)
			*pData->pbIsMultiMapPopulated = true;
	}

	pData->pvecTimeTaken->clear();
	pData->pvecTestName->clear();

	for(size_t i=0; i<pData->pvecDlls->size(); ++i)
	{
		if(pData->pvecDlls->at(i)->SupportMultimap()==false)
			continue;
		*pData->pnDoneCnt = i;
		UINT timeTaken=0;
		wchar_t buf[MAX_PATH];
		ZeroMemory(buf, sizeof(buf));
		USHORT len = MAX_PATH;
		pData->pvecDlls->at(i)->BenchmarkMultimap(pData->nRandSeed, pData->nTotalSearch, &timeTaken, pData->pnCurrentProgress, buf, &len);
		pData->pvecTimeTaken->push_back(timeTaken);
		pData->pvecTestName->push_back(buf);
	}
	*pData->pnDoneCnt = pData->pvecDlls->size();

	pData->postback->PostMessage(WM_BENCHMARK_DONE, 0, 0);

	delete pData;

	Sleep(100);
	ReleaseMutex(pData->hMutex);
}

void BenchmarkSetThread(void * args)
{
	PThreadData pData = (PThreadData)(args);

	WaitForSingleObject(pData->hMutex, INFINITE);

	if(*pData->pbIsSetPopulated==false)
	{
		for(size_t i=0; i<pData->pvecDlls->size(); ++i)
		{
			if(pData->pvecDlls->at(i)->SupportSet()==false)
				continue;
			UINT timeTaken=0;
			UINT progress=0;
			wchar_t buf[MAX_PATH];
			ZeroMemory(buf, sizeof(buf));
			USHORT len = MAX_PATH;
			pData->pvecDlls->at(i)->PopulateSet(&timeTaken, &progress, buf, &len);;
		}
		if(pData->pvecDlls->size()>0)
			*pData->pbIsSetPopulated = true;
	}

	pData->pvecTimeTaken->clear();
	pData->pvecTestName->clear();

	for(size_t i=0; i<pData->pvecDlls->size(); ++i)
	{
		if(pData->pvecDlls->at(i)->SupportSet()==false)
			continue;
		*pData->pnDoneCnt = i;
		UINT timeTaken=0;
		wchar_t buf[MAX_PATH];
		ZeroMemory(buf, sizeof(buf));
		USHORT len = MAX_PATH;
		pData->pvecDlls->at(i)->BenchmarkSet(pData->nRandSeed, pData->nTotalSearch, &timeTaken, pData->pnCurrentProgress, buf, &len);
		pData->pvecTimeTaken->push_back(timeTaken);
		pData->pvecTestName->push_back(buf);
	}
	*pData->pnDoneCnt = pData->pvecDlls->size();

	pData->postback->PostMessage(WM_BENCHMARK_DONE, 0, 0);

	delete pData;

	Sleep(100);
	ReleaseMutex(pData->hMutex);
}

void BenchmarkMultiSetThread(void * args)
{
	PThreadData pData = (PThreadData)(args);

	WaitForSingleObject(pData->hMutex, INFINITE);

	if(*pData->pbIsMultiSetPopulated==false)
	{
		for(size_t i=0; i<pData->pvecDlls->size(); ++i)
		{
			if(pData->pvecDlls->at(i)->SupportMultiset()==false)
				continue;
			UINT timeTaken=0;
			UINT progress=0;
			wchar_t buf[MAX_PATH];
			ZeroMemory(buf, sizeof(buf));
			USHORT len = MAX_PATH;
			pData->pvecDlls->at(i)->PopulateMultiset(&timeTaken, &progress, buf, &len);;
		}
		if(pData->pvecDlls->size()>0)
			*pData->pbIsMultiSetPopulated = true;
	}

	pData->pvecTimeTaken->clear();
	pData->pvecTestName->clear();

	for(size_t i=0; i<pData->pvecDlls->size(); ++i)
	{
		if(pData->pvecDlls->at(i)->SupportMultiset()==false)
			continue;
		*pData->pnDoneCnt = i;
		UINT timeTaken=0;
		wchar_t buf[MAX_PATH];
		ZeroMemory(buf, sizeof(buf));
		USHORT len = MAX_PATH;
		pData->pvecDlls->at(i)->BenchmarkMultiset(pData->nRandSeed, pData->nTotalSearch, &timeTaken, pData->pnCurrentProgress, buf, &len);
		pData->pvecTimeTaken->push_back(timeTaken);
		pData->pvecTestName->push_back(buf);
	}
	*pData->pnDoneCnt = pData->pvecDlls->size();

	pData->postback->PostMessage(WM_BENCHMARK_DONE, 0, 0);

	delete pData;

	Sleep(100);
	ReleaseMutex(pData->hMutex);
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHashContainerBenchmarkDlg dialog




CHashContainerBenchmarkDlg::CHashContainerBenchmarkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHashContainerBenchmarkDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hMutex = NULL;
	m_bIsMapPopulated = false;
	m_bIsMultiMapPopulated = false;
	m_bIsSetPopulated = false;
	m_bIsMultiSetPopulated = false;

	m_BenchType = map;

	UINT m_nMapTime = 0;
	UINT m_nMultiMapTime = 0;
	UINT m_nSetTime = 0;
	UINT m_nMultiSetTime = 0;

}

void CHashContainerBenchmarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_BENCHMARK_TYPE, m_cboBenchmarkType);
	DDX_Control(pDX, IDC_EDT_TOTAL_SEARCH_CNT, m_edtTotalSearchCnt);
	DDX_Control(pDX, IDC_EDT_RANDOM_SEED, m_edtRandomSeed);
	DDX_Control(pDX, IDC_PROGRESS1, m_progressCtrl);
	DDX_Control(pDX, IDC_STATIC_GRAPH, m_staticGraph);
	DDX_Control(pDX, IDC_BTN_BENCHMARK, m_btnBenchmark);
	DDX_Control(pDX, IDC_BTN_SAVE_GRAPH, m_btnSaveGraph);
	DDX_Control(pDX, IDC_BTN_GEN_SEED, m_btnGenerateSeed);
}

BEGIN_MESSAGE_MAP(CHashContainerBenchmarkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BENCHMARK, &CHashContainerBenchmarkDlg::OnBnClickedBtnBenchmark)
	ON_BN_CLICKED(IDC_BTN_SAVE_GRAPH, &CHashContainerBenchmarkDlg::OnBnClickedBtnSaveGraph)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_BENCHMARK_DONE,&CHashContainerBenchmarkDlg::OnBenchmarkDone)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_GEN_SEED, &CHashContainerBenchmarkDlg::OnBnClickedBtnGenSeed)
END_MESSAGE_MAP()


// CHashContainerBenchmarkDlg message handlers

BOOL CHashContainerBenchmarkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	srand( (unsigned int) ( time(NULL) ) );

	InitializeData();

	m_staticGraph.m_pGraph = &m_Graph;

	m_cboBenchmarkType.AddString(L"Map");
	m_cboBenchmarkType.AddString(L"MultiMap");
	m_cboBenchmarkType.AddString(L"Set");
	m_cboBenchmarkType.AddString(L"MultiSet");

	m_cboBenchmarkType.SetCurSel(0);

	m_progressCtrl.SetRange(0, HUNDRED_PERCENT);

	CString szSeed;
	szSeed.Format(L"%d", rand());
	m_edtRandomSeed.SetWindowTextW(szSeed);
	m_edtTotalSearchCnt.SetWindowTextW(L"500000");

	EnumDlls();
	if(m_vecDllPaths.size()<=0)
	{
		MessageBox(L"No dll found!!", L"Error", MB_OK);
		return true;
	}

	LoadDlls();
	if(m_vecDlls.size()<=0)
		MessageBox(L"No suitable dll found!!", L"Error", MB_OK);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHashContainerBenchmarkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHashContainerBenchmarkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHashContainerBenchmarkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CHashContainerBenchmarkDlg::SavePngFile(Gdiplus::Bitmap* pBmp, const wchar_t* pszFile)
{
	if(pBmp)
	{
		CLSID pngClsid;
		GetEncoderClsid(L"image/png", &pngClsid);
		Gdiplus::Status status = pBmp->Save(pszFile, &pngClsid, NULL);
		return status == Gdiplus::Ok ? true : false;
	}

	return false;
}

bool CHashContainerBenchmarkDlg::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	using namespace Gdiplus;

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return false;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return false;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return true;  // Success
		}    
	}

	free(pImageCodecInfo);
	return false;  // Failure
}


void CHashContainerBenchmarkDlg::OnBnClickedBtnBenchmark()
{
	CString szSeed;
	m_edtRandomSeed.GetWindowText(szSeed);
	if(szSeed.IsEmpty())
	{
		MessageBox(L"Random seed is not specified!", L"Error!", MB_OK);
		return;
	}
	CString szTotal;
	m_edtTotalSearchCnt.GetWindowText(szTotal);
	if(szTotal.IsEmpty())
	{
		MessageBox(L"Total number of items to search for, is not specified!", L"Error!", MB_OK);
		return;
	}

	int nTotalSearch = _wtoi((LPCWSTR)(szTotal));
	if(nTotalSearch<10000)
	{
		MessageBox(L"Total number of items to search for, must be more than 10000!", L"Error!", MB_OK);
		return;
	}

	if(m_cboBenchmarkType.GetCurSel()==0)
		m_BenchType = map;
	else if(m_cboBenchmarkType.GetCurSel()==1)
		m_BenchType = multimap;
	else if(m_cboBenchmarkType.GetCurSel()==2)
		m_BenchType = set;
	else if(m_cboBenchmarkType.GetCurSel()==3)
		m_BenchType = multiset;

	//disable all controls
	m_cboBenchmarkType.EnableWindow(FALSE);
	m_edtTotalSearchCnt.EnableWindow(FALSE);
	m_edtRandomSeed.EnableWindow(FALSE);
	m_btnBenchmark.EnableWindow(FALSE);
	m_btnSaveGraph.EnableWindow(FALSE);
	m_btnGenerateSeed.EnableWindow(FALSE);


	PThreadData pData = new ThreadData();

	pData->hMutex = m_hMutex;
	pData->pvecDlls = &m_vecDlls;

	pData->nRandSeed = _wtoi((LPCWSTR)(szSeed)); 
	pData->nTotalSearch = _wtoi((LPCWSTR)(szTotal));
	pData->pbIsMapPopulated = &m_bIsMapPopulated;
	pData->pbIsMultiMapPopulated = &m_bIsMultiMapPopulated;
	pData->pbIsSetPopulated = &m_bIsSetPopulated;
	pData->pbIsMultiSetPopulated = &m_bIsMultiSetPopulated;

	m_nCurrentProgress = 0;
	pData->pnCurrentProgress = &m_nCurrentProgress;
	m_nDoneCnt = 0;
	pData->pnDoneCnt = &m_nDoneCnt;
	pData->postback = (CWnd*)(this);
	m_vecTestName.clear();
	pData->pvecTestName = &m_vecTestName;
	m_vecTimeTaken.clear();
	pData->pvecTimeTaken = &m_vecTimeTaken;

	if(m_BenchType == map)
	{
		_beginthread(BenchmarkMapThread, 0, pData);
	}
	else if(m_BenchType == multimap)
	{
		_beginthread(BenchmarkMultiMapThread, 0, pData);
	}
	else if(m_BenchType == set)
	{
		_beginthread(BenchmarkSetThread, 0, pData);
	}
	else if(m_BenchType == multiset)
	{
		_beginthread(BenchmarkMultiSetThread, 0, pData);
	}

	m_progressCtrl.SetPos(0);
	
	SetTimer(PROGRESS_TIMER, 40, NULL);
}


void CHashContainerBenchmarkDlg::OnBnClickedBtnSaveGraph()
{
	wchar_t strFilter[] = { L"PNG Files (*.png)|*.png||" };

	CFileDialog fileDlg(FALSE, L".png", m_Graph.GetTitle().c_str(), 0, strFilter);

	if( fileDlg.DoModal() == IDOK )
	{
		RECT rect;
		m_staticGraph.GetClientRect(&rect);

		Gdiplus::Bitmap bmp(rect.right, rect.bottom, PixelFormat32bppARGB);
		Gdiplus::Graphics graphics(&bmp);

		m_Graph.Paint(&graphics, rect.right, rect.bottom);

		SavePngFile(&bmp, (LPCWSTR)(fileDlg.GetPathName()));
	}
}


void CHashContainerBenchmarkDlg::OnDestroy()
{
	m_staticGraph.m_pGraph = NULL;
	KillTimer(PROGRESS_TIMER);
	CDialogEx::OnDestroy();

	WaitForSingleObject(m_hMutex, INFINITE);
	DestroyDlls();
}

bool CHashContainerBenchmarkDlg::EnumDlls()
{
	// With CString
   TCHAR szDir[MAX_PATH];
	CString strAppDirectory;

	::GetModuleFileName(0, szDir, sizeof(szDir) - 1);

	// Extract directory
	strAppDirectory = szDir;
	strAppDirectory = strAppDirectory.Left(strAppDirectory.ReverseFind(L'\\'));


	WIN32_FIND_DATA ffd;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;
   

   // Prepare string for use with FindFile functions.  First, copy the
   // string to a buffer, then append '\*' to the directory name.
   StringCchCopy(szDir, MAX_PATH, strAppDirectory);
   StringCchCat(szDir, MAX_PATH, TEXT("\\*.dll"));

   // Find the first file in the directory.

   hFind = FindFirstFile(szDir, &ffd);

   if (INVALID_HANDLE_VALUE == hFind) 
   {
      return false;
   } 
   
   // List all the files in the directory with some info about them.

   m_vecDllPaths.clear();
   do
   {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
         
      }
      else
      {
		  CString fullpath = strAppDirectory;
		  PathAppend(fullpath.GetBuffer(MAX_PATH), ffd.cFileName);
		  fullpath.ReleaseBuffer();
		  m_vecDllPaths.push_back((LPCWSTR)(fullpath));
      }
   }
   while (FindNextFile(hFind, &ffd) != 0);
 
   dwError = GetLastError();

   FindClose(hFind);

   return true;
}

bool CHashContainerBenchmarkDlg::LoadDlls()
{
	if(m_vecDllPaths.size()<=0)
		return false;

	m_vecDlls.clear();
	for(size_t i=0; i<m_vecDllPaths.size(); ++i)
	{
		LoadDll* pload = new LoadDll();

		pload->SetDllPath(m_vecDllPaths[i]);

		pload->Initialize(&m_vecEngDict, &m_vecEngDictCString);

		if(pload->IsReady())
		{
			m_vecDlls.push_back(pload);
		}
		else
		{
			delete pload;
			pload = NULL;
		}
	}
	if(m_vecDlls.size()>0)
	{
		std::sort(m_vecDlls.begin(), m_vecDlls.end(), [] (LoadDll* a, LoadDll* b) { return a->GetIndex() < b->GetIndex(); } );
	}

	return true;
}

bool CHashContainerBenchmarkDlg::DestroyDlls()
{
	for(size_t i=0; i<m_vecDlls.size(); ++i)
	{
		if(m_vecDlls[i])
		{
			m_vecDlls[i]->Destroy();
			delete m_vecDlls[i];
			m_vecDlls[i] = NULL;
		}
	}
	if(m_vecDlls.size()>0)
	{
		m_vecDlls.clear();
	}
	return true;
}

LRESULT CHashContainerBenchmarkDlg::OnBenchmarkDone(WPARAM wParam, LPARAM lParam)
{
	KillTimer(PROGRESS_TIMER);
	m_progressCtrl.SetPos(HUNDRED_PERCENT);
	m_cboBenchmarkType.EnableWindow(TRUE);
	m_edtTotalSearchCnt.EnableWindow(TRUE);
	m_edtRandomSeed.EnableWindow(TRUE);
	m_btnBenchmark.EnableWindow(TRUE);
	m_btnSaveGraph.EnableWindow(TRUE);
	m_btnGenerateSeed.EnableWindow(TRUE);

	m_Graph.ClearData();

	if(m_BenchType == map)
	{
		m_Graph.SetTitle(L"Map Benchmark");
	}
	else if(m_BenchType == multimap)
	{
		m_Graph.SetTitle(L"MultiMap Benchmark");
	}
	else if(m_BenchType == set)
	{
		m_Graph.SetTitle(L"Set Benchmark");
	}
	else if(m_BenchType == multiset)
	{
		m_Graph.SetTitle(L"MultiSet Benchmark");
	}

	for(size_t i=0; i<m_vecTestName.size(); ++i)
	{
		if(m_BenchType == map&&m_vecDlls.at(i)->SupportMap()==false)
			continue;
		else if(m_BenchType == multimap&&m_vecDlls.at(i)->SupportMultimap()==false)
			continue;
		else if(m_BenchType == set&&m_vecDlls.at(i)->SupportSet()==false)
			continue;
		else if(m_BenchType == multiset&&m_vecDlls.at(i)->SupportMultiset()==false)
			continue;
		
		m_Graph.AddBarName(m_vecTestName[i]);
	}

	for(size_t i=0; i<m_vecTimeTaken.size(); ++i)
	{
		if(m_BenchType == map&&m_vecDlls.at(i)->SupportMap()==false)
			continue;
		else if(m_BenchType == multimap&&m_vecDlls.at(i)->SupportMultimap()==false)
			continue;
		else if(m_BenchType == set&&m_vecDlls.at(i)->SupportSet()==false)
			continue;
		else if(m_BenchType == multiset&&m_vecDlls.at(i)->SupportMultiset()==false)
			continue;

		CString str;
		if(m_vecTimeTaken[i]>60000)
		{
			str.Format(L"%um%02us", m_vecTimeTaken[i]/60000, (m_vecTimeTaken[i]%60000)/1000);
		}
		else if(m_vecTimeTaken[i]>1000)
		{
			str.Format(L"%u.%03us", m_vecTimeTaken[i]/1000, m_vecTimeTaken[i]%1000);
		}
		else
		{
			str.Format(L"%ums", m_vecTimeTaken[i]);
		}
		m_Graph.SetBarValue(i, (float)(m_vecTimeTaken[i]), (LPCWSTR)(str));
	}

	m_staticGraph.Invalidate();

	return true;
}

bool CHashContainerBenchmarkDlg::InitializeData()
{
	m_vecEngDict.reserve(32768);
	m_vecEngDictCString.reserve(32768);
	HINSTANCE hResInstance = AfxGetResourceHandle( );

	HRSRC res = FindResource(hResInstance,
							 MAKEINTRESOURCE(IDR_ENGTEXT),L"TEXT");
	if (res) 
	{
		HGLOBAL mem = LoadResource(hResInstance, res);
		void *data = LockResource(mem);
		size_t len = SizeofResource(hResInstance, res);

		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, len);
		LPVOID pvData = GlobalLock( hGlobal );
		memcpy(pvData,data,len);
		GlobalUnlock(hGlobal);

		char* p = (char*)(pvData);

		std::wstring str = L"";
		size_t i = 0;
		while(p++&&i<len)
		{
			++i;
			if(*p=='\r')
			{
				++p;
				++i;
				m_vecEngDict.push_back(str);
				m_vecEngDictCString.push_back(str.c_str());
				str = L"";
			}
			else
				str += (wchar_t)(*p);
		}
	}
	else
		return false;

	std::random_shuffle(m_vecEngDict.begin(), m_vecEngDict.end());
	std::random_shuffle(m_vecEngDict.begin(), m_vecEngDict.end());
	std::random_shuffle(m_vecEngDictCString.begin(), m_vecEngDictCString.end());
	std::random_shuffle(m_vecEngDictCString.begin(), m_vecEngDictCString.end());

	return true;
}


void CHashContainerBenchmarkDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CClientDC dc(this);
	int PosY = 133*dc.GetDeviceCaps(LOGPIXELSY)/96;
	int nMargin = 11*dc.GetDeviceCaps(LOGPIXELSY)/96;

	if(m_staticGraph.GetSafeHwnd())
	{
		m_staticGraph.SetWindowPos(
			&m_progressCtrl,
			nMargin,
			PosY,
			cx-nMargin*2,
			cy-nMargin-PosY,
			SWP_SHOWWINDOW);

		m_staticGraph.Invalidate();
	}

	if(m_progressCtrl.GetSafeHwnd())
	{
		RECT rect;
		m_progressCtrl.GetClientRect(&rect);
		PosY = 89*dc.GetDeviceCaps(LOGPIXELSY)/96;
		m_progressCtrl.SetWindowPos(
			&m_edtTotalSearchCnt,
			nMargin,
			PosY,
			cx-nMargin*2,
			rect.bottom,
			SWP_SHOWWINDOW);
	}
}


void CHashContainerBenchmarkDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == PROGRESS_TIMER)
	{
		if(m_nDoneCnt==m_vecDlls.size())
			m_progressCtrl.SetPos(HUNDRED_PERCENT);
		else if(m_vecDlls.size()>0)
		{
			UINT pos=m_nDoneCnt * HUNDRED_PERCENT / m_vecDlls.size();
			pos += (m_nCurrentProgress / m_vecDlls.size());
			if(pos > HUNDRED_PERCENT)
				pos = HUNDRED_PERCENT;

			m_progressCtrl.SetPos(pos);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CHashContainerBenchmarkDlg::OnBnClickedBtnGenSeed()
{
	CString str;
	str.Format(L"%d", rand());
	m_edtRandomSeed.SetWindowTextW(str);
}
