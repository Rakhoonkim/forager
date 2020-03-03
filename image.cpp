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
	//����۰� �����ϸ� �޸� ����
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	// �� DC���� �ϳ��� �����
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->isRotate = false;

	//���� ������ �����ؼ� ����۰� �������� �ʾҴٸ�
	if (_imageInfo == NULL)
	{
		//�޸� ����
		release();

		//�׸��� �����ߴ� �޼����� ȣ���ض�
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
	//ȣ������ �̹��� ������ �ʱ�ȭ �Ǿ����� �ʴٸ� ������ ���Ѷ�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �����Ѵ�
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
	//ã�����ϴ� �̹��� ���� �̸��� ������ ���и� ����ض�
	if (fileName == NULL) return E_FAIL;

	//ȣ������ �̹��� ������ �ʱ�ȭ �Ǿ����� �ʴٸ� ������ ���Ѷ�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �����Ѵ�
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->isRotate = false;

	//�����̸��� ���̸� �˾ƿ´�
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
	//ã�����ϴ� �̹��� ���� �̸��� ������ ���и� ����ض�
	if (fileName == NULL) return E_FAIL;

	//ȣ������ �̹��� ������ �ʱ�ȭ �Ǿ����� �ʴٸ� ������ ���Ѷ�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �����Ѵ�
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

	//�����̸��� ���̸� �˾ƿ´�
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
	//ã�����ϴ� �̹��� ���� �̸��� ������ ���и� ����ض�
	if (fileName == NULL) return E_FAIL;

	//ȣ������ �̹��� ������ �ʱ�ȭ �Ǿ����� �ʴٸ� ������ ���Ѷ�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �����Ѵ�
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->isRotate = false;

	//�����̸��� ���̸� �˾ƿ´�
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
	//// ���ڴ� ���� 
	//HRESULT hr = E_FAIL;
	//IWICBitmapDecoder* DecoderPtr = nullptr;
	//
	//hr = ::_gp_WICFactory->CreateDecoderFromFilename((LPCWSTR)fileName, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &DecoderPtr);

	//assert(hr == S_OK);
	////������ ��� 
	//IWICBitmapFrameDecode* FramePtr = nullptr;
	//hr = DecoderPtr->GetFrame(0, &FramePtr);
	//assert(hr == S_OK);

	//// ���� ������ ����� 
	//SafeRelease(_gp_ipConvertedSrcBmp);

	//hr = ::_gp_WICFactory->CreateFormatConverter(&::_gp_ipConvertedSrcBmp);
	//assert(hr == S_OK);

	//hr = ::_gp_ipConvertedSrcBmp->Initialize(FramePtr, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
	//	nullptr, 0.0f, WICBitmapPaletteTypeCustom);
	//assert(hr == S_OK);

	//// ���� ��Ʈ�� �����
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
	//Ʈ���� �÷� ó���� �ؾ��ϳ�
	if (_trans)
	{
		//ȭ�鿡 �ѷ��ٶ� Ư�� �ȼ����� ���� ������ش�
		GdiTransparentBlt(
			hdc,					//����� ������ DC 
			_imageInfo->x,			//����� ��ǥ X
			_imageInfo->y,			//����� ��ǥ Y
			_imageInfo->width,		//����� ũ��
			_imageInfo->height,		//����� ũ��
			_imageInfo->hMemDC,		//������ DC
			0, 0,					//�����ؿ� ��ǥ
			_imageInfo->width,		//�����ؿ� ũ��
			_imageInfo->height,
			_transColor);			//�����ؿö� ������ Į��
	}
	//�ƴϳ�
	else
	{
		BitBlt(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	//Ʈ���� �÷� ó���� �ؾ��ϳ�
	if (_trans)
	{
		//ȭ�鿡 �ѷ��ٶ� Ư�� �ȼ����� ���� ������ش�
		GdiTransparentBlt(
			hdc,					//����� ������ DC 
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			_imageInfo->width,		//����� ũ��
			_imageInfo->height,		//����� ũ��
			_imageInfo->hMemDC,		//������ DC
			0, 0,					//�����ؿ� ��ǥ
			_imageInfo->width,		//�����ؿ� ũ��
			_imageInfo->height,
			_transColor);			//�����ؿö� ������ Į��

	}
	//�ƴϳ�
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//Ʈ���� �÷� ó���� �ؾ��ϳ�
	if (_trans)
	{
		//ȭ�鿡 �ѷ��ٶ� Ư�� �ȼ����� ���� ������ش�
		GdiTransparentBlt(
			hdc,					//����� ������ DC 
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			sourWidth,				//����� ũ��
			sourHeight,				//����� ũ��
			_imageInfo->hMemDC,		//������ DC
			sourX, sourY,			//�����ؿ� ��ǥ
			sourWidth,				//�����ؿ� ũ��
			sourHeight,
			_transColor);			//�����ؿö� ������ Į��

	}
	//�ƴϳ�
	else
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}

}

void image::frameRender(HDC hdc, int destX, int destY)
{
	//Ʈ���� �÷� ó���� �ؾ��ϳ�
	if (_trans)
	{
		//ȭ�鿡 �ѷ��ٶ� Ư�� �ȼ����� ���� ������ش�
		GdiTransparentBlt(
			hdc,												//����� ������ DC 
			destX,												//����� ��ǥ X
			destY,												//����� ��ǥ Y
			_imageInfo->frameWidth,								//����� ũ��
			_imageInfo->frameHeight,							//����� ũ��
			_imageInfo->hMemDC,									//������ DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,									//�����ؿ� ��ǥ
			_imageInfo->frameWidth,									//�����ؿ� ũ��
			_imageInfo->frameHeight,
			_transColor);										//�����ؿö� ������ Į��

	}
	//�ƴϳ�
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

	//Ʈ���� �÷� ó���� �ؾ��ϳ�
	if (_trans)
	{
		//ȭ�鿡 �ѷ��ٶ� Ư�� �ȼ����� ���� ������ش�
		GdiTransparentBlt(
			hdc,												//����� ������ DC 
			destX,												//����� ��ǥ X
			destY,												//����� ��ǥ Y
			_imageInfo->frameWidth,								//����� ũ��
			_imageInfo->frameHeight,							//����� ũ��
			_imageInfo->hMemDC,									//������ DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,									//�����ؿ� ��ǥ
			_imageInfo->frameWidth,									//�����ؿ� ũ��
			_imageInfo->frameHeight,
			_transColor);										//�����ؿö� ������ Į��

	}
	//�ƴϳ�
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

	int drawAreaX = drawArea->left;					//�׷��� ������ left
	int drawAreaY = drawArea->top;					//�׷��� ������ top
	int drawAreaW = drawArea->right - drawAreaX;	//�׷��� ������ ����ũ��
	int drawAreaH = drawArea->bottom - drawAreaY;	//�׷��� ������ ����ũ��

	//Y�� �����Ҷ� ó��
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//ȭ�鿡�� ���� ������ŭ�� ��´�
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//�߶󳻼� �ٽ� ȭ�� ������ ���� ũ�⸦ ��´�
		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ������� ���� ������ �ٽ� ȭ������� �ִ� �۾��� �ݺ��Ѵ�.
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�ѷ��� �������� �ѷ��ش�.
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//Y��ó�� X�൵ ����.
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
	//���ĺ��尡 ����Ǵ� ������ �����ϸ鼭 ���ô�
	if (_imageInfo->isAlpha) {
		if (value != -1) {
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			_blendFunc.SourceConstantAlpha = value;
		}
		//���ĺ��尡 ����Ǵ� ������ �����ϸ鼭 ���ô�
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
		//���ĺ��尡 ����Ǵ� ������ �����ϸ鼭 ���ô�
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
		//���ĺ��尡 ����Ǵ� ������ �����ϸ鼭 ���ô�
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
		//���ĺ��尡 ����Ǵ� ������ �����ϸ鼭 ���ô�
		else
			_blendFunc.SourceConstantAlpha = _imageInfo->alpha;

		//Ʈ���� �÷� ó���� �ؾ��ϳ�
		if (_trans)
		{
			BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
				hdc, destX, destY, SRCCOPY);

			//ȭ�鿡 �ѷ��ٶ� Ư�� �ȼ����� ���� ������ش�
			GdiTransparentBlt(
				hdc,												//����� ������ DC 
				destX,												//����� ��ǥ X
				destY,												//����� ��ǥ Y
				_imageInfo->frameWidth,								//����� ũ��
				_imageInfo->frameHeight,							//����� ũ��
				_imageInfo->hMemDC,									//������ DC
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,									//�����ؿ� ��ǥ
				_imageInfo->frameWidth,									//�����ؿ� ũ��
				_imageInfo->frameHeight,
				_transColor);										//�����ؿö� ������ Į��

			AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
				_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
				_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);


		}
		//�ƴϳ�
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
		//���ĺ��尡 ����Ǵ� ������ �����ϸ鼭 ���ô�
		else
			_blendFunc.SourceConstantAlpha = _imageInfo->alpha;
		//Ʈ���� �÷� ó���� �ؾ��ϳ�
		if (_trans)
		{
			BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
				hdc, destX, destY, SRCCOPY);
			//ȭ�鿡 �ѷ��ٶ� Ư�� �ȼ����� ���� ������ش�
			GdiTransparentBlt(
				hdc,												//����� ������ DC 
				destX,												//����� ��ǥ X
				destY,												//����� ��ǥ Y
				_imageInfo->frameWidth,								//����� ũ��
				_imageInfo->frameHeight,							//����� ũ��
				_imageInfo->hMemDC,									//������ DC
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,									//�����ؿ� ��ǥ
				_imageInfo->frameWidth,									//�����ؿ� ũ��
				_imageInfo->frameHeight,
				_transColor);										//�����ؿö� ������ Į��

			AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
				_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
				_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);


		}
		//�ƴϳ�
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
	//���̹� ī�� ����� �Խ��ǿ���
//Blt�� �˻��ؼ� �ߴ� �� �� �о�� �ٶ�
//�׷����� �̰� �̿��ؼ� �����ӷ����� ���ǻ� �ʿ��� ��������� ���� ����ϱ� �ٶ�

	SetStretchBltMode(getMemDC(), COLORONCOLOR);

	//ȭ�鿡 �ѷ��ٶ� Ư�� �ȼ����� ���� ������ش�
	TransparentBlt(
		hdc,					//����� ������ DC 
		destX,					//����� ��ǥ X
		destY,					//����� ��ǥ Y
		_imageInfo->width * scaleX,		//����� ũ��
		_imageInfo->height * scaleY,		//����� ũ��
		_imageInfo->hMemDC,		//������ DC
		0, 0,					//�����ؿ� ��ǥ
		_imageInfo->width,		//�����ؿ� ũ��
		_imageInfo->height,
		_transColor);			//�����ؿö� ������ Į��
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
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
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
	//��� ���� �ٷ� ���� �Ŷ�� SET�ҷ��༭ �ʿ��� ���� �Ϸ��ض� 
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
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
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

		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->frameWidth, _rotateImage->frameHeight,
			hdc,
			0, 0, BLACKNESS);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
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
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->frameWidth, _rotateImage->frameHeight,
			hdc,
			0, 0, BLACKNESS);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
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

		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
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
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
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
	//ȸ���� �ʿ������� �����Ѵ� 
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


