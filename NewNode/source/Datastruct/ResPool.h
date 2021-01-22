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
	//释放连接池
	void ReleasePool()
	{
		MMutexGuarder guarder(m_CritConn);
		
		for (int i = 0; i < m_iNum; i++)
		{
			STD::Free(m_ResStack[i]);
		}
		m_iNum	= 0;
		
	}

	//获取资源个数
	int	GetNum()
	{
		MMutexGuarder guarder(m_CritConn);
		
		return m_iNum;
	}
	//返回一个连接
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

		//没有连接，则需创建一个新连接
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


	//增加一个连接，加在顶部
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
		else	//满了
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
