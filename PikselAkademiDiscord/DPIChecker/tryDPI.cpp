#include "tryDPI.h"
#include "../LazyImporter/lazy.h"
struct DpiProfile
{
    const char* name;
    const char* args;
};

DpiProfile g_profiles[] =
{
    {
        "Default",
        "-5 --set-ttl 5 "
        "--dns-addr 77.88.8.8 --dns-port 1253 "
        "--dnsv6-addr 2a02:6b8::feed:0ff --dnsv6-port 1253"
    },
    {
        "Alt-1",
        "--set-ttl 3"
    },
    {
        "Alt-2",
        "-5"
    },
    {
        "Alt-3",
        "--set-ttl 3 "
        "--dns-addr 77.88.8.8 --dns-port 1253 "
        "--dnsv6-addr 2a02:6b8::feed:0ff --dnsv6-port 1253"
    },
    {
        "Alt-4",
        "-5 "
        "--dns-addr 77.88.8.8 --dns-port 1253 "
        "--dnsv6-addr 2a02:6b8::feed:0ff --dnsv6-port 1253"
    },
    {
        "Alt-5",
        "-9 "
        "--dns-addr 77.88.8.8 --dns-port 1253 "
        "--dnsv6-addr 2a02:6b8::feed:0ff --dnsv6-port 1253"
    },
    {
        "Alt-6",
        "-9"
    }
};
std::string GetArchDir()
{
#if defined(_WIN64)
    return "x86_64";
#else
    BOOL wow64 = FALSE;
    IsWow64Process(GetCurrentProcess(), &wow64);
    return wow64 ? "x86_64" : "x86";
#endif
}
bool RunSC(const std::string& args)
{
    std::string cmd = "sc " + args;
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);
    if (!c(CreateProcessA)(nullptr, &cmd[0], nullptr, nullptr,
        FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi))
        return false;
    c(WaitForSingleObject)(pi.hProcess, INFINITE);
    c(CloseHandle)(pi.hProcess);
    c(CloseHandle)(pi.hThread);
    return true;
}
void ServisTemizle()
{
    RunSC("stop GoodbyeDPI");
    RunSC("delete GoodbyeDPI");
    RunSC("stop WinDivert");
    RunSC("delete WinDivert");
    RunSC("stop WinDivert14");
    RunSC("delete WinDivert14");
}

bool InstallProfile(const DpiProfile& p, const std::string& baseKonum)
{
    std::string arch = GetArchDir();
    std::string exe = baseKonum + "\\" + arch + "\\goodbyedpi.exe";
    std::string binPath = "\"" + exe + "\" " + p.args;
    ServisTemizle();
    std::string createCmd ="create GoodbyeDPI binPath= \"" + binPath + "\" start= auto";
    if (!RunSC(createCmd))
        return false;
    RunSC("description GoodbyeDPI \"Turkiye icin DNS zorlamasini kaldirir\"");
    RunSC("start GoodbyeDPI");
    return true;
}
bool ProfilleriDene(const std::string& baseDir)
{
    for (const auto& p : g_profiles)
    {
        c(printf)("[*] Profil deneniyor: %s\n", p.name);

        if (!InstallProfile(p, baseDir))
            continue;

        c(Sleep)(3000); 

        if (DiscordHttpTest())
        {
            printf("[+] Basarili profil: %s\n", p.name);
            return true;
        }

        c(printf)("[-] Profil basarisiz, temizleniyor...\n");
        ServisTemizle();
        Sleep(2000);
    }
    return false;
}
