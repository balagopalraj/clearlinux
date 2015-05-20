/*
 * %CopyrightBegin%
 *
 * Copyright Ericsson AB 2008-2014. All Rights Reserved.
 *
 * The contents of this file are subject to the Erlang Public License,
 * Version 1.1, (the "License"); you may not use this file except in
 * compliance with the License. You should have received a copy of the
 * Erlang Public License along with this software. If not, it can be
 * retrieved online at http://www.erlang.org/.
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * %CopyrightEnd%
 */

#ifndef _WXE_GL_H
#define _WXE_GL_H

#include "egl_impl.h"
#include "wxe_return.h"

void activateGL(ErlDrvTermData caller);
void setActiveGL(ErlDrvTermData caller, wxGLCanvas *canvas);
void deleteActiveGL(wxGLCanvas *canvas);
void wxe_initOpenGL(wxeReturn, char*);
void gl_dispatch(int op, char *bp, ErlDrvTermData caller, WXEBinRef *bins[]);

WX_DECLARE_HASH_MAP(ErlDrvTermData, wxGLCanvas*, wxIntegerHash, wxIntegerEqual, wxeGLC);
extern wxeGLC glc;

#endif