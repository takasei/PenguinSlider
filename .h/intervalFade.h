//==================================================================================================================
//
// インターバルフェード処理[intervalFade.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _INTERVALFADE_H
#define _INTERVALFADE_H

//==================================================================================================================
// インクルードファイル
//==================================================================================================================
#include "main.h"
#include "scene2D.h"

//==================================================================================================================
//
// インターバルフェードクラスの定義
//
//==================================================================================================================
class CIntervalFade : public CScene2D
{
public:
	// ==========================================================
	// フェードの状態
	// ==========================================================
	typedef enum
	{
		FADE_NONE = 0,							// 何もない状態
		FADE_IN,								// フェードイン処理
		FADE_OUT,								// フェードアウト処理
		FADE_MAX								// 最大数
	} INTERVAL_FADE;

	CIntervalFade(PRIORITY type);				// コンストラクタ
	~CIntervalFade();							// デストラクタ
	void Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	static INTERVAL_FADE GetIntervalFade(void);	// フェードの取得処理
	static CIntervalFade *Create(void);			// 生成処理
	static HRESULT Load(void);					// フェードの情報ロード
	static void Unload(void);					// フェードの情報アンロード
	static void FadeIN(void);					// フェードインさせる処理
	static void FadeOUT(void);					// フェードアウトさせる処理

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャ情報
	static INTERVAL_FADE m_fade;				// フェードの情報
	static D3DXCOLOR m_colorFade;				// フェードの色情報

	D3DXVECTOR3 m_pos;							// 位置
};
#endif
