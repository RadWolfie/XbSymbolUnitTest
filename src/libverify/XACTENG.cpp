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
	REGISTER_SYMBOL_INLINE(XACTEngineCreate, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACTEngineDoWork, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CEngine_CreateSoundBank, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CEngine_CreateSoundSource, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CEngine_DownloadEffectsImage, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CEngine_GetNotification, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CEngine_RegisterNotification, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CEngine_RegisterStreamedWaveBank, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CEngine_RegisterWaveBank, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CEngine_UnRegisterWaveBank, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CSoundBank_GetSoundCueIndexFromFriendlyName, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(XACT_CSoundBank_Play, VER_RANGE(5344, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTEngine_CreateSoundBank, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTEngine_CreateSoundSource, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTEngine_DownloadEffectsImage, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTEngine_GetNotification, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTEngine_RegisterNotification, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTEngine_RegisterStreamedWaveBank, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTEngine_RegisterWaveBank, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTEngine_UnRegisterWaveBank, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTSoundBank_GetSoundCueIndexFromFriendlyName, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTSoundBank_Play, VER_RANGE(4627, VER_MAX, VER_NONE, VER_NONE)),
	REGISTER_SYMBOL_INLINE(IXACTSoundBank_PlayEx, VER_RANGE(5344, VER_MAX, VER_NONE, VER_NONE)),
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/xacteng.def>
#undef XREF_SYMBOL
	LOCAL_COUNT
} LOCAL_XREFS;

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(XACT_CEngine_RegisterWaveBank)
static_assert(XREF_OFFSET == 0);

// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

void getLibraryXACTENG(library_db& lib_db)
{
	lib_db.min = nullptr; //&database_min;
	lib_db.full = &database_full;
	lib_db.xref_offset = XREF_OFFSET;
	lib_db.xref_total = LOCAL_COUNT;
	assert(database_full.size() == LOCAL_COUNT);
}
