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

static const library_list database_min = {};

static const library_list database_full = {
	REGISTER_SYMBOL_INLINE(XnInit, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(WSAStartup, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XNetStartup, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XNetGetEthernetLinkStatus, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(bind, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(connect, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(ioctlsocket, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(listen, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(recv, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(send, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(socket, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/xnet.def>
#undef XREF_SYMBOL
	LOCAL_COUNT
};

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(XnInit)
static_assert(XREF_OFFSET == 0);
// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

void getLibraryXNET(library_db& lib_db)
{
	lib_db.min = nullptr; //&database_min;
	lib_db.full = &database_full;
	lib_db.xref_offset = XREF_OFFSET;
	lib_db.xref_total = LOCAL_COUNT;
	assert(database_full.size() == LOCAL_COUNT);
}
