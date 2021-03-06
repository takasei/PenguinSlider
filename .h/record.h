//==================================================================================================================
//
// レコード[record.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _RECORD_H_
#define _RECORD_H_

//==================================================================================================================
// インクルードファイル
//==================================================================================================================
#include "main.h"

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define SAVE_DATA (5)							// セーブするデータの個数
#define LOAD_DATA (5)							// ロードするデータの個数
#define SAVE_FILE_NAME "data/TEXT/Ranking.txt"	// 読み込むテキストデータのソース先

//==================================================================================================================
//
// レコードクラスの定義
//
//==================================================================================================================
class CRecord
{
public:
	CRecord();									// コンストラクタ
	~CRecord();									// デストラクタ
	void InitSave(void);						// 初期化処理
	void InitLoad(void);						// 初期化処理
	void LoadData(void);						// ロード処理
	void SaveData(int nPoint);					// セーブ処理

	static int *GetSave(void);					// セーブ情報取得
	static int *GetLoad(int nLoad);				// ロード情報取得

protected:

private:
	static int m_nSavePoint[SAVE_DATA];			// セーブ情報
	static int m_nLoadPoint[LOAD_DATA];			// ロード情報
};
#endif