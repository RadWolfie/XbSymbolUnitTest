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

static const std::map<std::string, version_ranges> database_min = {
    {"JVS_SendCommand_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsBACKUP_Read_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsBACKUP_Write_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsEEPROM_Read_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsEEPROM_Write_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareDownload_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareUpload_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsNodeReceivePacket_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsNodeSendPacket_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsRTC_Read_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsRTC_Write_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScFirmwareDownload_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScFirmwareUpload_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScReceiveMidi_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScReceiveRs323c_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScSendMidi_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScSendRs323c_String", {4831, VER_MAX, VER_NONE, VER_NONE}},
};

static const std::map<std::string, version_ranges> database_full = {
    {"JVS_SendCommand", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JVS_SendCommand2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JVS_SendCommand3", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsBACKUP_Read", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsBACKUP_Read2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsBACKUP_Read3", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsBACKUP_Write", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsBACKUP_Write2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsEEPROM_Read", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsEEPROM_Read2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsEEPROM_Read3", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsEEPROM_Write", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsEEPROM_Write2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsEEPROM_Write3", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareDownload", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareDownload2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareDownload3", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareDownload4", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareUpload", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareUpload2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareUpload3", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsFirmwareUpload4", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsNodeReceivePacket", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsNodeReceivePacket2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsNodeSendPacket", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsNodeSendPacket2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsRTC_Read", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsRTC_Read2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsRTC_Read3", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsRTC_Write", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsRTC_Write2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScFirmwareDownload", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScFirmwareDownload2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScFirmwareDownload3", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScFirmwareDownload4", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScFirmwareUpload", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScFirmwareUpload2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScFirmwareUpload3", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScReceiveMidi", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScReceiveMidi2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScReceiveRs323c", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScReceiveRs323c2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScSendMidi", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScSendMidi2", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScSendRs323c", {4831, VER_MAX, VER_NONE, VER_NONE}},
    {"JvsScSendRs323c2", {4831, VER_MAX, VER_NONE, VER_NONE}},
};

void getLibraryJVS(const library_list **db_min, const library_list **db_full)
{
	*db_min = &database_min;
	*db_full = &database_full;
}
