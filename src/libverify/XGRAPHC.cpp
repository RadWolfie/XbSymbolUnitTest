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

static const std::map<std::string, version_ranges> database_full = {
    {"DisassembleVertexShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"SupportsSSE", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XFONT_OpenBitmapFontFromMemory", {4361, VER_MAX, VER_NONE, VER_NONE}},
    {"XGAssembleShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGBufferCreate", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGColorAdjustContrast", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGColorAdjustSaturation", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGCompressRect", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGIsSwizzledFormat", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGPlaneFromPointNormal", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGPlaneFromPoints", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGPlaneIntersectLine", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGPlaneNormalize", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGPlaneTransform", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSetCubeTextureHeader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSetFixupHeader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSetIndexBufferHeader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSetPaletteHeader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSetPushBufferHeader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSetSurfaceHeader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSetTextureHeader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSetVertexBufferHeader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSetVolumeTextureHeader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSwizzleBox", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGSwizzleRect", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGUnswizzleBox", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGUnswizzleRect", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGWriteSurfaceOrTextureToXPR", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGWriteSurfaceToFile", {3911, VER_MAX, VER_NONE, VER_NONE}},
};

void getLibraryXGRAPHIC(const library_list **db_min,
                        const library_list **db_full)
{
	*db_min = nullptr; //&database_min;
	*db_full = &database_full;
}
