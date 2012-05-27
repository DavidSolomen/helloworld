// TaskSchedulerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TaskScheduler.h"
#include "TaskSchedulerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct JCB
{
	CString name;
	char status;
	CString nResource;
	int nTime;
	int sTime;
	struct JCB *link;
} *ready = 0, *task;

int rTime = 0;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskSchedulerDlg dialog

CTaskSchedulerDlg::CTaskSchedulerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskSchedulerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTaskSchedulerDlg)
	m_resource = _T("");
	m_time = 0;
	m_name = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTaskSchedulerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskSchedulerDlg)
	DDX_Control(pDX, IDC_LIST1, m_display);
	DDX_Control(pDX, IDC_BUTTON_RUN, m_run);
	DDX_Control(pDX, IDC_BUTTON_CREATE, m_create);
	DDX_Text(pDX, IDC_EDIT_RESOURCE, m_resource);
	DDX_Text(pDX, IDC_EDIT_TIME, m_time);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTaskSchedulerDlg, CDialog)
	//{{AFX_MSG_MAP(CTaskSchedulerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE, OnButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskSchedulerDlg message handlers

BOOL CTaskSchedulerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	// TODO: Add extra initialization here
	CheckRadioButton(IDC_FCFS,IDC_HRN,IDC_FCFS);
	SetTimer(0,1000,false);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTaskSchedulerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTaskSchedulerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTaskSchedulerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTaskSchedulerDlg::sort(UINT nID)
{
	JCB *first,*next;
	switch(nID)
	{
		case IDC_FCFS:	//先来先服务算法,直接插入链表
			if(ready == 0)
			{
				task->link = ready;
				ready = task;
			}
			else
			{
				first = ready;
				next = first->link;
				while(next != 0)
				{
					first = first->link;
					next = next->link;
				}
				first->link = task;
				task->link = 0;
			}
			break;
		case IDC_SJF:	//短作业优先算法
			if(ready == 0 || (task->nTime)<(ready->nTime))
			{
				task->link = ready;
				ready = task;
			}
			else
			{
				int insert = 0;
				first = ready;
				next = first->link;
				while(next != 0)
				{//根据作业需求的时间进行排序
					if((task->nTime)<(next->nTime))
					{
						task->link = next;
						first->link = task;
						next = 0;
						insert = 1;
					}
					else
					{
						first = first->link;
						next = next->link;
					}
				}
				if(insert == 0) 
				{
					first->link = task;
					task->link = 0;
				}
			}
			break;
		case IDC_HRN:	//响应比高者优先算法	
			if(ready == 0 ||(rTime/task->sTime + 1)>(rTime/ready->sTime +1))
			{
				task->link = ready;
				ready = task;
			}
			else
			{
				int insert = 0;
				first = ready;
				next = first->link;
				while(next != 0)
				{//根据响应比进行排序
					if((rTime/task->sTime +1)>(rTime/next->sTime +1))
					{
						task->link = next;
						first->link = task;
						next = 0;
						insert = 1;
					}
					else
					{
						first = first->link;
						next = next->link;
					}
				}
				if(insert == 0)
				{
					first->link = task;
					task->link = 0;
				}
			}
			break;
	}
}

int CTaskSchedulerDlg::length()
{
	int len = 0;
	JCB *next = ready;
	while(next != 0)
	{
		len++;
		next = next->link;
	}
	return(len);
}

void CTaskSchedulerDlg::check()
{
	JCB *ta;
	CString s;
	m_display.AddString("*****************************************");
	m_display.AddString("***** 当前正在运行的作业是：" + task->name);
	m_display.AddString("taskName：       " + task->name);
	s.Format("%c",task->status);
	m_display.AddString("status：         " + s);
	s.Format("%d",task->sTime);
	m_display.AddString("submitTime：     " + s);
	s.Format("%d",task->nTime);
	m_display.AddString("needTime：       " + s);
    m_display.AddString("needResource：   " + task->nResource);
	ta = ready;
	m_display.AddString("*****************************************");
	m_display.AddString("***** 当前就绪队列状态为：\n");
	while(ta != 0)
	{
		m_display.AddString("taskName：       " + ta->name);
		s.Format("%c",ta->status);
		m_display.AddString("status：         " + s);
		s.Format("%d",ta->sTime);
		m_display.AddString("submitTime：     " + s);
		s.Format("%d",ta->nTime);
		m_display.AddString("needTime：       " + s);
		m_display.AddString("needResource：   " + ta->nResource);
		m_display.AddString("---------------------------------");
		ta = ta->link;
	}
}

void CTaskSchedulerDlg::destroy()
{
	m_display.AddString(" 作业 " + task->name + " 已完成。\n");
	delete task;
}

void CTaskSchedulerDlg::OnButtonCreate() 
{
	UpdateData(true);
	task = new JCB;
	task->name = m_name;
	task->nResource = m_resource;
	task->nTime = m_time;
	task->sTime = rTime;
	task->status = 'W';
	task->link = 0;
	UINT nID = CWnd::GetCheckedRadioButton(IDC_FCFS,IDC_HRN);
	sort(nID);
}

void CTaskSchedulerDlg::OnButtonRun() 
{
	// TODO: Add your control notification handler code here
	KillTimer(0);
	int len,ti,wi,sumt = 0,sumw = 0;
	CString str;
	len = length();
	while(ready != 0) 
	{ 
		task = ready;
		ready = ready->link;
		task->link = 0;
		task->status = 'R';
		check();
		m_display.AddString("*****************************************");
		int time = rTime;
		while((rTime - time) != task->nTime)
		{
			rTime++;
		}
		str.Format("%d",time);
		m_display.AddString("作业" + task->name + "开始运行时间:" + str);
		str.Format("%d",rTime);
		m_display.AddString("作业" + task->name + "完成时间:" + str);
		ti = rTime - task->sTime;
		str.Format("%d",ti);
		m_display.AddString("作业" + task->name + "周转时间:" + str);
		wi = (rTime - task->sTime)/task->nTime;
		str.Format("%d",wi);
		m_display.AddString("作业" + task->name + "带权周转时间:" + str);
		sumt += ti;
		sumw += wi;
		destroy();
	}
	m_display.AddString("*****************************************");
	m_display.AddString("\n 所有作业已经完成。\n");
	str.Format("%d",sumt/len);
	m_display.AddString("平均周转时间为:" + str);
	str.Format("%d",sumw/len);
	m_display.AddString("带权平均周转时间为:" + str);
	SetTimer(0,1000,false);
}

void CTaskSchedulerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	rTime++;
	CDialog::OnTimer(nIDEvent);
}
