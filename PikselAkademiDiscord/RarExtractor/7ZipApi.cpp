#include "7ZipApi.h"
#include "../LazyImporter/lazy.h"
bool ZipdenCikar(const std::string& zipKonum, const std::string& cikisKlasoru)
{
	if (c(GetFileAttributesA)(zipKonum.c_str()) == INVALID_FILE_ATTRIBUTES)
	{
		c(printf)("[-] ZIP bulunamadi: %s\n", zipKonum.c_str());
		return false;
	}
	c(CreateDirectoryA)(cikisKlasoru.c_str(), nullptr);

	std::string _7ZipExe = "C:\\Program Files\\7-Zip\\7z.exe";

	if (c(GetFileAttributesA)(_7ZipExe.c_str()) == INVALID_FILE_ATTRIBUTES)
	{
		c(printf)("[-] 7z.exe bulunamadi\n");
		return false;
	}

	std::string cmd = "\"" + _7ZipExe + "\" x \"" + zipKonum + "\" -o\"" + cikisKlasoru + "\" -y";

	c(printf)("[*] CMD: %s\n", cmd.c_str());
	STARTUPINFOA si{};
	PROCESS_INFORMATION pi{};
	si.cb = sizeof(si);
	BOOL ok = c(CreateProcessA)(nullptr, &cmd[0], nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi);
	if (!ok)
	{
		c(printf)("[-] CreateProcess hata: %lu\n", c(GetLastError)());
		return false;
	}

	c(WaitForSingleObject)(pi.hProcess, INFINITE);

	DWORD exitCode = 0;
	c(GetExitCodeProcess)(pi.hProcess, &exitCode);

	c(CloseHandle)(pi.hProcess);
	c(CloseHandle)(pi.hThread);

	c(printf)("[*] 7z Cikis Kodu : %lu\n", exitCode);
	return exitCode == 0;
}
