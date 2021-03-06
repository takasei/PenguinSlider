//==================================================================================================================
//
// titleの描画 [title.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#define _CRT_SECURE_NO_WARNINGS			// 警告回避文

//==================================================================================================================
//	インクルードファイル
//==================================================================================================================
#include "title.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "sound.h"
#include "scene2D.h"
#include "scene3D.h"
#include "camera.h"
#include "light.h"
#include "logo.h"
#include "meshField.h"
#include "motionModel.h"
#include "player.h"
#include "inputGamepad.h"
#include "meshSphere.h"
#include "model.h"
#include "titleFade.h"

//==================================================================================================================
//	マクロ定義
//==================================================================================================================
#define MAX_FADE_COUNT 800			// フェードののカウントの最大数

//==================================================================================================================
//	静的メンバ変数宣言
//==================================================================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;		// テクスチャ情報
CCamera *CTitle::m_pCamera = NULL;					// カメラ情報
CLight *CTitle::m_pLight = NULL;					// ライト情報
CPolygon *CTitle::m_pPolygon = NULL;				// ポリゴン情報
CMeshField *CTitle::m_pMeshField = NULL;			// メッシュフィールド情報
CLogo *CTitle::m_pLogo = NULL;						// ロゴ情報
CPlayer *CTitle::m_pPlayer = NULL;					// プレイヤー情報
CMeshSphere *CTitle::m_pMeshSphere = NULL;			// メッシュ球情報
CModel *CTitle::m_pModel[MAX_TITLE_MODEL] = {};		// モデル情報
CTitleFade *CTitle::m_pTitleFade = NULL;			// タイトルフェード情報

//==================================================================================================================
//	コンストラクタ
//==================================================================================================================
CTitle::CTitle()
{

}

//==================================================================================================================
//	デストラクタ
//==================================================================================================================
CTitle::~CTitle()
{

}

//==================================================================================================================
//	初期化処理
//==================================================================================================================
void CTitle::Init(void)
{
	//変数の初期化
	m_nCntRanking = 0;			// ランキングへのカウンタ

	CMeshField::Load();			// メッシュフィールドロード
	CLogo::Load();				// ロゴロード
	CMotionModel::Load();		// モーション用モデルロード
	CMeshSphere::Load();		// メッシュ球のテクスチャロード
	CModel::Load();				// モデルのロード

	// ライトの生成処理
	m_pLight = CLight::Create();

	// カメラの生成処理
	m_pCamera = CCamera::Create();

	// メッシュ球生成
	m_pMeshSphere = CMeshSphere::Create();

	// インターバルフェードの生成処理
	m_pTitleFade = CTitleFade::Create();
	// 大きさ設定
	m_pTitleFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
	// 位置設定
	m_pTitleFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
	// 色設定
	m_pTitleFade->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	// プレイヤー生成
	m_pPlayer = CPlayer::Create();
	// プレイヤ位置設定
	m_pPlayer->SetPos(D3DXVECTOR3(0, 10, -900));

	// メッシュフィールド生成
	m_pMeshField = CMeshField::Create();

	// モデルの設定
	SetModel();

	// ロゴ生成
	m_pLogo = CLogo::Create();
}

//==================================================================================================================
//	終了処理
//==================================================================================================================
void CTitle::Uninit(void)
{
	// scene2Dの破棄処理
	CScene2D::ReleaseAll();

	// scene3Dの破棄処理
	CScene3D::ReleaseAll();

	CMeshField::Unload();			// 床テクスチャアンロード
	CLogo::Unload();				// ロゴアンロード
	CMotionModel::Unload();			// モーション用モデルアンロード
	CMeshSphere::Unload();			// メッシュ球のテクスチャアンロード
	CModel::Unload();				// モデルのアンロード

	delete m_pLight;				// メモリ削除
	m_pLight = nullptr;				// ポインタNULL

	delete m_pCamera;				// メモリ削除
	m_pCamera = nullptr;			// ポインタNULL
}

//==================================================================================================================
//	更新処理
//==================================================================================================================
void CTitle::Update(void)
{
	// キーボード取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//コントローラーの取得
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	// フェード取得
	CFade::FADE fade = CFade::GetFade();

	// カメラの更新処理
	m_pCamera->Update();

	// ライトの更新処理
	m_pLight->Update();

	// キーボードの[Enter] 又は コントローラーの[START]を押したとき
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_START))
	{
		// フェードが何もない時
		if (fade == CFade::FADE_NONE)
		{
			// フェードの設定
			CFade::SetFade(CRenderer::MODE_TUTORIAL);
		}
	}

	// ランキングへのカウンタ加算
	m_nCntRanking++;

	// ランキングカウンタが規定値を超えたら
	if (m_nCntRanking >= MAX_FADE_COUNT)
	{
		// フェードが何もない時
		if (fade == CFade::FADE_NONE)
		{
			// フェードの設定
			CFade::SetFade(CRenderer::MODE_RANKING);
		}
	}
}

//==================================================================================================================
//	描画処理
//==================================================================================================================
void CTitle::Draw(void)
{
	// カメラがあるとき
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();			// カメラの設定
		m_pCamera->Draw();				// カメラの描画処理
	}
}

//==================================================================================================================
// オブジェクトの生成
//==================================================================================================================
CTitle * CTitle::Create(void)
{
	CTitle *pTitle = NULL;			// チュートリアル情報をNULLにする

	pTitle = new CTitle;			// 動的に確保
	pTitle->Init();					// 初期化処理

	return pTitle;					// 値を返す
}

//==================================================================================================================
// プレイヤー情報取得
//==================================================================================================================
CPlayer * CTitle::GetPlayer(void)
{
	return m_pPlayer;
}

//==================================================================================================================
// カメラ情報取得
//==================================================================================================================
CCamera * CTitle::GetCamera(void)
{
	return m_pCamera;
}

//==================================================================================================================
// モデルの設定
//==================================================================================================================
void CTitle::SetModel(void)
{
	int nNumber = 0;		// モデルの番号

	// 土台モデル
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);	// 生成処理
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(0.0f, 3.5f, 800.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 10.7f));		// 大きさ設定
	nNumber++;														// モデルの番号加算
}
