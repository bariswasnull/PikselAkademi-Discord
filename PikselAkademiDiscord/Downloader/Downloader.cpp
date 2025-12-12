#include <curl/curl.h>
#include <windows.h>
#include <cstdio>
#include <string>
#include "../LazyImporter/lazy.h"

size_t WriteFileCallback(void* ptr, size_t size, size_t nmemb, void* stream)
{
    return c(fwrite)(ptr, 1, size * nmemb, (FILE*)stream);
}
bool DownloadFile(const char* url, const char* ciktiKonum)
{
    CURL* curl = curl_easy_init();
    if (!curl) return false;
    FILE* f = nullptr;
    c(fopen_s)(&f, ciktiKonum, "wb");
    if (!f)
    {
        curl_easy_cleanup(curl);
        return false;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Installer/1.0");

    CURLcode res = curl_easy_perform(curl);

    c(fclose)(f);
    curl_easy_cleanup(curl);
    return res == CURLE_OK;
}

bool IndirmeyiBaslat()
{
    char temp[MAX_PATH];
    c(GetTempPathA)(MAX_PATH, temp);
    std::string dpiZip = std::string(temp) + "goodbyedpi.zip";
    std::string sevenZipInstaller = std::string(temp) + "7z1900-x64.exe";
    c(printf)("[*] GoodbyeDPI indiriliyor...\n");
    if (!DownloadFile("https://github.com/cagritaskn/GoodbyeDPI-Turkey/releases/" "download/release-0.2.3rc3-turkey/" "goodbyedpi-0.2.3rc3-turkey.zip", dpiZip.c_str()))
    {
        c(printf)("[-] GoodbyeDPI indirilemedi\n");
        return false;
    }
    c(printf)("[+] GoodbyeDPI indirildi\n");
    c(printf)("[*] 7-Zip indiriliyor...\n");
    if (!DownloadFile(
        "https://www.7-zip.org/a/7z1900-x64.exe",
        sevenZipInstaller.c_str()))
    {
        c(printf)("[-] 7-Zip indirilemedi\n");
        return false;
    }
    c(printf)("[+] 7-Zip indirildi\n");
    c(printf)("[*] 7-Zip kuruluyor...\n");
    std::string cmd = "\"" + sevenZipInstaller + "\" /S";
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);
    if (!c(CreateProcessA)(nullptr, &cmd[0],nullptr, nullptr, FALSE, 0,          nullptr, nullptr, &si, &pi))
    {
        c(printf)("[-] 7-Zip kurulum baslatilamadi. Hata: %lu\n", c(GetLastError)());
        return false;
    }
    c(WaitForSingleObject)(pi.hProcess, INFINITE);
    DWORD exitCode = 0;
    c(GetExitCodeProcess)(pi.hProcess, &exitCode);
    c(CloseHandle)(pi.hProcess);
    c(CloseHandle)(pi.hThread);
    if (exitCode != 0)
    {
        c(printf)("[-] 7-Zip kurulum hata kodu: %lu\n", exitCode);
        return false;
    }
    c(printf)("[+] 7-Zip kuruldu\n");
    return true;
}