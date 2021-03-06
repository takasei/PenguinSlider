//==================================================================================================================
//
// ランキング記録[record.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "record.h"

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define INIT_NUMBER 100000				// 初期化の数字

//==================================================================================================================
// 静的メンバー変数の初期化
//==================================================================================================================
int CRecord::m_nSavePoint[SAVE_DATA] = {};					// セーブ情報
int CRecord::m_nLoadPoint[SAVE_DATA] = {};					// ロード情報

//==================================================================================================================
//
// コンストラクタ
//
//==================================================================================================================
CRecord::CRecord()
{

}

//==================================================================================================================
//
// デストラクタ
//
//==================================================================================================================
CRecord::~CRecord()
{

}

//==================================================================================================================
// セーブの初期化
//==================================================================================================================
void CRecord::InitSave(void)
{
	// 最大データまでカウント
	for (int nCntSave = 0; nCntSave < SAVE_DATA; nCntSave++)
	{
		// 初期化
		m_nSavePoint[nCntSave] = INIT_NUMBER;					// セーブ情報
	}
}

//==================================================================================================================
// ロードの初期化
//==================================================================================================================
void CRecord::InitLoad(void)
{
	// 最大データまでカウント
	for (int nCntLoad = 0; nCntLoad < LOAD_DATA; nCntLoad++)
	{
		// 初期化
		m_nLoadPoint[nCntLoad] = INIT_NUMBER;					// ロード情報
	}

	// データのロード
	LoadData();
}

//==================================================================================================================
// データのロード
//==================================================================================================================
void CRecord::LoadData(void)
{
	// ファイルポイント
	FILE *pFile;

	// ファイル開
	pFile = fopen(SAVE_FILE_NAME, "r");

	// 開けた
	if (pFile != NULL)
	{
		// 最大データまでカウント
		for (int nCntLoad = 0; nCntLoad < LOAD_DATA; nCntLoad++)
		{
			// 読み取り
			fscanf(pFile, "%d", &m_nLoadPoint[nCntLoad]); // 名前
		}
		// ファイル閉
		fclose(pFile);
	}
	// 開けない
	else
	{
		printf("開けれませんでした\n");
	}
}

//==================================================================================================================
// データのセーブ
//==================================================================================================================
void CRecord::SaveData(int nPoint)
{
	FILE *pFile;																	// ファイルポイント
	int nData;																		// 格納用変数
	int nCntSave;																	// データ用カウンタ
	int nCntNum;																	// 現在のデータのカウンタ

	// 最大データまでカウント
	for (nCntSave = 0; nCntSave < SAVE_DATA; nCntSave++)
	{
		// ロード情報をセーブ情報に代入
		m_nSavePoint[nCntSave] = m_nLoadPoint[nCntSave];
	}

	// 配列の最後にスコアを代入
	m_nSavePoint[5] = nPoint;

	// 小さい順に並べる処理
	for (nCntSave = 0; nCntSave < SAVE_DATA + 1; nCntSave++)
	{
		for (nCntNum = nCntSave + 1; nCntNum < SAVE_DATA + 1; nCntNum++)
		{
			// 現在のスコアのほうが小さいとき
			if (m_nSavePoint[nCntSave] > m_nSavePoint[nCntNum])
			{
				nData = m_nSavePoint[nCntNum];										// いったん格納
				m_nSavePoint[nCntNum] = m_nSavePoint[nCntSave];						// 置き換え
				m_nSavePoint[nCntSave] = nData;										// 置き換え
			}
		}
	}

	// ファイル開
	pFile = fopen(SAVE_FILE_NAME, "w");

	// 開けた
	if (pFile != NULL)
	{
		// 最大データまでカウント
		for (nCntSave = 0; nCntSave < SAVE_DATA; nCntSave++)
		{
			// 読み取り
			fprintf(pFile, "%d\n\n", m_nSavePoint[nCntSave]);	// ポイント
		}
		// ファイル閉
		fclose(pFile);
	}

	// 開けない
	else
	{
		printf("開けれませんでした\n");
	}
}

//==================================================================================================================
// セーブの取得
//==================================================================================================================
int *CRecord::GetSave(void)
{
	return &m_nSavePoint[0];
}

//==================================================================================================================
// ロードの取得
//==================================================================================================================
int *CRecord::GetLoad(int nLoad)
{
	return &m_nLoadPoint[nLoad];
}