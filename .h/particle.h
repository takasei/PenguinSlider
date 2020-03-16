//==================================================================================================================
//
// パーティクル[particle.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//==================================================================================================================
// インクルードファイル
//==================================================================================================================
#include "main.h"
#include "scene.h"

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define MAX_PARTICLE 400		// パーティクルの最大数

//==================================================================================================================
//
// パーティクルクラスの定義
//
//==================================================================================================================
class CParticle : public CScene
{
public:

	CParticle(PRIORITY type);				// コンストラクタ
	~CParticle();							// デストラクタ
	void Init(void);						// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(void);						// 更新処理
	void Draw(void);						// 描画処理

	static CParticle *Create(int number, D3DXVECTOR3 pos);	// 生成処理
	static HRESULT Load(void);				// テクスチャ情報ロード
	static void Unload(void);				// テクスチャ情報アンロード

	void SetPos(D3DXVECTOR3 pos);			// 位置設定処理
	void SetSize(D3DXVECTOR3 size);			// 大きさ設定処理
	void SetMove(D3DXVECTOR3 move);			// 移動量設定処理

	D3DXVECTOR3 GetPos(void) { return m_pos; }		// 位置取得処理
	D3DXVECTOR3 GetSize(void) { return m_size; }	// 大きさ取得処理
	D3DXVECTOR3 GetMove(void) { return m_move; }	// 移動量取得処理

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャへのポインタ
	static CParticle *m_pParticle[MAX_PARTICLE];// パーティクル情報のポインタ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// バッファ
	VERTEX_3D *m_pVtx;						// 頂点格納
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 回転
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_size;						// 大きさ

	int m_nLife;							// ライフ
};
#endif