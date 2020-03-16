//==================================================================================================================
//
// �����L���O����[rankingNum.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "rankingNum.h"
#include "renderer.h"
#include "number.h"
#include "time.h"
#include "record.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define NUMBER_WIDTH 20.0f						// 2�����̐����̕�

//==================================================================================================================
// �ÓI�����o�[�ϐ��̏�����
//==================================================================================================================
CRankingNum *CRankingNum::m_pRankingNum;		// �����L���O�̐���

//==================================================================================================================
//
// �R���X�g���N�^
//
//==================================================================================================================
CRankingNum::CRankingNum(PRIORITY type = CScene::PRIORITY_UI) : CScene(type)
{
}

//==================================================================================================================
//
// �f�X�g���N�^
//
//==================================================================================================================
CRankingNum::~CRankingNum()
{

}

//==================================================================================================================
// �����L���O�����̏�����
//==================================================================================================================
void CRankingNum::Init(void)
{
	// �Q�[���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// �ő包���܂ŃJ�E���g
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// �����̐���
			m_apNumber[0][nCnt] = CNumber::CreateObject();

			// 0����1���ڂ̂Ƃ�
			if (nCnt == 0 || nCnt == 1)
			{
				// �ʒu�ݒ�
				m_apNumber[0][nCnt]->SetPos(D3DXVECTOR3(TIME_POS_X + TIME_INTERVAL_X * nCnt,			// �ʒuX
					TOPNUM_POS_Y,																		// �ʒuY
					0.0f),																				// �ʒuZ
					NUMBER_SIZE_X, NUMBER_SIZE_Y);														// �傫��
			}
			// �������ڂ̂Ƃ�
			else if (nCnt % 2 == 0)
			{
				// �ʒu�ݒ�
				m_apNumber[0][nCnt]->SetPos(D3DXVECTOR3(TIME_POS_X + TIME_INTERVAL_X * nCnt + TIME_WIDTH * nCnt / 2,	// �ʒuX
					TOPNUM_POS_Y,																						// �ʒuY
					0.0f),																								// �ʒuZ
					NUMBER_SIZE_X, NUMBER_SIZE_Y);																		// �傫��
			}
			// ����ڂ̂Ƃ�
			else
			{
				// �ʒu�ݒ�
				m_apNumber[0][nCnt]->SetPos(D3DXVECTOR3(TIME_POS_X + TIME_INTERVAL_X * nCnt + TIME_WIDTH * ((nCnt - 1) / 2),// �ʒuX
					TOPNUM_POS_Y,																							// �ʒuY
					0.0f),																									// �ʒuZ
					NUMBER_SIZE_X, NUMBER_SIZE_Y);																			// �傫��
			}
		}
	}
	// �����L���O�̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_RANKING)
	{
		// �ő叇�ʂ܂ŃJ�E���g
		for (int nCntScore = 0; nCntScore < RANK_NUM; nCntScore++)
		{
			// �ő包���܂ŃJ�E���g
			for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
			{
				// �����̐���
				m_apNumber[nCntScore][nCnt] = CNumber::CreateObject();

				// 0����1���ڂ̂Ƃ�
				if (nCnt == 0 || nCnt == 1)
				{
					// �ʒu�ݒ�
					m_apNumber[nCntScore][nCnt]->SetPos(D3DXVECTOR3(NUM_POS_X + NUM_INTERVAL_X * nCnt,		// �ʒuX
						NUM_POS_Y + NUM_INTERVAL_Y * nCntScore,												// �ʒuY
						0.0f),																				// �ʒuZ
						NUM_SIZE_X, NUM_SIZE_Y);															// �傫��
				}
				// �������ڂ̂Ƃ�
				else if (nCnt % 2 == 0)
				{
					// �ʒu�ݒ�
					m_apNumber[nCntScore][nCnt]->SetPos(D3DXVECTOR3(NUM_POS_X + NUM_INTERVAL_X * nCnt + NUMBER_WIDTH * nCnt / 2,// �ʒuX
						NUM_POS_Y + NUM_INTERVAL_Y * nCntScore,																	// �ʒuY
						0.0f),																									// �ʒuZ
						NUM_SIZE_X, NUM_SIZE_Y);																				// �傫��
				}
				// ����ڂ̂Ƃ�
				else
				{
					// �ʒu�ݒ�
					m_apNumber[nCntScore][nCnt]->SetPos(D3DXVECTOR3(NUM_POS_X + NUM_INTERVAL_X * nCnt + NUMBER_WIDTH * ((nCnt - 1) / 2),// �ʒuX
						NUM_POS_Y + NUM_INTERVAL_Y * nCntScore,																			// �ʒuY
						0.0f),																											// �ʒuZ
						NUM_SIZE_X, NUM_SIZE_Y);																						// �傫��
				}
			}
		}
	}
}

//==================================================================================================================
// �����L���O�����̏I��
//==================================================================================================================
void CRankingNum::Uninit(void)
{
	// �ő叇�ʂ܂ŃJ�E���g
	for (int nCntScore = 0; nCntScore < RANK_NUM; nCntScore++)
	{
		// �ő包���܂ŃJ�E���g
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// ����������Ƃ�
			if (m_apNumber[nCntScore][nCnt] != NULL)
			{
				// �����̏I������
				m_apNumber[nCntScore][nCnt]->Uninit();

				// �������폜
				delete m_apNumber[nCntScore][nCnt];

				// �|�C���^�pNULL
				m_apNumber[nCntScore][nCnt] = nullptr;
			}
		}
	}
}

//==================================================================================================================
// �����L���O�����̍X�V
//==================================================================================================================
void CRankingNum::Update(void)
{
	// �ő叇�ʂ܂ŃJ�E���g
	for (int nCntScore = 0; nCntScore < RANK_NUM; nCntScore++)
	{
		// �ő包���܂ŃJ�E���g
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// ����������Ƃ�
			if (m_apNumber[nCntScore][nCnt] != NULL)
			{
				// �����̍X�V����
				m_apNumber[nCntScore][nCnt]->Update();
			}
		}
	}
}

//==================================================================================================================
// �����L���O�����̕`��
//==================================================================================================================
void CRankingNum::Draw(void)
{
	// �ő叇�ʂ܂ŃJ�E���g	
	for (int nCntScore = 0; nCntScore < RANK_NUM; nCntScore++)
	{
		// �ő包���܂ŃJ�E���g
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// ����������Ƃ�
			if (m_apNumber[nCntScore][nCnt] != NULL)
			{
				// �����̕`�揈��
				m_apNumber[nCntScore][nCnt]->Draw();
			}
		}
	}
}

//==================================================================================================================
// �����L���O�����̐���
//==================================================================================================================
CRankingNum *CRankingNum::Create(void)
{
	// �V�[�����I�Ɋm��
	m_pRankingNum = new CRankingNum(CScene::PRIORITY_UI);

	// �����L���O�����̏�����
	m_pRankingNum->Init();

	// �l��Ԃ�
	return m_pRankingNum;
}

//==================================================================================================================
// �����L���O�����ݒ�
//==================================================================================================================
void CRankingNum::AddRankingNum(void)
{
	int nCount;						// �z��p�J�E���^
	int nNumber;					// �\�����ׂ�����������

	// �Q�[���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// �e�L�X�g�f�[�^�̃��[�h
		m_nRanking[0] = *CRecord::GetLoad(0);

		// �ő包���܂ŃJ�E���g
		for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
		{
			// �\�����ׂ��������Ȃɂ��J�E���g
			nNumber = m_nRanking[0] % (int)powf((float)TIME_INTERVAL, (float)MAX_TIME - nCnt) /			// X��Y��
				(int)powf((float)TIME_INTERVAL, (float)MAX_TIME - 1.0f - nCnt);							// X��Y��

			// �ԍ��ݒ�
			m_apNumber[0][nCnt]->SetNumber(nNumber);
		}
	}
	// �����L���O�̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_RANKING)
	{
		// �ő叇�ʂ܂ŃJ�E���g
		for (nCount = 0; nCount < RANK_NUM; nCount++)
		{
			// �e�L�X�g�f�[�^�̃��[�h
			m_nRanking[nCount] = *CRecord::GetLoad(nCount);

			// �ő包���܂ŃJ�E���g
			for (int nCnt = 0; nCnt < RANK_SCORE; nCnt++)
			{
				// �\�����ׂ��������Ȃɂ��J�E���g
				nNumber = m_nRanking[nCount] % (int)powf((float)TIME_INTERVAL, (float)MAX_TIME - nCnt) /	// X��Y��
					(int)powf((float)TIME_INTERVAL, (float)MAX_TIME - 1.0f - nCnt);							// X��Y��

				// �ԍ��ݒ�
				m_apNumber[nCount][nCnt]->SetNumber(nNumber);
			}
		}
	}
}

//==================================================================================================================
// �����L���O�������擾
//==================================================================================================================
CRankingNum *CRankingNum::GetRank(void)
{
	return m_pRankingNum;
}

//==================================================================================================================
// �����L���O�������擾
//==================================================================================================================
void CRankingNum::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}