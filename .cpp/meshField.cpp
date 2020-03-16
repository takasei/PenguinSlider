//==================================================================================================================
//
// メッシュフィールド処理[meshField.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "renderer.h"
#include "meshField.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "player.h"
#include "tutorial.h"
#include "game.h"
#include "title.h"

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define MASS_WIDTH 15										// 横のマス
#define TUTORIAL_MASS_WIDTH 25								// チュートリアル時の横のマス
#define MASS_DEPTH 200										// 縦のマス
#define CURVE_NUMBER 16										// カーブ滑らかさ
#define FIELD_ALPHA 0.1f									// メッシュフィールドアルファ
#define START_NUMBER0 0										// 0番目の始まる番号
#define FINISH_NUMBER0 35									// 0番目の終わる番号
#define START_NUMBER1 FINISH_NUMBER0 + 1					// 1番目の始まる番号
#define FINISH_NUMBER1 43									// 1番目の終わる番号
#define START_NUMBER2 FINISH_NUMBER1 + 1					// 2番目の始まる番号
#define FINISH_NUMBER2 150									// 2番目の終わる番号
#define START_NUMBER3 FINISH_NUMBER2 + 1					// 3番目の始まる番号
#define FINISH_NUMBER3 158									// 3番目の終わる番号
#define START_NUMBER4 FINISH_NUMBER3 + 1					// 4番目の始まる番号
#define FINISH_NUMBER4 198									// 4番目の終わる番号
#define START_NUMBER5 FINISH_NUMBER4 + 1					// 5番目の始まる番号
#define FINISH_NUMBER5 214									// 5番目の終わる番号
#define START_NUMBER6 FINISH_NUMBER5 + 1					// 6番目の始まる番号
#define FINISH_NUMBER6 314									// 6番目の終わる番号
#define START_NUMBER7 FINISH_NUMBER6 + 1					// 7番目の始まる番号
#define FINISH_NUMBER7 317									// 7番目の終わる番号
#define START_NUMBER8 FINISH_NUMBER7 + 1					// 8番目の始まる番号
#define FINISH_NUMBER8 392									// 8番目の終わる番号
#define START_NUMBER9 FINISH_NUMBER8 + 1					// 9番目の始まる番号
#define FINISH_NUMBER9 400									// 9番目の終わる番号
#define START_NUMBER10 FINISH_NUMBER9 + 1					// 10番目の始まる番号
#define FINISH_NUMBER10 415									// 10番目の終わる番号
#define START_NUMBER11 FINISH_NUMBER10 + 1					// 11番目の始まる番号
#define FINISH_NUMBER11 435									// 11番目の終わる番号
#define START_NUMBER12 START_NUMBER11 + 1					// 12番目の始まる番号
#define FINISH_NUMBER12 570									// 12番目の終わる番号

//==================================================================================================================
// 静的メンバ変数の初期化
//==================================================================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture = NULL;			// テクスチャ変数
CMeshField *CMeshField::m_pMeshField = NULL;				// メッシュフィールドの情報
CPlayer *CMeshField::m_pPlayer = NULL;						// プレイヤーの情報

//==================================================================================================================
// コンストラクタ
//==================================================================================================================
CMeshField::CMeshField(PRIORITY type = CScene::PRIORITY_FIELD) : CScene(type)
{

}

//==================================================================================================================
// デストラクタ
//==================================================================================================================
CMeshField::~CMeshField()
{

}

//==================================================================================================================
// 初期化処理
//==================================================================================================================
void CMeshField::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();		// レンダラー情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();	// デバイスの取得

	// タイトルのとき
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{
		m_nDepth = 300;									// 縦のブロック数
		m_nWidth = MASS_WIDTH;							// 横のブロック数
	}

	// チュートリアルのとき
	if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		m_nDepth = MASS_DEPTH;							// 縦のブロック数
		m_nWidth = TUTORIAL_MASS_WIDTH;					// 横のブロック数
	}

	// ゲームのとき
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		m_nDepth = FINISH_NUMBER12;						// 縦のブロック数
		m_nWidth = MASS_WIDTH;							// 横のブロック数
	}

	// 位置・回転の初期設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 回転
	m_nNumVertex = ((m_nWidth + 1) * m_nDepth * 2) + (m_nDepth - 1) * 2;// 総頂点数
	m_nNumIndex = (m_nDepth + 1) * (m_nWidth + 1);						// 総インデックス数
	m_nNumPolygon = m_nNumVertex - 2;									// 三角形の数
	m_aVecA[m_nDepth * m_nWidth] = {};									// 法線ベクトルを面の数分一時的に格納
	m_aVecB[m_nDepth * m_nWidth] = {};									// 法線ベクトルを面の数分一時的に格納
	m_vectorA = D3DXVECTOR3(0, 0, 0);									// 一つ目の外積用変数
	m_vectorB = D3DXVECTOR3(0, 0, 0);									// 二つ目の外積用変数
	m_vectorC = D3DXVECTOR3(0, 0, 0);									// 三つ目の外積用変数
	m_nNumber = 0;														// 配列の番号
	m_nStartBox = m_nWidth + 1;											// 始まる箱
	m_nEndBox = 0;														// 引かれる箱
	fDivide = 0;														// sinの中身を割る変数

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// インデックスバッファを生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// 縦をカウント
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// 横をカウント
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// 頂点座標の設定
			m_pVtx[0].pos.x = (-WhileX * m_nWidth) / 2 + WhileX * nWide;
			m_pVtx[0].pos.y = 0.0f;
			m_pVtx[0].pos.z = (WhileZ / 2 * m_nDepth) - WhileZ * nDepth;

			// 頂点カラー
			m_pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, FIELD_ALPHA);

			// テクスチャ描写の位置
			m_pVtx[0].tex = D3DXVECTOR2(1.0f * nWide, 1.0f * nDepth);

			// 頂点番号加算
			m_pVtx++;
		}
	}

	// 頂点データをアンロック
	m_pVtxBuff->Unlock();

	// 頂点データの範囲をロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	//////////////////////////////法線ベクトル//////////////////////////////
	// 縦をカウント
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// 横をカウント
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// インデックス番号
			int nIdx = nDepth * (m_nWidth + 1) + nWide;

			// 端は計算させない
			if (nWide != m_nWidth && nDepth != m_nDepth)
			{
				m_vectorA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;								// 一つ目のベクトル
				m_vectorB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;							// 二つ目のベクトル
				m_vectorC = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;								// 三つ目のベクトル
				D3DXVec3Cross(&m_aVecA[m_nNumber], &m_vectorA, &m_vectorB);									// 二つのベクトルの直交ベクトル
				D3DXVec3Normalize(&m_aVecA[m_nNumber], &m_aVecA[m_nNumber]);								// 正規化する
				D3DXVec3Cross(&m_aVecB[m_nNumber], &m_vectorB, &m_vectorC);									// 二つのベクトルの直交ベクトル
				D3DXVec3Normalize(&m_aVecB[m_nNumber], &m_aVecB[m_nNumber]);								// 正規化する

				// 配列の番号1プラスする
				m_nStartBox++;
				m_nEndBox++;
				m_nNumber++;
			}

			// 右上だったとき
			if (nIdx == m_nWidth)
			{
				// 法線ベクトル
				m_pVtx[nIdx].nor = m_aVecB[m_nWidth - 1];
			}
			else if (nIdx == m_nDepth * (m_nWidth + 1))
			{// 左下だったとき
				// 法線ベクトル
				m_pVtx[nIdx].nor = m_aVecA[(m_nDepth - 1) * m_nWidth];
			}
			else if (nIdx == 0)
			{// 左上だったとき
				// 法線ベクトル
				m_pVtx[nIdx].nor = (m_aVecA[nIdx] + m_aVecB[nIdx]) / 2;
			}
			else if (nIdx == (m_nDepth + 1) * (m_nWidth + 1) - 1)
			{// 右下だったとき
				// 法線ベクトル
				m_pVtx[nIdx].nor = (m_aVecA[m_nDepth * m_nWidth - 1] + m_aVecB[m_nDepth * m_nWidth - 1]) / 2;
			}
			else if (nWide != 0 && nWide != m_nWidth)
			{// 横の列が端じゃないとき
				// 縦が一列目だったとき
				if (nDepth == 0)
				{
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecB[nWide - 1] + m_aVecA[nWide] + m_aVecB[nWide]) / 3;
				}
				else if (nDepth == m_nDepth)
				{// 縦が最後尾だったとき
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecB[(m_nDepth - 1) * m_nWidth - 1 + nWide] +
						m_aVecA[(m_nDepth - 1) * m_nWidth + nWide] +
						m_aVecB[(m_nDepth - 1) * m_nWidth + nWide]) / 3;
				}
				else
				{// それ以外
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1]) / 6;
				}
			}
			else if (nDepth != 0 && nDepth != m_nDepth)
			{// 縦の列が端じゃないとき
				// 先頭のとき
				if (nWide == 0)
				{
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecA[(nDepth - 1) * m_nWidth] +
						m_aVecB[m_nWidth + (nDepth - 1) * m_nWidth] +
						m_aVecA[m_nWidth + (nDepth - 1) * m_nWidth]) / 3;
				}
				else if (nWide == m_nWidth)
				{// 最後尾のとき
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecB[m_nWidth - 1 + m_nWidth * (nDepth - 1)] +
						m_aVecA[m_nWidth - 1 + m_nWidth * (nDepth - 1)] +
						m_aVecB[m_nWidth - 1 + m_nWidth * nDepth]) / 3;
				}
			}
		}
		// 配列の番号1プラスする
		m_nStartBox++;
		m_nEndBox++;
	}

	// 頂点データをアンロック
	m_pVtxBuff->Unlock();

	WORD *pIdx;				// インデックスバッファへのポインタ

	// インデックスバッファをロックしインデックスデータへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// 縦をカウント
	for (int nCntY = 0; nCntY < m_nDepth; nCntY++)
	{
		// 一行目じゃないとき
		if (nCntY != 0)
		{
			pIdx[0] = (m_nWidth + 1) + nCntY * (m_nWidth + 1);
			pIdx++;
		}

		// 横をカウント
		for (int nCntX = 0; nCntX < m_nWidth + 1; nCntX++)
		{
			pIdx[0] = (m_nWidth + 1) + nCntX + nCntY * (m_nWidth + 1);
			pIdx[1] = nCntX + nCntY * (m_nWidth + 1);
			pIdx += 2;
		}

		// 縮退ポリゴン
		if (nCntY + 1 < m_nDepth)
		{
			pIdx[0] = m_nWidth + nCntY * (m_nWidth + 1);
			pIdx++;
		}
	}

	// インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();
}

//==================================================================================================================
// 終了処理
//==================================================================================================================
void CMeshField::Uninit(void)
{
	// 頂点バッファがNULLじゃないとき
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();				// 頂点バッファの開放
		m_pVtxBuff = NULL;					// NULLにする
	}

	// インデックスバッファがNULLじゃないとき
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();				// インデックスバッファの開放
		m_pIdxBuff = NULL;					// NULLにする
	}
}

//==================================================================================================================
// 更新処理
//==================================================================================================================
void CMeshField::Update(void)
{
	// キーボード取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	VERTEX_3D *m_pVtx;									// 頂点情報

	// 再初期化
	m_nNumber = 0;										// 配列の番号
	m_nStartBox = m_nWidth + 1;							// 始まる箱
	m_nEndBox = 0;										// 引かれる箱

	// 動かす
	fDivide -= 0.05f;

	// 頂点データの範囲をロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// 縦をカウント
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// 横をカウント
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// ゲームのとき
			if (CRenderer::GetMode() == CRenderer::MODE_GAME)
			{
				// 縦のブロックが規定値範囲内のとき
				if (nDepth >= START_NUMBER0 && nDepth <= FINISH_NUMBER0)
				{// ゴール手前のジャンプした後
					// 頂点座標の設定
					m_pVtx[0].pos.x = -200 + WhileX * nWide;												// X座標
					m_pVtx[0].pos.y = (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;				// Y座標
					m_pVtx[0].pos.z = -WhileZ * (nDepth + 5.5f);											// Z座標
				}
				else if (nDepth >= START_NUMBER1 && nDepth <= FINISH_NUMBER1)
				{// 縦の列ブロックが規定範囲内のとき
					// ジャンプした後のゴール手前のカーブ
					// 頂点座標の設定
					m_pVtx[0].pos.x = (m_nWidth - nWide) * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER1 - 16))) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						60 + 110 * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER1 - 16)));									// 内側曲線(位置+半径*sinf(分割数*番目))
					m_pVtx[0].pos.y = (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;											// Y座標
					m_pVtx[0].pos.z = (m_nWidth - nWide) * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER1 - 16))) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						-420 + 90 * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER1 - 16)));									// 内側曲線(位置+半径*sinf(分割数*番目))
				}
				else if (nDepth >= START_NUMBER2 && nDepth <= FINISH_NUMBER2)
				{// 縦の列ブロックが規定値範囲内のとき
					// ゴールとスタートの長い直線
					// 頂点座標の設定
					m_pVtx[0].pos.x = -435 + WhileZ * (nDepth + 5.5f);									// X座標
					m_pVtx[0].pos.y = (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;			// Y座標
					m_pVtx[0].pos.z = -660 + WhileX * nWide;											// Z座標
				}
				else if (nDepth >= START_NUMBER3 && nDepth <= FINISH_NUMBER3)
				{// 縦の列ブロックが規定値範囲内のとき
					// スタート後の最初のカーブ
					// 頂点座標の設定
					m_pVtx[0].pos.x = nWide * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER3 + 7 - nDepth)) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						1125 + 60 * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER3 + 7 - nDepth));						// 内側曲線(位置+半径*sinf(分割数*番目))
					m_pVtx[0].pos.y = (nDepth - FINISH_NUMBER2) * 2 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;// Y座標
					m_pVtx[0].pos.z = nWide * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER3 + 7 - nDepth)) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						-720 + 60 * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER3 + 7 - nDepth));						// 内側曲線(位置+半径*sinf(分割数*番目))
				}
				else if (nDepth >= START_NUMBER4 && nDepth <= FINISH_NUMBER4)
				{// 縦の列ブロックが規定値範囲内のとき
					// 最初カーブした後の短い直線
					// 頂点座標の設定
					m_pVtx[0].pos.x = 1185 + WhileX * nWide;																		// X座標
					m_pVtx[0].pos.y = 16 + (nDepth - FINISH_NUMBER3) * 2 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;	// Y座標
					m_pVtx[0].pos.z = 860 + -WhileZ * nDepth;																		// Z座標
				}
				else if (nDepth >= START_NUMBER5 && nDepth <= FINISH_NUMBER5)
				{// 縦の列ブロックが規定値範囲内のとき
					// 1回目の180度カーブ
					// 頂点座標の設定
					m_pVtx[0].pos.x = nWide * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER5 - 1 - nDepth)) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						1100 + 86 * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER5 - 1 - nDepth));						// 内側曲線(位置+半径*sinf(分割数*番目))
					m_pVtx[0].pos.y = 96 + (nDepth - FINISH_NUMBER4) * 3 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;// Y座標
					m_pVtx[0].pos.z = nWide * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER5 - 1 - nDepth)) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						-1120 + 86 * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER5 - 1 - nDepth));						// 内側曲線(位置+半径*sinf(分割数*番目))
				}
				else if (nDepth >= START_NUMBER6 && nDepth <= FINISH_NUMBER6)
				{// 縦の列ブロックが規定値範囲内のとき
					// 180度カーブ後の直線
					// 頂点座標の設定
					m_pVtx[0].pos.x = 865 + (WhileX * m_nWidth) - WhileX * nWide;													// X座標
					m_pVtx[0].pos.y = 144 + (nDepth - FINISH_NUMBER5) + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;	// Y座標
					m_pVtx[0].pos.z = -3260 + WhileZ * nDepth;																		// Z座標
				}
				else if (nDepth >= START_NUMBER7 && nDepth <= FINISH_NUMBER7)
				{// 縦の列ブロックが規定値範囲内のとき
					// 直線後のちょっとしたカーブ
					// 頂点座標の設定
					m_pVtx[0].pos.x = (m_nWidth - nWide) * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER7 - 1))) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						805 + 60 * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER7 - 1)));										// 内側曲線(位置+半径*sinf(分割数*番目))
					m_pVtx[0].pos.y = 244 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;									// Y座標
					m_pVtx[0].pos.z = (m_nWidth - nWide) * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER7 - 1))) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						-120 + 60 * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER7 - 1)));									// 内側曲線(位置+半径*sinf(分割数*番目))
				}
				else if (nDepth >= START_NUMBER8 && nDepth <= FINISH_NUMBER8)
				{// 縦の列ブロックが規定値範囲内のとき
					// 斜め直線
					// 頂点座標の設定
					m_pVtx[0].pos.x = 845 + (m_nWidth - nWide) * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * 3) - (nDepth - (START_NUMBER8)) * 10;		// X座標
					m_pVtx[0].pos.y = 244 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;												// Y座標
					m_pVtx[0].pos.z = -75 + (m_nWidth - nWide) * WhileZ  * sinf((D3DX_PI / CURVE_NUMBER) * 3) + (nDepth - (START_NUMBER8)) * 10;	// Z座標
				}
				else if (nDepth >= START_NUMBER9 && nDepth <= FINISH_NUMBER9)
				{// 縦の列ブロックが規定範囲内のとき
					// 斜め直線後カーブ
					// 頂点座標の設定
					m_pVtx[0].pos.x = nWide * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER9 + 19 - nDepth)) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						324 + 120 * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER9 + 19 - nDepth));						// 内側曲線(位置+半径*sinf(分割数*番目))
					m_pVtx[0].pos.y = 244 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;					// Y座標
					m_pVtx[0].pos.z = nWide * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER9 + 19 - nDepth)) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						800 + 80 * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER9 + 19 - nDepth));						// 内側曲線(位置+半径*sinf(分割数*番目))
				}
				else if (nDepth >= START_NUMBER10 && nDepth <= FINISH_NUMBER10)
				{// 縦の列ブロックが規定値範囲内のとき
					// 二回目の斜め直線
					// 頂点座標の設定
					m_pVtx[0].pos.x = 247 + nWide * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * 12) + (nDepth - (START_NUMBER10)) * 10;	// X座標
					m_pVtx[0].pos.y = 244 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;									// Y座標
					m_pVtx[0].pos.z = 865 + nWide * WhileZ  * sinf((D3DX_PI / CURVE_NUMBER) * 12) + (nDepth - (START_NUMBER10)) * 10;	// Z座標
				}
				else if (nDepth >= START_NUMBER11 && nDepth <= FINISH_NUMBER11)
				{// 縦の列ブロックが規定範囲内のとき
					// 大きいカーブ
					// 頂点座標の設定
					m_pVtx[0].pos.x = (m_nWidth - nWide) * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER11 + 4))) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						150 + 200 * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER11 + 4)));									// 内側曲線(位置+半径*sinf(分割数*番目))
					m_pVtx[0].pos.y = 244 - (nDepth - FINISH_NUMBER10) * 3 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;	// Y座標
					m_pVtx[0].pos.z = (m_nWidth - nWide) * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER11 + 4))) +	// 外側曲線(位置+半径*sinf(分割数*番目))
						1293 + 245 * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER11 + 4)));									// 内側曲線(位置+半径*sinf(分割数*番目))
				}
				else if (nDepth >= START_NUMBER12 && nDepth <= FINISH_NUMBER12)
				{// 縦の列ブロックが規定範囲内のとき
					// ジャンプ台までの長い直線
					// 頂点座標の設定
					m_pVtx[0].pos.x = -197 + WhileX * nWide;											// X座標
					m_pVtx[0].pos.y = 184 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;	// Y座標
					m_pVtx[0].pos.z = 5660 + -WhileZ * nDepth;											// Z座標
				}
			}
			else
			{
				///////////////////////////////////////////////ナミナミ///////////////////////////////////////////////
				// 頂点座標の設定
				m_pVtx[0].pos = D3DXVECTOR3((-WhileX * m_nWidth) / 2 + WhileX * nWide,				// X座標
					(sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY / 2,					// Y座標
					(WhileZ / 2 * m_nDepth) - WhileZ * nDepth);										// Z座標
			}

			// 頂点カラー
			m_pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, FIELD_ALPHA);

			// 頂点情報加算
			m_pVtx++;
		}
	}

	// 頂点データをアンロック
	m_pVtxBuff->Unlock();

	// 頂点データの範囲をロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	//////////////////////////////法線ベクトル//////////////////////////////
	// 縦をカウント
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// 横をカウント
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// インデックス番号
			int nIdx = nDepth * (m_nWidth + 1) + nWide;

			// 端は計算させない
			if (nWide != m_nWidth && nDepth != m_nDepth)
			{
				m_vectorA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;								// 一つ目のベクトル
				m_vectorB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;							// 二つ目のベクトル
				m_vectorC = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;								// 三つ目のベクトル
				D3DXVec3Cross(&m_aVecA[m_nNumber], &m_vectorA, &m_vectorB);									// 二つのベクトルの直交ベクトル
				D3DXVec3Normalize(&m_aVecA[m_nNumber], &m_aVecA[m_nNumber]);								// 正規化する
				D3DXVec3Cross(&m_aVecB[m_nNumber], &m_vectorB, &m_vectorC);									// 二つのベクトルの直交ベクトル
				D3DXVec3Normalize(&m_aVecB[m_nNumber], &m_aVecB[m_nNumber]);								// 正規化する

				// 配列の番号1プラスする
				m_nStartBox++;
				m_nEndBox++;
				m_nNumber++;
			}

			// 右上だったとき
			if (nIdx == m_nWidth)
			{
				// 法線ベクトル
				m_pVtx[nIdx].nor = m_aVecB[m_nWidth - 1];
			}
			else if (nIdx == m_nDepth * (m_nWidth + 1))
			{// 左下だったとき
				// 法線ベクトル
				m_pVtx[nIdx].nor = m_aVecA[(m_nDepth - 1) * m_nWidth];
			}
			else if (nIdx == 0)
			{// 左上だったとき
				// 法線ベクトル
				m_pVtx[nIdx].nor = (m_aVecA[nIdx] + m_aVecB[nIdx]) / 2;
			}
			else if (nIdx == (m_nDepth + 1) * (m_nWidth + 1) - 1)
			{// 右下だったとき
				// 法線ベクトル
				m_pVtx[nIdx].nor = (m_aVecA[m_nDepth * m_nWidth - 1] + m_aVecB[m_nDepth * m_nWidth - 1]) / 2;
			}
			else if (nWide != 0 && nWide != m_nWidth)
			{// 横の列が端じゃないとき
				// 縦が一列目だったとき
				if (nDepth == 0)
				{
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecB[nWide - 1] + m_aVecA[nWide] + m_aVecB[nWide]) / 3;
				}
				else if (nDepth == m_nDepth)
				{// 縦が最後尾だったとき
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecB[(m_nDepth - 1) * m_nWidth - 1 + nWide] +
						m_aVecA[(m_nDepth - 1) * m_nWidth + nWide] +
						m_aVecB[(m_nDepth - 1) * m_nWidth + nWide]) / 3;
				}
				else
				{// それ以外
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1]) / 6;
				}
			}
			else if (nDepth != 0 && nDepth != m_nDepth)
			{// 縦の列が端じゃないとき
				 // 先頭のとき
				if (nWide == 0)
				{
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecA[(nDepth - 1) * m_nWidth] +
						m_aVecA[m_nWidth + (nDepth - 1) * m_nWidth] +
						m_aVecB[m_nWidth + (nDepth - 1) * m_nWidth]) / 3;
				}
				else if (nWide == m_nWidth)
				{// 最後尾のとき
					// 法線ベクトル
					m_pVtx[nIdx].nor = (m_aVecB[(m_nWidth - 1) + m_nWidth * nDepth] +
						m_aVecA[(m_nWidth - 1) + m_nWidth * nDepth] +
						m_aVecB[m_nWidth - 1 + m_nWidth * nDepth]) / 3;
				}
			}
		}
		// 配列の番号を1プラスする
		m_nStartBox++;
		m_nEndBox++;
	}

	// 頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// 描画処理
//==================================================================================================================
void CMeshField::Draw(void)
{
	// レンダラー情報取得
	CRenderer *pRenderer = CManager::GetRenderer();			// レンダラーの情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;							// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

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

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);
}

//==================================================================================================================
// 位置設定
//==================================================================================================================
void CMeshField::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// ポリゴン生成
//==================================================================================================================
CMeshField *CMeshField::Create(void)
{
	// メモリを動的に確保
	m_pMeshField = new CMeshField(CScene::PRIORITY_FIELD);

	// メッシュ球があるとき
	if (m_pMeshField != NULL)
	{
		// シーン初期化
		m_pMeshField->Init();
	}

	// 値を返す
	return m_pMeshField;
}

//==================================================================================================================
// テクスチャ情報ロード
//==================================================================================================================
HRESULT CMeshField::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();						// レンダラーの情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();					// デバイスを取得する

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		FIELD_TEXTUE,							// ファイルの名前
		&m_pTexture);							// 読み込むメモリー

	// 値を返す
	return S_OK;
}

//==================================================================================================================
// テクスチャ情報破棄
//==================================================================================================================
void CMeshField::Unload(void)
{
	// テクスチャ情報があるとき
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();			// テクスチャ情報の開放
		m_pTexture = NULL;				// NULLにする
	}
}

//==================================================================================================================
// メッシュフィールド情報取得
//==================================================================================================================
CMeshField * CMeshField::GetMeshField(void)
{
	return m_pMeshField;
}

//==================================================================================================================
// 位置取得
//==================================================================================================================
D3DXVECTOR3 CMeshField::GetPos(void)
{
	return m_pos;
}

//==================================================================================================================
// 移動量取得
//==================================================================================================================
D3DXVECTOR3 CMeshField::GetMove(void)
{
	return m_move;
}

//==================================================================================================================
// 高さ算出用関数
//==================================================================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 playerPos;			// プレイヤーの位置
	int nNumPlace = 0;				// リスポーン場所
	float Height = 0.0f;			// 高さ計算用変数
	bool bRange = false;			// 範囲にいるかどうか

	// タイトルのとき
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{
		// プレイヤーの情報取得
		m_pPlayer = CTitle::GetPlayer();
	}

	// チュートリアルのとき
	if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		// プレイヤーの情報取得
		m_pPlayer = CTutorial::GetPlayer();
	}

	// ゲームのとき
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// プレイヤーの情報取得
		m_pPlayer = CGame::GetPlayer();

		// リスポーン場所取得
		nNumPlace = m_pPlayer->GetnNumPlace();

		// プレイヤーの位置取得
		playerPos = m_pPlayer->GetPos();
	}

	// 頂点データの範囲をロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// ゲームのとき
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// リスポーン場所が0 又は 1のとき
		if (nNumPlace == 0 || nNumPlace == 1)
		{
			// 再初期化
			m_nNumber = (START_NUMBER2 - 1) * m_nWidth;							// 配列の番号
			m_nStartBox = (START_NUMBER2)* m_nWidth + START_NUMBER2;			// 始まる箱
			m_nEndBox = (START_NUMBER2 - 1) * m_nWidth + (START_NUMBER2 - 1);	// 引かれる箱

			// 直交ベクトル用変数
			D3DXVECTOR3 norB = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norA = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norC = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norD = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norE = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norF = D3DXVECTOR3(0, 0, 0);

			// 縦をカウント
			for (int nDepth = 44; nDepth < FINISH_NUMBER3 + 1; nDepth++)
			{
				// 横をカウント
				for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
				{
					// 範囲外にいるとき
					if (!bRange)
					{
						// 頂点が端じゃないとき端は計算させない
						if (nWide != m_nWidth && nDepth != m_nDepth)
						{
							// 全てのベクトルを出す
							D3DXVECTOR3 vecA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecC = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vecD = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecE = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox + 1].pos;

							// 引数のposから頂点までをベクトルにする
							D3DXVECTOR3 vec0 = pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vec1 = pos - m_pVtx[m_nEndBox + 1].pos;
							D3DXVECTOR3 vec2 = pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vec3 = pos - m_pVtx[m_nStartBox + 1].pos;

							//////直交ベクトル算出//////
							// 一つ目の三角形
							D3DXVec3Cross(&norA, &vecA, &vec0);					// 直交ベクトル算出
							D3DXVec3Cross(&norB, &vec0, &vecB);					// 直交ベクトル算出
							D3DXVec3Cross(&norC, &vecC, &vec2);					// 直交ベクトル算出

							// 二つ目の三角形
							D3DXVec3Cross(&norD, &vecB, &vec0);					// 直交ベクトル算出
							D3DXVec3Cross(&norE, &vec0, &vecD);					// 直交ベクトル算出
							D3DXVec3Cross(&norF, &vec1, &vecE);					// 直交ベクトル算出

							// 法線が面の表より上だったとき
							if (m_aVecA[m_nNumber] >= 0)
							{
								// 三角形の中にいるとき
								if (norA.y <= 0 && norB.y <= 0 && norC.y <= 0)
								{
									// メッシュフィールドの中にいる
									bRange = true;

									// 引数のposが頂点と同じであるとき
									if (pos == m_pVtx[m_nStartBox].pos)
									{
										// 別な頂点を使って高さを算出
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nStartBox + 1].pos.y + (-m_aVecA[m_nNumber].x * vec3.x - m_aVecA[m_nNumber].z * vec3.z) / m_aVecA[m_nNumber].y;
									}
									else
									{
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nStartBox].pos.y + (-m_aVecA[m_nNumber].x * vec2.x - m_aVecA[m_nNumber].z * vec2.z) / m_aVecA[m_nNumber].y;
									}
								}
							}

							// 法線が面の表より上だったとき
							if (m_aVecB[m_nNumber] >= 0)
							{
								// 三角形の中にいるとき
								if (norD.y <= 0 && norE.y <= 0 && norF.y <= 0)
								{
									// メッシュフィールドの中にいる
									bRange = true;

									// 引数のposが頂点と同じであるとき
									if (pos == m_pVtx[m_nEndBox + 1].pos)
									{
										// 別な頂点を使って高さを算出
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nEndBox].pos.y + (-m_aVecB[m_nNumber].x * (vec0.x) - m_aVecB[m_nNumber].z * (vec0.z)) / m_aVecB[m_nNumber].y;
									}
									else
									{
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nEndBox + 1].pos.y + (-m_aVecB[m_nNumber].x * (vec1.x) - m_aVecB[m_nNumber].z * (vec1.z)) / m_aVecB[m_nNumber].y;
									}
								}
							}

							// 配列の番号1プラスする
							m_nStartBox++;
							m_nEndBox++;
							m_nNumber++;
						}
					}
				}

				// 横終わったら配列の番号を1プラスする
				m_nStartBox++;
				m_nEndBox++;
			}
		}
		else if (playerPos.y > CALCULATION_POS_Y)
		{// リスポーン場所が規定値のとき
			// 再初期化
			m_nNumber = (START_NUMBER5 - 1) * m_nWidth;							// 配列の番号
			m_nStartBox = (START_NUMBER5) * m_nWidth + START_NUMBER5;			// 始まる箱
			m_nEndBox = (START_NUMBER5 - 1) * m_nWidth + (START_NUMBER5 - 1);	// 引かれる箱

			// 直交ベクトル用変数
			D3DXVECTOR3 norB = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norA = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norC = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norD = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norE = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norF = D3DXVECTOR3(0, 0, 0);

			// 縦をカウント
			for (int nDepth = 199; nDepth < FINISH_NUMBER12 + 1; nDepth++)
			{
				// 横をカウント
				for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
				{
					// 範囲外にいるとき
					if (!bRange)
					{
						// 頂点が端じゃないとき端は計算させない
						if (nWide != m_nWidth && nDepth != m_nDepth)
						{
							// 全てのベクトルを出す
							D3DXVECTOR3 vecA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecC = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vecD = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecE = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox + 1].pos;

							// 引数のposから頂点までをベクトルにする
							D3DXVECTOR3 vec0 = pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vec1 = pos - m_pVtx[m_nEndBox + 1].pos;
							D3DXVECTOR3 vec2 = pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vec3 = pos - m_pVtx[m_nStartBox + 1].pos;

							//////直交ベクトル算出//////
							// 一つ目の三角形
							D3DXVec3Cross(&norA, &vecA, &vec0);					// 直交ベクトル算出
							D3DXVec3Cross(&norB, &vec0, &vecB);					// 直交ベクトル算出
							D3DXVec3Cross(&norC, &vecC, &vec2);					// 直交ベクトル算出

							// 二つ目の三角形
							D3DXVec3Cross(&norD, &vecB, &vec0);					// 直交ベクトル算出
							D3DXVec3Cross(&norE, &vec0, &vecD);					// 直交ベクトル算出
							D3DXVec3Cross(&norF, &vec1, &vecE);					// 直交ベクトル算出

							// 法線が面の表より上だったとき
							if (m_aVecA[m_nNumber] >= 0)
							{
								// 三角形の中にいるとき
								if (norA.y <= 0 && norB.y <= 0 && norC.y <= 0)
								{
									// メッシュフィールドの中にいる
									bRange = true;

									// 引数のposが頂点と同じであるとき
									if (pos == m_pVtx[m_nStartBox].pos)
									{
										// 別な頂点を使って高さを算出
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nStartBox + 1].pos.y + (-m_aVecA[m_nNumber].x * vec3.x - m_aVecA[m_nNumber].z * vec3.z) / m_aVecA[m_nNumber].y;
									}
									else
									{
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nStartBox].pos.y + (-m_aVecA[m_nNumber].x * vec2.x - m_aVecA[m_nNumber].z * vec2.z) / m_aVecA[m_nNumber].y;
									}
								}
							}

							// 法線が面の表より上だったとき
							if (m_aVecB[m_nNumber] >= 0)
							{
								// 三角形の中にいるとき
								if (norD.y <= 0 && norE.y <= 0 && norF.y <= 0)
								{
									// メッシュフィールドの中にいる
									bRange = true;

									// 引数のposが頂点と同じであるとき
									if (pos == m_pVtx[m_nEndBox + 1].pos)
									{
										// 別な頂点を使って高さを算出
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nEndBox].pos.y + (-m_aVecB[m_nNumber].x * (vec0.x) - m_aVecB[m_nNumber].z * (vec0.z)) / m_aVecB[m_nNumber].y;
									}
									else
									{
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nEndBox + 1].pos.y + (-m_aVecB[m_nNumber].x * (vec1.x) - m_aVecB[m_nNumber].z * (vec1.z)) / m_aVecB[m_nNumber].y;
									}
								}
							}

							// 配列の番号1プラスする
							m_nStartBox++;
							m_nEndBox++;
							m_nNumber++;
						}
					}
				}

				// 横終わったら配列の番号を1プラスする
				m_nStartBox++;
				m_nEndBox++;
			}
		}
		else
		{// それ以外
			// 再初期化
			m_nNumber = 0;										// 配列の番号
			m_nStartBox = m_nWidth + 1;							// 始まる箱
			m_nEndBox = 0;										// 引かれる箱

			// 直交ベクトル用変数
			D3DXVECTOR3 norA = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norB = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norC = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norD = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norE = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norF = D3DXVECTOR3(0, 0, 0);

			// 縦をカウント
			for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
			{
				// 横をカウント
				for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
				{
					// 範囲外にいるとき
					if (!bRange)
					{
						// 頂点が端じゃないとき端は計算させない
						if (nWide != m_nWidth && nDepth != m_nDepth)
						{
							// 全てのベクトルを出す
							D3DXVECTOR3 vecA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecC = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vecD = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecE = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox + 1].pos;

							// 引数のposから頂点までをベクトルにする
							D3DXVECTOR3 vec0 = pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vec1 = pos - m_pVtx[m_nEndBox + 1].pos;
							D3DXVECTOR3 vec2 = pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vec3 = pos - m_pVtx[m_nStartBox + 1].pos;

							//////直交ベクトル算出//////
							// 一つ目の三角形
							D3DXVec3Cross(&norA, &vecA, &vec0);					// 直交ベクトル算出
							D3DXVec3Cross(&norB, &vec0, &vecB);					// 直交ベクトル算出
							D3DXVec3Cross(&norC, &vecC, &vec2);					// 直交ベクトル算出

							// 二つ目の三角形
							D3DXVec3Cross(&norD, &vecB, &vec0);					// 直交ベクトル算出
							D3DXVec3Cross(&norE, &vec0, &vecD);					// 直交ベクトル算出
							D3DXVec3Cross(&norF, &vec1, &vecE);					// 直交ベクトル算出

							// 法線が面の表より上だったとき
							if (m_aVecA[m_nNumber] >= 0)
							{
								// 三角形の中にいるとき
								if (norA.y <= 0 && norB.y <= 0 && norC.y <= 0)
								{
									// メッシュフィールドの中にいる
									bRange = true;

									// 引数のposが頂点と同じであるとき
									if (pos == m_pVtx[m_nStartBox].pos)
									{
										// 別な頂点を使って高さを算出
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nStartBox + 1].pos.y + (-m_aVecA[m_nNumber].x * vec3.x - m_aVecA[m_nNumber].z * vec3.z) / m_aVecA[m_nNumber].y;
									}
									else
									{
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nStartBox].pos.y + (-m_aVecA[m_nNumber].x * vec2.x - m_aVecA[m_nNumber].z * vec2.z) / m_aVecA[m_nNumber].y;
									}
								}
							}

							// 法線が面の表より上だったとき
							if (m_aVecB[m_nNumber] >= 0)
							{
								// 三角形の中にいるとき
								if (norD.y <= 0 && norE.y <= 0 && norF.y <= 0)
								{
									// メッシュフィールドの中にいる
									bRange = true;

									// 引数のposが頂点と同じであるとき
									if (pos == m_pVtx[m_nEndBox + 1].pos)
									{
										// 別な頂点を使って高さを算出
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nEndBox].pos.y + (-m_aVecB[m_nNumber].x * (vec0.x) - m_aVecB[m_nNumber].z * (vec0.z)) / m_aVecB[m_nNumber].y;
									}
									else
									{
										// 指定された位置での高さを算出
										Height = m_pVtx[m_nEndBox + 1].pos.y + (-m_aVecB[m_nNumber].x * (vec1.x) - m_aVecB[m_nNumber].z * (vec1.z)) / m_aVecB[m_nNumber].y;
									}
								}
							}

							// 配列の番号1プラスする
							m_nStartBox++;
							m_nEndBox++;
							m_nNumber++;
						}
					}
				}
				// 横終わったら配列の番号を1プラスする
				m_nStartBox++;
				m_nEndBox++;
			}
		}
	}
	else
	{// タイトル 又は チュートリアルのとき
		// 再初期化
		m_nNumber = 0;										// 配列の番号
		m_nStartBox = m_nWidth + 1;							// 始まる箱
		m_nEndBox = 0;										// 引かれる箱

		// 縦をカウント
		for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
		{
			// 横をカウント
			for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
			{
				// 範囲外にいるとき
				if (!bRange)
				{
					// 頂点が端じゃないとき端は計算させない
					if (nWide != m_nWidth && nDepth != m_nDepth)
					{
						// 全てのベクトルを出す
						D3DXVECTOR3 vecA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;
						D3DXVECTOR3 vecB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;
						D3DXVECTOR3 vecC = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nStartBox].pos;
						D3DXVECTOR3 vecD = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;
						D3DXVECTOR3 vecE = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox + 1].pos;

						// 引数のposから頂点までをベクトルにする
						D3DXVECTOR3 vec0 = pos - m_pVtx[m_nEndBox].pos;
						D3DXVECTOR3 vec1 = pos - m_pVtx[m_nEndBox + 1].pos;
						D3DXVECTOR3 vec2 = pos - m_pVtx[m_nStartBox].pos;
						D3DXVECTOR3 vec3 = pos - m_pVtx[m_nStartBox + 1].pos;

						// 直交ベクトル用変数
						D3DXVECTOR3 norB = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norA = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norC = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norD = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norE = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norF = D3DXVECTOR3(0, 0, 0);

						//////直交ベクトル算出//////
						// 一つ目の三角形
						D3DXVec3Cross(&norA, &vecA, &vec0);					// 直交ベクトル算出
						D3DXVec3Cross(&norB, &vec0, &vecB);					// 直交ベクトル算出
						D3DXVec3Cross(&norC, &vecC, &vec2);					// 直交ベクトル算出

						// 二つ目の三角形
						D3DXVec3Cross(&norD, &vecB, &vec0);					// 直交ベクトル算出
						D3DXVec3Cross(&norE, &vec0, &vecD);					// 直交ベクトル算出
						D3DXVec3Cross(&norF, &vec1, &vecE);					// 直交ベクトル算出

						// 法線が面の表より上だったとき
						if (m_aVecA[m_nNumber] >= 0)
						{
							// 三角形の中にいるとき
							if (norA.y <= 0 && norB.y <= 0 && norC.y <= 0)
							{
								// メッシュフィールドの中にいる
								bRange = true;

								// 引数のposが頂点と同じであるとき
								if (pos == m_pVtx[m_nStartBox].pos)
								{
									// 別な頂点を使って高さを算出
									// 指定された位置での高さを算出
									Height = m_pVtx[m_nStartBox + 1].pos.y + (-m_aVecA[m_nNumber].x * vec3.x - m_aVecA[m_nNumber].z * vec3.z) / m_aVecA[m_nNumber].y;
								}
								else
								{
									// 指定された位置での高さを算出
									Height = m_pVtx[m_nStartBox].pos.y + (-m_aVecA[m_nNumber].x * vec2.x - m_aVecA[m_nNumber].z * vec2.z) / m_aVecA[m_nNumber].y;
								}
							}
						}

						// 法線が面の表より上だったとき
						if (m_aVecB[m_nNumber] >= 0)
						{
							// 三角形の中にいるとき
							if (norD.y <= 0 && norE.y <= 0 && norF.y <= 0)
							{
								// メッシュフィールドの中にいる
								bRange = true;

								// 引数のposが頂点と同じであるとき
								if (pos == m_pVtx[m_nEndBox + 1].pos)
								{
									// 別な頂点を使って高さを算出
									// 指定された位置での高さを算出
									Height = m_pVtx[m_nEndBox].pos.y + (-m_aVecB[m_nNumber].x * (vec0.x) - m_aVecB[m_nNumber].z * (vec0.z)) / m_aVecB[m_nNumber].y;
								}
								else
								{
									// 指定された位置での高さを算出
									Height = m_pVtx[m_nEndBox + 1].pos.y + (-m_aVecB[m_nNumber].x * (vec1.x) - m_aVecB[m_nNumber].z * (vec1.z)) / m_aVecB[m_nNumber].y;
								}
							}
						}

						// 配列の番号1プラスする
						m_nStartBox++;
						m_nEndBox++;
						m_nNumber++;
					}
				}
			}
			// 横終わったら配列の番号を1プラスする
			m_nStartBox++;
			m_nEndBox++;
		}
	}

	// 頂点データをアンロック
	m_pVtxBuff->Unlock();

	// プレイヤーの範囲内状況設定
	m_pPlayer->SetbRange(bRange);

	return Height;
}

//==================================================================================================================
// 移動量設定
//==================================================================================================================
void CMeshField::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}