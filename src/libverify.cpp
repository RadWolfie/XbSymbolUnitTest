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

// Perform detected symbol inspection for any symbols may had been missed or
// not.

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "libverify.hpp"
#include "libverify/unittest.hpp"

typedef std::map<uint32_t, symbol_result>::iterator list_iterator;

typedef std::vector<std::string>::iterator missing_iterator;

bool verify_version_range(const std::string& symbol_str,
                          const version_ranges& version_range)
{
	bool ret = true;
	if (version_range.intro_start == VER_NONE &&
	    version_range.intro_end == VER_NONE) {
		ret = false;
		std::cout << "ERROR: " << symbol_str
		          << " cannot have VER_NONE in intro range. start= "
		          << version_range.intro_start
		          << "; end= " << version_range.intro_end << "\n";
	}
	else if (version_range.intro_start >= version_range.intro_end) {
		ret = false;
		std::cout << "ERROR: " << symbol_str
		          << " has invalid intro range. start= "
		          << version_range.intro_start
		          << "; end= " << version_range.intro_end << "\n";
	}

	if ((version_range.revive_start == VER_NONE &&
	     version_range.revive_end != VER_NONE) ||
	    (version_range.revive_start != VER_NONE &&
	     version_range.revive_end == VER_NONE) ||
	    (version_range.revive_start != VER_NONE &&
	     version_range.revive_start >= version_range.revive_end)) {
		ret = false;
		std::cout << "ERROR: " << symbol_str
		          << " has invalid revive range. start= "
		          << version_range.revive_start
		          << "; end= " << version_range.revive_end << "\n";
	}

	return ret;
}

bool within_version_range(const uint16_t lib_version,
                          const version_ranges& version_range)
{
	bool ret = false;
	if (version_range.intro_start <= lib_version &&
	    lib_version < version_range.intro_end) {
		ret = true;
	}
	else if (version_range.revive_start != VER_NONE &&
	         version_range.revive_start <= lib_version &&
	         lib_version < version_range.revive_end) {
		ret = true;
	}
	return ret;
}

bool match_library_db(std::map<uint32_t, symbol_result>& list,
                      const uint16_t lib_version,
                      const library_list* lib_db,
                      uint32_t xref_offset,
                      uint32_t xref_total,
                      const uint32_t lib_flags,
                      std::vector<std::string>& missing,
                      unsigned& error_count)
{
	size_t lib_db_size = lib_db->size();
	size_t found_size = 0;

	// Search registered symbols from unit test's database.
	for (library_list::const_iterator xref = lib_db->begin();
	     xref != lib_db->end();
	     xref++) {

		// Skip if not within xref range
		if (xref->first < xref_offset ||
		    xref->first >= xref_total + xref_offset) {
			lib_db_size--;
			error_count++;
			std::cout << "ERROR: XReference index is not within range: "
			          << xref->second.begin()->first << "\n";
			continue;
		}

		// If group of the symbols' range is bad, the function will output
		// error(s) then skip given symbol to verify.
		bool skip_verify = false;
		for (auto&& [symbol_str, version_range] : xref->second) {
			if (!verify_version_range(symbol_str, version_range)) {
				error_count++;
				skip_verify = true;
				continue;
			}
		}
		if (skip_verify) {
			continue;
		}

		bool within_range = false;
		for (auto&& [symbol_str, version_range] : xref->second) {
			if (within_version_range(lib_version, version_range)) {
				within_range = true;
			}
		}
		auto found_xref = list.find(xref->first);
		// If not within range, then verify if xref is also not found.
		if (!within_range) {
			lib_db_size--;
			// If xref is found, then we need to report it.
			if (found_xref != list.end()) {
				error_count++;
				std::cout << "ERROR: " << found_xref->second.symbol << " (b"
				          << std::dec << std::setfill('0') << std::setw(4)
				          << found_xref->second.build << ") is detected!\n";
			}
			continue;
		}

		// Since xref is within range, check if symbol is found.
		// If a match is not found, then we basically need to push them into
		// missing list.
		if (found_xref == list.end()) {
			std::string symbols;
			for (auto& symbol : xref->second) {
				if (!symbols.empty()) {
					symbols += ", ";
				}
				symbols += symbol.first;
			}
			missing.push_back(symbols);
			continue;
		}

		auto found_str = xref->second.find(found_xref->second.symbol);

		if (found_str == xref->second.end()) {
			/*
			// Handled by missing_library_db, so we just skip it.
			// Although, somehow D3D_DestroyResource symbol didn't show up if
			not in entry? Why? std::cout << "ERROR: Symbol is missing from unit
			test's database: "
			          << found_xref->second.symbol
			          << "\n";
			error_count++;
			*/
			continue;
		}

		// Skip if not matched library.
		if ((found_xref->second.library_flag & lib_flags) == 0) {
			continue;
		}
		found_size++;
#if _VERBOSE // Output which symbol is detected.
		std::cout << "INFO : " << found_xref->second.symbol << " (b" << std::dec
		          << std::setfill('0') << std::setw(4)
		          << found_xref->second.build << ") found!\n";
#endif
	}

	if (found_size == 0) {
		if (missing.empty()) {
			// TODO: Check if any symbols are below title's build version.
			std::cout << "ERROR: Couldn't find any recognized symbols!\n";
		}
		return false;
	}

#ifdef _VERBOSE
	std::cout << "INFO: Actual= " << lib_db->size()
	          << "; Current= " << lib_db_size << "; Found= " << found_size
	          << "\n";
#endif

	return found_size == lib_db_size;
}

void missing_library_db(std::map<uint32_t, symbol_result>& list,
                        const library_db& lib_db,
                        const uint32_t lib_flags,
                        unsigned& error_count)
{
	// Report missing symbol registrations
	for (auto&& [xref_index, xref_entry] : list) {

		unsigned match_found = 0;
		if (lib_db.min) {
			// If check xref register is missing
			auto found_xref = lib_db.min->find(xref_index);
			if (found_xref != lib_db.min->end()) {
				// If check unregistered symbol is missing
				auto found_str = found_xref->second.find(xref_entry.symbol);
				if (found_str != found_xref->second.end()) {
					match_found++;
				}
			}
		}

		if (lib_db.full) {
			// If check xref register is missing
			auto found_xref = lib_db.full->find(xref_index);
			if (found_xref != lib_db.full->end()) {
				// If check symbol register is missing
				auto found_str = found_xref->second.find(xref_entry.symbol);
				if (found_str != found_xref->second.end()) {
					match_found++;
				}
			}
		}

		// If there are duplicate match, then shame on contributor for doing
		// paste and not update new entry or making duplicate entries.
		if (match_found == 2) {
			error_count++;
			std::cout << "ERROR: Duplicate symbol registers detected: "
			          << xref_entry.symbol << "\n";
		}

		// Skip if not matched library.
		if ((xref_entry.library_flag & lib_flags) == 0) {
			if (match_found) {
				error_count++;
				std::cout << "ERROR: Symbol is not registered in right place: "
				          << xref_entry.symbol << "\n";
			}
			continue;
		}

		// Skip if not within range
		if (xref_index < lib_db.xref_offset ||
		    xref_index >= lib_db.xref_total + lib_db.xref_offset) {
			// Handled inside match_library_db function.
			continue;
		}

		if (match_found) {
			continue;
		}


		error_count++;
		std::cout << "ERROR: Unit test is missing " << xref_entry.symbol
		          << " (b" << std::dec << std::setfill('0') << std::setw(4)
		          << xref_entry.build << ") symbol register!\n";
	}
}

void run_test_verify_symbol(std::map<uint32_t, symbol_result>& symbols_list,
                            const char* lib_str,
                            const uint16_t lib_ver,
                            const uint32_t lib_flags,
                            const library_db& lib_db,
                            unsigned& full_lib_count,
                            unsigned& error_count)
{
	std::vector<std::string> symbols_missing;
	bool is_match;

	if (lib_ver == 0) {
		std::cout << "INFO: " << lib_str << " is not detected, skipping...\n\n";
		return;
	}

	missing_library_db(symbols_list, lib_db, lib_flags, error_count);

	if (lib_db.min != nullptr) {

		symbols_missing.clear();
		is_match = match_library_db(symbols_list, lib_ver, lib_db.min, lib_db.xref_offset, lib_db.xref_total, lib_flags, symbols_missing, error_count);

		if (!is_match) {
			for (auto& symbol : symbols_missing) {
				std::cout << "INFO: Title is missing one of " << symbol << "\n";
			}
			std::cout << "INFO: " << lib_str << " min = FAIL\n\n";
			return;
		}
		std::cout << "INFO: " << lib_str << " min = PASS\n";
	}

	if (lib_db.full == nullptr) {
		std::cout << "WARN: " << lib_str << " db is missing, skipping...\n\n";
		return;
	}
	symbols_missing.clear();
	is_match = match_library_db(symbols_list, lib_ver, lib_db.full, lib_db.xref_offset, lib_db.xref_total, lib_flags, symbols_missing, error_count);

	if (!is_match) {
		for (auto& symbol : symbols_missing) {
			std::cout << "INFO: Title is missing one of " << symbol << "\n";
		}
		std::cout << "INFO: " << lib_str << " full = FAIL\n\n";
		return;
	}
	full_lib_count++;
	std::cout << "INFO: " << lib_str << " full = PASS\n\n";
}

void run_test_verify_symbols(lib_versions& lib_vers,
                             std::map<uint32_t, symbol_result>& symbols_list,
                             unsigned& full_lib_count,
                             unsigned& error_count)
{
	library_db lib_db;

	getLibraryD3D8(lib_db);
	if (lib_vers.d3d8ltcg) {
		run_test_verify_symbol(symbols_list, Lib_D3D8LTCG, lib_vers.d3d8ltcg, XbSymbolLib_D3D8LTCG, lib_db, full_lib_count, error_count);
	}
	else {
		run_test_verify_symbol(symbols_list, Lib_D3D8, lib_vers.d3d8, XbSymbolLib_D3D8, lib_db, full_lib_count, error_count);
	}

	getLibraryDSOUND(lib_db);
	run_test_verify_symbol(symbols_list, Lib_DSOUND, lib_vers.dsound, XbSymbolLib_DSOUND, lib_db, full_lib_count, error_count);

	getLibraryJVS(lib_db);
	run_test_verify_symbol(symbols_list, Lib_JVS, lib_vers.jvs, XbSymbolLib_JVS, lib_db, full_lib_count, error_count);

	getLibraryXACTENG(lib_db);
	run_test_verify_symbol(symbols_list, Lib_XACTENG, lib_vers.xacteng, XbSymbolLib_XACTENG, lib_db, full_lib_count, error_count);

	getLibraryXAPILIB(lib_db);
	run_test_verify_symbol(symbols_list, Lib_XAPILIB, lib_vers.xapilib, XbSymbolLib_XAPILIB, lib_db, full_lib_count, error_count);

	getLibraryXGRAPHIC(lib_db);
	run_test_verify_symbol(symbols_list, Lib_XGRAPHC, lib_vers.xgraphic, XbSymbolLib_XGRAPHC, lib_db, full_lib_count, error_count);

	getLibraryXNET(lib_db);
	constexpr auto XbSymbolLib_XNET_flags =
	    XbSymbolLib_XNET | XbSymbolLib_XNETS | XbSymbolLib_XNETN |
	    XbSymbolLib_XONLINE | XbSymbolLib_XONLINES | XbSymbolLib_XONLINLS;
	run_test_verify_symbol(symbols_list, Lib_XNET, lib_vers.xnet, XbSymbolLib_XNET_flags, lib_db, full_lib_count, error_count);

	getLibraryXONLINE(lib_db);
	constexpr auto XbSymbolLib_XONLINE_flags =
	    XbSymbolLib_XONLINE | XbSymbolLib_XONLINES | XbSymbolLib_XONLINLS;
	run_test_verify_symbol(symbols_list, Lib_XONLINE, lib_vers.xonline, XbSymbolLib_XONLINE_flags, lib_db, full_lib_count, error_count);
}
