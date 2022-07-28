/*
    Copyright (C) 2019  RadWolfie

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <map>
#include <string>

#include "unittest.hpp"

static const library_list database_full = {
	//REGISTER_SYMBOL_INLINE(DisassembleVertexShader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(SupportsSSE, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	REGISTER_SYMBOL_INLINE(XFONT_OpenBitmapFontFromMemory, VER_RANGE(4361, VER_MAX, VER_NONE, VER_NONE)),
	//REGISTER_SYMBOL_INLINE(XGAssembleShader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGBufferCreate, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGColorAdjustContrast, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGColorAdjustSaturation, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	REGISTER_SYMBOL_INLINE(XGCompressRect, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XGIsSwizzledFormat, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	//REGISTER_SYMBOL_INLINE(XGPlaneFromPointNormal, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGPlaneFromPoints, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGPlaneIntersectLine, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGPlaneNormalize, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGPlaneTransform, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGSetCubeTextureHeader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGSetFixupHeader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	REGISTER_SYMBOL_INLINE(XGSetIndexBufferHeader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	//REGISTER_SYMBOL_INLINE(XGSetPaletteHeader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGSetPushBufferHeader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	//REGISTER_SYMBOL_INLINE(XGSetSurfaceHeader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	REGISTER_SYMBOL_INLINE(XGSetTextureHeader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XGSetVertexBufferHeader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	//REGISTER_SYMBOL_INLINE(XGSetVolumeTextureHeader, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
	REGISTER_SYMBOL_INLINE(XGSwizzleBox, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XGSwizzleRect, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XGUnswizzleBox, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XGUnswizzleRect, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XGWriteSurfaceOrTextureToXPR, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	//REGISTER_SYMBOL_INLINE(XGWriteSurfaceToFile, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // TODO: Need assign XREF...
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/xgraphic.def>
#undef XREF_SYMBOL
	LOCAL_COUNT
};

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(XFONT_OpenBitmapFontFromMemory)
static_assert(XREF_OFFSET == 0);
// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

void getLibraryXGRAPHIC(library_db& lib_db)
{
	lib_db.min = nullptr; //&database_min;
	lib_db.full = &database_full;
	lib_db.xref_offset = XREF_OFFSET;
	lib_db.xref_total = LOCAL_COUNT;
	assert(database_full.size() == LOCAL_COUNT);
}
