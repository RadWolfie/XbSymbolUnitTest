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

#include "unittest.hpp"

static const library_list database_full = {
	REGISTER_SYMBOL_INLINE(CXo_XOnlineLogon, VER_RANGE(4361, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XOnlineLogon, VER_RANGE(4361, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSearch, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XOnlineMatchSearch, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSearchResultsLen, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XOnlineMatchSearchResultsLen, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSearchGetResults, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XOnlineMatchSearchGetResults, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSessionUpdate, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XOnlineMatchSessionUpdate, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(CXo_XOnlineMatchSessionCreate, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XOnlineMatchSessionCreate, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XoUpdateLaunchNewImageInternal, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/xonline.def>
#undef XREF_SYMBOL
	LOCAL_COUNT
};

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(CXo_XOnlineLogon)
static_assert(XREF_OFFSET == 0);
// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

void getLibraryXONLINE(library_db& lib_db)
{
	lib_db.optional = nullptr;
	lib_db.min = nullptr; //&database_min;
	lib_db.full = &database_full;
	lib_db.xref_offset = XREF_OFFSET;
	lib_db.xref_total = LOCAL_COUNT;
	lib_db.xref_exclude = 0;
}
