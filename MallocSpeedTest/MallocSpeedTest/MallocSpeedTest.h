
// MallocSpeedTest.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMallocSpeedTestApp:
// このクラスの実装については、MallocSpeedTest.cpp を参照してください
//

class CMallocSpeedTestApp : public CWinApp
{
public:
	CMallocSpeedTestApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMallocSpeedTestApp theApp;
