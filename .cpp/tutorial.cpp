//==================================================================================================================
//
// tutorialの描画 [tutorial.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#define _CRT_SECURE_NO_WARNINGS											// 警告回避文

//==================================================================================================================
//	インクルードファイル
//==================================================================================================================
#include "tutorial.h"
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
#include "player.h"
#include "motionModel.h"
#include "model.h"
#include "inputGamepad.h"
#include "meshSphere.h"
#include "intervalFade.h"

//==================================================================================================================
//	静的メンバ変数宣言
//==================================================================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;			// テクスチャ情報
CCamera *CTutorial::m_pCamera = NULL;						// カメラ情報
CLight *CTutorial::m_pLight = NULL;							// ライト情報
CPolygon *CTutorial::m_pPolygon = NULL;						// ポリゴン情報
CMeshField *CTutorial::m_pMeshField = NULL;					// メッシュフィールド情報
CPlayer *CTutorial::m_pPlayer = NULL;						// プレイヤー情報
CLogo *CTutorial::m_pLogo = NULL;							// ロゴ情報
CMeshSphere *CTutorial::m_pMeshSphere = NULL;				// メッシュ球情報
CIntervalFade *CTutorial::m_pIntervalFade = NULL;			// インターバルフェード情報
CModel *CTutorial::m_pModel[TUTORIAL_MAX_MODEL] = {};		// モデル情報

//==================================================================================================================
//	コンストラクタ
//==================================================================================================================
CTutorial::CTutorial()
{

}

//==================================================================================================================
//	デストラクタ
//==================================================================================================================
CTutorial::~CTutorial()
{

}

//==================================================================================================================
//	初期化処理
//==================================================================================================================
void CTutorial::Init(void)
{
	CMeshField::Load();				// メッシュフィールドテクスチャロード
	CMotionModel::Load();			// モデルロード
	CLogo::Load();					// ロゴロード
	CModel::Load();					// モデルロード
	CMeshSphere::Load();			// メッシュ球テクスチャロード
	CIntervalFade::Load();			// インターバルフェードテクスチャロード

	// カメラの生成処理
	m_pCamera = CCamera::Create();

	// ライトの生成処理
	m_pLight = CLight::Create();

	// プレイヤー生成
	m_pPlayer = CPlayer::Create();
	// プレイヤ位置設定
	m_pPlayer->SetPos(D3DXVECTOR3(0, 10, -900));

	// メッシュフィールド生成
	m_pMeshField = CMeshField::Create();

	// ゴール輪っかモデルの生成処理
	m_pModel[0] = CModel::Create(CModel::MODEL_GOAL_CIRCLE);
	m_pModel[0]->SetPos(D3DXVECTOR3(0.0f, 10.0f, 500.0f));
	m_pModel[0]->SetSize(D3DXVECTOR3(5.0f, 5.0f, 5.0f));

	// メッシュ球生成
	m_pMeshSphere = CMeshSphere::Create();

	// インターバルフェードの生成処理
	m_pIntervalFade = CIntervalFade::Create();
	// 大きさ設定
	m_pIntervalFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
	// 位置設定
	m_pIntervalFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
	// 色設定
	m_pIntervalFade->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	// ロゴ生成
	m_pLogo = CLogo::Create();
}

//==================================================================================================================
//	終了処理
//==================================================================================================================
void CTutorial::Uninit(void)
{
	// scene2Dの破棄処理
	CScene2D::ReleaseAll();

	// scene3Dの破棄処理
	CScene3D::ReleaseAll();

	CMeshField::Unload();			// メッシュフィールドテクスチャアンロード
	CMotionModel::Unload();			// プレイヤーテクスチャモデルアンロード
	CLogo::Unload();				// ロゴアンロード
	CModel::Unload();				// モデルアンロード
	CMeshSphere::Unload();			// メッシュ球テクスチャアンロード
	CIntervalFade::Unload();		// インターバルフェードテクスチャアンロード

	delete m_pLight;				// メモリ削除
	m_pLight = nullptr;				// ポインタNULL

	delete m_pCamera;				// メモリ削除
	m_pCamera = nullptr;			// ポインタNULL
}

//==================================================================================================================
//	更新処理
//==================================================================================================================
void CTutorial::Update(void)
{
	// キーボード取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
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
			CFade::SetFade(CRenderer::MODE_GAME);
		}
	}
}

//==================================================================================================================
//	描画処理
//==================================================================================================================
void CTutorial::Draw(void)
{
	// カメラの設定
	m_pCamera->SetCamera();

	// カメラの描画処理
	m_pCamera->Draw();
}

//==================================================================================================================
// オブジェクトの生成
//==================================================================================================================
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial = NULL;		// チュートリアル情報をNULLにする

	pTutorial = new CTutorial;			// 動的に確保
	pTutorial->Init();					// 初期化処理

	return pTutorial;					// 値を返す
}

//==================================================================================================================
// プレイヤー情報取得処理
//==================================================================================================================
CPlayer * CTutorial::GetPlayer(void)
{
	return m_pPlayer;
}
