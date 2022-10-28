#pragma once

#include "../../Main.h"

#if !defined(CDR_FINAL)

int main(int, const char**)
{
	return CDR::Main();
}

#else

#include <Windows.h>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	return CDR::Main();
}

#endif