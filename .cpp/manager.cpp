//==================================================================================================================
//
// 管理[manager.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "manager.h"
#include "scene2D.h"
#include "scene3D.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "inputGamepad.h"

//==================================================================================================================
// 静的メンバ変数の初期化
//==================================================================================================================
CRenderer *CManager::m_pRenderer = NULL;				// レンダラー情報
CInputKeyboard *CManager::m_pInputKeyboard = NULL;		// キーボード情報
CInputGamepad *CManager::m_pInputGamepad = NULL;		// ゲームパッド情報

//==================================================================================================================
// コンストラクタ
//==================================================================================================================
CManager::CManager()
{

}

//==================================================================================================================
// デストラクタ
//==================================================================================================================
CManager::~CManager()
{

}

//==================================================================================================================
// 初期化処理
//==================================================================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow)
{
	// レンダラー動的に確保
	m_pRenderer = new CRenderer;

	// キーボード動的に確保
	m_pInputKeyboard = new CInputKeyboard;

	// コントローラー動的に確保
	m_pInputGamepad = new CInputGamepad;

	// 初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return-1;
	}

	// キーボード初期化
	m_pInputKeyboard->Init(hInstance, hWnd);

	// コントローラー初期化
	m_pInputGamepad->Init(hInstance, hWnd);

	// 値を返す
	return S_OK;
}

//==================================================================================================================
// 終了
//==================================================================================================================
void CManager::Uninit(void)
{
	// 全てを破棄
	CScene::ReleaseAll();

	// レンダラーがあるとき
	if (m_pRenderer != NULL)
	{
		// レンダラー終了処理
		m_pRenderer->Uninit();

		// レンダラー破棄
		delete m_pRenderer;

		// NULLにする
		m_pRenderer = NULL;
	}

	// キーボードがあるとき
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの終了処理
		m_pInputKeyboard->Uninit();

		// 破棄
		delete m_pInputKeyboard;

		// NULLにする
		m_pInputKeyboard = NULL;
	}

	// コントローラーがあるとき
	if (m_pInputGamepad != NULL)
	{
		// コントローラーの終了処理
		m_pInputGamepad->Uninit();

		// 破棄
		delete[] m_pInputGamepad;

		// NULLにする
		m_pInputGamepad = NULL;
	}
}

//==================================================================================================================
// 更新処理
//==================================================================================================================
void CManager::Update(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();					// レンダラーの情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();				// デバイスを取得する

	//キーボード取得
	CInputKeyboard *pInputKeyboard = GetInputKeyboard();

	// レンダラーがあるとき
	if (m_pRenderer != NULL)
	{
		// レンダラー更新処理
		m_pRenderer->Update();
	}

	// キーボードがあるとき
	if (m_pInputKeyboard != NULL)
	{
		// キーボード更新処理
		m_pInputKeyboard->Update();
	}

	// コントローラーがあるとき
	if (m_pInputGamepad != NULL)
	{
		// コントローラーの更新処理
		m_pInputGamepad->Update();
	}
}

//==================================================================================================================
// 描画処理
//==================================================================================================================
void CManager::Draw(void)
{
	// レンダラーがあるとき
	if (m_pRenderer != NULL)
	{
		// レンダラーの描画処理
		m_pRenderer->Draw();
	}
}

//==================================================================================================================
// レンダラー情報取得
//==================================================================================================================
CRenderer *CManager:: GetRenderer(void)
{
	return m_pRenderer;
}

//==================================================================================================================
// キーボード情報取得
//==================================================================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//==================================================================================================================
// コントローラー情報取得
//==================================================================================================================
CInputGamepad * CManager::GetInputGamepad(void)
{
	return m_pInputGamepad;
}
