
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // remove support for MFC controls in dialogs

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars
#include <afxcontrolbars.h>









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <iostream>
#include "opencv/opencv2/opencv.hpp"
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#ifdef _DEBUG
#pragma comment(lib, "opencv/lib/opencv_core345d.lib")
#pragma comment(lib, "opencv/lib/opencv_imgcodecs345d.lib")
#pragma comment(lib, "opencv/lib/opencv_highgui345d.lib")
#pragma comment(lib, "opencv/lib/opencv_videoio345d.lib")
#pragma comment(lib, "opencv/lib/opencv_imgproc345d.lib")
#else
#pragma comment(lib, "opencv/lib/opencv_core345.lib")
#pragma comment(lib, "opencv/lib/opencv_imgcodecs345.lib")
#pragma comment(lib, "opencv/lib/opencv_highgui345.lib")
#pragma comment(lib, "opencv/lib/opencv_videoio345.lib")
#pragma comment(lib, "opencv/lib/opencv_imgproc345.lib")
#endif

using std::cout;
using std::endl;