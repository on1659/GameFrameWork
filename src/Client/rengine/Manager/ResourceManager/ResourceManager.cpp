
#include "PreComplie.h"
#include "ResourceManager.h"

#pragma warning(disable: 4244)

Image::Image()
{

}

Image::Image(tstring filePath)
{
	LoadCImage(filePath);
}

Image::~Image()
{
	//delete m_image;
}


WARP_RESULT_ENUM Image::Init(tstring filePath)
{
	return LoadCImage(filePath);
}

WARP_RESULT_ENUM Image::LoadCImage(tstring filePath)
{
	m_image = new CImage();
	HRESULT result = m_image->Load(filePath.c_str());
	if (result == S_OK)
	{
		m_Width = m_image->GetWidth();
		m_Height = m_image->GetHeight();
	}
	else
	{
		MessageBox(NULL, filePath.c_str(), L"경로가 잘못되었습니다.", 0);
		//GlobalVar::GetInstance()->ErrorMessage(filePath, "경로가 잘못되었습니다");
		return WARP_RESULT_ENUM::NOT_FOUND_RESOURCE;
	}

	return WARP_RESULT_ENUM::OK;
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	Release();
}

WARP_RESULT_ENUM ResourceManager::AddImage(tstring filePath, tstring name)
 {
	auto pFindImg = FindImage(name);

	if (pFindImg != NULL)
	{
		return WARP_RESULT_ENUM::NOT_FOUND_RESOURCE;
	}
	else
	{
		std::vector<Image> vecImage;
		Image img;
		WARP_RESULT_ENUM result = img.LoadCImage(filePath.c_str());
 		if (result != WARP_RESULT_ENUM::OK)
			return result;

		vecImage.push_back(img);
		m_ImageMap.insert(std::make_pair(name, vecImage));

	}
	return WARP_RESULT_ENUM::OK;

}

std::vector<Image>* ResourceManager::FindImage(tstring name)
{
	std::map<tstring, std::vector<Image>>::iterator iter = m_ImageMap.find(name);

	if (iter == m_ImageMap.end())
		return nullptr;
	else
		return &iter->second;
}

WARP_RESULT_ENUM ResourceManager::LoadCImage()
{
	//AddImage(_XTT("Resource/WarpLogo.png"), _XTT("로고"));
	//AddImage(_XTT("Resource/BtnSave.png"),  _XTT("Start"));
	//AddImage(_XTT("Resource/BtnPlay.png"),  _XTT("Load"));
	//AddImage(_XTT("Resource/BtnHelp.png"),  _XTT("Help"));
	//AddImage(_XTT("Resource/BtnExit.png"), _XTT("Exit"));
	//AddImage(_XTT("Resource/help.png"), _XTT("HelpImg"));

	return WARP_RESULT_ENUM::OK;
}


void ResourceManager::DrawImageSpriteAlphaBackground(HDC hdc, tstring name, const float left, const float top, const float width, const float height, const float s_left, const float s_top, const float s_width, const float s_height, COLORREF removeColor, int alpha)
{
	HDC LayDC;
	HBITMAP Lay;
	BLENDFUNCTION bf;

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	Lay = CreateCompatibleBitmap(hdc, (int)width, (int)height);
	LayDC = CreateCompatibleDC(hdc);
	SelectObject(LayDC, Lay);
	TransparentBlt(LayDC, 0, 0, (int)width, (int)height, hdc, s_left, s_top, s_width, s_left, removeColor);

	std::vector<Image>* image = FindImage(name);

	if (image)
		image->begin()->GetCimage()->TransparentBlt(hdc, left, top, width, height,
		s_left, s_top, s_width, s_height, removeColor);

	AlphaBlend(hdc, (int)left, (int)top, (int)width, (int)height, LayDC, 0, 0, (int)width, (int)height, bf);

	//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);

	DeleteDC(LayDC);
	DeleteObject(Lay);
}

void ResourceManager::Render(HDC hdc, tstring name, const float left, const float top, const float width, const float height, const float s_left, const float s_top, const float s_width, const float s_height, COLORREF removeColor)
{
	std::vector<Image>* image = FindImage(name);

	if (image)
	{
		image->begin()->GetCimage()->TransparentBlt(hdc, (int)left, (int)top, (int)width, (int)height, (int)s_left, (int)s_top, (int)s_width, (int)s_height, removeColor);

	}
}

Image* ResourceManager::GetImage(tstring name)
{
	return FindImage(name)->begin()->GetImage();
}

WARP_RESULT_ENUM ResourceManager::Release()
{
	m_ImageMap.clear();
	return WARP_RESULT_ENUM::OK;
}


