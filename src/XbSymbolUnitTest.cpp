// XbSymbolCacheGenTest.cpp : Defines the entry point for the console
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

#include "XbSymbolDatabase.h"
#include "Xbe.h"
#include "helper.hpp"
#include "xxhash.h"

#define _128_MiB 0x08000000

std::map<std::string, uint32_t> g_SymbolAddresses;
std::ios_base::fmtflags cout_fmt = std::cout.flags();

static const char *section_symbols = "Symbols";

void pause_for_user_input()
{
	std::cout << "Press 'enter' key to continue...";
	(void)std::getchar();
}

int invalid_argument(int argc, char **argv)
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
	return 1;
}

extern void EmuOutputMessage(xb_output_message mFlag, const char *message);
extern bool VerifyXbeIsBuildWithXDK(const xbe_header *pXbeHeader);
extern void ScanXbe(const xbe_header *pXbeHeader, bool is_raw);

unsigned int run_test_raw(const xbe_header *pXbeHeader)
{
	std::cout << "Scanning raw xbe file...\n";

	ScanXbe(pXbeHeader, true);

	std::cout << "Scanning raw xbe file... COMPLETE!\n";

	return 0;
}

unsigned int run_test_virtual(const xbe_header *pXbeHeader,
                              const uint8_t *xbe_data)
{
	void *xb_environment = std::calloc(_128_MiB, 1);

	const uint8_t *xb_env_data =
	    reinterpret_cast<const uint8_t *>(xb_environment);

	if (xb_environment == (void *)0) {
		std::cout
		    << "ERROR: Unable to allocate 128 MiB of virtual xbox memory!\n";
		pause_for_user_input();
		return 3;
	}

	std::cout << "Loading sections into virtual xbox memory...\n";

	std::memcpy((uint8_t *)xb_environment + pXbeHeader->dwBaseAddr, pXbeHeader,
	            sizeof(xbe_header));

	if (sizeof(xbe_header) < pXbeHeader->dwSizeofHeaders) {

		uint32_t extra_size = pXbeHeader->dwSizeofHeaders - sizeof(xbe_header);
		std::memcpy((uint8_t *)xb_environment + pXbeHeader->dwBaseAddr +
		                sizeof(xbe_header),
		            (uint8_t *)xbe_data + sizeof(xbe_header), extra_size);
	}

	xbe_section_header *pSectionHeaders =
	    (xbe_section_header *)((uint8_t *)xb_environment +
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

			std::memset((uint8_t *)xb_environment +
			                pSectionHeaders[s].dwVirtualAddr,
			            0, pSectionHeaders[s].dwVirtualSize);

			std::memcpy((uint8_t *)xb_environment +
			                pSectionHeaders[s].dwVirtualAddr,
			            xbe_data + pSectionHeaders[s].dwRawAddr,
			            pSectionHeaders[s].dwSizeofRaw);

			// Let XbSymbolDatabase know this section is loaded.
			pSectionHeaders[s].dwSectionRefCount++;
			std::cout << "Section preloaded: "
			          << (const char *)((uint8_t *)xb_environment +
			                            pSectionHeaders[s].SectionNameAddr)
			          << "\n";
		}
	}

	std::cout << "Scanning virtual xbox environment...\n";

	ScanXbe((xbe_header *)((uint8_t *)xb_environment + pXbeHeader->dwBaseAddr),
	        false);

	std::free(xb_environment);

	std::cout << "Scanning virtual xbox environment... COMPLETE!\n";

	return 0;
}

int main(int argc, char **argv)
{
	std::string path_xbe;
	if (argc > 2) {
		return invalid_argument(argc, argv);
	}

	if (argc == 2) {
		path_xbe = argv[1];
	}

	XbSymbolSetOutputVerbosity(XB_OUTPUT_MESSAGE_DEBUG);
	XbSymbolSetOutputMessage(EmuOutputMessage);
	XbSymbolDataBaseTestOOVPAs();

	// Do not process xbe test verification
	if (argc == 1) {
		std::cout << "INFO: No xbe given, unit test end.\n";
		return 0;
	}

	// For output various false detection messages.
	XbSymbolBypassBuildVersionLimit(true);
	XbSymbolContinuousSigScan(true);
	XbSymbolFirstDetectAddressOnly(true);

	std::setlocale(LC_ALL, "English");

	std::ifstream xbeFile = std::ifstream(path_xbe, std::ios::binary);
	if (!xbeFile.is_open()) {
		std::cout << "ERROR: Unable to open the file!\n";
		pause_for_user_input();
		return 2;
	}

	std::string fileData = std::string(std::istreambuf_iterator<char>(xbeFile),
	                                   std::istreambuf_iterator<char>());
	std::cout << "File size: " << fileData.size() << " byte(s).\n";

	const uint8_t *xbe_data =
	    reinterpret_cast<const uint8_t *>(fileData.data());

	const xbe_header *pXbeHeader =
	    reinterpret_cast<const xbe_header *>(xbe_data);

	if (!VerifyXbeIsBuildWithXDK(pXbeHeader)) {
		pause_for_user_input();
		return 3;
	}

	unsigned int test_ret = run_test_raw(pXbeHeader);
	if (test_ret != 0) {
		std::cout << "ERROR: Raw test failed!\n";
		pause_for_user_input();
		return test_ret;
	}

	std::cout << "\n";

	std::map<std::string, uint32_t> g_SymbolAddressesRaw = g_SymbolAddresses;

	test_ret = run_test_virtual(pXbeHeader, xbe_data);
	if (test_ret != 0) {
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
		return 4;
	}

	// Then check both raw and simulated do indeed have same size.
	if (g_SymbolAddresses.size() != g_SymbolAddressesRaw.size()) {
		std::cout << "ERROR: Registered symbols is not even.\n"
		          << "INFO: Raw xbe: " << g_SymbolAddressesRaw.size()
		          << " - Sim xbox: " << g_SymbolAddresses.size() << "\n";
		pause_for_user_input();
		return 5;
	}
	else {
		std::cout << "INFO: Symbol registered size...OK!\n";
	}

	// Finally, check each string and addresses are the same.
	if (!std::equal(g_SymbolAddresses.begin(), g_SymbolAddresses.end(),
	                g_SymbolAddressesRaw.begin())) {
		std::cout
		    << "ERROR: Symbol registered does not match raw vs virtual xbox\n";
		pause_for_user_input();
		return 6;
	}
	else {
		std::cout << "INFO: Symbol registered matching...OK!\n";
	}

	// TODO: Need a function for symbol checking. Will be best to put them in
	// their own source code file than in here.

#if 0
	pause_for_user_input();
#else
	std::cout << "INFO: Scanning xbe file is completed.\n";
#endif

	std::cout << "INFO: Unit test end.\n";

	return 0;
}

void EmuOutputMessage(xb_output_message mFlag, const char *message)
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
		case XB_OUTPUT_MESSAGE_DEBUG:
		default: {
#ifdef _DEBUG_TRACE
			std::cout << "DEBUG  : " << message << std::endl;
#endif
			break;
		}
	}
}

void EmuRegisterSymbol(const char *library_str, uint32_t library_flag,
                       const char *symbol_str, uint32_t func_addr,
                       uint32_t build)
{
	// Ignore registered symbol in current database.
	uint32_t hasSymbol = g_SymbolAddresses[symbol_str];

	if (hasSymbol != 0) {
		return;
	}

#ifdef _DEBUG
	// Output some details
	std::cout << "Symbol Detected: (b" << std::dec << std::setfill('0')
	       << std::setw(4) << build << ") 0x" << std::setfill('0')
	       << std::setw(8) << std::hex << func_addr << " -> " << symbol_str
	       << "\n";
	std::cout.flags(cout_fmt);
#endif

	g_SymbolAddresses[symbol_str] = func_addr;
}

bool VerifyXbeIsBuildWithXDK(const xbe_header *pXbeHeader)
{
	size_t xb_start_addr =
	    reinterpret_cast<size_t>(pXbeHeader) - pXbeHeader->dwBaseAddr;
	xbe_library_version *pLibraryVersion = nullptr;
	xbe_certificate *pCertificate = nullptr;

	//
	// initialize Microsoft XDK scanning
	//

	if (pXbeHeader->dwMagic != 'HEBX') {
		std::cout << "ERROR: Xbe does not have valid magic!\n";
		return false;
	}

	if (pXbeHeader->pLibraryVersionsAddr != 0) {
		pLibraryVersion = reinterpret_cast<xbe_library_version *>(
		    xb_start_addr + pXbeHeader->pLibraryVersionsAddr);
	}
	else {
		std::cout << "ERROR: Xbe does not contain library versions!\n";
		return false;
	}

	if (pXbeHeader->pCertificateAddr != 0) {
		pCertificate = reinterpret_cast<xbe_certificate *>(
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

	// Output Symbol Database version
	std::cout << "XbSymbolLibraryVersion: " << XbSymbolLibraryVersion() << "\n";

	// Store Certificate Details
	std::cout << "Name                  : " << tAsciiTitle << "\n";
	std::cout << "TitleID               : "
	          << FormatTitleId(pCertificate->dwTitleId) << "\n";
	std::cout << "Region                : " << pCertificate->dwGameRegion
	          << "\n";

	// Hash the loaded XBE's header, use it as a filename
	uint32_t uiHash = XXH32((void *)pXbeHeader, sizeof(xbe_header), 0);
	std::cout << "Xbe header hash       : " << std::hex << uiHash << "\n";
	std::cout.flags(cout_fmt);

	// Store Library Details
	for (uint32_t i = 0; i < pXbeHeader->dwLibraryVersions; i++) {
		std::string LibraryName(pLibraryVersion[i].szName,
		                        pLibraryVersion[i].szName + 8);
		std::cout << "Library Name[" << std::setw(2) << i
		          << "]      : " << LibraryName << "\n";

		if (buildVersion < pLibraryVersion[i].wBuildVersion) {
			buildVersion = pLibraryVersion[i].wBuildVersion;
		}
	}
	std::cout.flags(cout_fmt);

	std::cout << "BuildVersion          : " << buildVersion << "\n";
	return true;
}

void ScanXbe(const xbe_header *pXbeHeader, bool is_raw)
{
	bool scan_ret;

	// Ensure nothing is still in g_SymbolAddresses before new scan process
	// start.
	g_SymbolAddresses.clear();

	scan_ret = XbSymbolScan(pXbeHeader, EmuRegisterSymbol, is_raw);

	if (!scan_ret) {
		std::cout << "ERROR: XbSymbolScan failed!\n";
		pause_for_user_input();
		return;
	}

	std::cout << "\n";
}
