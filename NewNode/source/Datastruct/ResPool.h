// ResPool.h: interface for the CResPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESPOOL_H__315D473E_A0BE_4D86_A917_9FF513A1F3AC__INCLUDED_)
#define AFX_RESPOOL_H__315D473E_A0BE_4D86_A917_9FF513A1F3AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "STD.h"

template <class _Tx, int MAX_NUM>
class CResPool  
{
public:
	CResPool()
	{
		m_iNum		= 0;
		m_iMaxNum	= MAX_NUM;
	}

	virtual ~CResPool()
	{
		this->ReleasePool();
	}

public:
	//�ͷ����ӳ�
	void ReleasePool()
	{
		MMutexGuarder guarder(m_CritConn);
		
		for (int i = 0; i < m_iNum; i++)
		{
			STD::Free(m_ResStack[i]);
		}
		m_iNum	= 0;
		
	}

	//��ȡ��Դ����
	int	GetNum()
	{
		MMutexGuarder guarder(m_CritConn);
		
		return m_iNum;
	}
	//����һ������
	_Tx* GetRes()
	{
		MMutexGuarder guarder(m_CritConn);

		if (m_iNum > 0)
		{
			m_iNum--;
			_Tx *p = m_ResStack[m_iNum];


			return p;
		}

		guarder.UnLock();

		//û�����ӣ����贴��һ��������
		_Tx* p	= new _Tx();
		if (p)
		{
			if (!p->Create())
			{
				STD::Free(p);
			}
		}

		return p;
	}


	//����һ�����ӣ����ڶ���
	bool PutRes(_Tx *  pconn)
	{
		if (pconn == NULL)
		{
			return false;
		}
		MMutexGuarder guarder(m_CritConn);
		if (m_iNum < m_iMaxNum)
		{
			m_ResStack[m_iNum]	= pconn;
			m_iNum++;
			
			return true;
		}
		else	//����
		{
			guarder.UnLock();

			delete pconn;
			return false;
		}
	}

	bool ReleaseRes(_Tx * pconn)
	{
		if (pconn == NULL)
		{
			return false;
		}
		delete pconn;

		return true;
	}

private:

	_Tx*				m_ResStack[MAX_NUM];
	int					m_iMaxNum;
	int					m_iNum;

	MCriticalSection	m_CritConn;
};

#endif // !defined(AFX_RESPOOL_H__315D473E_A0BE_4D86_A917_9FF513A1F3AC__INCLUDED_)
