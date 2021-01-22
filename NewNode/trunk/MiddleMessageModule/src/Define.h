#include "Version.h"
#define _Stringizing(v)       #v 
#define _VerJoin(a,b,c,d)		_Stringizing(a.b.c.d)
#define STR_Version				TEXT(_VerJoin(MainVer, SubVer, PubVer, BuildVer))
#define STR_CompanyName			TEXT("POBO")
#define STR_Description			TEXT("交易网关中间件")
#define STR_ProductName			TEXT("交易网关中间件") 
#define STR_Copyright			TEXT("Copyright 2021- ") 
#define STR_Corporation			TEXT("") 
#define STR_InternalName		TEXT("MiddleMessageModule")
#define STR_OriginalFilename	TEXT("MiddleMessageModule.dll")


