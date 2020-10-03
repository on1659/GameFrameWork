#pragma once

// Copyright ⓒ http://radar92.tistory.com 
// 무단 전재 및 재배포 금지
// 코드 사용 시 on1659@naver.com로 연락하시길 바랍니다.

enum eNumImage
{
	IMAGE_TEST,
	IMAGE_BOOM,
	IMAGE_END,
};

class Image
{
private:
	CImage*					m_image;
	int						m_Width;
	int						m_Height;

public:
	Image();
	Image(tstring filePath);
	~Image();

	WARP_RESULT_ENUM Init(tstring filePath);

	WARP_RESULT_ENUM LoadCImage(tstring filePath);

	int GetWidth(){ return m_Width; }

	int GetHeight(){ return m_Height; }

	CImage* GetCimage(){ return m_image; }

	Image* GetImage(){ return this; }

};

class ResourceManager : public CSingleTonBase<ResourceManager>
{

private:
	std::map<tstring, std::vector<Image>> m_ImageMap;

public:

	WARP_RESULT_ENUM LoadCImage();

	WARP_RESULT_ENUM Release();

	WARP_RESULT_ENUM AddImage(tstring filePath, tstring name);

	void Render(HDC hdc, tstring name, const float left, const float top, const float width, const float height, const float s_left, const float s_top, const float s_width, const float s_height, COLORREF removeColor);

	void DrawImageSpriteAlphaBackground(HDC hdc, tstring name, const float left, const float top, const float width, const float height, const float s_left, const float s_top, const float s_width, const float s_height, COLORREF removeColor, int alpha);

	Image* GetImage(tstring name);

	std::vector<Image>*	 FindImage(tstring name);

public:
	ResourceManager();

	~ResourceManager();

};

