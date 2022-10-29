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
	uint16_t d3d8x; // TODO: Do we need this?
	uint16_t dsound;
	uint16_t jvs;
	uint16_t xacteng;
	uint16_t xapilib;
	uint16_t xgraphic;
	uint16_t xnet;
	uint16_t xonline;
} lib_versions;

typedef struct _symbol_result {
	uint32_t addr;
	uint32_t build;
	uint32_t library_flag;
	std::string symbol;
} symbol_result;

constexpr bool operator==(const symbol_result &lhs,
                          const symbol_result &rhs)
{
	return lhs.addr == rhs.addr && lhs.build == rhs.build && lhs.library_flag == rhs.library_flag && lhs.symbol == rhs.symbol;
}

// Perform self test for all libraries' symbol registers are in sync with libXbSymbolDatabase.
bool run_test_verify_libraries();

void run_test_verify_symbols(lib_versions &lib_ver,
                             std::map<uint32_t, symbol_result> &symbols_list,
                             unsigned &full_lib_count, size_t &error_count);

template<bool doCache>
void Generic_OutputMessage(xb_output_message mFlag, const char* section, const std::string& message);

template<bool doCache = true>
static void XbSUT_OutputMessage(xb_output_message mFlag, const std::string& message)
{
	Generic_OutputMessage<doCache>(mFlag, "XbSUT Messages", message);
}
void Custom_OutputMessage(xb_output_message mFlag, const std::string& section, const std::string& key, const std::string& value);
