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
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "libverify.hpp"
#include "libverify/unittest.hpp"

typedef std::map<std::string, uint32_t>::iterator list_iterator;

typedef std::vector<std::string>::iterator missing_iterator;

bool verify_version_range(const std::string &symbol_str,
                          version_ranges &version_range)
{
	bool ret = true;
	if (version_range.intro_start == VER_NONE ||
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

bool match_library_db(std::map<std::string, uint32_t> &list,
                      uint16_t lib_version, const library_list *lib_db,
                      std::vector<std::string> &missing)
{
	size_t lib_db_size = lib_db->size();
	size_t found_size = 0;
	list_iterator found_str;
	list_iterator list_begin = list.begin();
	list_iterator list_end = list.end();
	version_ranges version_range;

	for (library_list::const_iterator item = lib_db->begin();
	     item != lib_db->end(); item++) {

		version_range = item->second;
		bool skip_verify = true;

		// If the range is bad, the function will output error(s)
		// then skip the symbol verify.
		if (!verify_version_range(item->first, version_range)) {
			continue;
		}

		found_str = list.find(item->first);

		if (version_range.intro_start <= lib_version &&
		    lib_version < version_range.intro_end) {
			skip_verify = false;
		}
		else if (version_range.revive_start != VER_NONE &&
		         version_range.revive_start <= lib_version &&
		         lib_version < version_range.revive_end) {
			skip_verify = false;
		}

		// Reduce and skip verify when version
		if (skip_verify) {
			lib_db_size--;

			// Make sure the symbol is not found
			if (found_str != list_end) {

				// TODO: Keep it?
				missing.push_back(item->first);

				std::cout << "ERROR: Symbol, " << found_str->first
				          << ", is detected!\n";
			}
			continue;
		}

		// Finally, check if symbol exist.
		if (found_str != list_end) {
			found_size++;
		}
		// If not, then add to missing list.
		else {
			missing.push_back(item->first);
		}
	}

	if (found_size == 0) {
		return false;
	}

#ifdef _VERBOSE
	std::cout << "INFO: Actual= " << lib_db->size()
	          << "; Current= " << lib_db_size << "; Found= " << found_size
	          << "\n";
#endif

	return found_size == lib_db_size;
}

void run_test_verify_symbol(std::map<std::string, uint32_t> &symbol_addr,
                            const char *lib_str, uint16_t lib_ver,
                            const library_list *db_min,
                            const library_list *db_full)
{
	std::vector<std::string> symbol_missing;
	bool is_match;

	if (lib_ver == 0) {
		std::cout << "INFO: " << lib_str << " is not detected, skipping...\n";
		return;
	}

	symbol_missing.clear();
	is_match = match_library_db(symbol_addr, lib_ver, db_min, symbol_missing);

	if (!is_match) {
		std::cout << "INFO: " << lib_str << " min = FAIL\n";
		for (missing_iterator item = symbol_missing.begin();
		     item != symbol_missing.end(); item++) {
			std::cout << "INFO: Missing " << *item << "\n";
		}
		return;
	}
	std::cout << "INFO: " << lib_str << " min = PASS\n";

	symbol_missing.clear();
	is_match = match_library_db(symbol_addr, lib_ver, db_full, symbol_missing);

	if (!is_match) {
		for (missing_iterator item = symbol_missing.begin();
		     item != symbol_missing.end(); item++) {
			std::cout << "INFO: Missing " << *item << "\n";
		}
		std::cout << "INFO: " << lib_str << " full = FAIL\n";
		return;
	}
	std::cout << "INFO: " << lib_str << " full = PASS\n";
}

void run_test_verify_symbols(lib_versions &lib_vers,
                             std::map<std::string, uint32_t> &symbol_addr)
{
	const library_list *db_min;
	const library_list *db_full;
}
