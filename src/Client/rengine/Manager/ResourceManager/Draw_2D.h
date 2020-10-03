#pragma once


#include <windows.h>
#include "task/MyDefine.h"
#include "task/MyUsing.h"

enum RColor
{
	RED						= RGB(255, 0, 0)
	, BLUE					= RGB(0, 0, 255)
	, GREEN					= RGB(0, 255, 0)	
	, BLACK					= RGB(0, 0, 0)
	, ORANGE				= RGB(230, 130, 5)
	, CYAN					= RGB(0, 255, 255)
	, MAGENTA				= RGB(255, 0, 255)
	, YELLOW				= RGB(255, 255, 0)



	, BRIGHT_RED_1			= RGB(238, 20, 45)
	, BRIGHT_RED_2			= RGB(229, 52, 165)
	, BRIGHT_RED_3			= RGB(231, 15, 62)
	, BRIGHT_RED_4			= RGB(246, 122, 218)
	, BRIGHT_RED_5			= RGB(238, 5, 33)
	, BRIGHT_RED_6			= RGB(243, 58, 60)
	  
	, BRIGHT_YELLOW_1		= RGB(235, 249,81)
	, BRIGHT_YELLOW_2		= RGB(244,229,109)
	, BRIGHT_YELLOW_3		= RGB(244, 213, 28)
	, BRIGHT_YELLOW_4		= RGB(253, 218, 76)
	, BRIGHT_YELLOW_5		= RGB(228,234,92)
	, BRIGHT_YELLOW_6		= RGB(234,228,106)

	, BRIGHT_ORANGE_1		= RGB(241, 132, 18)
	, BRIGHT_ORANGE_2		= RGB(244, 129, 83)

	, BRIGHT_GREEN_1		= RGB(115, 225, 121)
	, BRIGHT_GREEN_2		= RGB(102, 250, 82)
	, BRIGHT_GREEN_3		= RGB(177,244,83)
	, BRIGHT_GREEN_4		= RGB(117, 226, 153)
	, BRIGHT_GREEN_5		= RGB(7, 226, 129)
	, BRIGHT_GREEN_6		= RGB(111,226,120)
	, BRIGHT_GREEN_7		= RGB(90,254,108)
	, BRIGHT_GREEN_8		= RGB(111, 226, 120)
	, BRIGHT_GREEN_9		= RGB(163, 255, 118)
							  
	, BRIGHT_BLUE_1			= RGB(11, 201, 216)
	, BRIGHT_BLUE_2			= RGB(77, 94, 209)
	, BRIGHT_BLUE_3			= RGB(30, 168, 194)
	, BRIGHT_BLUE_4			= RGB(84, 216, 177)
	
					
	,BROWN_GROUND			= RGB(202, 97, 37)

	//보라색이문제가있네

	, WHITE					= RGB(255, 255, 255)
	, BRUSH					= RGB(248, 248, 248)
	, BRUSH2				= RGB(240, 240, 240)
	, BRIGHT_BLACK			= RGB(130, 130, 130)
};

class Draw_2D
{

public:
	Draw_2D(){ return; }
	~Draw_2D(){ return; }


	void static drawText(HDC hdc, TCHAR* msg, int x, int y, uint32 color){
		TCHAR* message = { NULL };
		
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, color);
		TextOut(hdc, x, y, msg, sizeof(msg));
	}

	void static drawText(HDC hdc, float data, int x, int y, uint32 color){
		
		TCHAR *message = new TCHAR(sizeof(data));// NULL;
		SetTextColor(hdc, color);
		SetBkMode(hdc, TRANSPARENT);
		wsprintf(message, L"%d", (int)data);
		TextOut(hdc, x, y, message, sizeof(message));
	}

	void static drawText(HDC hdc, int x, int y, uint32 color, TCHAR* msg, ...)
	{
		va_list arg;
		va_start(arg, msg);
		TCHAR buf[500] = { NULL };
		vswprintf_s(buf, sizeof(msg), msg, arg);
		int count = 0;
		for (int i = 0; buf[i] != NULL; ++i)
			count++;
		
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, color);
		TextOut(hdc, x, y, (TCHAR*)buf, count);
		va_end(arg);
	}	
	
	void static drawText(HDC hdc, TCHAR _message[], int data, int x, int y, uint32 color, int size, TCHAR _font[]){
		TCHAR message[80];
		
		HFONT hFont, OldFont;
		
		SetTextColor(hdc, color);
		hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, (_font));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		wsprintf(message, L"%s %d", _message, data);
		TextOut(hdc, x, y, message, (int)wcslen(message));
		DeleteObject(hFont);
		DeleteObject(OldFont);
	}

	void static drawText(HDC hdc, int x, int y, uint32 color, int size, TCHAR _font[], TCHAR *_message, ...)
	{
		HFONT hFont, OldFont;
		
		SetTextColor(hdc, color);
		hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, (_font));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);



		va_list arg;
		va_start(arg, _message);
		TCHAR buf[500] = { NULL };
		vswprintf_s(buf, sizeof(_message), _message, arg);
		int count = 0;
		for (int i = 0; buf[i] != NULL; ++i)
			count++;
		TextOut(hdc, x, y, buf, count);

		DeleteObject(hFont);
		DeleteObject(OldFont);
		va_end(arg);

	}

	void static drawText(HDC hdc, int x, int y, uint32 color, int size, TCHAR *_message, ...)
	{
		SetTextColor(hdc, color);
		SetBkMode(hdc, TRANSPARENT);

		va_list arg;
		va_start(arg, _message);
		TCHAR buf[500] = { NULL };
		vswprintf_s(buf, sizeof(_message), _message, arg);
		int count = 0;
		for (int i = 0; buf[i] != NULL; ++i)
			count++;
		TextOut(hdc, x, y, buf, count);

		va_end(arg);

	}


	/*
	void static drawText(HDC hdc, std::string _message, int data, int x, int y, uint32 color){
	char* message[80];
	
	
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);
	wsprintf(message, "%s %d", _message, data);
	TextOutA(hdc, x, y, message, wcslen(message));
	}

	void static drawText(HDC hdc, int data, int x, int y, uint32 color){
	
	TCHAR message[80];
	
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT);
	wsprintfW(message, L"%d", data);
	TextOut(hdc, x, y, message, wcslen(message));

	}

	void static drawText(HDC hdc, float data, int x, int y, uint32 color){
	
	TCHAR message[80];
	
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT);
	wsprintfW(message, L"%d", data);
	TextOut(hdc, x, y, message, wcslen(message));
	}

	*/

	
	void static drawText(HDC hdc, TCHAR message[], int x, int y, uint32 color, int size, TCHAR _font[]){
	
	HFONT hFont, OldFont;
	
	SetTextColor(hdc, color);
	hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, (_font));
	OldFont = (HFONT)SelectObject(hdc, hFont);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);
	TextOut(hdc, x, y, message, (int)wcslen(message));
	DeleteObject(hFont);
	DeleteObject(OldFont);
	}




	

	/*
	void static drawText(HDC hdc, char _message[], int data, int x, int y, uint32 color, int size, TCHAR _font[]){
	TCHAR message[80];
	
	
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT);
	wsprintf(message, L"%s %d", _message, data);
	TextOut(hdc, x, y, message, wcslen(message));

	}

	void static drawText(HDC hdc, char _message[], float data, int x, int y, uint32 color){
	TCHAR message[80];
	
	
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT);
	wsprintf(message, L"%c %1.0f", _message, data);
	TextOut(hdc, x, y, message, wcslen(message));
	}
	*/

	void static drawLine(HDC hdc, int start_x, int start_y, int end_x, int end_y, uint32 color){
		
		
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 3, color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		MoveToEx(hdc, start_x, start_y, NULL);
		LineTo(hdc, end_x, end_y);
		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);

	}

	void static drawLine(HDC hdc, int start_x, int start_y, int end_x, int end_y){
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		MoveToEx(hdc, start_x, start_y, NULL);
		LineTo(hdc, end_x, end_y);
		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);

	}

	void static drawLine(HDC hdc, int start_x, int start_y, int end_x, int end_y, int Linesize, uint32 color){
		
		
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, Linesize, color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		MoveToEx(hdc, start_x, start_y, NULL);
		LineTo(hdc, end_x, end_y);
		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
	}




	///DrawRect
	void static drawRect(HDC hdc, float _l, float _t, float _w, float _h, uint32 color, bool type)
	{
		int l = (int)_l;
		int t = (int)_t;
		int w = (int)_w;
		int h = (int)_h;


		
		
		HBRUSH hBrush, oldBrush;
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		if (type)
			Rectangle(hdc, l, t, l + w, t + h);

		else
		{
			MoveToEx(hdc, l, t, NULL);
			LineTo(hdc, l + w, t);

			MoveToEx(hdc, l + w, t, NULL);
			LineTo(hdc, l + w, t + h);


			MoveToEx(hdc, l + w, t + h, NULL);
			LineTo(hdc, l, t + h);


			MoveToEx(hdc, l, t + h, NULL);
			LineTo(hdc, l, t);

		}

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	//Draw_2D
	void static drawRect(HDC hdc, float _l, float _t, float _w, float _h, uint32 color, uint32 penColor, int penSize, bool type){
		int l = (int)_l;
		int t = (int)_t;
		int w = (int)_w;
		int h = (int)_h;

		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, penSize, penColor);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		if (type == false){


			MoveToEx(hdc, l, t, NULL);
			LineTo(hdc, l + w, t);

			MoveToEx(hdc, l + w, t, NULL);
			LineTo(hdc, l + w, t + h);


			MoveToEx(hdc, l + w, t + h, NULL);
			LineTo(hdc, l, t + h);


			MoveToEx(hdc, l, t + h, NULL);
			LineTo(hdc, l, t);
		}
		else{
			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Rectangle(hdc, l, t, l + w, t + h);

			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);
		}

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	void static drawRect(HDC hdc, int x, int y, int size, uint32 color){
		
		

		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 3, color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x + size, y);

		MoveToEx(hdc, x + size, y, NULL);
		LineTo(hdc, x + size, y + size);


		MoveToEx(hdc, x + size, y + size, NULL);
		LineTo(hdc, x, y + size);


		MoveToEx(hdc, x, y + size, NULL);
		LineTo(hdc, x, y);

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, x, y, x + size, y + size);
	}

	void static drawRect(HDC hdc, int x, int y, int sizeX, int sizeY, uint32 color){
		
		
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 1, color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x + sizeX, y);

		MoveToEx(hdc, x + sizeX, y, NULL);
		LineTo(hdc, x + sizeX, y + sizeY);

		MoveToEx(hdc, x + sizeX, y + sizeY, NULL);
		LineTo(hdc, x, y + sizeY);

		MoveToEx(hdc, x, y + sizeY, NULL);
		LineTo(hdc, x, y);

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	void static drawRect(HDC hdc, int x, int y, int sizeX, int sizeY, uint32 color, bool type){
		
		
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 3, color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		if (type == false){
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x + sizeX, y);

			MoveToEx(hdc, x + sizeX, y, NULL);
			LineTo(hdc, x + sizeX, y + sizeY);

			MoveToEx(hdc, x + sizeX, y + sizeY, NULL);
			LineTo(hdc, x, y + sizeY);

			MoveToEx(hdc, x, y + sizeY, NULL);
			LineTo(hdc, x, y);
		}
		else{
			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, x, y, x + sizeX, y + sizeY);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);
		}

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	void static drawRect(HDC hdc, int x, int y, int sizeX, int sizeY, uint32 color, uint32 penColor, bool type)	{

		HPEN MyPen, OldPen;

		MyPen = CreatePen(PS_SOLID, 1, penColor);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		if (type == false){
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x + sizeX, y);

			MoveToEx(hdc, x + sizeX, y, NULL);
			LineTo(hdc, x + sizeX, y + sizeY);

			MoveToEx(hdc, x + sizeX, y + sizeY, NULL);
			LineTo(hdc, x, y + sizeY);

			MoveToEx(hdc, x, y + sizeY, NULL);
			LineTo(hdc, x, y);
		}
		else
		{
			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, x, y, x + sizeX, y + sizeY);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);
		}

		SelectObject(hdc, OldPen);

		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	void static drawRect(HDC hdc, float _l, float _t, float _w, float _h, uint32 color, uint32 penColor, bool type = false)	{
		int l = (int)_l;
		int t = (int)_t;
		int w = (int)_w;
		int h = (int)_h;

		HPEN MyPen, OldPen;
	
		MyPen = CreatePen(PS_SOLID, 1, penColor);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		if (type == false)
		{

			MoveToEx(hdc, (int)l, (int)t, NULL);
			LineTo(hdc, (int)(l + w), (int)t);

			MoveToEx(hdc, (int)(l + w), (int)t, NULL);
			LineTo(hdc, (int)(l + w), (int)(t + h));


			MoveToEx(hdc, (int)(l + w), (int)(t + h), NULL);
			LineTo(hdc, (int)l, (int)(t + h));


			MoveToEx(hdc, (int)l, (int)(t + h), NULL);
			LineTo(hdc, (int)l, (int)t);
		}
		else{
			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Rectangle(hdc, (int)l, (int)t, (int)(l + w), (int)(t + h));

			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);
		}

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}



	void static drawProgrees(HDC hdc, int persent, float _l, float _t, float _w, float _h, uint32 color, uint32 penColor)
	{
		float per = _w * (float)persent * 0.01f;
		if (per > _w)per = _w;
		Draw_2D::drawRect(hdc, _l, _t, _w, _h, WHITE, penColor, true);
		Draw_2D::drawRect(hdc, _l, _t, per, _h, color, penColor, true);
	}
	
	void static drawRectRound(HDC hdc, float _l, float _t, float _w, float _h, uint32 color, uint32 penColor, int round){
		int l = (int)_l;
		int t = (int)_t;
		int w = (int)_w;
		int h = (int)_h;

		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 1, penColor);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		HBRUSH hBrush, oldBrush;
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		RoundRect(hdc, (int)l, (int)t, (int)(l + w), (int)(t + h), round, round);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	void static drawRectRoundAlpha(HDC hdc, float _l, float _t, float _w, float _h, uint32 color, uint32 penColor, int alpha, int round){
		int l = (int)_l;
		int t = (int)_t;
		int w = (int)_w;
		int h = (int)_h;

		HDC LayDC;
		HBITMAP Lay;
		BLENDFUNCTION bf;

		HPEN MyPen, OldPen;
		HBRUSH hBrush, oldBrush;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = alpha;

		Lay = CreateCompatibleBitmap(hdc, (int)w, (int)h);
		LayDC = CreateCompatibleDC(hdc);
		SelectObject(LayDC, Lay);
		BitBlt(LayDC, 0, 0, (int)w, (int)h, hdc, (int)l, (int)t, SRCCOPY);

		MyPen = CreatePen(PS_SOLID, 1, penColor);
		OldPen = (HPEN)SelectObject(LayDC, MyPen);

		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(LayDC, hBrush);

		RoundRect(LayDC, 0, 0, (int)w, (int)h, round, round);
		SelectObject(LayDC, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);

		SelectObject(LayDC, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);

		AlphaBlend(hdc, (int)l, (int)t, (int)w, (int)h, LayDC, 0, 0, (int)w, (int)h, bf);


		DeleteDC(LayDC);
		DeleteObject(Lay);


		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	//

	void static drawCicle(HDC hdc, int cx, int cy, int size, uint32 color, uint32 penColor, int Linesize){
		HBRUSH hBrush, oldBrush;
		HPEN hPen, oldPen;
		
		hPen = CreatePen(PS_DOT, Linesize, penColor);
		oldPen = (HPEN)SelectObject(hdc, hPen);
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, cx - size / 2, cy - size / 2, cx + size / 2, cy + size / 2);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);
		DeleteObject(hPen);
		DeleteObject(oldPen);
	}

	void static drawCicle(HDC hdc, int start_x, int start_y, int end_x, int end_y, uint32 color){
		HBRUSH hBrush, oldBrush;
		
		
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, start_x, start_y, end_x, end_y);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);
	}

	void static drawCicle(HDC hdc, float _l, float _t, float _w, float _h, uint32 color, uint32 penColor, int Linesize){
		int l = (int)_l;
		int t = (int)_t;
		int w = (int)_w;
		int h = (int)_h;

		HBRUSH hBrush, oldBrush;
		HPEN hPen, oldPen;
		
		hPen = CreatePen(PS_DOT, Linesize, penColor);
		oldPen = (HPEN)SelectObject(hdc, hPen);
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, (int)l, (int)t, (int)(l + w), (int)(t + h));
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);
		DeleteObject(hPen);
		DeleteObject(oldPen);
	}

	void static drawCircleAlpha(HDC hdc, float _l, float _t, float _w, float _h, uint32 color, uint32 penColor, int alpha){
		int l = (int)_l;
		int t = (int)_t;
		int w = (int)_w;
		int h = (int)_h;

		HDC LayDC;
		HBITMAP Lay;
		BLENDFUNCTION bf;

		HPEN MyPen, OldPen;
		HBRUSH hBrush, oldBrush;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = alpha;

		Lay = CreateCompatibleBitmap(hdc, (int)w, (int)h);
		LayDC = CreateCompatibleDC(hdc);
		SelectObject(LayDC, Lay);
		BitBlt(LayDC, 0, 0, (int)w, (int)h, hdc, (int)l, (int)t, SRCCOPY);

		MyPen = CreatePen(PS_SOLID, 1, penColor);
		OldPen = (HPEN)SelectObject(LayDC, MyPen);

		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(LayDC, hBrush);

		Ellipse(LayDC, 0, 0, (int)w, (int)h);
		SelectObject(LayDC, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);

		SelectObject(LayDC, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);

		AlphaBlend(hdc, (int)l, (int)t, (int)w, (int)h, LayDC, 0, 0, (int)w, (int)h, bf);


		DeleteDC(LayDC);
		DeleteObject(Lay);


		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}


	//DrawTrangle

	void static drawPentagon(HDC hdc, int cx, int cy, int w, int h, uint32 color){
		HPEN MyPen, OldPen;
		
		

		MyPen = CreatePen(PS_SOLID, 3, color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		MoveToEx(hdc, cx, cy - h, NULL);
		LineTo(hdc, cx + w, cy);

		MoveToEx(hdc, cx + w, cy, NULL);
		LineTo(hdc, cx + w, cy + h);

		MoveToEx(hdc, cx + w, cy + h, NULL);
		LineTo(hdc, cx - w, cy + h);

		MoveToEx(hdc, cx - w, cy + h, NULL);
		LineTo(hdc, cx - w, cy);

		MoveToEx(hdc, cx - w, cy, NULL);
		LineTo(hdc, cx, cy - h);

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
	}



	void static ytRand_rgb_bri(uint32 color[])
	{
		int imsi = 1;// (rand() % 255)* 0.1;
		color[0] = (int)((rand() % 255) *1.5);
		color[1] = (int)((rand() % 255) *1.2);
		color[2] = (int)((rand() % 255) *0.9);
	}

	int static random(int start, int end){
		if (end <= start) {
			return (rand() % (start - end) + start);
		}
		return (rand() % (end - start) + start);
	}


	int  static randomDir(int start, int end){
		int dir;
		if (rand() % 2 == 0)
			dir = 1;
		else dir = -1;

		if (end <= start) {
			return (rand() % (start - end) + start) * dir;
		}
		return (rand() % (end - start) + start) * dir;
	}
};