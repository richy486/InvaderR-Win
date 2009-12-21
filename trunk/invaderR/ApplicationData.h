#pragma once
#ifndef _APPLICATION_DATA_H_
#define _APPLICATION_DATA_H_

#include "consts.h"

class ApplicationData
{
public:
	static ApplicationData* GetInstance();
	~ApplicationData();

	HINSTANCE& getHInstance();
	WNDCLASSEX& getWindowClass();
	ATOM& getRegisteredClass();
	HWND& getWindow();

	HDC& getDeviceContext();
	HGLRC& getRenderingContext();
	int& getPixelFormat();

private:
	ApplicationData();

	HINSTANCE m_HInstance;
	WNDCLASSEX m_WindowClass;
	ATOM m_RegisteredClass;
	HWND m_Window;

	HDC m_HDC;			// handle to the device context
	HGLRC m_HGLRC;		// handle to the OpenGL rendering context
	int m_PixelFormat;
};

#endif // _APPLICATION_DATA_H_