//==================================================================================================================
//
// モデルタイプ別描画[tpy.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "renderer.h"
#include "model.h"
#include "debugProc.h"

//==================================================================================================================
// マクロ定義
//==================================================================================================================
#define COLLISION_SIZE 100.0f								// 当たり判定の大きさ
#define TUTORIAL_COLLISION_SIZE 150.0f						// チュートリアル時の当たり判定の大きさ

//==================================================================================================================
// 静的メンバ変数の初期化
//==================================================================================================================
LPDIRECT3DTEXTURE9 CModel::m_pTex[MODEL_MAX] = {};			// テクスチャ情報
LPD3DXMESH CModel::m_pMesh[MODEL_MAX] = {};					// メッシュ情報
LPD3DXBUFFER CModel::m_pBuffMat[MODEL_MAX] = {};			// バッファ情報
DWORD CModel::m_nNumMat[MODEL_MAX] = {};					// マテリアル情報の数
CModel *CModel::m_pModel[MODEL_MAX] = {};					// モデル情報
char *CModel::m_apFileName[MODEL_MAX] =						// 読み込むモデルのソース先
{
	{ "data/MODEL/GoalCircle2.x" },							// ゴール輪っか
	{ "data/MODEL/arrow.x" },								// リスポーンモデル0
	{ "data/MODEL/arrow.x" },								// リスポーンモデル1
	{ "data/MODEL/arrow.x" },								// リスポーンモデル2
	{ "data/MODEL/arrow.x" },								// リスポーンモデル3
	{ "data/MODEL/arrow.x" },								// リスポーンモデル4
	{ "data/MODEL/arrow.x" },								// リスポーンモデル5
	{ "data/MODEL/arrow.x" },								// リスポーンモデル6
	{ "data/MODEL/arrow.x" },								// リスポーンモデル7
	{ "data/MODEL/arrow.x" },								// リスポーンモデル8
	{ "data/MODEL/arrow.x" },								// リスポーンモデル9
	{ "data/MODEL/arrow.x" },								// リスポーンモデル10
	{ "data/MODEL/arrow.x" },								// リスポーンモデル11
	{ "data/MODEL/arrow.x" },								// リスポーンモデル12
	{ "data/MODEL/foundation.x" },							// 土台モデル0
	{ "data/MODEL/faudationCurve.x" },						// 土台カーブモデル0
	{ "data/MODEL/faudationCurve1.x" },						// 土台カーブモデル1
	{ "data/MODEL/faudationCurve2.x" },						// 土台カーブモデル2
	{ "data/MODEL/faudationCurve3.x" },						// 土台カーブモデル3
	{ "data/MODEL/faudationCurve4.x" },						// 土台カーブモデル4
	{ "data/MODEL/faudationCurve5.x" },						// 土台カーブモデル5
	{ "data/MODEL/pole.x" },								// ポール
	{ "data/MODEL/signboard.x" },							// 看板
};

//==================================================================================================================
// コンストラクタ
//==================================================================================================================
CModel::CModel(PRIORITY type = CScene::PRIORITY_MODEL) :CSceneX(type)
{

}

//==================================================================================================================
// デストラクタ
//==================================================================================================================
CModel::~CModel()
{

}

//==================================================================================================================
// 初期化処理
//==================================================================================================================
void CModel::Init(void)
{
	// sceneXの初期化処理
	CSceneX::Init();

	// 変数の初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 大きさ
	m_RotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ゴールの回転
}

//==================================================================================================================
// 終了処理
//==================================================================================================================
void CModel::Uninit(void)
{
	// sceneXの終了処理
	CSceneX::Uninit();
}

//==================================================================================================================
// 更新処理
//==================================================================================================================
void CModel::Update(void)
{
	// チュートリアルのとき
	if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		m_RotGoal = m_pModel[MODEL_GOAL_CIRCLE]->GetRot();	// ゴール輪っかモデル回転取得

		// 回転加算
		m_RotGoal.z += 0.011f;

		m_pModel[MODEL_GOAL_CIRCLE]->SetRot(m_RotGoal);		// ゴール輪っかモデル回転設定
	}
	else if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{// ゲームのとき
		m_RotGoal = m_pModel[MODEL_GOAL_CIRCLE]->GetRot();	// ゴール輪っかモデル回転取得

		// 回転加算
		m_RotGoal.z += 0.0005f;

		m_pModel[MODEL_GOAL_CIRCLE]->SetRot(m_RotGoal);		// ゴール輪っかモデル回転設定
	}
	m_size = GetSize();									// 大きさ取得
	m_pos = GetPos();									// 位置取得

	SetSize(m_size);									// 大きさ設定
	SetPos(m_pos);										// 位置設定

	// sceneXの更新処理
	CSceneX::Update();
}

//==================================================================================================================
// 描画処理
//==================================================================================================================
void CModel::Draw(void)
{
	// sceneXの描画処理
	CSceneX::Draw();
}

//==================================================================================================================
// 生成処理
//==================================================================================================================
CModel *CModel::Create(MODEL type)
{
	// モデル情報を動的に確保
	m_pModel[type] = new CModel(CScene::PRIORITY_MODEL);

	// モデルがあるとき
	if (m_pModel[type] != NULL)
	{
		m_pModel[type]->Init();																// モデルの初期化
		m_pModel[type]->BindModel(m_pBuffMat[type], m_nNumMat[type], m_pMesh[type]);		// モデルの変数を結合させる
		m_pModel[type]->BindTex(m_pTex[type]);												// テクスチャの変数を結合させる
	}

	// 値を返す
	return m_pModel[type];
}

//==================================================================================================================
// テクスチャとモデルロード
//==================================================================================================================
HRESULT CModel::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();				// レンダラー情報取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();			// デバイスの取得

	// モデルの最大数までカウント
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, "", &m_pTex[nCnt]);

		// Xファイルの読み込み
		D3DXLoadMeshFromX(
			m_apFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCnt],
			NULL,
			&m_nNumMat[nCnt],
			&m_pMesh[nCnt]);
	}

	// 値を返す
	return S_OK;
}

//==================================================================================================================
// テクスチャとモデル破棄
//==================================================================================================================
void CModel::Unload(void)
{
	// モデルの最大種類までカウント
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// テクスチャがあるとき
		if (m_pTex[nCnt] != NULL)
		{
			m_pTex[nCnt]->Release();			// テクスチャ解放
			m_pTex[nCnt] = NULL;				// NULLにする
		}

		// メッシュがあるとき
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();			// メッシュの開放
			m_pMesh[nCnt] = NULL;				// NULLにする
		}

		// バッファがあるとき
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();		// マテリアルの開放
			m_pBuffMat[nCnt] = NULL;			// NULLにする
		}
	}
}

//==================================================================================================================
// 線と点の当たり判定
//==================================================================================================================
bool CModel::CollisionBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 posOld, MODEL model)
{
	// 当たり判定用変数
	bool bHit = false;
	m_pos = m_pModel[model]->GetPos();			// モデルの位置取得

	// モデルの種類によって切り替える
	switch (model)
	{
		// ゴール輪っかのとき
	case MODEL_GOAL_CIRCLE:
		// チュートリアルのとき
		if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
		{
			// モデルの横幅の範囲内にいるとき
			if (m_pos.x - TUTORIAL_COLLISION_SIZE < posOld.x && m_pos.x + TUTORIAL_COLLISION_SIZE > posOld.x)
			{
				// 下からモデルのぶつかった
				if (m_pos.z - 1.0f > posOld.z && m_pos.z - 1.0f <= pos.z)
				{
					// 当たったことにする
					bHit = true;
				}
			}
		}
		else if (CRenderer::GetMode() == CRenderer::MODE_GAME)
		{// ゲームのとき
			// モデルの横幅の範囲内にいるとき
			if (m_pos.z - COLLISION_SIZE < posOld.z && m_pos.z + COLLISION_SIZE > posOld.z)
			{
				// 下からモデルのぶつかった
				if (m_pos.x - 1.0f > posOld.x && m_pos.x - 1.0f <= pos.x)
				{
					// 当たったことにする
					bHit = true;
				}
			}
		}
		break;
	}

	// 値を返す
	return bHit;
}

//==================================================================================================================
// 逆からの線と点の当たり判定
//==================================================================================================================
bool CModel::CollisionBlockReturn(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 posOld, MODEL model)
{
	// 当たり判定用変数
	bool bHit = false;
	m_pos = m_pModel[model]->GetPos();			// モデルの位置取得

	// モデルの種類によって切り替える
	switch (model)
	{
		// ゴール輪っかのとき
	case MODEL_GOAL_CIRCLE:
		// ゲームのとき
		if (CRenderer::GetMode() == CRenderer::MODE_GAME)
		{
			// モデルの横幅の範囲内にいるとき
			if (m_pos.z - COLLISION_SIZE < posOld.z && m_pos.z + COLLISION_SIZE > posOld.z)
			{
				// 下からモデルのぶつかった
				if (m_pos.x + 1.0f < posOld.x && m_pos.x + 1.0f >= pos.x)
				{
					// 当たったことにする
					bHit = true;
				}
			}
		}
		break;
	}

	// 値を返す
	return bHit;
}

//==================================================================================================================
// 球と球の当たり判定
//==================================================================================================================
bool CModel::CollisionSphere(D3DXVECTOR3 pos2, float radius1, float radius2, MODEL model)
{
	// 当たり判定用変数
	bool bHit = false;

	// モデルの位置取得
	m_pos = m_pModel[model]->GetPos();

	// それぞれの軸の差を求める
	float XDistance = m_pos.x - pos2.x;
	float YDistance = m_pos.y - pos2.y;
	float ZDistance = m_pos.z - pos2.z;
	float fRadius = radius1 + radius2;

	// 球と球がぶつかったとき
	if (XDistance * XDistance + YDistance * YDistance + ZDistance * ZDistance <= fRadius * fRadius)
	{
		// 当たったことにする
		bHit = true;
	}

	// 値を返す
	return bHit;
}

