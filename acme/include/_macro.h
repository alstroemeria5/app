// Created by camilo 2021-09-10 07:03 BRT <3ThomasBS_!!
#pragma once



#define __UNREFERENCED_PARAMETER(u)	(void)(u)



#define __MAKE_LONG(a, b)           ((::i32)(((::u16)(((::uptr)(a)) & 0xffff)) | ((::u32)((::u16)(((::uptr)(b)) & 0xffff))) << 16))

#define __MAKE_LPARAM(l, h)         ((::lparam)(::uptr)(::u32)__MAKE_LONG(l, h))


#define __LOBYTE(w)                 ((byte)(((dword_ptr)(w)) & 0xff))


