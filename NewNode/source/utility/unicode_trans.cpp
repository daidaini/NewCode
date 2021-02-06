#include "unicode_trans.h"
//
//namespace utility
//{
//	#define	MY_CP_ACP		54936
//
//	int Utf8ToAnsi(char* out, int len, const char *szUTF8, int utf_len)
//	{
//#ifdef _WINDOWS
//		WCHAR	temp[32768 + 1];
//
//		int size = MultiByteToWideChar(CP_UTF8, 0, szUTF8, utf_len, temp, sizeof(temp) / sizeof(temp[0]));
//		size = WideCharToMultiByte(MY_CP_ACP, 0, temp, size, out, len - 1, NULL, NULL);
//		out[size] = 0;
//#else
//		int size = UTF82GB2312((char*)szUTF8, utf_len, out, len);
//#endif
//		return size;
//	}
//
//#ifdef _WINDOWS
//	int	ConvertToUnicode(WCHAR* dst, int size, const char* src, int len)
//	{
//		if (len == -1)
//		{
//			len = static_cast<int>(strlen(src));
//		}
//		int ret = MultiByteToWideChar(MY_CP_ACP, 0, src, len, dst, size - 1);
//		dst[ret] = 0;
//		return ret;
//	}
//#endif
//
//	int AnsiToUtf8(char* out, int len, const char* src, int srclen)
//	{
//#ifdef _WINDOWS
//		WCHAR buffer[32768 + 1];
//		WCHAR* p = buffer;
//
//		if (srclen < sizeof(buffer))
//		{
//			srclen = ConvertToUnicode(buffer, sizeof(buffer), src, srclen);
//		}
//		else
//		{
//			p = new WCHAR[srclen + 1];
//
//			if (p)
//			{
//				srclen = ConvertToUnicode(p, srclen + 1, src, srclen);
//			}
//		}
//
//		int size = WideCharToMultiByte(CP_UTF8, 0, p, srclen, out, len - 1, NULL, NULL);
//		out[size] = 0;
//
//		if (p != buffer)
//		{
//			delete[] p;
//		}
//#else
//		//ANSIתUTF-8
//		int size = code_convert("gb2312", "UTF-8", (char*)src, srclen, out, len);
//#endif
//
//		return size;
//	}
//
//
//}
