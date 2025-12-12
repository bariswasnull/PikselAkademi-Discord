#include "includes.h"
int main()
{
	IndirmeyiBaslat();
	ZipdenCikar(GetDpiZipPath(), "C:\\GoodbyeDPI");
	c(system)("cls");
	if (ProfilleriDene("C:\\GoodbyeDPI"))
	{
		c(printf)("[+] DPI bypass basarili\n");
		c(Sleep)(1000);
		c(printf)("[+] Discord Sunucumuza Yonlendiriliyorsunuz...\n");
		c(Sleep)(1000);
		(ShellExecuteA)(nullptr, "open", "https://discord.gg/gm4zruwG6t", nullptr, nullptr, SW_SHOWNORMAL);
		c(system)("pause");
		return 0xB4DC0D3;
	}
	c(printf)("[-] Hicbir DPI profili basarili olmadi\n");
	return 0;
}