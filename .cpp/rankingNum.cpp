//==================================================================================================================
//
// ランキング数字[rankingNum.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "rankingNum.h"
#include "renderer.h"
#include "number.h"
#include "time.h"
#include "record.h"

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define NUMBER_WIDTH 20.0f						// 2桁分の数字の幅

//==================================================================================================================
// 静的メンバー変数の初期化
//==================================================================================================================
CRankingNum *CRankingNum::m_pRankingNum;		// ランキングの数字

//==================================================================================================================
//
// コンストラクタ
//
//==================================================================================================================
CRankingNum::CRankingNum(PRIORITY type = CScene::PRIORITY_UI) : CScene(type)
{
}

//==================================================================================================================
//
// デストラクタ
//
//==================================================================================================================
CRankingNum::~CRankingNum()
{

}

//==================================================================================================================
// ランキング数字の初期化
//==================================================================================================================
void CRankingNum::Init(void)
{
	// ゲームのとき
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// 最大桁数までカウント
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// 数字の生成
			m_apNumber[0][nCnt] = CNumber::CreateObject();

			// 0桁目1桁目のとき
			if (nCnt == 0 || nCnt == 1)
			{
				// 位置設定
				m_apNumber[0][nCnt]->SetPos(D3DXVECTOR3(TIME_POS_X + TIME_INTERVAL_X * nCnt,			// 位置X
					TOPNUM_POS_Y,																		// 位置Y
					0.0f),																				// 位置Z
					NUMBER_SIZE_X, NUMBER_SIZE_Y);														// 大きさ
			}
			// 偶数桁目のとき
			else if (nCnt % 2 == 0)
			{
				// 位置設定
				m_apNumber[0][nCnt]->SetPos(D3DXVECTOR3(TIME_POS_X + TIME_INTERVAL_X * nCnt + TIME_WIDTH * nCnt / 2,	// 位置X
					TOPNUM_POS_Y,																						// 位置Y
					0.0f),																								// 位置Z
					NUMBER_SIZE_X, NUMBER_SIZE_Y);																		// 大きさ
			}
			// 奇数桁目のとき
			else
			{
				// 位置設定
				m_apNumber[0][nCnt]->SetPos(D3DXVECTOR3(TIME_POS_X + TIME_INTERVAL_X * nCnt + TIME_WIDTH * ((nCnt - 1) / 2),// 位置X
					TOPNUM_POS_Y,																							// 位置Y
					0.0f),																									// 位置Z
					NUMBER_SIZE_X, NUMBER_SIZE_Y);																			// 大きさ
			}
		}
	}
	// ランキングのとき
	if (CRenderer::GetMode() == CRenderer::MODE_RANKING)
	{
		// 最大順位までカウント
		for (int nCntScore = 0; nCntScore < RANK_NUM; nCntScore++)
		{
			// 最大桁数までカウント
			for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
			{
				// 数字の生成
				m_apNumber[nCntScore][nCnt] = CNumber::CreateObject();

				// 0桁目1桁目のとき
				if (nCnt == 0 || nCnt == 1)
				{
					// 位置設定
					m_apNumber[nCntScore][nCnt]->SetPos(D3DXVECTOR3(NUM_POS_X + NUM_INTERVAL_X * nCnt,		// 位置X
						NUM_POS_Y + NUM_INTERVAL_Y * nCntScore,												// 位置Y
						0.0f),																				// 位置Z
						NUM_SIZE_X, NUM_SIZE_Y);															// 大きさ
				}
				// 偶数桁目のとき
				else if (nCnt % 2 == 0)
				{
					// 位置設定
					m_apNumber[nCntScore][nCnt]->SetPos(D3DXVECTOR3(NUM_POS_X + NUM_INTERVAL_X * nCnt + NUMBER_WIDTH * nCnt / 2,// 位置X
						NUM_POS_Y + NUM_INTERVAL_Y * nCntScore,																	// 位置Y
						0.0f),																									// 位置Z
						NUM_SIZE_X, NUM_SIZE_Y);																				// 大きさ
				}
				// 奇数桁目のとき
				else
				{
					// 位置設定
					m_apNumber[nCntScore][nCnt]->SetPos(D3DXVECTOR3(NUM_POS_X + NUM_INTERVAL_X * nCnt + NUMBER_WIDTH * ((nCnt - 1) / 2),// 位置X
						NUM_POS_Y + NUM_INTERVAL_Y * nCntScore,																			// 位置Y
						0.0f),																											// 位置Z
						NUM_SIZE_X, NUM_SIZE_Y);																						// 大きさ
				}
			}
		}
	}
}

//==================================================================================================================
// ランキング数字の終了
//==================================================================================================================
void CRankingNum::Uninit(void)
{
	// 最大順位までカウント
	for (int nCntScore = 0; nCntScore < RANK_NUM; nCntScore++)
	{
		// 最大桁数までカウント
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// 数字があるとき
			if (m_apNumber[nCntScore][nCnt] != NULL)
			{
				// 数字の終了処理
				m_apNumber[nCntScore][nCnt]->Uninit();

				// メモリ削除
				delete m_apNumber[nCntScore][nCnt];

				// ポインタ用NULL
				m_apNumber[nCntScore][nCnt] = nullptr;
			}
		}
	}
}

//==================================================================================================================
// ランキング数字の更新
//==================================================================================================================
void CRankingNum::Update(void)
{
	// 最大順位までカウント
	for (int nCntScore = 0; nCntScore < RANK_NUM; nCntScore++)
	{
		// 最大桁数までカウント
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// 数字があるとき
			if (m_apNumber[nCntScore][nCnt] != NULL)
			{
				// 数字の更新処理
				m_apNumber[nCntScore][nCnt]->Update();
			}
		}
	}
}

//==================================================================================================================
// ランキング数字の描画
//==================================================================================================================
void CRankingNum::Draw(void)
{
	// 最大順位までカウント	
	for (int nCntScore = 0; nCntScore < RANK_NUM; nCntScore++)
	{
		// 最大桁数までカウント
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// 数字があるとき
			if (m_apNumber[nCntScore][nCnt] != NULL)
			{
				// 数字の描画処理
				m_apNumber[nCntScore][nCnt]->Draw();
			}
		}
	}
}

//==================================================================================================================
// ランキング数字の生成
//==================================================================================================================
CRankingNum *CRankingNum::Create(void)
{
	// シーン動的に確保
	m_pRankingNum = new CRankingNum(CScene::PRIORITY_UI);

	// ランキング数字の初期化
	m_pRankingNum->Init();

	// 値を返す
	return m_pRankingNum;
}

//==================================================================================================================
// ランキング数字設定
//==================================================================================================================
void CRankingNum::AddRankingNum(void)
{
	int nCount;						// 配列用カウンタ
	int nNumber;					// 表示すべき数字が何か

	// ゲームのとき
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// テキストデータのロード
		m_nRanking[0] = *CRecord::GetLoad(0);

		// 最大桁数までカウント
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// 表示すべき数字がなにかカウント
			nNumber = m_nRanking[0] % (int)powf((float)TIME_INTERVAL, (float)MAX_TIME - nCnt) /			// XのY乗
				(int)powf((float)TIME_INTERVAL, (float)MAX_TIME - 1.0f - nCnt);							// XのY乗

			// 番号設定
			m_apNumber[0][nCnt]->SetNumber(nNumber);
		}
	}
	// ランキングのとき
	if (CRenderer::GetMode() == CRenderer::MODE_RANKING)
	{
		// 最大順位までカウント
		for (nCount = 0; nCount < RANK_NUM; nCount++)
		{
			// テキストデータのロード
			m_nRanking[nCount] = *CRecord::GetLoad(nCount);

			// 最大桁数までカウント
			for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
			{
				// 表示すべき数字がなにかカウント
				nNumber = m_nRanking[nCount] % (int)powf((float)TIME_INTERVAL, (float)MAX_TIME - nCnt) /	// XのY乗
					(int)powf((float)TIME_INTERVAL, (float)MAX_TIME - 1.0f - nCnt);							// XのY乗

				// 番号設定
				m_apNumber[nCount][nCnt]->SetNumber(nNumber);
			}
		}
	}
}

//==================================================================================================================
// ランキング数字情報取得
//==================================================================================================================
CRankingNum *CRankingNum::GetRank(void)
{
	return m_pRankingNum;
}

//==================================================================================================================
// ランキング数字情報取得
//==================================================================================================================
void CRankingNum::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}