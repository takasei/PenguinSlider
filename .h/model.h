//==================================================================================================================
//
// モデルクラス[model.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//==================================================================================================================
// インクルードファイル
//==================================================================================================================
#include "main.h"
#include "sceneX.h"

//==================================================================================================================
//
// モデルクラスの定義
//
//==================================================================================================================
class CModel : public CSceneX
{
public:

	//=============================================================================
	// オブジェクトの種類
	//=============================================================================
	typedef enum
	{
		MODEL_GOAL_CIRCLE,			// ゴール輪っか
		MODEL_RESPOWN0,				// リスポーン地点モデル0
		MODEL_RESPOWN1,				// リスポーン地点モデル1
		MODEL_RESPOWN2,				// リスポーン地点モデル2
		MODEL_RESPOWN3,				// リスポーン地点モデル3
		MODEL_RESPOWN4,				// リスポーン地点モデル4
		MODEL_RESPOWN5,				// リスポーン地点モデル5
		MODEL_RESPOWN6,				// リスポーン地点モデル6
		MODEL_RESPOWN7,				// リスポーン地点モデル7
		MODEL_RESPOWN8,				// リスポーン地点モデル8
		MODEL_RESPOWN9,				// リスポーン地点モデル9
		MODEL_RESPOWN10,			// リスポーン地点モデル10
		MODEL_RESPOWN11,			// リスポーン地点モデル11
		MODEL_RESPOWN12,			// リスポーン地点モデル12
		MODEL_FAUNDATIOIN0,			// 土台モデル0
		MODEL_FAUNDATIOIN_CURVE0,	// 土台カーブモデル0
		MODEL_FAUNDATIOIN_CURVE1,	// 土台カーブモデル1
		MODEL_FAUNDATIOIN_CURVE2,	// 土台カーブモデル2
		MODEL_FAUNDATIOIN_CURVE3,	// 土台カーブモデル3
		MODEL_FAUNDATIOIN_CURVE4,	// 土台カーブモデル4
		MODEL_FAUNDATIOIN_CURVE5,	// 土台カーブモデル5
		MODEL_POLE0,				// ポール
		MODEL_SIGNBOARD,			// 看板
		MODEL_MAX					// 最大数
	} MODEL;

	CModel(PRIORITY type);							// コンストラクタ
	~CModel();										// デストラクタ
	void Init(void);								// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理

	static CModel *Create(MODEL type);				// 生成処理
	static HRESULT Load(void);						// テクスチャとモデルの情報ロード
	static void Unload(void);						// テクスチャとモデルの情報アンロード

	bool CollisionBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 posOld, MODEL model);// 線と点の当たり判定処理
	bool CollisionBlockReturn(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 posOld, MODEL model);// 逆からの線と点の当たり判定処理
	bool CollisionSphere(D3DXVECTOR3 pos2, float radius1, float radius2, MODEL model);// 球と球の当たり判定処理

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex[MODEL_MAX];				// テクスチャ情報
	static LPD3DXMESH m_pMesh[MODEL_MAX];						// メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMat[MODEL_MAX];					// マテリアル情報へのポインタ
	static DWORD m_nNumMat[MODEL_MAX];							// マテリアル情報の数
	static CModel *m_pModel[MODEL_MAX];							// モデルの情報ポインタ
	static char *m_apFileName[MODEL_MAX];						// モデルのファイル名

	D3DXVECTOR3 m_pos;											// 位置
	D3DXVECTOR3 m_rot;											// 回転
	D3DXVECTOR3 m_size;											// 大きさ
	D3DXVECTOR3 m_RotGoal;										// ゴールの回転
	D3DXVECTOR3 m_RespownPos;									// リスポーン位置
};
#endif