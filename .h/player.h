//==================================================================================================================
//
// プレイヤー[player.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//==================================================================================================================
// インクルードファイル
//==================================================================================================================
#include "main.h"
#include "sceneX.h"
#include "intervalFade.h"
#include "fade.h"

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define TEXTURE_PLAYER "data/TEXTURE/field000.jpg"		// 読み込むテクスチャのソース先
#define PLAYER_MODEL "data/MODEL/testmodel.x"			// 読み込むモデルのソース先
#define PLAYERSIZE_X	(100)							// プレイヤーのXサイズ
#define PLAYERSIZE_Y	(100)							// プレイヤーのYサイズ
#define PLAYER_MAX_MODEL (6)							// player.cpp内のモデルのパーツ数
#define CALCULATION_POS_Y 120							// 計算する位置Y

//==================================================================================================================
// 前方宣言
//==================================================================================================================
class CCamera;
class CMeshOrbit;
class CMotionModel;
class CRecord;
class CModel;
class CMeshField;
class CInputKeyboard;
class CInputGamepad;
class CFade;
class CParticle;
class CEnemy;

//==================================================================================================================
//
// プレイヤークラスの定義
//
//==================================================================================================================
class CPlayer : public CScene
{
public:
	//=============================================================================
	// 構造体定義
	//=============================================================================
	// キー要素
	typedef struct
	{
		D3DXVECTOR3 pos;				// キー要素の位置
		D3DXVECTOR3 rot;				// キー要素の回転
	}KEY;

	// キー情報
	typedef struct
	{
		KEY key[PLAYER_MAX_MODEL];		// パーツ数
		int nFram;						// フレーム
	}KEY_INFO;

	// プレイヤーのモーション
	typedef struct
	{
		KEY_INFO key_info[10];				// キーが何セットあるか
		D3DXVECTOR3 CollisionOfset;			// オフセット
		int nLoop;							// ループ
		int nNumKey;						// キー情報の数
		int Collision_nParts;				// パーツ番号
		int CollisionStartFram;				// 開始フレーム
		int CollisionEndFram;				// 終了フレーム
		int Collision_Damage;				// ダメージ数
		float CollisionRadius;				// 円の半径
	}MOTION_PLAYER;

	// モーションのタイプ
	typedef enum
	{
		PLAYER_MOTION_NORMAL = 0,			// ニュートラル
		PLAYER_MOTION_WALK,					// 歩き
		PLAYER_MOTION_ACTION,				// アクション
		PLAYER_MOTION_JUMP,					// ジャンプ
		PLAYER_MOTION_LANDING,				// 着地
		PLAYER_MOTION_DAMAGE,				// ダメージ
		PLAYER_MOTION_MAX					// モーションの最大数
	}PLAYER_MOTION_STATE;

	CPlayer(PRIORITY type);							// コンストラクタ
	~CPlayer();										// デストラクタ
	void Init(void);								// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理

	static CPlayer *Create(void);					// 生成処理

	void SetPos(D3DXVECTOR3 pos);					// 位置設定処理
	void SetRot(D3DXVECTOR3 rot);					// 回転設定処理
	void SetnNumPlace(int nNumPlace);				// リスポーン場所設定処理
	void SetbRand(bool bRand);						// 着地判定設定処理
	void SetbRange(bool bRange);					// 範囲内判定設定処理
	void SetRespawn(bool bRespawn);					// リスポーン判定設定処理
	void SetbGoal(bool bGoal);						// ゴール判定設定処理
	void SetbStart(bool bStart);					// スタート判定設定処理
	void SetbTitleLogo(bool bTitleLogo);			// タイトルロゴ判定設定処理
	void SetbTitleFade(bool bTitleFade);			// タイトルフェード設定処理

	D3DXVECTOR3 GetPos(void) { return m_pos; }		// 位置取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// 回転取得処理
	D3DXVECTOR3 GetMove(void) { return m_move; }	// 移動量取得処理

	int GetnNumPlace(void) {return m_nNumPlace; }	// リスポーン場所取得処理

	bool GetbRand(void);							// 着地判定取得処理
	bool GetbRange(void);							// 範囲内判定取得処理
	bool GetRespawn(void);							// リスポーン判定取得処理
	bool GetbGoal(void);							// ゴール判定取得処理
	bool GetStart(void);							// スタート判定取得処理
	bool GetbTitleLogo(void);						// タイトルロゴ判定取得処理
	bool GetbTitleFade(void);						// タイトルフェード判定処理

protected:

private:
	void LoadMotion(void);							// モーション読み込み
	void Moation(void);								// モーションさせる
	void OperationMove(CInputKeyboard *pInputKeyboard, 
		CInputGamepad *pInputGamepad);				// 操作処理
	void TitleUpdate(void);							// タイトルでのプレイヤー更新処理
	void TutorialUpdate(void);						// チュートリアルでのプレイヤー更新処理
	void GameUpdate(void);							// ゲームでのプレイヤー更新処理
	void bStartUpdate(CFade::FADE fade);			// プレイヤー内でのスタートの更新処理
	void bRangeUpdate(float height);				// プレイヤー内での範囲内にいるときの更新処理
	void bRandUpdate(float height);					// プレイヤー内での着地しているときの更新処理
	void nCntRandUpdate(CMeshField *pMeshField, 
		CIntervalFade::INTERVAL_FADE intervalFade);	// プレイヤー内での着地カウントの更新処理
	void PlayerModelUpdate(void);					// プレイヤー内でのモデルの更新処理

	float MeshFieldUpdate(CMeshField *pMeshField);	// プレイヤー内でのメッシュフィールドの更新処理

	CMotionModel *m_MotionModel[PLAYER_MAX_MODEL];	// モデル情報
	MOTION_PLAYER m_PlayerMotion[PLAYER_MOTION_MAX];// モーション情報
	D3DXMATRIX  m_mtxWorld;							// マトリックス

	static CCamera *m_pCamera;				// カメラの情報ポインタ
	static CMeshOrbit *m_pMeshOrbit;		// 軌跡の情報ポインタ
	static CRecord *m_pRecord;				// 記録情報ポインタ
	static CModel *m_pModel;				// モデル情報ポインタ
	static CParticle *m_pParticle;			// パーティクル情報ポインタ
	static CEnemy *m_pEnemy;				// 敵情報ポインタ

	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_posOld;					// 前回の位置
	D3DXVECTOR3 m_rot;						// 回転
	D3DXVECTOR3 m_move;						// 移動
	D3DXVECTOR3 m_size;						// 大きさ
	D3DXVECTOR3 m_difference;				// 回転の目標地点
	D3DXVECTOR3 posBET[PLAYER_MAX_MODEL];	// 各パーツの位置
	D3DXVECTOR3 rotBET[PLAYER_MAX_MODEL];	// 各パーツの回転
	D3DXVECTOR3 m_RespownPos;				// リスポーン位置
	D3DXVECTOR3 m_RespownRot;				// リスポーン回転

	int m_MotionType;						// モーションの種類
	int m_MotionOld;						// 前のモーション
	int m_Fram;								// フレーム
	int m_nCntKeySet;						// キーセットのカウント
	int m_nCntState;						// ステータスのカウント
	int m_nCntRand;							// 着地していないカウント
	int m_nCntGravity;						// 重力用カウント
	int m_nCntTitle;						// タイトル用カウント
	int m_nCntGoal;							// ゴールしたカウント
	int m_nNumPlace;						// リスポーン番号
	int m_nCntInterval;						// リスポーンのインターバル時間
	int m_nInterval;						// パーティクルの出る間隔
	int m_nCntTitleFade;					// タイトルフェードのカウント

	float m_RotModel;						// モデルの回転情報
	float m_fStickMove;						// コントローラーのスティックの移動量

	bool m_bRand;							// 着地しているかどうか
	bool m_bRange;							// 範囲内にいるかどうか
	bool m_bRespawn;						// リスポーンしたかどうか
	bool m_bGoal;							// 記録をするかどうか
	bool m_bStart;							// スタートしたかどうか
	bool m_bTitleLogo;						// タイトルロゴを表示していいかどうか
	bool m_bJump;							// ジャンプしたかどうか
	bool m_bStop;							// 止まっているかどうか
	bool m_bInterval;						// インターバルするかどうか
	bool m_bTitleFade;						// タイトルフェードするかどうか
};
#endif