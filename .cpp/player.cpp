//==================================================================================================================
//
// プレイヤー処理[player.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "inputKeyboard.h"
#include "renderer.h"
#include "player.h"
#include "debugProc.h"
#include "camera.h"
#include "meshField.h"
#include "motionModel.h"
#include "model.h"
#include "time.h"
#include "record.h"
#include "title.h"
#include <initializer_list>
#include "tutorial.h"
#include "game.h"
#include "inputGamepad.h"
#include "particle.h"
#include "titleFade.h"

//==================================================================================================================
// 静的メンバ変数の初期化
//==================================================================================================================
CCamera *CPlayer::m_pCamera = NULL;				// カメラ情報
CMeshOrbit *CPlayer::m_pMeshOrbit = NULL;		// 軌跡情報
CRecord *CPlayer::m_pRecord = NULL;				// 記録情報
CModel *CPlayer::m_pModel = NULL;				// モデル情報
CParticle *CPlayer::m_pParticle = NULL;			// パーティクル情報
CEnemy *CPlayer::m_pEnemy = NULL;				// 敵情報

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define MOTION_FILE_NAME "data/TEXT/C++3DMotion.txt"// 読み込むテキストデータのソース先
#define TITLE_PLAYER_MOVE 0.15f		// タイトルのプレイヤーの移動量
#define PLAYER_MOVE 0.25f			// プレイヤーの移動量
#define PLAYER_TURNING_MOVE 0.01f	// プレイヤーのジャンプ時の横の移動量
#define PLAYER_INERTIA 3.0f			// 慣性スピード
#define PLAYER_SPEED_DOWN -0.2f		// スピードダウン速度
#define JUMP_SPEED 0.2f				// ジャンプしたときの進行スピード
#define JUMP_MOVE 11.0f				// ジャンプするときの移動量
#define MAX_JAMP_SPEED 0.05f		// 最大ジャンプスピード
#define ROT_JUMP_TURNING 0.8f		// ジャンプ時のプレイヤーの回転制限
#define MAX_GRAVITY -6.0f			// 重力の最大値
#define GRAVITY -0.4f				// 重力
#define ROT_LIMIT 1.0f				// 回転制限
#define ROT_SPEED 0.4f				// 回転速度
#define ROT_AMOUNT 0.05f			// 回転の差を減らしていく量
#define REDUCE_SPEED 0.06f			// 減速スピード
#define RAND_COUNT 130				// 着地カウント
#define JUMP_COUNT1 40				// タイトル時のジャンプカウント1
#define JUMP_COUNT2 60				// タイトル時のジャンプカウント2
#define COLLISION_RADIUS1 20		// スポーンの当たり判定半径
#define COLLISION_RADIUS_PLAYER 50	// プレイヤーの当たり判定半径
#define GOAL_COUNT 2				// ゴールしたカウント
#define JOY_MIN_RANGE_V	20000.0f	// コントローラーの縦スティック反応最小値
#define GAME_MAX_PARTICLE 50		// パーティクルの最大数
#define INTERVAL 10					// インターバルの最大数
#define INTERVAL_COUNT_MAX1 90		// インターバルカウントの最大数1
#define INTERVAL_COUNT_MAX2 150		// インターバルカウントの最大数2
#define PLAYER_MOVE_SPEED 0.1f		// インターバル時のプレイヤーのスピード
#define LANDING_CAUNT 10			// 着地カウント

//==================================================================================================================
// コンストラクタ
//==================================================================================================================
CPlayer::CPlayer(PRIORITY type = CScene::PRIORITY_PLAYER) :CScene(type)
{
	m_pModel = nullptr;				// モデル情報初期化
}

//==================================================================================================================
// デストラクタ
//==================================================================================================================
CPlayer::~CPlayer()
{

}

//==================================================================================================================
// 初期化処理
//==================================================================================================================
void CPlayer::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, WhileY, 0.0f);				// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 前回の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 移動量
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// 大きさ
	m_RespownPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// リスポーン位置
	m_RespownRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// リスポーン回転
	m_nCntRand = 0;											// 着地していないカウント
	m_nCntGravity = 0;										// 重力用カウント
	m_nCntTitle = 0;										// タイトル用カウント
	m_nNumPlace = 0;										// リスポーン番号
	m_nCntGoal = 0;											// ゴールしたカウント
	m_fStickMove = 0.0f;									// コントローラーのスティックの移動量
	m_nCntInterval = 0;										// リスポーンのインターバル時間
	m_nInterval = 0;										// パーティクルのインターバル時間
	m_nCntTitleFade = 0;									// タイトルフェードのカウント
	m_bRand = false;										// 着地しているか
	m_bRange = false;										// 範囲内にいるかどうか
	m_bRespawn = false;										// リスポーンしているかどうか
	m_bGoal = false;										// 記録をするかどうか
	m_bStart = false;										// スタートしたかどうか
	m_bTitleLogo = false;									// タイトルロゴを表示していいかどうか
	m_bJump = false;										// ジャンプしたかどうか
	m_bStop = false;										// 止まっているかどうか
	m_bInterval = false;									// インターバルするかどうか
	m_bTitleFade = false;									// タイトルフェードするかどうか

	// タイトルのとき
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{
		m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);			// 回転
		m_difference = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// 回転の目標地点
	}
	else if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{// チュートリアルのとき
		m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);			// 回転
		m_difference = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// 回転の目標地点

		m_nCntGoal = 1;										// ゴールしたカウント
	}
	else if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		m_rot = D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f);		// 回転
		m_difference = D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f);// 回転の目標地点
	}
	else
	{
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 回転
		m_difference = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転の目標地点
	}

	//モーションの初期化
	for (int nCntMotion = 0; nCntMotion < PLAYER_MOTION_MAX; nCntMotion++)
	{
		m_PlayerMotion[nCntMotion].nLoop = 0;										// ループ
		m_PlayerMotion[nCntMotion].nNumKey = 0;										// キー情報の数
		m_PlayerMotion[nCntMotion].Collision_nParts = 0;							// パーツ番号
		m_PlayerMotion[nCntMotion].CollisionOfset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// オフセット
		m_PlayerMotion[nCntMotion].CollisionRadius = 0.0f;							// 円の半径
		m_PlayerMotion[nCntMotion].CollisionStartFram = 0;							// 開始フレーム
		m_PlayerMotion[nCntMotion].CollisionEndFram = 0;							// 終了フレーム
		m_PlayerMotion[nCntMotion].Collision_Damage = 0;							// ダメージ数

		// キーの総数をカウント
		for (int nCntKeySet = 0; nCntKeySet < 10; nCntKeySet++)
		{
			m_PlayerMotion[nCntMotion].key_info[nCntKeySet].nFram = 0;				// 各キーのフレーム

			for (int nCntKey = 0; nCntKey < 11; nCntKey++)
			{
				m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 各パーツの各キーの位置
				m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 各パーツの各キーの回転
			}
		}
	}

	//=================================モデルの設定=================================//
	//体 0
	m_MotionModel[0] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_BODY);		// 体生成
	m_MotionModel[0]->SetPos(D3DXVECTOR3(0, -2.0f, 0));										// 位置設定
	m_MotionModel[0]->SetRot(D3DXVECTOR3(0.0f, -1.5f, 0.0f));								// 回転設定
	m_MotionModel[0]->SetParent(NULL);														// 親設定
	//頭 1
	m_MotionModel[1] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_HEAD);		// 頭パーツ生成
	m_MotionModel[1]->SetPos(D3DXVECTOR3(-11.0f, 5.0f, -0.44f));							// 位置設定
	m_MotionModel[1]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// 親設定
	//左腕 2
	m_MotionModel[2] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_LARM);		// 左腕生成
	m_MotionModel[2]->SetPos(D3DXVECTOR3(-5.0f, 3.0f, -4.0f));								// 位置設定
	m_MotionModel[2]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// 親設定
	//右腕 3
	m_MotionModel[3] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_RARM);		// 右腕生成
	m_MotionModel[3]->SetPos(D3DXVECTOR3(-5.0f, 3.0f, 4.0f));								// 位置設定
	m_MotionModel[3]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// 親設定
	//左足 4
	m_MotionModel[4] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_LLEG);		// 左足生成
	m_MotionModel[4]->SetPos(D3DXVECTOR3(6.0f, 0.0f, -3.0f));								// 位置設定
	m_MotionModel[4]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// 親設定
	//右足 5
	m_MotionModel[5] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_RLEG);		// 右足生成
	m_MotionModel[5]->SetPos(D3DXVECTOR3(6.0f, 0.0f, 3.0f));								// 位置設定
	m_MotionModel[5]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// 親設定

	// モーションの読み込み
	LoadMotion();

	// パーティクルテクスチャロード
	CParticle::Load();

	// パーティクルの生成処理
	m_pParticle = CParticle::Create(GAME_MAX_PARTICLE, m_pos);
}

//==================================================================================================================
// 終了処理
//==================================================================================================================
void CPlayer::Uninit(void)
{
	// パーティクルテクスチャアンロード
	CParticle::Unload();

	// プレイヤーモデルの最大パーツまでカウント
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// モデルの終了処理
		m_MotionModel[nCnt]->Uninit();

		// メモリ削除
		delete m_MotionModel[nCnt];

		// ポインタ用NULL
		m_MotionModel[nCnt] = nullptr;
	}
}

//==================================================================================================================
// 更新処理
//==================================================================================================================
void CPlayer::Update(void)
{
	// フェード取得
	CFade::FADE fade = CFade::GetFade();

	// インターバルフェードの取得
	CIntervalFade::INTERVAL_FADE intervalFade = CIntervalFade::GetIntervalFade();

	// MeshField情報取得
	CMeshField *pMeshField = CMeshField::GetMeshField();

	// タイトルでのプレイヤー更新処理
	TitleUpdate();

	// チュートリアルでのプレイヤー更新処理
	TutorialUpdate();

	// ゲームでのプレイヤー更新処理
	GameUpdate();

	float height = WhileY;				// プレイヤーの高さ
	m_bRand = GetbRand();				// プレイヤーの着地判定取得
	m_bRange = GetbRange();				// プレイヤーの範囲内判定取得
	m_MotionOld = m_MotionType;			// 前のモーションの代入
	m_posOld = m_pos;					// 今の位置を前回の位置にする

	// プレイヤー内でのスタートの更新処理
	bStartUpdate(fade);

	// プレイヤー内でのメッシュフィールドの更新処理
	height = MeshFieldUpdate(pMeshField);

	// プレイヤー内での範囲内にいるときの更新処理
	bRangeUpdate(height);

	// プレイヤー内での着地判定の更新処理
	bRandUpdate(height);

	// モーション
	Moation();

	// プレイヤー内での着地カウントの更新処理
	nCntRandUpdate(pMeshField, intervalFade);

	// プレイヤー内でのモデルの更新処理
	PlayerModelUpdate();

	// リスポーン判定設定
	SetRespawn(m_bRespawn);

	// パーティクルのインターバルカウント加算
	m_nInterval++;

	// インターバルカウントが規定値より大きくなったとき
	if (m_nInterval >= INTERVAL)
	{
		// パーティクルの生成処理
		m_pParticle = CParticle::Create(GAME_MAX_PARTICLE, m_pos);

		// パーティクルのインターバルカウント初期化
		m_nInterval = 0;
	}

	// インターバルする状態のとき
	if (m_bInterval)
	{
		// インターバルカウント加算
		m_nCntInterval++;

		// プレイヤーの移動量止める
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// インターバルカウントが規定値以上のとき
		if (m_nCntInterval >= INTERVAL_COUNT_MAX1)
		{
			// フェードイン処理
			CIntervalFade::FadeIN();
		}

		// インターバルカウントが規定値以上のとき
		if (m_nCntInterval >= INTERVAL_COUNT_MAX2)
		{
			// インターバルをしない状態にする
			m_bInterval = false;

			// インターバルカウント初期化
			m_nCntInterval = 0;
		}
	}

#ifdef _DEBUG
	// デバッグ表示
	CDebugProc::Print("プレイヤーの位置 : %.2f, %.2f, %.2f\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("プレイヤーの移動量 : %.2f, %.2f, %.2f\n", m_move.x, m_move.y, m_move.z);
	CDebugProc::Print("プレイヤーの回転 : %.2f, %.2f, %.2f\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("当たった場所 : %d\n", m_nNumPlace);
#endif // _DEBUG
}

//==================================================================================================================
// 描画処理
//==================================================================================================================
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;			// 計算用格納変数

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	// 2つの行列の積
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// 2つの行列の積
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// 2つの行列の積
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// モデルの描画
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// 中心のマトリックス設定
		m_MotionModel[nCnt]->SetMtxCenter(m_mtxWorld);

		// 描画処理
		m_MotionModel[nCnt]->Draw();
	}
}

//==================================================================================================================
// 生成処理
//==================================================================================================================
CPlayer *CPlayer::Create(void)
{
	// シーン動的に確保
	CPlayer *pPlayer = new CPlayer(CScene::PRIORITY_PLAYER);

	pPlayer->Init();			// プレイヤーの初期化

	// 値を返す
	return pPlayer;
}

//==================================================================================================================
// 位置設定
//==================================================================================================================
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// 回転設定
//==================================================================================================================
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==================================================================================================================
// リスポーン場所設定
//==================================================================================================================
void CPlayer::SetnNumPlace(int nNumPlace)
{
	m_nNumPlace = nNumPlace;
}

//==================================================================================================================
// 操作処理
//==================================================================================================================
void CPlayer::OperationMove(CInputKeyboard *pInputKeyboard, CInputGamepad *pInputGamepad)
{
	D3DXVECTOR3 Diff;	// 計算用格納変数

	// コントローラー
	float fValueH = 0.0f;		// 縦
	float fValueV = 0.0f;		// 横
	float fMove = 0.0f;			// コントローラースティック移動量

	// 移動処理 左スティック
	pInputGamepad->GetStickLeft(0, &fValueV, &fValueH);

	// 着地しているとき
	if (m_bRand == true)
	{
		// キーボードの移動キーが押されていないとき
		if (!pInputKeyboard->GetKeyboardPress(DIK_D) && !pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			// 横スティック 又は 縦スティックが0じゃないとき
			if (fValueH != 0 || fValueV != 0)
			{
				// 左にスティックが倒れたとき
				if (fValueV >= -JOY_MAX_RANGE && fValueV < 0)
				{
					// 移動量計算
					fMove = fValueV * -PLAYER_MOVE / JOY_MAX_RANGE;

					// スティックの傾き度で移動させる
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

					// 回転の目標地点を決める
					m_difference.z = -ROT_LIMIT;

					// 回転の目標地点を代入
					m_difference.y = m_rot.y - ROT_SPEED;

					// モーションさせる
					m_MotionType = PLAYER_MOTION_WALK;
				}
				else if (fValueV <= JOY_MAX_RANGE && fValueV > 0)
				{// 右にスティックが倒れたとき
					// 移動量計算
					fMove = fValueV * PLAYER_MOVE / JOY_MAX_RANGE;

					// スティックの傾き度で移動させる
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

					// 回転の目標地点を決める
					m_difference.z = ROT_LIMIT;

					// 回転の目標地点を代入
					m_difference.y = m_rot.y + ROT_SPEED;

					// モーションさせる
					m_MotionType = PLAYER_MOTION_WALK;
				}
			}
		}

		// コントローラーの左スティックが倒されていないとき
		if (fValueV == 0)
		{
			// キーボードの[A]が押されたとき
			if (pInputKeyboard->GetKeyboardPress(DIK_A))
			{// 左
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

				// 回転の目標地点を決める
				m_difference.z = -ROT_LIMIT;

				// 回転の目標地点を代入
				m_difference.y = m_rot.y - ROT_SPEED;

				// モーションさせる
				m_MotionType = PLAYER_MOTION_WALK;
			}
			else if (pInputKeyboard->GetKeyboardPress(DIK_D))
			{// キーボードの[D]が押されたとき
			 // 右
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

				// 回転の目標地点を決める
				m_difference.z = ROT_LIMIT;

				// 回転の目標地点を代入
				m_difference.y = m_rot.y + ROT_SPEED;

				// モーションさせる
				m_MotionType = PLAYER_MOTION_WALK;
			}
		}

		// コントローラーの[A]が押されていないとき
		if (!pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_A))
		{
			// キーボードの[S]が押されたとき
			if (pInputKeyboard->GetKeyboardPress(DIK_S))
			{// 下
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_SPEED_DOWN;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_SPEED_DOWN;

				// 回転の目標地点を決める
				m_difference.z = 0.0f;

				// モーションさせる
				m_MotionType = PLAYER_MOTION_WALK;
			}
		}

		// キーボードの[S]が押されていないとき
		if (!pInputKeyboard->GetKeyboardPress(DIK_S))
		{
			// コントローラーの[A]が押されたとき
			if (pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_A))
			{
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_SPEED_DOWN;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_SPEED_DOWN;

				// 回転の目標地点を決める
				m_difference.z = 0.0f;

				// モーションさせる
				m_MotionType = PLAYER_MOTION_WALK;
			}
		}

		// 移動キーが押されていないとき
		if (!pInputKeyboard->GetKeyboardPress(DIK_D) && !pInputKeyboard->GetKeyboardPress(DIK_A) && fValueV == 0)
		{
			// 回転の目標地点を決める
			m_difference.z = 0.0f;

			// 回転の目標地点を代入
			m_difference.y = m_rot.y;

			// キーボードの[SPACE] 又は コントローラーの[B]が押されていないとき
			if (!pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) || !pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_B))
			{
				// タイトルのとき
				if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
				{
					// 常に前へ進むようにする
					m_move.x += sinf(D3DX_PI + m_rot.y) * TITLE_PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * TITLE_PLAYER_MOVE;
				}
				else
				{
					// 常に前へ進むようにする
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
				}
			}
		}
	}
	else
	{// 着地していないとき
		// 移動キーが押されていないとき
		if (!pInputKeyboard->GetKeyboardPress(DIK_D) && !pInputKeyboard->GetKeyboardPress(DIK_A) && fValueV == 0)
		{
			// 回転の目標地点を決める
			m_difference.z = 0.0f;

			// 回転の目標地点を代入
			m_difference.y = m_rot.y;
		}

		// コントローラーの左スティックを倒していないとき
		if (fValueV == 0)
		{
			// キーボードの[A]が押されたとき
			if (pInputKeyboard->GetKeyboardPress(DIK_A))
			{// 左
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;
				m_move.z += 0.0f;

				// 回転の目標地点を決める
				m_difference.z = -ROT_LIMIT;

				// 回転の目標地点を代入
				m_difference.y = m_rot.y - ROT_SPEED;
			}
			else if (pInputKeyboard->GetKeyboardPress(DIK_D))
			{// キーボードの[D]が押されたとき
				// 右
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;
				m_move.z += 0.0f;

				// 回転の目標地点を決める
				m_difference.z = ROT_LIMIT;

				// 回転の目標地点を代入
				m_difference.y = m_rot.y + ROT_SPEED;
			}
		}

		// キーボードの移動キーが押されていないとき
		if (!pInputKeyboard->GetKeyboardPress(DIK_D) && !pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			// 横スティック 又は 縦スティックが0じゃないとき(スティックが倒れているとき)
			if (fValueH != 0 || fValueV != 0)
			{
				// 左にスティックが倒れたとき
				if (fValueV >= -JOY_MAX_RANGE && fValueV < 0)
				{
					// 移動量計算
					fMove = fValueV * -PLAYER_TURNING_MOVE / JOY_MAX_RANGE;

					// スティックの傾き度で移動させる
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;

					// 回転の目標地点を決める
					m_difference.z = -ROT_LIMIT;

					// 回転の目標地点を代入
					m_difference.y = m_rot.y - ROT_SPEED;
				}
				else if (fValueV <= JOY_MAX_RANGE && fValueV > 0)
				{// 右にスティックが倒れたとき
					// 移動量計算
					fMove = fValueV * PLAYER_TURNING_MOVE / JOY_MAX_RANGE;

					// スティックの傾き度で移動させる
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;

					// 回転の目標地点を決める
					m_difference.z = ROT_LIMIT;

					// 回転の目標地点を代入
					m_difference.y = m_rot.y + ROT_SPEED;
				}
			}
		}
	}

	// プレイヤーの回転と目標地点の差を格納
	Diff.y = m_rot.y - m_difference.y;
	Diff.z = m_rot.z - m_difference.z;

	// D3DX_PIより大きいとき
	if (Diff.y > D3DX_PI)
	{
		Diff.y -= D3DX_PI * 2;
	}
	else if (Diff.y < -D3DX_PI)
	{// D3DX_PIより小さいとき
		Diff.y += D3DX_PI * 2;
	}

	// プレイヤーを徐々に回転させていく
	m_rot.y -= Diff.y * ROT_AMOUNT;
	m_rot.z -= Diff.z * ROT_AMOUNT;

	// プレイヤーの回転Zが制限以上だったとき
	if (m_rot.z < -ROT_LIMIT)
	{
		// 最大制限にする
		m_rot.z = -ROT_LIMIT;
	}

	// プレイヤーの回転Zが制限以上だったら
	if (m_rot.z > ROT_LIMIT)
	{
		// 最大制限にする
		m_rot.z = ROT_LIMIT;
	}
}

//==================================================================================================================
// タイトルでのプレイヤー更新処理
//==================================================================================================================
void CPlayer::TitleUpdate(void)
{
	// タイトルのとき
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{
		// タイトルフェードの取得
		CTitleFade::TITLE_FADE titleFade = CTitleFade::GetTitleFade();

		// カメラ情報取得
		CCamera *pCamera = CTitle::GetCamera();

		// カメラの視点位置取得
		D3DXVECTOR3 CameraposV = pCamera->GetPosV();

		// タイトルのときは動いていい状態にする
		m_bStart = true;

		// プレイヤーの位置Zがカメラの位置Zを超えたら
		if (m_pos.z > CameraposV.z)
		{
			// フェードがないとき
			if (titleFade == CTitleFade::FADE_NONE)
			{
				// フェードアウトさせる
				CTitleFade::FadeOUT();

				// フェードしていい状態にする
				m_bTitleFade = true;

				// フェード判定設定処理
				SetbTitleFade(m_bTitleFade);
			}
		}

		// フェードしていい状態のとき
		if (m_bTitleFade)
		{
			// インターバルカウント加算
			m_nCntTitleFade++;

			// インターバルカウントが規定値以上のとき
			if (m_nCntTitleFade >= INTERVAL_COUNT_MAX1)
			{
				// フェードイン処理
				CTitleFade::FadeIN();
			}

			// 常に前へ進むようにする
			m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE_SPEED;
			m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE_SPEED;

		}
		else
		{
			// 常に前へ進むようにする
			m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
			m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
		}

	}
}

//==================================================================================================================
// チュートリアルでのプレイヤー更新処理
//==================================================================================================================
void CPlayer::TutorialUpdate(void)
{
	// キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// コントローラーの情報取得
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	// チュートリアルのとき
	if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		// モデルの最大種類カウント
		for (int nCnt = 0; nCnt < TUTORIAL_MAX_MODEL; nCnt++)
		{
			// モデル情報取得
			m_pModel = (CModel*)CScene::GetScene(PRIORITY_MODEL, nCnt);
		}

		// キーボードの[SPACE] 又は ゲームパッドの[B]が押されたとき
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) || pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_B))
		{
			// チュートリアルのときは動いていい状態にする
			m_bStart = true;
		}
	}
}

//==================================================================================================================
// ゲームでのプレイヤー更新処理
//==================================================================================================================
void CPlayer::GameUpdate(void)
{
	// ゲームのとき
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// モデルの最大数までカウント
		for (int nCnt = 0; nCnt < GAME_MAX_MODEL; nCnt++)
		{
			// モデル情報取得
			m_pModel = (CModel*)CScene::GetScene(PRIORITY_MODEL, nCnt);
		}
	}
}

//==================================================================================================================
// プレイヤー内でのスタートの更新処理
//==================================================================================================================
void CPlayer::bStartUpdate(CFade::FADE fade)
{
	// キーボード取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// コントローラー取得
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	// スタートしていないとき
	if (m_bStart == false)
	{
		// スタート時は移動スピードを0にする
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// 着地している状態にする
		m_bRand = true;
	}
	else
	{// スタートしたとき
		// 着地しているとき
		if (m_bRand)
		{
			// タイトルのとき
			if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
			{
				// タイトル用カウント加算
				m_nCntTitle++;

				// カウントが規定値のとき
				if (m_nCntTitle == JUMP_COUNT1)
				{
					// 着地していない状態にする
					m_bRand = false;

					// 上に移動量を増やす
					m_move.y += JUMP_MOVE;

					// ジャンプしている状態にする
					m_bJump = true;

					// モーションさせる
					m_MotionType = PLAYER_MOTION_JUMP;
				}
				else if (m_nCntTitle == JUMP_COUNT2)
				{// カウントが規定値のとき
					// 着地していない状態にする
					m_bRand = false;

					// 上に移動量を増やす
					m_move.y += JUMP_MOVE;

					// ジャンプしている状態にする
					m_bJump = true;

					// モーションさせる
					m_MotionType = PLAYER_MOTION_JUMP;
				}
			}

			// チュートリアル 又は ゲームのとき
			if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL || CRenderer::GetMode() == CRenderer::MODE_GAME)
			{
				// キーボードの[SPACE] 又は コントローラーのBが押されたとき
				if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) || pInputGamepad->GetTrigger(0, CInputGamepad::JOYPADKEY_B))
				{
					// 着地していない状態にする
					m_bRand = false;

					// 上に移動量を増やす
					m_move.y += JUMP_MOVE;

					// モーションさせる
					m_MotionType = PLAYER_MOTION_JUMP;

					// ジャンプした状態にする
					m_bJump = true;
				}
			}

			// 着地カウントを0にする
			m_nCntRand = 0;
		}
		else
		{// 着地していないとき
		 // ジャンプスピードが規定値を超えたら
			if (m_move.y > MAX_JAMP_SPEED)
			{
				// ジャンプスピードを規定値にする
				m_move.y += MAX_JAMP_SPEED;
			}

			// 着地カウントが規定値範囲内のとき
			if (m_nCntRand >= 1 && m_nCntRand <= LANDING_CAUNT)
			{
				// ジャンプしていないとき
				if (m_bJump == false)
				{
					// キーボードの[SPACE] 又は コントローラーのBが押されたとき
					if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) || pInputGamepad->GetTrigger(0, CInputGamepad::JOYPADKEY_B))
					{
						// 上に移動量を規定値増やす
						m_move.y += JUMP_MOVE;

						// モーションさせる
						m_MotionType = PLAYER_MOTION_JUMP;

						// ジャンプした状態にする
						m_bJump = true;
					}
				}
			}
		}

		// 位置更新
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
		m_pos.z += m_move.z;

		// 減速
		m_move.x += (0 - m_move.x) * REDUCE_SPEED;
		m_move.z += (0 - m_move.z) * REDUCE_SPEED;

		// モデルがあるとき
		if (m_pModel != NULL)
		{
			// モデルが指定のモデルに当たったとき
			if ((m_pModel->CollisionBlock(m_pos, m_size, m_posOld, CModel::MODEL_GOAL_CIRCLE)) == true)
			{
				// ゴールしたカウント加算
				m_nCntGoal++;

				// ゴールしたカウントが規定値以上だったとき
				if (m_nCntGoal >= GOAL_COUNT)
				{
					// 記録が行われていないとき
					if (m_bGoal == false)
					{
						// チュートリアルのとき
						if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
						{
							// フェードが何もない時
							if (fade == CFade::FADE_NONE)
							{
								// フェードの設定
								CFade::SetFade(CRenderer::MODE_GAME);
							}
						}

						// ゲームのとき
						if (CRenderer::GetMode() == CRenderer::MODE_GAME)
						{
							// 時間取得
							int nTime = CTime::GetTime();

							// 記録のセーブ
							m_pRecord->SaveData(nTime);

							// 記録のロード
							m_pRecord->LoadData();
						}

						// 記録した状態にする
						m_bGoal = true;

						// ゴールした状態にする
						SetbGoal(m_bGoal);
					}
				}
			}
			else if ((m_pModel->CollisionBlockReturn(m_pos, m_size, m_posOld, CModel::MODEL_GOAL_CIRCLE)) == true)
			{// モデルが指定のモデルに当たったとき
				// ゴールしたカウント減算
				m_nCntGoal--;

				// ゴールカウントが規定値以下のとき
				if (m_nCntGoal < 0)
				{
					// ゴールカウント規定値にする
					m_nCntGoal = 0;
				}
			}

			// ゲームのとき
			if (CRenderer::GetMode() == CRenderer::MODE_GAME)
			{
				// 列挙型のfor文
				for (auto nCnt : { CModel::MODEL_RESPOWN0, CModel::MODEL_RESPOWN1, CModel::MODEL_RESPOWN2, CModel::MODEL_RESPOWN3, CModel::MODEL_RESPOWN4,
					CModel::MODEL_RESPOWN5, CModel::MODEL_RESPOWN6, CModel::MODEL_RESPOWN7, CModel::MODEL_RESPOWN8,
					CModel::MODEL_RESPOWN9, CModel::MODEL_RESPOWN10,CModel::MODEL_RESPOWN11, CModel::MODEL_RESPOWN12 })
				{
					// モデル情報取得
					m_pModel = (CModel*)CScene::GetScene(CScene::PRIORITY_MODEL, nCnt);

					// 球と球が当たったとき
					if (m_pModel->CollisionSphere(m_pos, COLLISION_RADIUS1, COLLISION_RADIUS_PLAYER, nCnt) == true)
					{
						// リスポーン番号設定
						m_nNumPlace = nCnt - CModel::MODEL_RESPOWN0;

						// リスポーン位置取得
						m_RespownPos = m_pModel->GetPos();

						// リスポーン回転取得
						m_RespownRot = m_pModel->GetRot();

						// リスポーン場所設定
						SetnNumPlace(m_nNumPlace);
					}
				}
			}
		}

		// ゴールしているとき
		if (m_bGoal == true)
		{
			// ゴール時は移動スピードを減らしていく
			m_move.x += sinf(D3DX_PI + m_rot.y) * -JUMP_SPEED;
			m_move.z += cosf(D3DX_PI + m_rot.y) * -JUMP_SPEED;

			// 移動量Xが規定値以下になったとき
			if (m_move.x <= 0)
			{
				// 移動量なくす
				m_move.x = 0;
			}

			// 移動量Zが規定値以下になったとき
			if (m_move.z <= 0)
			{
				// 移動量なくす
				m_move.z = 0;
			}
		}

		// チュートリアル 又は ゲームのとき
		if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL || CRenderer::GetMode() == CRenderer::MODE_GAME)
		{
			// 移動処理
			OperationMove(pInputKeyboard, pInputGamepad);
		}
	}
}

//==================================================================================================================
// プレイヤー内での範囲内にいるときの更新処理
//==================================================================================================================
void CPlayer::bRangeUpdate(float height)
{
	// メッシュフィールドの範囲内にいるとき
	if (m_bRange)
	{
		// プレイヤーモデルの一番下位置yがGetHeight内だったとき
		if (m_pos.y < WhileY + height && m_pos.y >= height)
		{
			// 着地している状態にする
			m_bRand = true;

			// モーションさせる
			m_MotionType = PLAYER_MOTION_LANDING;
		}
	}
	else
	{// メッシュフィールドの範囲外にいるとき
		// プレイヤーの位置Yが規定値以下のとき
		if (m_pos.y <= CALCULATION_POS_Y)
		{
			// ジャンプしていないとき
			if (m_bJump == false)
			{
				// 重力処理
				m_move.y += GRAVITY;

				// 落下スピードが規定値を超えたら
				if (m_move.y < MAX_GRAVITY)
				{
					// 落下スピードを規定値にする
					m_move.y = MAX_GRAVITY;
				}
			}
		}

		// 着地していない状態にする
		m_bRand = false;
	}
}

//==================================================================================================================
// プレイヤー内での着地している判定の更新処理
//==================================================================================================================
void CPlayer::bRandUpdate(float height)
{
	// 着地しているとき
	if (m_bRand)
	{
		// モーションさせる
		m_MotionType = PLAYER_MOTION_WALK;

		// 位置設定
		SetPos(D3DXVECTOR3(m_pos.x, height, m_pos.z));

		// 移動量yなくす
		m_move.y = 0.0f;

		// ジャンプしていない状態にする
		m_bJump = false;
	}
	else
	{// 着地していないとき
	 // 重力処理
		m_move.y += GRAVITY;

		// 落下スピードが規定値を超えたら
		if (m_move.y < MAX_GRAVITY)
		{
			// 落下スピードを規定値にする
			m_move.y = MAX_GRAVITY;
		}

		// ジャンプ時は移動スピードを少し速くする
		m_move.x += sinf(D3DX_PI + m_rot.y) * JUMP_SPEED;
		m_move.z += cosf(D3DX_PI + m_rot.y) * JUMP_SPEED;

		// 着地カウントを加算する
		m_nCntRand++;

		// 位置設定
		SetPos(D3DXVECTOR3(m_pos));
	}
}

//==================================================================================================================
// プレイヤー内での着地カウントの更新処理
//==================================================================================================================
void CPlayer::nCntRandUpdate(CMeshField *pMeshField, CIntervalFade::INTERVAL_FADE intervalFade)
{
	// 着地カウントが規定値を超えたとき
	if (m_nCntRand >= RAND_COUNT - 20)
	{
		// フェードがないとき
		if (intervalFade == CIntervalFade::FADE_NONE)
		{
			// フェードアウトさせる
			CIntervalFade::FadeOUT();

			// インターバルをする状態にする
			m_bInterval = true;
		}
	}

	// 着地カウントが規定値を超えたとき
	if (m_nCntRand >= RAND_COUNT)
	{
		// メッシュフィールドがあるとき
		if (pMeshField != NULL)
		{
			// チュートリアルのとき
			if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
			{
				// プレイヤーのX位置をメッシュフィールドのX位置にする
				m_pos.x = pMeshField->GetPos().x;

				// プレイヤーのY位置をメッシュフィールドのY位置にする
				m_pos.y = WhileY;

				// プレイヤーの回転を進行方向にする
				m_rot.y = D3DX_PI;
			}
			else
			{// ゲームのとき
				// プレイヤーの位置をリスポーンの位置にする
				m_pos = m_RespownPos;

				// プレイヤーの回転をリスポーン回転にする
				m_rot = m_RespownRot;
			}
		}

		// 着地している状態にする
		m_bRand = true;

		// リスポーンカウント初期化
		m_nCntRand = 0;

		// リスポーンしている状態にする
		m_bRespawn = true;
	}
}

//==================================================================================================================
// プレイヤー内でのモデルの更新処理
//==================================================================================================================
void CPlayer::PlayerModelUpdate(void)
{
	// プレイヤーモデルの最大パーツまでカウント
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// モデルの終了処理
		m_MotionModel[nCnt]->Update();
	}
}

//==================================================================================================================
// プレイヤー内でのメッシュフィールドの更新処理
//==================================================================================================================
float CPlayer::MeshFieldUpdate(CMeshField * pMeshField)
{
	// 変数の初期化
	float fHeight = 0.0f;

	// メッシュフィールドがあるとき
	if (pMeshField != NULL)
	{
		// 高さを算出
		fHeight = pMeshField->GetHeight(m_pos);
	}

	// 値を返す
	return fHeight;
}

//==================================================================================================================
// 着地判定取得
//==================================================================================================================
bool CPlayer::GetbRand(void)
{
	return m_bRand;
}

//==================================================================================================================
// 範囲内判定取得
//==================================================================================================================
bool CPlayer::GetbRange(void)
{
	return m_bRange;
}

//==================================================================================================================
// リスポーン判定取得
//==================================================================================================================
bool CPlayer::GetRespawn(void)
{
	return m_bRespawn;
}

//==================================================================================================================
// ゴール判定取得
//==================================================================================================================
bool CPlayer::GetbGoal(void)
{
	return m_bGoal;
}

//==================================================================================================================
// スタート判定取得
//==================================================================================================================
bool CPlayer::GetStart(void)
{
	return m_bStart;
}

//==================================================================================================================
// タイトルロゴ判定取得
//==================================================================================================================
bool CPlayer::GetbTitleLogo(void)
{
	return m_bTitleLogo;
}

//==================================================================================================================
// タイトルフェード判定取得
//==================================================================================================================
bool CPlayer::GetbTitleFade(void)
{
	return m_bTitleFade;
}

//==================================================================================================================
// モーション読み込み
//==================================================================================================================
void CPlayer::LoadMotion(void)
{
	FILE *pFile;			// ファイルポイント
	int nCntMotion = 0;		// モーションの数
	int nCntModel = 0;		// モデルのカウント
	int nCntKeySet = 0;		// フレームの分割数
	int nCntKey = 0;		// パーツの番号
	char cReadText[128];	// 文字として読み取り用
	char cHeadText[128];	// 比較する用
	char cDie[128];			// 不要な文字

	// ファイルを開く
	pFile = fopen(MOTION_FILE_NAME, "r");

	// ファイルがあるとき
	if (pFile != NULL)
	{
		// 読み込んだ文字が[SCRIPT]まで繰り返す
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);						// 一文を読み込む
			sscanf(cReadText, "%s", &cHeadText);							// 比較用テキストに文字を代入
		}

		// 読み込んだ文字が[SCRIPT]のとき
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// エンドスクリプトが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);					// 一文を読み込む
				sscanf(cReadText, "%s", &cHeadText);						// 比較用テキストに文字を代入

				// モーションセットが来たら
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					// フレーム分割数の初期化
					nCntKeySet = 0;

					// エンドモーションセットが来るまでループ
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);			// 一文を読み込む
						sscanf(cReadText, "%s", &cHeadText);				// 比較用テキストに文字を代入

						// 読み込んだ文字が[LOOP]のとき
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nLoop);			// ループ変数に値を代入
						}
						// 読み込んだ文字が[NUM_KEY]のとき
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nNumKey);		// キー情報の数に値を代入
						}
						// 読み込んだ文字が[KEYSET]のとき
						else if (strcmp(cHeadText, "KEYSET") == 0)
						{
							nCntKey = 0;									// キー情報初期化

							// 読み込んだ文字が[END_KEYSET]まで繰り返す
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);							// 一文を読み込む
								sscanf(cReadText, "%s", &cHeadText);								// 比較用テキストに文字を代入

								// 読み込んだ文字が[FRAME]のとき
								if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie,
										&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].nFram);	// フレームに値を代入
								}
								// 読み込んだ文字が[KEY]のとき
								else if (strcmp(cHeadText, "KEY") == 0)
								{
									// 読み込んだ文字が[END_KEY]まで繰り返す
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile);				// 一文を読み込む
										sscanf(cReadText, "%s", &cHeadText);					// 比較用テキストに文字を代入

										// 読み込んだ文字が[POS]のとき
										if (strcmp(cHeadText, "POS") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f",					// 位置に値を代入
												&cDie, &cDie,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.x,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.y,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.z);

											//m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos += m_Model[nCntKey]->GetPosition();
										}
										// 読み込んだ文字が[ROT]のとき
										else if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f",					// 回転に値を代入
												&cDie, &cDie,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.x,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.y,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.z);
										}
									}

									// パーツ番号加算
									nCntKey++;
								}
							}

							// フレームの分割数加算
							nCntKeySet++;
						}
					}
					// モーションの数加算
					nCntMotion++;
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	// ファイルが無いとき
	else
	{
		// メッセージで知らせる
		MessageBox(NULL, "モーションデータの読み込み失敗", "警告", MB_ICONWARNING);
	}
}

//==================================================================================================================
// モーションさせる
//==================================================================================================================
void CPlayer::Moation(void)
{
	// 前のモーションと今のモーションが違うとき
	if (m_MotionType != m_MotionOld)
	{
		m_Fram = 0;					// フレームを初期値に戻す
		m_nCntKeySet = 0;			// モーション情報を初期値に戻す
	}

	// プレイヤーのモデルの最大パーツ数までカウント
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// フレームが0のとき
		if (m_Fram == 0)
		{
			// モーション情報のフレームが0じゃないとき
			if (m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram != 0)
			{
				// 移動量ROTの計算
				rotBET[nCnt] = (m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].key[nCnt].rot - m_MotionModel[nCnt]->GetRot()) /
					(float)m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram;
			}
			else
			{
				//m_MotionModel[nCnt]->GetPosition() = m_PlayerMotion[m_MotionType].key_info[mCntKeySet].key[nCnt].pos;
				m_MotionModel[nCnt]->GetRot() = m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].key[nCnt].rot;
				posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		// フレーム移動
		if (m_Fram <= m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram)
		{
			m_MotionModel[nCnt]->SetPos(m_MotionModel[nCnt]->GetPos() + posBET[nCnt]);
			m_MotionModel[nCnt]->SetRot(m_MotionModel[nCnt]->GetRot() + rotBET[nCnt]);
		}
	}

	// フレームがモーション情報のフレームと同じであるとき
	if (m_Fram == m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram)
	{
		m_nCntKeySet++;
		m_Fram = 0;

		// キーセット数が規定値と同じになったら
		if (m_nCntKeySet == m_PlayerMotion[m_MotionType].nNumKey)
		{
			// ループしないとき
			if (m_PlayerMotion[m_MotionType].nLoop == 0)
			{
				m_nCntKeySet = 0;
				m_MotionType = 0;
				m_Fram = m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram;
				//g_Player.bAttack = false;
			}
			// ループするとき
			else if (m_PlayerMotion[m_MotionType].nLoop == 1)
			{
				m_nCntKeySet = 0;
				m_MotionType = 0;
			}
		}
	}
	// フレーム数が規定値と同じではないとき
	else
	{
		// フレーム加算
		m_Fram++;
	}
}

//==================================================================================================================
// 着地判定設定
//==================================================================================================================
void CPlayer::SetbRand(bool bRand)
{
	m_bRand = bRand;
}

//==================================================================================================================
// 範囲内判定設定
//==================================================================================================================
void CPlayer::SetbRange(bool bRange)
{
	m_bRange = bRange;
}

//==================================================================================================================
// リスポーン判定設定
//==================================================================================================================
void CPlayer::SetRespawn(bool bRespawn)
{
	m_bRespawn = bRespawn;
}

//==================================================================================================================
// ゴール判定設定
//==================================================================================================================
void CPlayer::SetbGoal(bool bGoal)
{
	m_bGoal = bGoal;
}

//==================================================================================================================
// スタート判定設定
//==================================================================================================================
void CPlayer::SetbStart(bool bStart)
{
	m_bStart = bStart;
}

//==================================================================================================================
// タイトルロゴ判定設定
//==================================================================================================================
void CPlayer::SetbTitleLogo(bool bTitleLogo)
{
	m_bTitleLogo = bTitleLogo;
}

//==================================================================================================================
// タイトルフェード判定設定
//==================================================================================================================
void CPlayer::SetbTitleFade(bool bTitleFade)
{
	m_bTitleFade = bTitleFade;
}
