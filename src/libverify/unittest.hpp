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

#pragma once

#include <xref/list_xref.h>

#include <cassert>
#include <map>
#include <stdint.h>
#include <string>

typedef struct _version_ranges {
	uint16_t intro_start;
	uint16_t intro_end;
	uint32_t revive_start;
	uint32_t revive_end;
} version_ranges;

#define VER_NONE 0x000
#define VER_MAX 0xFFFF

#define STRINGIZEX(x) #x
#define STRINGIZE(x) STRINGIZEX(x)
#define XREF_SYMBOL(e) XREF_##e
// clang-format off
#define VER_RANGE(v1l, v1h, v2l, v2h) {v1l, v1h, v2l, v2h}
#define REGISTER_SYMBOL_INLINE(e, v) { XREF_SYMBOL(e), {{ #e, v}}}
// Below are aliases for XREF usage only.
#define REGISTER_SYMBOL_INLINE_D3D(e, v) { XREF_SYMBOL(D3D_##e), {{ #e, v}}}
#define REGISTER_SYMBOL_INLINE_D3D8(e, v) { XREF_SYMBOL(D3D8_##e), {{ #e, v}}}
#define REGISTER_SYMBOL_INLINE_VAR_OFFSET(e, v) { XREF_SYMBOL(OFFSET_##e), {{ STRINGIZE(e##_OFFSET), v}}}
#define REGISTER_SYMBOL_INLINE_XAPI(e, v) { XREF_SYMBOL(XAPI_##e), {{ #e, v}}}
// Below macros are intended to use multiple symbol names combine with single XREF.
#define REGISTER_SYMBOL(e, v) { #e, v}
#define REGISTER_SYMBOLS(Symbol, ...) { XREF_##Symbol, { __VA_ARGS__ }}
// clang-format on
typedef const std::map<uint32_t, const std::map<const std::string, version_ranges>>
    library_list;

struct library_db {
	const library_list* min;
	const library_list* full;
	const library_list* optional;
	uint32_t xref_offset;
	uint32_t xref_total;
	uint32_t xref_exclude;
};

void getLibraryD3D8(library_db& lib_db);

void getLibraryDSOUND(library_db& lib_db);

void getLibraryJVS(library_db& lib_db);

void getLibraryXACTENG(library_db& lib_db);

void getLibraryXAPILIB(library_db& lib_db);

void getLibraryXGRAPHIC(library_db& lib_db);

void getLibraryXNET(library_db& lib_db);

void getLibraryXONLINE(library_db& lib_db);
