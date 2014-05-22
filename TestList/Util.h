#pragma once
class Util
{
public:
	Util(void);
	~Util(void);
};

class CMyImageList
{
public:
	CMyImageList();

	int  GetImage(int type);
	CImageList* GetMyImageList();

protected:
	CImageList m_ImageList;
};