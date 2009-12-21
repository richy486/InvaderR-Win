#include "ApplicationData.h"

static ApplicationData* s_Instance = NULL;

ApplicationData* ApplicationData::GetInstance()
{
	if (s_Instance == NULL)
	{
		s_Instance = new ApplicationData();
	}
	return s_Instance;
}

ApplicationData::~ApplicationData()
{
}

HINSTANCE& ApplicationData::getHInstance()
{
	return m_HInstance;
}
WNDCLASSEX& ApplicationData::getWindowClass()
{
	return m_WindowClass;
}
ATOM& ApplicationData::getRegisteredClass()
{
	return m_RegisteredClass;
}
HWND& ApplicationData::getWindow()
{
	return m_Window;
}

HDC& ApplicationData::getDeviceContext()
{
	return m_HDC;
}
HGLRC& ApplicationData::getRenderingContext()
{
	return m_HGLRC;
}

int& ApplicationData::getPixelFormat()
{
	return m_PixelFormat;
}

ApplicationData::ApplicationData()
{
}
