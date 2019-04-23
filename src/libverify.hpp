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

#include <cstdint>
#include <map>
#include <string>

#include <libXbSymbolDatabase.h>

typedef struct _lib_versions {
	uint16_t d3d8;
	uint16_t d3d8ltcg;
	uint16_t d3d8x; // Do we need this?
	uint16_t dsound;
	uint16_t xacteng;
	uint16_t xapilib;
	uint16_t xgraphic;
	uint16_t xnet;
	uint16_t xonline;
} lib_versions;

//                symbol_addr, build
typedef std::pair<uint32_t, uint32_t> symbol_version;

void run_test_verify_symbols(
    lib_versions &lib_ver, std::map<std::string, symbol_version> &symbol_addr);
