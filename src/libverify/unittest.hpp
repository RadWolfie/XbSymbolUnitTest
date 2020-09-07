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

typedef std::map<std::string, version_ranges> library_list;

void getLibraryD3D8(const library_list **db_min, 
                    const library_list **db_full);
