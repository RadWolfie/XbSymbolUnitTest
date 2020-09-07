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

static const std::map<std::string, version_ranges> database_full = {
    {"CXo_XOnlineLogon", {4361, VER_MAX, VER_NONE, VER_NONE}},
    {"XOnlineLogon", {4361, VER_MAX, VER_NONE, VER_NONE}},
    {"CXo_XOnlineMatchSearch", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"XOnlineMatchSearch", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"XOnlineMatchSearchResultsLen_Body", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"XOnlineMatchSearchResultsLen", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"CXo_XOnlineMatchSearchGetResults", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"XOnlineMatchSearchGetResults", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"CXo_XOnlineMatchSessionUpdate", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"XOnlineMatchSessionUpdate", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"CXo_XOnlineMatchSessionCreate", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"XOnlineMatchSessionCreate", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"XoUpdateLaunchNewImageInternal", {4627, VER_MAX, VER_NONE, VER_NONE}},
};

void getLibraryXONLINE(const library_list **db_min, const library_list **db_full)
{
	*db_min = nullptr; //&database_min;
	*db_full = &database_full;
}
