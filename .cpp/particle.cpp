//==================================================================================================================
//
// パーティクル処理[particle.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "debugProc.h"
#include "particle.h"
#include "renderer.h"
#include "manager.h"
#include "math.h"
#include <time.h>
#include "player.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "inputKeyboard.h"

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define PARTICLE_TEXTURE "data/TEXTURE/shadow000.jpg"	// 読み込むテクスチャのソース先
#define PARTICLE_SIZE 7									// パーティクルの大きさ
#define RANDOM_RANGE 50									// ランダムの最大範囲
#define PARTICLE_LIFE 20								// パーティクルのライフ
#define PARTICLE_GRAVITY 0.2f							// パーティクルの重力
#define PARTICLE_FRICTION 0.95f							// パーティクルの摩擦
#define PARTICLE_DECREASE 0.01f							// パーティクルの大きさ減少量
#define RARTICLE_RAND 400								// パーティクルのランダム範囲

//==================================================================================================================
// 静的メンバ変数の初期化
//==================================================================================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;	// テクスチャ変数
CParticle *CParticle::m_pParticle[MAX_PARTICLE] = {};// パーティクル情報

//==================================================================================================================
// コンストラクタ
//==================================================================================================================
CParticle::CParticle(PRIORITY type = CScene::PRIORITY_EFFECT) :CScene(type)
{

}

//==================================================================================================================
// デストラクタ
//==================================================================================================================
CParticle::~CParticle()
{

}

//==================================================================================================================
// 初期化処理
//==================================================================================================================
void CParticle::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// レンダラー情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// デバイスの取得

	// 位置・回転の初期設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// 回転
	m_move.x = (float(rand() % RARTICLE_RAND) - float(rand() % RARTICLE_RAND)) / 100;	// X移動量
	m_move.y = (float(rand() % RARTICLE_RAND) - float(rand() % RARTICLE_RAND)) / 100;	// Y移動量
	m_move.z = (float(rand() % RARTICLE_RAND) - float(rand() % RARTICLE_RAND)) / 100;	// Z移動量
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);												// 大きさ
	m_nLife = PARTICLE_LIFE;															// ライフ

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	//頂点座標の設定(右回りで設定する)
	m_pVtx[0].pos = D3DXVECTOR3(-PARTICLE_SIZE / 2, +PARTICLE_SIZE / 2, 0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(+PARTICLE_SIZE / 2, +PARTICLE_SIZE / 2, 0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(-PARTICLE_SIZE / 2, -PARTICLE_SIZE / 2, 0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(+PARTICLE_SIZE / 2, -PARTICLE_SIZE / 2, 0.0f);

	//法線ベクトルの設定
	m_pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//色の設定
	m_pVtx[0].col = D3DXCOLOR(0.4980f, 1.0f, 0.8313f, 1.0f);
	m_pVtx[1].col = D3DXCOLOR(0.4980f, 1.0f, 0.8313f, 1.0f);
	m_pVtx[2].col = D3DXCOLOR(0.4980f, 1.0f, 0.8313f, 1.0f);
	m_pVtx[3].col = D3DXCOLOR(0.4980f, 1.0f, 0.8313f, 1.0f);

	//テクスチャ座標の設定
	m_pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// 終了処理
//==================================================================================================================
void CParticle::Uninit(void)
{
	// 頂点バッファがNULLじゃないとき
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();				// 頂点バッファの開放
		m_pVtxBuff = NULL;					// NULLにする
	}
}

//==================================================================================================================
// 更新処理
//==================================================================================================================
void CParticle::Update(void)
{
	// 乱数化
	srand((unsigned)time(NULL));

	// 大きさ取得
	m_size = GetSize();

	// ライフを1ずつ減少
	m_nLife--;

	// ライフが無くなったら
	if (m_nLife <= 0)
	{
		// 消去
		Release();
		return;
	}

	// 位置更新
	m_pos += m_move;

	// 摩擦計算
	m_move.x *= PARTICLE_FRICTION;
	m_move.y *= PARTICLE_FRICTION;
	m_move.z *= PARTICLE_FRICTION;

	// 大きさをだんだん小さくする
	m_size.x -= PARTICLE_DECREASE;
	m_size.y -= PARTICLE_DECREASE;

	// 重力
	m_move.y -= PARTICLE_GRAVITY;

	// 大きさ設定
	SetSize(m_size);

	// 移動量設定
	SetMove(m_move);
}

//==================================================================================================================
// 描画処理
//==================================================================================================================
void CParticle::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// レンダラー情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxView;			// 計算用マトリックス

	// 加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);		// 現在のビューマトリックスを取得
	m_mtxWorld._11 = mtxView._11;						// 逆行列を設定
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// スケールを反映
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 220);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// 通常ブレンド
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//αテストの設定を戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 220);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

//==================================================================================================================
// 位置設定
//==================================================================================================================
void CParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// 大きさ設定
//==================================================================================================================
void CParticle::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//==================================================================================================================
// 移動量設定
//==================================================================================================================
void CParticle::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//==================================================================================================================
// ポリゴン生成
//==================================================================================================================
CParticle *CParticle::Create(int number, D3DXVECTOR3 pos)
{
	// 変数初期化
	CParticle *pParticle = NULL;

	// パーティクルの最大数までカウント
	for (int nCnt = 0; nCnt < number; nCnt++)
	{
		// メモリを動的に確保
		pParticle = new CParticle(CScene::PRIORITY_EFFECT);

		// 軌跡変数の初期処理
		pParticle->Init();

		// 位置設定
		pParticle->SetPos(pos);

		// 配列に保存
		m_pParticle[nCnt] = pParticle;
	}

	// 値を返す
	return pParticle;
}

//==================================================================================================================
// テクスチャ情報ロード
//==================================================================================================================
HRESULT CParticle::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// レンダラーの情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// デバイスを取得する

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		PARTICLE_TEXTURE,					// ファイルの名前
		&m_pTexture);						// 読み込むメモリー

	return S_OK;
}

//==================================================================================================================
// テクスチャ情報破棄
//==================================================================================================================
void CParticle::Unload(void)
{
	// テクスチャ情報はNULLじゃないとき
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();					// テクスチャ情報開放
		m_pTexture = NULL;						// NULLにする
	}
}