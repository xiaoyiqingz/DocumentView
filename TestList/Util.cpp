#include "StdAfx.h"
#include "Util.h"
#include "resource.h"

Util::Util(void)
{
}


Util::~Util(void)
{
}


CMyImageList::CMyImageList()
{
	m_ImageList.Create(32,32, ILC_COLOR32 |ILC_MASK , 5, 1);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_DEVICE_TYPE_ANDROID));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_DEVICE_TYPE_WINDOWS));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_DEVICE_TYPE_IOS));
}

int CMyImageList::GetImage(int type)
{
	switch (type)
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 2;
	}
}

CImageList* CMyImageList::GetMyImageList()
{
	return &m_ImageList;
}

