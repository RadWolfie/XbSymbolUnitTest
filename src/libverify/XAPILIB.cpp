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

static const std::map<std::string, version_ranges> database_min = {};

static const std::map<std::string, version_ranges> database_full = {
    {"_cinit", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"_rtinit", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XapiFormatObjectAttributes", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XapiCallThreadNotifyRoutines", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XLaunchNewImageA", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"UnhandledExceptionFilter", {3911, VER_MAX, VER_NONE, VER_NONE}},

    {"GetLastError", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"SetLastError", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XapiBootToDash", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XapiSetLastNTError", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XapiThreadStartup", {3911, VER_MAX, VER_NONE, VER_NONE}},

    {"CreateMutexA", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"CreateThread", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"ExitThread", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"MoveFileA", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"SwitchToThread", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XapiInitProcess", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XCalculateSignatureBeginEx", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XCalculateSignatureBegin", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"ConvertThreadToFiber", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"CreateFiber", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"DeleteFiber", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"GetExitCodeThread", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"GetOverlappedResult", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"GetThreadPriority", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"GetTimeZoneInformation", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"GetTypeInformation", {4134, VER_MAX, VER_NONE, VER_NONE}},
    {"OutputDebugStringA", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"OutputDebugStringW", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"QueueUserAPC", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"QueryPerformanceCounter", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"RaiseException", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"SetThreadPriority", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"SetThreadPriorityBoost", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"SignalObjectAndWait", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"SwitchToFiber", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XAutoPowerDownResetTimer", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XFormatUtilityDrive", {4242, VER_MAX, VER_NONE, VER_NONE}},
    {"XGetDeviceChanges", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGetDeviceEnumerationStatus", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"XGetDevices", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGetLaunchInfo", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XGetSectionSize", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XID_fCloseDevice", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XInitDevices", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XInputClose", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XInputGetCapabilities", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XInputGetDeviceDescription", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"XInputGetState", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XInputOpen", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XInputPoll", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XInputSetState", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XMountAlternateTitleA", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XMountMUA", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XMountMURootA", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XMountUtilityDrive", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XRegisterThreadNotifyRoutine", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XSetProcessQuantumLength", {4134, VER_MAX, VER_NONE, VER_NONE}},
    {"XUnmountAlternateTitleA", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"XapiFiberStartup", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"timeKillEvent", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"timeSetEvent", {3911, VER_MAX, VER_NONE, VER_NONE}},
};

void getLibraryXAPILIB(const library_list **db_min,
                       const library_list **db_full)
{
	*db_min = nullptr; //&database_min;
	*db_full = &database_full;
}
