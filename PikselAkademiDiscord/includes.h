#pragma once
#include "Downloader/Downloader.h"
#include "DiscordCheck/HttpTest.h"
#include "RarExtractor/7ZipApi.h"
#include "DPIChecker/tryDPI.h"
#include "LazyImporter/lazy.h"
#include <iostream>
std::string GetDpiZipPath()
{
	char temp[MAX_PATH];
	c(GetTempPathA)(MAX_PATH, temp);
	return std::string(temp) + "goodbyedpi.zip";
}
