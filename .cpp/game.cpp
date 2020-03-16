//==================================================================================================================
//
// Gameの描画 [game.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#define _CRT_SECURE_NO_WARNINGS											// 警告回避

//==================================================================================================================
//	インクルードファイル
//==================================================================================================================
#include "game.h"
#include "player.h"
#include "number.h"
#include "fade.h"
#include "inputKeyboard.h"
#include "meshField.h"
#include "scene3D.h"
#include "camera.h"
#include "light.h"
#include "time.h"
#include "renderer.h"
#include "logo.h"
#include "rankingNum.h"
#include "motionModel.h"
#include "model.h"
#include "pause.h"
#include "inputGamepad.h"
#include "intervalFade.h"
#include "meshSphere.h"

//==================================================================================================================
//	マクロ定義
//==================================================================================================================
#define PLAYER_START_POS_X 390.0f									// プレイヤーの初期位置X
#define PLAYER_START_POS_Z -585.0f									// プレイヤーの初期位置Z
#define RESPAWN_SIZE 1.0f											// リスポーンモデルの大きさ

//==================================================================================================================
//	静的メンバ変数宣言
//==================================================================================================================
CPlayer *CGame::m_pPlayer = NULL;									// プレイヤー情報
CMeshField *CGame::m_pMeshField = NULL;								// メッシュフィールド情報
CCamera *CGame::m_pCamera = NULL;									// カメラ情報
CLight *CGame::m_pLight = NULL;										// ライト情報
CLogo *CGame::m_pLogo = NULL;										// ロゴ情報
CPause *CGame::m_pPause = NULL;										// ポーズ情報
CIntervalFade *CGame::m_pIntervalFade = NULL;						// インターバルフェード情報
CMeshSphere *CGame::m_pMeshSphere = NULL;							// メッシュ球の情報
CGame::GAMESTATE CGame::m_gameState = CGame::GAMESTATE_NONE;		// ゲーム状態
int CGame::m_nCounterGameState = NULL;								// ゲームの状態管理カウンター

//==================================================================================================================
//	コンストラクタ
//==================================================================================================================
CGame::CGame()
{

}

//==================================================================================================================
//	デストラクタ
//==================================================================================================================
CGame::~CGame()
{
}

//==================================================================================================================
//	初期化処理
//==================================================================================================================
void CGame::Init(void)
{
	CNumber::Load();						// 数字テクスチャロード
	CMeshField::Load();						// 床テクスチャロード
	CNumber::Load();						// 数字テクスチャロード
	CLogo::Load();							// ロゴテクスチャロード
	CMotionModel::Load();					// モーション用モデルロード
	CModel::Load();							// モデルロード
	CPause::Load();							// ポーズテクスチャロード
	CIntervalFade::Load();					// インターバルフェードテクスチャロード
	CMeshSphere::Load();					// メッシュ球のテクスチャロード

	// カメラの生成処理
	m_pCamera = CCamera::Create();

	// ライトの生成処理
	m_pLight = CLight::Create();

	// プレイヤー生成処理
	m_pPlayer = CPlayer::Create();
	// 位置設定
	m_pPlayer->SetPos(D3DXVECTOR3(PLAYER_START_POS_X, WhileY, PLAYER_START_POS_Z));
	// 回転設定
	m_pPlayer->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));

	// 敵の設定
	//SetEnemy();

	// メッシュフィールド生成
	m_pMeshField = CMeshField::Create();

	// モデルの設定処理
	SetModel();

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

	// タイムの生成
	CTime::Create();

	// ランキングスコア生成
	CRankingNum *pRankingNum = CRankingNum::Create();
	// ランキング数字設定
	pRankingNum->AddRankingNum();

	// ポーズの生成処理
	m_pPause = CPause::Create();

	SetGameState(GAMESTATE_NORMAL);			// 通常状態に設定
	m_nCounterGameState = 0;				// ゲームの状態管理カウンターを0にする
}

//==================================================================================================================
//	終了処理
//==================================================================================================================
void CGame::Uninit(void)
{
	// ゲーム状態を通常にする
	m_gameState = GAMESTATE_NORMAL;

	CScene2D::ReleaseAll();				// 2Dのもの全て破棄
	CScene3D::ReleaseAll();				// 3Dのもの全て破棄

	CNumber::Unload();					// 数字テクスチャアンロード
	CMeshField::Unload();				// 床テクスチャアンロード
	CLogo::Unload();					// ロゴアンロード
	CMotionModel::Unload();				// モーション用モデルアンロード
	CModel::Unload();					// モデルアンロード
	CIntervalFade::Unload();			// インターバルフェードテクスチャアンロード
	CMeshSphere::Unload();				// メッシュ球のテクスチャアンロード

	// ポーズの終了処理
	m_pPause->Uninit();

	delete m_pPause;					// メモリ削除
	m_pPause = nullptr;					// ポインタNULL

	delete m_pCamera;					// メモリ削除
	m_pCamera = nullptr;				// ポインタNULL

	delete m_pLight;					// メモリ削除
	m_pLight = nullptr;					// ポインタNULL
}

//==================================================================================================================
//	更新処理
//==================================================================================================================
void CGame::Update(void)
{
	// キーボード取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// コントローラー取得
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	// フェード取得
	CFade::FADE fade = CFade::GetFade();

	// ゲームの状態取得
	m_gameState = GetGameState();

	// ゲーム状態がポーズのとき
	if (m_gameState == GAMESTATE_PAUSE)
	{
		// ポーズの更新処理
		m_pPause->Update();

		// ゲーム状態が初めからやり直すとき
		if (m_gameState == GAMESTATE_START_OVER)
		{
			// フェードを設定する
			CFade::SetFade(CRenderer::MODE_GAME);
		}
		else if (m_gameState == GAMESTATE_BREAK)
		{// ゲーム状態が中断のとき
			// フェードを設定する
			CFade::SetFade(CRenderer::MODE_TITLE);
		}
	}
	else
	{
		// カメラの更新処理
		m_pCamera->Update();

		// ライトの更新処理
		m_pLight->Update();
	}

	// キーボードの[P] 又は コントローラーの[START]ボタンが押されたとき
	if (pInputKeyboard->GetKeyboardTrigger(DIK_P) || pInputGamepad->GetTrigger(0, CInputGamepad::JOYPADKEY_START))
	{// ポーズ切り替え
		// ゲーム状態がポーズのとき
		if (m_gameState == GAMESTATE_PAUSE)
		{
			// ゲーム状態をNORMALにする
			m_gameState = GAMESTATE_NORMAL;

			// ポーズ状態の設定
			m_pPause->SetPause(false);
		}
		else
		{// ゲーム状態がポーズじゃないとき
			// ゲーム状態をポーズにする
			m_gameState = GAMESTATE_PAUSE;

			// ポーズ状態の設定
			m_pPause->SetPause(true);
		}
	}
#ifdef _DEBUG
	// キーボードの[0]を押したとき
	if (pInputKeyboard->GetKeyboardTrigger(DIK_0))
	{
		// フェードが何もない時
		if (fade == CFade::FADE_NONE)
		{
			// フェードを設定する
			CFade::SetFade(CRenderer::MODE_RANKING);
		}
	}
#endif // _DEBUG
}

//==================================================================================================================
//	描画処理
//==================================================================================================================
void CGame::Draw(void)
{
	// カメラの設定
	m_pCamera->SetCamera();

	// カメラの描画処理
	m_pCamera->Draw();

	// ポーズ状態がtrueのとき
	if (m_pPause->GetPause() == true)
	{
		// ポーズの更新処理
		m_pPause->Draw();
	}
}

//==================================================================================================================
//	生成処理
//==================================================================================================================
CGame * CGame::Create(void)
{
	CGame *pGame = NULL;		// ゲーム変数NULL

	pGame = new CGame;			// 動的に確保
	pGame->Init();				// 初期化処理

	return pGame;				// 値を返す
}

//==================================================================================================================
//	ゲームの状態設定
//==================================================================================================================
void CGame::SetGameState(GAMESTATE state)
{
	m_gameState = state;
}

//==================================================================================================================
//	ゲームの状態取得
//==================================================================================================================
CGame::GAMESTATE CGame::GetGameState(void)
{
	return m_gameState;
}

//==================================================================================================================
//	プレイヤー情報取得
//==================================================================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//==================================================================================================================
//	モデルの設定
//==================================================================================================================
void CGame::SetModel(void)
{
	// 配列番号初期化
	int nNumber = 0;

	// ゴール輪っかモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_GOAL_CIRCLE);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(470.0f, 10.0f, -585.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.0f, 3.0f, 3.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));	// 回転設定
	nNumber++;															// 配列番号加算1

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN0);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(520.0f, 10.0f, -585.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));	// 回転設定
	nNumber++;															// 配列番号加算2

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN1);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(870.0f, 10.0f, -585.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));	// 回転設定
	nNumber++;															// 配列番号加算3

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN2);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1050.0f, 18.0f, -585.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));	// 回転設定
	nNumber++;															// 配列番号加算4

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN3);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1250.0f, 80.0f, -1000.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	nNumber++;															// 配列番号加算5

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN4);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(940.0f, 150.0f, -1100.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));		// 回転設定
	nNumber++;															// 配列番号加算6

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN5);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(940.0f, 250.0f, -200.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));		// 回転設定
	nNumber++;															// 配列番号加算7

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN6);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(750.0f, 250.0f, 125.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 4 * 3, 0.0f));// 回転設定
	nNumber++;															// 配列番号加算8

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN7);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(180.0f, 250.0f, 690.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 4 * 3, 0.0f));// 回転設定
	nNumber++;															// 配列番号加算9

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN8);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(250.0f, 250.0f, 960.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 4 * 3, 0.0f));// 回転設定10

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN9);			// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-120.0f, 200.0f, 1145.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	nNumber++;															// 配列番号加算11

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN10);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-120.0f, 200.0f, 300.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	nNumber++;															// 配列番号加算12

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN11);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-125.0f, 20.0f, -150.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	nNumber++;															// 配列番号加算13

	// リスポーンモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN12);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(170.0f, 10.0f, -585.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));	// 回転設定
	nNumber++;															// 配列番号加算14

	// 土台モデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(590.0f, 3.5f, -585.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 6.7f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));	// 回転設定
	nNumber++;															// 配列番号加算15

	// 土台モデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-123.0f, 3.5f, -230.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.35f, 3.0f, 2.2f));			// 大きさ設定
	nNumber++;															// 配列番号加算16

	// 土台モデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1260.0f, 59.0f, -920.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 2.7f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.19f, 0.0f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算17

	// 土台モデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(938.0f, 195.0f, -620.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 6.4f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(-0.1f, 0.0f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算18

	// 土台モデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(530.0f, 246.0f, 346.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 6.9f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 2.36f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算19

	// 土台モデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(262.0f, 246.0f, 986.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.4f, 3.0f, 1.5f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 0.8f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算20

	// 土台モデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-120.0f, 184.0f, 620.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 8.4f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -0.01f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算21

	// 土台カーブモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE0);// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-113.0f, 3.5f, -570.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));		// 回転設定
	nNumber++;															// 配列番号加算22

	// 土台カーブモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE1);// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1260.0f, 3.5f, -600.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// 大きさ設定
	nNumber++;															// 配列番号加算23

	// 土台カーブモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE2);// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1247.0f, 99.0f, -1280.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));	// 回転設定
	nNumber++;															// 配列番号加算24

	// 土台カーブモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE3);// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1001.0f, 248.0f, -134.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 0.75f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算25

	// 土台カーブモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE4);// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(95.0f, 248.0f, 810.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -2.3f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算26

	// 土台カーブモデルの生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE5);// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-105.0f, 184.0f, 1450.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -1.55f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算27

	// 看板の生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1340.0f, 30.0f, -585.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));	// 回転設定
	nNumber++;															// 配列番号加算28

	// 看板の生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1250.0f, 130.0f, -1385.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));		// 回転設定
	nNumber++;															// 配列番号加算29

	// 看板の生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1050.0f, 140.0f, -1385.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -2.5f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算30

	// 看板の生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(900.0f, 150.0f, -1335.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -2.0f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算31

	// 看板の生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(940.0f, 280.0f, 70.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));		// 回転設定
	nNumber++;															// 配列番号加算32

	// 看板の生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(60.0f, 280.0f, 880.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -1.0f, 0.0f));			// 回転設定
	nNumber++;															// 配列番号加算33

	// 看板の生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(530.0f, 260.0f, 1480.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 0.5f, D3DX_PI));		// 回転設定
	nNumber++;															// 配列番号加算34

	// 看板の生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-50.0f, 220.0f, 1650.0f));	// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -1.0f, D3DX_PI));		// 回転設定
	nNumber++;															// 配列番号加算35

	// 看板の生成処理
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// 生成
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-50.0f, 40.0f, -620.0f));		// 位置設定
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// 大きさ設定
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI));		// 回転設定
	nNumber++;															// 配列番号加算36
}

