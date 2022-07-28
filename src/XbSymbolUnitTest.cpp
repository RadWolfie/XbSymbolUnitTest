// XbSymbolUnitTest.cpp : Defines the entry point for the console
// application.
//

#include <clocale>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <thread>

#include "Xbe.h"
#include "helper.hpp"
#include "libverify.hpp"
#include "xxhash.h"
#include <libXbSymbolDatabase.h>
#include <xref/list_xref.h>

#define _128_MiB 0x08000000

std::map<uint32_t, symbol_result> g_SymbolAddresses;
std::ios_base::fmtflags cout_fmt = std::cout.flags();
unsigned int XbSDB_test_error = 0;
unsigned int XbUnitTest_error = 0;

static const char* section_symbols = "Symbols";

#define UNITTEST_OK 0
#define UNITTEST_FAIL_INVALID_ARG 1
#define UNITTEST_FAIL_XBSDB 2
#define UNITTEST_FAIL_OPEN_FILE 3
#define UNITTEST_FAIL_INVALID_XBE 4
#define UNITTEST_FAIL_UNABLE_ALLOC_MEM 5
#define UNITTEST_FAIL_SYMBOLS_NOT_FOUND 6
#define UNITTEST_FAIL_SYMBOLS_DIFF_SIZE 7
#define UNITTEST_FAIL_SYMBOLS_NOT_MATCH 8

void pause_for_user_input()
{
	std::cout << "Press 'enter' key to continue...";
	(void)std::getchar();
}

int invalid_argument(int argc, char** argv)
{
	std::cout << "ERROR: Input correct argument as described below.\n\n"
	             "> XbSymbolCacheGenTest default.xbe\n"
	             "> XbSymbolCacheGenTest default.xbe --out [output to "
	             "specific folder]\n"
	             "> XbSymbolCacheGenTest --out [output to specific folder]"
	             " default.xbe\n";

#if _DEBUG
	// Verbose ARG output test
	while (argc > 0) {
		argc--;
		std::cout << "ARG" << argc << ": " << argv[argc] << "\n";
	}
#endif

	pause_for_user_input();
	return UNITTEST_FAIL_INVALID_ARG;
}

int output_result_XbSDB()
{
	std::cout << "XbSymbolDatabase Test: ";
	if (XbSDB_test_error == 0) {
		std::cout << "PASS\n";
		return UNITTEST_OK;
	}

	std::cout << "FAIL - " << XbSDB_test_error << " errors\n";
	return UNITTEST_FAIL_XBSDB;
}

extern void EmuOutputMessage(xb_output_message mFlag, const char* message);
extern bool VerifyXbeIsBuiltWithXDK(const xbe_header* pXbeHeader,
                                    lib_versions& lib_vers,
                                    std::filesystem::path path_xbe);
extern bool VerifyXbSymbolDatabaseFilters(const xbe_header* pXbeHeader);

extern int run_test_raw(const xbe_header* pXbeHeader);
extern int run_test_virtual(const xbe_header* pXbeHeader,
                            const uint8_t* xbe_data);

int main(int argc, char** argv)
{
	std::string path_xbe;
	int test_ret = UNITTEST_OK;
	if (argc > 2) {
		return invalid_argument(argc, argv);
	}

	if (argc == 2) {
		path_xbe = argv[1];
	}

	XbSymbolDatabase_SetOutputVerbosity(XB_OUTPUT_MESSAGE_DEBUG);
	XbSymbolDatabase_SetOutputMessage(EmuOutputMessage);
	XbSDB_test_error = XbSymbolDatabase_TestOOVPAs();

	std::cout << "Total symbols in XbSymbolDatabase: "
	          << XbSymbolDatabase_GetTotalSymbols(XbSymbolLib_ALL) << "\n";

	// Do not process xbe test verification
	if (argc == 1) {
		test_ret = output_result_XbSDB();
		std::cout << "INFO: No xbe given, unit test end.\n";
		return test_ret;
	}

	std::setlocale(LC_ALL, "English");

	std::ifstream xbeFile = std::ifstream(path_xbe, std::ios::binary);
	if (!xbeFile.is_open()) {
		std::cout << "ERROR: Unable to open the file!\n";
		pause_for_user_input();
		return UNITTEST_FAIL_OPEN_FILE;
	}

	std::string fileData = std::string(std::istreambuf_iterator<char>(xbeFile),
	                                   std::istreambuf_iterator<char>());
	std::cout << "File size: " << fileData.size() << " byte(s).\n";

	const uint8_t* xbe_data =
	    reinterpret_cast<const uint8_t*>(fileData.data());

	const xbe_header* pXbeHeader =
	    reinterpret_cast<const xbe_header*>(xbe_data);

	lib_versions lib_vers{};

	if (!VerifyXbeIsBuiltWithXDK(pXbeHeader, lib_vers, path_xbe)) {
		pause_for_user_input();
		return UNITTEST_FAIL_INVALID_XBE;
	}

	if (!VerifyXbSymbolDatabaseFilters(pXbeHeader)) {
		pause_for_user_input();
		return UNITTEST_FAIL_INVALID_XBE;
	}

	test_ret = run_test_raw(pXbeHeader);
	if (test_ret != UNITTEST_OK) {
		std::cout << "ERROR: Raw test failed!\n";
		pause_for_user_input();
		return test_ret;
	}

	std::cout << "\n";

	std::map<uint32_t, symbol_result> g_SymbolAddressesRaw = g_SymbolAddresses;

	test_ret = run_test_virtual(pXbeHeader, xbe_data);
	if (test_ret != UNITTEST_OK) {
		std::cout << "ERROR: Virtual test failed!\n";
		pause_for_user_input();
		return test_ret;
	}

	std::cout << "\n";

	std::cout << "Verifying symbols registered...\n";

	// Ensure both raw and simulated xbox environment do have symbols detected.
	if (g_SymbolAddresses.size() == 0 || g_SymbolAddressesRaw.size() == 0) {
		std::cout << "ERROR: Symbols are not detected!\n";
		pause_for_user_input();
		return UNITTEST_FAIL_SYMBOLS_NOT_FOUND;
	}

	// Then check both raw and simulated do indeed have same size.
	if (g_SymbolAddresses.size() != g_SymbolAddressesRaw.size()) {
		std::cout << "ERROR: Registered symbols is not even.\n"
		          << "INFO: Raw xbe: " << g_SymbolAddressesRaw.size()
		          << " - Sim xbox: " << g_SymbolAddresses.size() << "\n";

		// Remove all identical symbols
		for (const auto& xref : g_SymbolAddresses) {
			g_SymbolAddressesRaw.erase(xref.first);
		}
		for (const auto& xref : g_SymbolAddressesRaw) {
			g_SymbolAddresses.erase(xref.first);
		}

		// Now report what's missing compared to other.
		for (const auto& xref : g_SymbolAddresses) {
			std::cout << "ERROR: g_SymbolAddressesRaw is missing "
			          << XbSymbolDatabase_LibraryToString(
			                 xref.second.library_flag)
			          << " (b" << std::dec << std::setfill('0') << std::setw(4)
			          << xref.second.build << ") " << xref.second.addr
			          << " -> " << xref.second.symbol << "\n";
		}
		for (const auto& xref : g_SymbolAddressesRaw) {
			std::cout << "ERROR: g_SymbolAddresses is missing "
			          << XbSymbolDatabase_LibraryToString(
			                 xref.second.library_flag)
			          << " (b" << std::dec << std::setfill('0') << std::setw(4)
			          << xref.second.build << ") " << xref.second.addr
			          << " -> " << xref.second.symbol << "\n";
		}

		pause_for_user_input();
		return UNITTEST_FAIL_SYMBOLS_DIFF_SIZE;
	}
	else {
		std::cout << "INFO: Symbol registered size...OK!\n";
	}

	// Finally, check each string and addresses are the same.
	if (!std::equal(g_SymbolAddresses.begin(), g_SymbolAddresses.end(), g_SymbolAddressesRaw.begin())) {
		std::cout
		    << "ERROR: Symbol registered does not match raw vs virtual xbox\n";
		pause_for_user_input();
		return UNITTEST_FAIL_SYMBOLS_NOT_MATCH;
	}
	else {
		std::cout << "INFO: Symbol registered matching...OK!\n";
	}

	std::cout << "INFO: Scanning xbe file is completed.\n"
	          << "INFO: Verifying detected symbols against unit test's "
	             "symbols...\n\n";

	unsigned full_lib_count = 0;
	unsigned error_count = 0;
	run_test_verify_symbols(lib_vers, g_SymbolAddresses, full_lib_count, error_count);

	// Append internal errors such as EmuRegisterSymbol function's result.
	error_count += XbUnitTest_error;

	if (error_count) {
		std::cout << "XbSymbolUnitTest: FAIL - " << error_count << " errors\n";
	}

	if (full_lib_count) {
		std::cout << "XbSymbolUnitTest: Total of " << full_lib_count
		          << " full libraries found\n";
	}

	test_ret = output_result_XbSDB();

	std::cout << "INFO: Unit test end.\n";

	return test_ret;
}

void EmuOutputMessage(xb_output_message mFlag, const char* message)
{
	switch (mFlag) {
		case XB_OUTPUT_MESSAGE_INFO: {
			std::cout << "INFO   : " << message << std::endl;
			break;
		}
		case XB_OUTPUT_MESSAGE_WARN: {
			std::cout << "WARNING: " << message << std::endl;
			break;
		}
		case XB_OUTPUT_MESSAGE_ERROR: {
			std::cout << "ERROR  : " << message << std::endl;
			break;
		}
		case XB_OUTPUT_MESSAGE_DEBUG: {
			std::cout << "DEBUG  : " << message << std::endl;
			break;
		}
		default: {
			std::cout << "UNKNOWN: " << message << std::endl;
			break;
		}
	}
}

void EmuRegisterSymbol(const char* library_str,
                       uint32_t library_flag,
                       uint32_t xref_index,
                       const char* symbol_str,
                       uint32_t func_addr,
                       uint32_t build)
{
	// Report invalid index
	if (xref_index == -1) {
		std::cout
		    << "ERROR  : Symbol could not be register due to xref index is -1: "
		    << XbSymbolDatabase_LibraryToString(library_flag) << " (b"
		    << std::dec << std::setfill('0') << std::setw(4) << build << ") 0x"
		    << std::setfill('0') << std::setw(8) << std::hex << func_addr
		    << " -> " << symbol_str << "\n";
		XbUnitTest_error++;
		return;
	}
	// Ignore kernel indexes
	if (xref_index <= XREF_KT_COUNT) {
		// TODO: Should we output a warning or info message about kernel thunk
		// being output?
		return;
	}

	// Ignore registered symbol in current database.
	symbol_result hasSymbol = g_SymbolAddresses[xref_index];

	if (hasSymbol.addr != 0) {
		// But check if symbol name is different from xref entry.
		if (hasSymbol.symbol != symbol_str) {
			std::cout
			    << "ERROR  : Symbol names returned for same xref index: \n"
			    << XbSymbolDatabase_LibraryToString(hasSymbol.library_flag)
			    << " (b" << std::dec << std::setfill('0') << std::setw(4)
			    << hasSymbol.build << ") 0x" << std::setfill('0')
			    << std::setw(8) << std::hex << hasSymbol.addr << " -> "
			    << hasSymbol.symbol << "\nvs\n"
			    << XbSymbolDatabase_LibraryToString(library_flag) << " (b"
			    << std::dec << std::setfill('0') << std::setw(4) << build
			    << ") 0x" << std::setfill('0') << std::setw(8) << std::hex
			    << func_addr << " -> " << symbol_str << "\n";
			XbUnitTest_error++;
		}
		return;
	}

#ifdef _DEBUG
	// Output some details
	std::cout << "[" << std::setw(8) << std::hex << std::this_thread::get_id()
	          << "] Symbol Detected: "
	          << XbSymbolDatabase_LibraryToString(library_flag) << " (b"
	          << std::dec << std::setfill('0') << std::setw(4) << build
	          << ") 0x" << std::setfill('0') << std::setw(8) << std::hex
	          << func_addr << " -> " << symbol_str << "\n";
	std::cout.flags(cout_fmt);
#endif
	hasSymbol.addr = func_addr;
	hasSymbol.build = build;
	hasSymbol.library_flag = library_flag;
	hasSymbol.symbol = symbol_str;

	g_SymbolAddresses[xref_index] = hasSymbol;
}

static xb_xbe_type GetXbeType(const xbe_header* pXbeHeader)
{
	// Detect if the XBE is for Chihiro (Untested!) :
	// This is based on
	// https://github.com/radare/radare2/blob/7ffe2599a192bf5b9333560345f80dd97f096277/libr/bin/p/bin_xbe.c#L29
	if ((pXbeHeader->dwEntryAddr & 0xf0000000) == 0x40000000) {
		return XB_XBE_TYPE_CHIHIRO;
	}

	// Check for Debug XBE, using high bit of the kernel thunk address :
	// (DO NOT test like
	// https://github.com/radare/radare2/blob/7ffe2599a192bf5b9333560345f80dd97f096277/libr/bin/p/bin_xbe.c#L33
	// !)
	if ((pXbeHeader->dwKernelImageThunkAddr & 0x80000000) > 0) {
		return XB_XBE_TYPE_DEBUG;
	}

	// Otherwise, the XBE is a Retail build :
	return XB_XBE_TYPE_RETAIL;
}

bool VerifyXbeIsBuiltWithXDK(const xbe_header* pXbeHeader,
                             lib_versions& lib_vers,
                             std::filesystem::path path_xbe)
{
	size_t xb_start_addr =
	    reinterpret_cast<size_t>(pXbeHeader) - pXbeHeader->dwBaseAddr;
	xbe_library_version* pLibraryVersion = nullptr;
	xbe_certificate* pCertificate = nullptr;
	xbe_section_header* pSections = nullptr;

	//
	// initialize Microsoft XDK scanning
	//

	if (pXbeHeader->dwMagic != 'HEBX') {
		std::cout << "ERROR: Xbe does not have valid magic!\n";
		return false;
	}

	if (pXbeHeader->pLibraryVersionsAddr != 0) {
		pLibraryVersion = reinterpret_cast<xbe_library_version*>(
		    xb_start_addr + pXbeHeader->pLibraryVersionsAddr);
	}
	else {
		std::cout << "ERROR: Xbe does not contain library versions!\n";
		return false;
	}

	if (pXbeHeader->pCertificateAddr != 0) {
		pCertificate = reinterpret_cast<xbe_certificate*>(
		    xb_start_addr + pXbeHeader->pCertificateAddr);
	}
	else {
		std::cout << "ERROR: Xbe does not contain certificate pointer!\n";
		return false;
	}

	std::cout << "INFO: Detected Microsoft XDK application...\n";

	uint16_t buildVersion = 0;
	char tAsciiTitle[40] = "Unknown";
	std::wcstombs(tAsciiTitle, pCertificate->wszTitleName, sizeof(tAsciiTitle));
	pSections = reinterpret_cast<xbe_section_header*>(
	    xb_start_addr + pXbeHeader->pSectionHeadersAddr);
	uint32_t sectionSize = pXbeHeader->dwSections;
	const char* section_str;

	// Output Symbol Database version
	std::cout << "XbSymbolDatabase_LibraryVersion: "
	          << XbSymbolDatabase_LibraryVersion() << "\n";

	// Store Certificate Details
	std::cout << "Name                  : " << tAsciiTitle << "\n";
	std::cout << "TitleID               : "
	          << FormatTitleId(pCertificate->dwTitleId) << "\n";
	std::cout << "Region                : " << pCertificate->dwGameRegion
	          << "\n";

	// Hash the loaded XBE's header, use it as a filename
	uint32_t uiHash = XXH32((void*)pXbeHeader, sizeof(xbe_header), 0);
	std::cout << "Xbe header hash       : " << std::hex << uiHash << "\n";
	std::cout.flags(cout_fmt);

	// Store Library Details
	for (uint32_t i = 0; i < pXbeHeader->dwLibraryVersions; i++) {
		std::string LibraryName(pLibraryVersion[i].szName,
		                        pLibraryVersion[i].szName + 8);
		std::cout << "Library Name[" << std::setw(2) << i
		          << "]      : " << LibraryName << " (b" << std::setw(4)
		          << pLibraryVersion[i].wBuildVersion << "." << std::setw(0)
		          << pLibraryVersion[i].wFlags.QFEVersion << ")\n";

		if (buildVersion < pLibraryVersion[i].wBuildVersion) {
			buildVersion = pLibraryVersion[i].wBuildVersion;
		}

		// Translate string to flag for quicker assignment.
		uint32_t lib_flag = XbSymbolDatabase_LibraryToFlag(LibraryName.c_str());
		switch (lib_flag) {
			case XbSymbolLib_D3D8:
				lib_vers.d3d8 = pLibraryVersion[i].wBuildVersion;
				break;
			case XbSymbolLib_D3D8LTCG:
				lib_vers.d3d8ltcg = pLibraryVersion[i].wBuildVersion;
				break;
#if 0
			case XbSymbolLib_D3DX8:
				lib_vers.d3dx8 = pLibraryVersion[i].wBuildVersion;
				break;
#endif
			// TODO: Need to add additional check since 4039 is ommited out.
			case XbSymbolLib_DSOUND:
				lib_vers.dsound = pLibraryVersion[i].wBuildVersion;
				break;
			case XbSymbolLib_XACTENG:
				lib_vers.xacteng = pLibraryVersion[i].wBuildVersion;
				break;
			case XbSymbolLib_XAPILIB:
				lib_vers.xapilib = pLibraryVersion[i].wBuildVersion;
				break;
			case XbSymbolLib_XGRAPHC:
				lib_vers.xgraphic = pLibraryVersion[i].wBuildVersion;
				break;
			case XbSymbolLib_XNET:
			case XbSymbolLib_XNETN:
			case XbSymbolLib_XNETS:
				lib_vers.xnet = pLibraryVersion[i].wBuildVersion;
				// Technically, it is combined with XONLINE library. So, check
				// if XONLINE doesn't exist then force check.
				if (!lib_vers.xonline) {
					lib_vers.xonline = pLibraryVersion[i].wBuildVersion;
				}
				break;
			case XbSymbolLib_XONLINE:
			case XbSymbolLib_XONLINES:
			case XbSymbolLib_XONLINLS:
				lib_vers.xonline = pLibraryVersion[i].wBuildVersion;
				// Technically, it is combined with XNET library. So, check if
				// XNET doesn't exist then force check.
				if (!lib_vers.xnet) {
					lib_vers.xnet = pLibraryVersion[i].wBuildVersion;
				}
				break;
		}
	}
	std::cout.flags(cout_fmt);

	// Force verify if DSOUND section do exist, then append.
	for (unsigned int i = 0; i < sectionSize; i++) {
		section_str = reinterpret_cast<const char*>(
		    xb_start_addr + pSections[i].SectionNameAddr);

		if (std::strncmp(section_str, Lib_DSOUND, 8) == 0) {
			lib_vers.dsound = buildVersion;
			break;
		}
	}

	// Force verify if title is chihiro or contains "boot.id" folder, then append.
	if (GetXbeType(pXbeHeader) == XB_XBE_TYPE_CHIHIRO ||
	    std::filesystem::exists(path_xbe.parent_path() / "boot.id")) {
		lib_vers.jvs = buildVersion;
	}

	std::cout << "BuildVersion          : " << buildVersion << "\n";

	std::cout << "\n";
	return true;
}


bool GetXbSymbolDatabaseFilters(const xbe_header* pXbeHeader,
                                bool is_raw,
                                XbSDBLibraryHeader& library_output,
                                XbSDBSectionHeader& section_output)
{
	std::string error_msg = "unknown";

	library_output.count =
	    XbSymbolDatabase_GenerateLibraryFilter(pXbeHeader, nullptr);

	if (library_output.count != 0) {
		library_output.filters = new XbSDBLibrary[library_output.count];
	}
	else {
		error_msg = "library_input.count variable return 0.";
		goto scanError;
	}

	if (library_output.filters == nullptr) {
		error_msg =
		    "Unable to allocate buffer for library_input.filters variable.";
		goto scanError;
	}

	(void)XbSymbolDatabase_GenerateLibraryFilter(pXbeHeader, &library_output);

	section_output.count =
	    XbSymbolDatabase_GenerateSectionFilter(pXbeHeader, nullptr, is_raw);

	if (section_output.count != 0) {
		section_output.filters = new XbSDBSection[section_output.count];
	}
	else {
		error_msg = "section_input.count variable return 0.";
		goto scanError;
	}

	if (section_output.filters == nullptr) {
		error_msg =
		    "Unable to allocate buffer for section_input.filters variable.";
		goto scanError;
	}

	(void)XbSymbolDatabase_GenerateSectionFilter(pXbeHeader, &section_output, is_raw);
	return true;

scanError:
	if (library_output.filters) {
		delete[] library_output.filters;
		library_output.filters = nullptr;
	}

	if (section_output.filters) {
		delete[] section_output.filters;
		section_output.filters = nullptr;
	}

	std::cout << "ERROR: GetXbSymbolDatabaseFilters failed for: " << error_msg
	          << "\n";
	pause_for_user_input();
	return false;
}

bool VerifyXbSymbolDatabaseFilters(const xbe_header* pXbeHeader)
{
	XbSDBLibraryHeader library_input = {};
	XbSDBSectionHeader section_input = {};

	std::cout << "Getting library and section filters...\n";

	if (!GetXbSymbolDatabaseFilters(pXbeHeader, true, library_input, section_input)) {
		return false;
	}

	// Verbose both library and section filters.
	std::cout << "Outputting library filters...\n";

	unsigned int i;
	for (i = 0; i < library_input.count; i++) {
		std::stringstream str_format;
		str_format << "Library[" << i << "]\n    name    = "
		           << std::string().assign(library_input.filters[i].name, 0, 8)
		           << ";\n    build   = " << std::dec
		           << library_input.filters[i].build_version
		           << ";\n    qre ver = 0x" << std::hex
		           << library_input.filters[i].qfe_version
		           << ";\n    flag    = 0x" << std::hex
		           << library_input.filters[i].flag << ";\n";
		std::cout << str_format.str();
	}

	std::cout << "\nOutputting section filters...\n";

	for (i = 0; i < section_input.count; i++) {
		std::stringstream str_format;
		str_format << "Section[" << i << "]\n     name        = "
		           << std::string().assign(section_input.filters[i].name, 0, 8)
		           << ";\n     virt addr   = 0x" << std::hex
		           << section_input.filters[i].xb_virt_addr
		           << ";\n     buffer addr = 0x" << std::hex
		           << section_input.filters[i].buffer_lower
		           << ";\n     buffer size = 0x" << std::hex
		           << section_input.filters[i].buffer_size << ";\n";
		std::cout << str_format.str();
	}

	delete[] library_input.filters;
	delete[] section_input.filters;

	std::cout << "\n";

	return true;
}

void ScanXbe(const xbe_header* pXbeHeader, bool is_raw)
{
	std::string error_msg = "unknown";

	// Ensure nothing is still in g_SymbolAddresses before new scan process
	// start.
	g_SymbolAddresses.clear();

	XbSymbolContextHandle pHandle;
	XbSDBLibraryHeader library_input = {};
	XbSDBSectionHeader section_input = {};

	if (!GetXbSymbolDatabaseFilters(pXbeHeader, is_raw, library_input, section_input)) {
		return;
	}

	std::vector<std::thread> threads;
	auto ScanLibraryFunc = [](XbSymbolContextHandle pHandle,
	                          const XbSDBLibrary* library) -> void {
		unsigned int LastUnResolvedXRefs = 0, CurrentUnResolvedXRefs = 0;
		bool xref_first_pass =
		    true; // Set to true for search speed optimization
		do {
			LastUnResolvedXRefs = CurrentUnResolvedXRefs;

			// Start library scan against symbol database we want to
			// search for address of symbols and xreferences.
			CurrentUnResolvedXRefs +=
			    XbSymbolContext_ScanLibrary(pHandle, library, xref_first_pass);

			xref_first_pass = false;
		} while (LastUnResolvedXRefs < CurrentUnResolvedXRefs);
	};

	xbaddr kt_addr = XbSymbolDatabase_GetKernelThunkAddress(pXbeHeader);

	if (!XbSymbolDatabase_CreateXbSymbolContext(&pHandle, EmuRegisterSymbol, library_input, section_input, kt_addr)) {
		error_msg = "Unable to create XbSymbolContext handle.";
		goto scanError;
	}

	// delete[] library_input.filters;
	// library_input.filters = nullptr;
	delete[] section_input.filters;
	section_input.filters = nullptr;

	// For output various false detection messages.
	XbSymbolContext_SetBypassBuildVersionLimit(pHandle, true);
	XbSymbolContext_SetContinuousSigScan(pHandle, true);
	XbSymbolContext_SetFirstDetectAddressOnly(pHandle, true);

	XbSymbolContext_ScanManual(pHandle);

	// TODO: Replace below to use XbSymbolContext_ScanLibrary function to speed
	// up scan process. Either by replace toolset to CLANG or wait until MSVC
	// support C11 standard. Perhaps use macro to detect compiler selection?
	// Then toggle between the two.
	// XbSymbolContext_ScanAllLibraryFilter(pHandle);

	for (unsigned i = 0; i < library_input.count; i++) {
		threads.emplace_back(
		    std::thread(ScanLibraryFunc, pHandle, &library_input.filters[i]));
	}

	for (auto& thread : threads) {
		thread.join();
	}
	delete[] library_input.filters;
	library_input.filters = nullptr;

	XbSymbolContext_RegisterXRefs(pHandle);

	XbSymbolContext_Release(pHandle);

	std::cout << "\n";

	return;

scanError:
	if (library_input.filters) {
		delete[] library_input.filters;
	}

	if (section_input.filters) {
		delete[] section_input.filters;
	}

	std::cout << "ERROR: ScanXbe failed for: " << error_msg << "\n";
	pause_for_user_input();
}

int run_test_raw(const xbe_header* pXbeHeader)
{
	std::cout << "Scanning raw xbe file...\n";

	ScanXbe(pXbeHeader, true);

	std::cout << "Scanning raw xbe file... COMPLETE!\n";

	return UNITTEST_OK;
}

int run_test_virtual(const xbe_header* pXbeHeader, const uint8_t* xbe_data)
{
	void* xb_environment = std::calloc(_128_MiB, 1);

	const uint8_t* xb_env_data =
	    reinterpret_cast<const uint8_t*>(xb_environment);

	if (xb_environment == (void*)0) {
		std::cout
		    << "ERROR: Unable to allocate 128 MiB of virtual xbox memory!\n";
		pause_for_user_input();
		return UNITTEST_FAIL_UNABLE_ALLOC_MEM;
	}

	std::cout << "Loading sections into virtual xbox memory...\n";

	std::memcpy((uint8_t*)xb_environment + pXbeHeader->dwBaseAddr, pXbeHeader, sizeof(xbe_header));

	if (sizeof(xbe_header) < pXbeHeader->dwSizeofHeaders) {

		uint32_t extra_size = pXbeHeader->dwSizeofHeaders - sizeof(xbe_header);
		std::memcpy((uint8_t*)xb_environment + pXbeHeader->dwBaseAddr +
		                sizeof(xbe_header),
		            (uint8_t*)xbe_data + sizeof(xbe_header),
		            extra_size);
	}

	xbe_section_header* pSectionHeaders =
	    (xbe_section_header*)((uint8_t*)xb_environment +
	                          pXbeHeader->pSectionHeadersAddr);

	// Load sections into virtualize xbox memory
	for (uint32_t s = 0; s < pXbeHeader->dwSections; s++) {

		if (pSectionHeaders[s].dwFlags.bPreload) {

			if (pSectionHeaders[s].dwVirtualAddr +
			        pSectionHeaders[s].dwVirtualSize >
			    _128_MiB) {
				std::cout << "ERROR: section request virtual size allocation "
				             "outside 128MiB "
				             "range, skipping...\n";
				continue;
			}

			if (pSectionHeaders[s].dwVirtualAddr +
			        pSectionHeaders[s].dwSizeofRaw >
			    _128_MiB) {
				std::cout << "ERROR: section request raw size allocation "
				             "outside 128MiB "
				             "range, skipping...\n";
				continue;
			}

			std::memset((uint8_t*)xb_environment +
			                pSectionHeaders[s].dwVirtualAddr,
			            0,
			            pSectionHeaders[s].dwVirtualSize);

			std::memcpy((uint8_t*)xb_environment +
			                pSectionHeaders[s].dwVirtualAddr,
			            xbe_data + pSectionHeaders[s].dwRawAddr,
			            pSectionHeaders[s].dwSizeofRaw);

			// Let XbSymbolDatabase know this section is loaded.
			pSectionHeaders[s].dwSectionRefCount++;
			std::cout << "Section preloaded: "
			          << (const char*)((uint8_t*)xb_environment +
			                           pSectionHeaders[s].SectionNameAddr)
			          << "\n";
		}
	}

	std::cout << "Scanning virtual xbox environment...\n";

	ScanXbe((xbe_header*)((uint8_t*)xb_environment + pXbeHeader->dwBaseAddr),
	        false);

	std::free(xb_environment);

	std::cout << "Scanning virtual xbox environment... COMPLETE!\n";

	return UNITTEST_OK;
}
