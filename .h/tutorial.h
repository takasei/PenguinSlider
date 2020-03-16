//==================================================================================================================
//
// チュートリアル処理[tutorial.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _TUTORIAL_H
#define _TUTORIAL_H

//==================================================================================================================
// インクルードファイル
//==================================================================================================================
#include "main.h"

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define TUTORIAL_MAX_MODEL 1				// チュートリアルのモデルの最大数

//==================================================================================================================
// 前方宣言
//==================================================================================================================
class CCamera;
class CLight;
class CPolygon;
class CMeshField;
class CPlayer;
class CLogo;
class CModel;
class CMeshSphere;
class CIntervalFade;

//==================================================================================================================
//
// チュートリアルクラスの定義
//
//==================================================================================================================
class CTutorial
{
public:
	CTutorial();									// コンストラクタ
	~CTutorial();									// デストラクタ
	void Init(void);								// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理

	static CTutorial *Create(void);					// 生成処理
	static CPlayer *GetPlayer(void);				// プレイヤーの情報取得処理

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャの情報ポインタ
	static CCamera *m_pCamera;						// カメラのの情報ポインタ
	static CLight *m_pLight;						// ライトのの情報ポインタ
	static CPolygon *m_pPolygon;					// ポリゴンの情報ポインタ
	static CMeshField *m_pMeshField;				// メッシュフィールドの情報ポインタ
	static CPlayer *m_pPlayer;						// プレイヤーの情報ポインタ
	static CLogo *m_pLogo;							// ロゴの情報ポインタ
	static CModel *m_pModel[TUTORIAL_MAX_MODEL];	// モデルの情報ポインタ
	static CMeshSphere *m_pMeshSphere;				// メッシュ球の情報ポインタ
	static CIntervalFade *m_pIntervalFade;			// インターバルフェードの情報ポインタ

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuff;			// 頂点バッファ

	D3DXVECTOR3 m_pos;								// 位置

};
#endif
