#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height, BOOL blend)
{
	//백버퍼가 존재하면 메모리 해제
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	// 빈 DC영역 하나를 만든다
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->isRotate = false;

	//위에 셋팅이 실패해서 백버퍼가 생성되지 않았다면
	if (_imageInfo == NULL)
	{
		//메모리 해제
		release();

		//그리고 실패했단 메세지를 호출해라
		return E_FAIL;
	}

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	if (blend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_imageInfo->isAlpha = true;
	}
	else
		_imageInfo->isAlpha = false;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}


HRESULT image::init(const DWORD resID, int width, int height, BOOL trans, COLORREF transColor, BOOL blend)
{
	//호옥시이 이미지 정보가 초기화 되어있지 않다면 해제를 시켜라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성한다
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->isRotate = false;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	if (blend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_imageInfo->isAlpha = true;
	}
	else
		_imageInfo->isAlpha = false;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height, BOOL trans, COLORREF transColor, BOOL blend)
{
	//찾고자하는 이미지 파일 이름이 없으면 실패를 출력해라
	if (fileName == NULL) return E_FAIL;

	//호옥시이 이미지 정보가 초기화 되어있지 않다면 해제를 시켜라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성한다
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->isRotate = false;

	//파일이름의 길이를 알아온다
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (blend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_imageInfo->isAlpha = true;
	}
	else
		_imageInfo->isAlpha = false;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend)
{
	//찾고자하는 이미지 파일 이름이 없으면 실패를 출력해라
	if (fileName == NULL) return E_FAIL;

	//호옥시이 이미지 정보가 초기화 되어있지 않다면 해제를 시켜라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성한다
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->isRotate = false;

	//파일이름의 길이를 알아온다
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (blend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_imageInfo->isAlpha = true;
	}
	else
		_imageInfo->isAlpha = false;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend)
{
	//찾고자하는 이미지 파일 이름이 없으면 실패를 출력해라
	if (fileName == NULL) return E_FAIL;

	//호옥시이 이미지 정보가 초기화 되어있지 않다면 해제를 시켜라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성한다
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->isRotate = false;

	//파일이름의 길이를 알아온다
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (blend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_imageInfo->isAlpha = true;
	}
	else
		_imageInfo->isAlpha = false;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName)
{
	//// 디코더 생성 
	//HRESULT hr = E_FAIL;
	//IWICBitmapDecoder* DecoderPtr = nullptr;
	//
	//hr = ::_gp_WICFactory->CreateDecoderFromFilename((LPCWSTR)fileName, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &DecoderPtr);

	//assert(hr == S_OK);
	////프레임 얻기 
	//IWICBitmapFrameDecode* FramePtr = nullptr;
	//hr = DecoderPtr->GetFrame(0, &FramePtr);
	//assert(hr == S_OK);

	//// 포맷 컨버터 만들기 
	//SafeRelease(_gp_ipConvertedSrcBmp);

	//hr = ::_gp_WICFactory->CreateFormatConverter(&::_gp_ipConvertedSrcBmp);
	//assert(hr == S_OK);

	//hr = ::_gp_ipConvertedSrcBmp->Initialize(FramePtr, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
	//	nullptr, 0.0f, WICBitmapPaletteTypeCustom);
	//assert(hr == S_OK);

	//// 실제 비트맨 만들기
	//SafeRelease(_gp_D2DBitMap);
	//hr = ::_gp_RenderTarget->CreateBitmapFromWicBitmap(::_gp_ipConvertedSrcBmp, nullptr, &::_gp_D2DBitMap);

	//assert(hr == S_OK);
	//SafeRelease(DecoderPtr);
	//SafeRelease(FramePtr);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		if (_imageInfo->isAlpha)
		{
			SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
			DeleteObject(_blendImage->hBit);
			DeleteDC(_blendImage->hMemDC);
			SAFE_DELETE(_blendImage);
		}


		if (_imageInfo->isRotate)
		{
			SelectObject(_rotateImage->hMemDC, _rotateImage->hOBit);
			DeleteObject(_rotateImage->hBit);
			DeleteDC(_rotateImage->hMemDC);
			SAFE_DELETE(_rotateImage);
		}


		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		_trans = NULL;
		_transColor = RGB(0, 0, 0);
	}

}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	trans = trans;
	transColor = transColor;
}

void image::render(HDC hdc)
{
	//트랜스 컬러 처리를 해야하냐
	if (_trans)
	{
		//화면에 뿌려줄때 특정 픽셀값을 빼고 출력해준다
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC 
			_imageInfo->x,			//복사될 좌표 X
			_imageInfo->y,			//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기
			_imageInfo->height,		//복사될 크기
			_imageInfo->hMemDC,		//복사할 DC
			0, 0,					//복사해올 좌표
			_imageInfo->width,		//복사해올 크기
			_imageInfo->height,
			_transColor);			//복사해올때 제외할 칼라
	}
	//아니냐
	else
	{
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	//트랜스 컬러 처리를 해야하냐
	if (_trans)
	{
		//화면에 뿌려줄때 특정 픽셀값을 빼고 출력해준다
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC 
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기
			_imageInfo->height,		//복사될 크기
			_imageInfo->hMemDC,		//복사할 DC
			0, 0,					//복사해올 좌표
			_imageInfo->width,		//복사해올 크기
			_imageInfo->height,
			_transColor);			//복사해올때 제외할 칼라

	}
	//아니냐
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//트랜스 컬러 처리를 해야하냐
	if (_trans)
	{
		//화면에 뿌려줄때 특정 픽셀값을 빼고 출력해준다
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC 
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			sourWidth,				//복사될 크기
			sourHeight,				//복사될 크기
			_imageInfo->hMemDC,		//복사할 DC
			sourX, sourY,			//복사해올 좌표
			sourWidth,				//복사해올 크기
			sourHeight,
			_transColor);			//복사해올때 제외할 칼라

	}
	//아니냐
	else
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}

}

void image::frameRender(HDC hdc, int destX, int destY)
{
	//트랜스 컬러 처리를 해야하냐
	if (_trans)
	{
		//화면에 뿌려줄때 특정 픽셀값을 빼고 출력해준다
		GdiTransparentBlt(
			hdc,												//복사될 영역의 DC 
			destX,												//복사될 좌표 X
			destY,												//복사될 좌표 Y
			_imageInfo->frameWidth,								//복사될 크기
			_imageInfo->frameHeight,							//복사될 크기
			_imageInfo->hMemDC,									//복사할 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,									//복사해올 좌표
			_imageInfo->frameWidth,									//복사해올 크기
			_imageInfo->frameHeight,
			_transColor);										//복사해올때 제외할 칼라

	}
	//아니냐
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	//트랜스 컬러 처리를 해야하냐
	if (_trans)
	{
		//화면에 뿌려줄때 특정 픽셀값을 빼고 출력해준다
		GdiTransparentBlt(
			hdc,												//복사될 영역의 DC 
			destX,												//복사될 좌표 X
			destY,												//복사될 좌표 Y
			_imageInfo->frameWidth,								//복사될 크기
			_imageInfo->frameHeight,							//복사될 크기
			_imageInfo->hMemDC,									//복사할 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,									//복사해올 좌표
			_imageInfo->frameWidth,									//복사해올 크기
			_imageInfo->frameHeight,
			_transColor);										//복사해올때 제외할 칼라

	}
	//아니냐
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;					//그려줄 영역의 left
	int drawAreaY = drawArea->top;					//그려줄 영역의 top
	int drawAreaW = drawArea->right - drawAreaX;	//그려줄 영역의 가로크기
	int drawAreaH = drawArea->bottom - drawAreaY;	//그려줄 영역의 세로크기

	//Y축 루프할때 처리
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//화면에서 나간 영역만큼을 잡는다
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//잘라내서 다시 화면 안으로 넣을 크기를 잡는다
		sourHeight = rcSour.bottom - rcSour.top;

		//화면밖으로 나간 영역을 다시 화면안으로 넣는 작업을 반복한다.
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//뿌려줄 영역에다 뿌려준다.
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//Y축처럼 X축도 같다.
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::alphaRender(HDC hdc, int value)
{
	//알파블렌드가 적용되는 순서에 주의하면서 봅시다
	if (_imageInfo->isAlpha) {
		if (value != -1) {
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			_blendFunc.SourceConstantAlpha = value;
		}
		//알파블렌드가 적용되는 순서에 주의하면서 봅시다
		else
			_blendFunc.SourceConstantAlpha = _imageInfo->alpha;

		if (_trans)
		{
			BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
				hdc, 0, 0, SRCCOPY);

			GdiTransparentBlt(
				_blendImage->hMemDC,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDC,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_transColor);

			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
				_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width,
				_imageInfo->height, _blendFunc);

		}
		else
		{
			AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
				_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
				_imageInfo->height, _blendFunc);
		}
	}
	else
		render(hdc);
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int value)
{
	if (_imageInfo->isAlpha)
	{
		if (value != -1) 
		{
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			_blendFunc.SourceConstantAlpha = value;
		}
		//알파블렌드가 적용되는 순서에 주의하면서 봅시다
		else
			_blendFunc.SourceConstantAlpha = _imageInfo->alpha;

		if (_trans)
		{
			BitBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
				hdc, destX, destY, SRCCOPY);

			GdiTransparentBlt(
				_blendImage->hMemDC,
				0, 0,
				sourWidth,
				sourHeight,
				_imageInfo->hMemDC,
				sourX, sourY,
				sourWidth,
				sourHeight,
				_transColor);

			AlphaBlend(hdc, destX, destY, sourWidth,
				sourHeight, _blendImage->hMemDC, 0, 0, sourWidth,
				sourHeight, _blendFunc);

		}
		else
		{
			AlphaBlend(hdc, destX, destY, sourWidth,
				sourHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth,
				sourHeight, _blendFunc);
		}

	}
	else
		render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);

}


void image::alphaRender(HDC hdc, int destX, int destY, int value)
{
	if (_imageInfo->isAlpha) 
	{
		if (value != -1) {
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			_blendFunc.SourceConstantAlpha = value;
		}
		//알파블렌드가 적용되는 순서에 주의하면서 봅시다
		else
			_blendFunc.SourceConstantAlpha = _imageInfo->alpha;

		if (_trans)
		{
			BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
				hdc, destX, destY, SRCCOPY);

			GdiTransparentBlt(
				_blendImage->hMemDC,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDC,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_transColor);

			AlphaBlend(hdc, destX, destY, _imageInfo->width,
				_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width,
				_imageInfo->height, _blendFunc);

		}
		else
		{
			AlphaBlend(hdc, destX, destY, _imageInfo->width,
				_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
				_imageInfo->height, _blendFunc);
		}
	}
	else
		render(hdc, destX, destY);
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int value)
{
	if (_imageInfo->isAlpha) {
		if (value != -1) {
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			_blendFunc.SourceConstantAlpha = value;
		}
		//알파블렌드가 적용되는 순서에 주의하면서 봅시다
		else
			_blendFunc.SourceConstantAlpha = _imageInfo->alpha;

		//트랜스 컬러 처리를 해야하냐
		if (_trans)
		{
			BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
				hdc, destX, destY, SRCCOPY);

			//화면에 뿌려줄때 특정 픽셀값을 빼고 출력해준다
			GdiTransparentBlt(
				hdc,												//복사될 영역의 DC 
				destX,												//복사될 좌표 X
				destY,												//복사될 좌표 Y
				_imageInfo->frameWidth,								//복사될 크기
				_imageInfo->frameHeight,							//복사될 크기
				_imageInfo->hMemDC,									//복사할 DC
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,									//복사해올 좌표
				_imageInfo->frameWidth,									//복사해올 크기
				_imageInfo->frameHeight,
				_transColor);										//복사해올때 제외할 칼라

			AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
				_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
				_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);


		}
		//아니냐
		else
		{
			AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
				_imageInfo->frameHeight, _blendImage->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
				_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);

		}
	}
	else
		frameRender(hdc, destX, destY);
}


void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int value)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (_imageInfo->isAlpha) {
		if (value != -1) {
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			_blendFunc.SourceConstantAlpha = value;
		}
		//알파블렌드가 적용되는 순서에 주의하면서 봅시다
		else
			_blendFunc.SourceConstantAlpha = _imageInfo->alpha;
		//트랜스 컬러 처리를 해야하냐
		if (_trans)
		{
			BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
				hdc, destX, destY, SRCCOPY);
			//화면에 뿌려줄때 특정 픽셀값을 빼고 출력해준다
			GdiTransparentBlt(
				hdc,												//복사될 영역의 DC 
				destX,												//복사될 좌표 X
				destY,												//복사될 좌표 Y
				_imageInfo->frameWidth,								//복사될 크기
				_imageInfo->frameHeight,							//복사될 크기
				_imageInfo->hMemDC,									//복사할 DC
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,									//복사해올 좌표
				_imageInfo->frameWidth,									//복사해올 크기
				_imageInfo->frameHeight,
				_transColor);										//복사해올때 제외할 칼라

			AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
				_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
				_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);


		}
		//아니냐
		else
		{
			AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
				_imageInfo->frameHeight, _blendImage->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
				_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);

		}
	}
	else
		frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}


void image::setAlpha(int value)
{

	if (value > 255) value = 255;
	if (value < 0) value = 0;
	_imageInfo->alpha = value;

	if (!_imageInfo->isAlpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;
		HDC hdc = GetDC(_hWnd);
		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
		_imageInfo->isAlpha = true;
		ReleaseDC(_hWnd, hdc);
	}

}

void image::scaleRender(HDC hdc, int destX, int destY, int scaleX, int scaleY)
{
	//네이버 카페 모두의 게시판에서
//Blt로 검색해서 뜨는 글 잘 읽어보길 바람
//그런다음 이걸 이용해서 프레임렌더나 편의상 필요한 렌더방식을 만들어서 사용하길 바람

	SetStretchBltMode(getMemDC(), COLORONCOLOR);

	//화면에 뿌려줄때 특정 픽셀값을 빼고 출력해준다
	TransparentBlt(
		hdc,					//복사될 영역의 DC 
		destX,					//복사될 좌표 X
		destY,					//복사될 좌표 Y
		_imageInfo->width * scaleX,		//복사될 크기
		_imageInfo->height * scaleY,		//복사될 크기
		_imageInfo->hMemDC,		//복사할 DC
		0, 0,					//복사해올 좌표
		_imageInfo->width,		//복사해올 크기
		_imageInfo->height,
		_transColor);			//복사해올때 제외할 칼라
}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::aniAlphaRender(HDC hdc, int destX, int destY, animation* ani , int alpha)
{
	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}


void image::rotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	setRotationAngle(angle);

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_trans)
	{
		// 검은 색으로 채운다
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);

		// 검은색과 1,1 점이 같으면 현재 브러쉬색(transColor)으로 채운다
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::alphaRotateRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha)
{
	//상수 값을 바로 넣은 거라면 SET불러줘서 필요한 세팅 완료해라 
	setRotationAngle(angle);
	setAlpha(alpha);

	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_trans)
	{
		// 검은 색으로 채운다
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// 검은색과 1,1 점이 같으면 현재 브러쉬색(transColor)으로 채운다
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);

		AlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height, _blendFunc);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::rotateFrameRender(HDC hdc, float centerX, float centerY, float angle)
{
	setRotationAngle(angle);

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}
	if (_trans)
	{

		// 검은 색으로 채운다
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->frameWidth, _rotateImage->frameHeight,
			hdc,
			0, 0, BLACKNESS);

		// 검은색과 1,1 점이 같으면 현재 브러쉬색(transColor)으로 채운다
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void image::rotateFrameRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle)
{
	setRotationAngle(angle);

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}
	if (_trans)
	{
		// 검은 색으로 채운다
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->frameWidth, _rotateImage->frameHeight,
			hdc,
			0, 0, BLACKNESS);

		// 검은색과 1,1 점이 같으면 현재 브러쉬색(transColor)으로 채운다
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void image::alphaRotateFrameRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha)
{
	setRotationAngle(angle);
	setAlpha(alpha);

	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}
	if (_trans)
	{

		// 검은 색으로 채운다
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// 검은색과 1,1 점이 같으면 현재 브러쉬색(transColor)으로 채운다
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
		AlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height, _blendFunc);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void image::alphaRotateFrameRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle, BYTE alpha)
{
	setRotationAngle(angle);
	setAlpha(alpha);


	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}
	if (_trans)
	{
		// 검은 색으로 채운다
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// 검은색과 1,1 점이 같으면 현재 브러쉬색(transColor)으로 채운다
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
		AlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height, _blendFunc);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}




void image::setRotationAngle(float angle)
{
	_imageInfo->rotationAngle = angle;
	//회전이 필요해지면 생성한다 
	if (!_imageInfo->isRotate)
	{
		HDC hdc = GetDC(_hWnd);

		int size;
		(_imageInfo->width > _imageInfo->height ? size = _imageInfo->width : size = _imageInfo->height);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
		_imageInfo->isRotate = true;
	}
}


