//
//  apple_graphics.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//
//
#pragma once


#include "acme/graphics/draw2d/color32.h"


#undef DEBUG


#include <Carbon/Carbon.h>


CGColorRef cg_create_color(color32_t crText);
int_bool cg_release_color(CGColorRef colorref);



//
//  c_os_win_user.h
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/30/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//











