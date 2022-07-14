#include <windows.h>
#include <iostream>

using namespace std;

string login, haslo, kolor;

char* ScanBasic(const char* pattern, const char* mask, char* begin, intptr_t size)
{
    intptr_t patternLen = strlen(mask);

    for (int i = 0; i < size; i++)
    {
        bool found = true;
        for (int j = 0; j < patternLen; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (begin + i);
        }
    }
    return nullptr;
}

void* ScanEx(const char* pattern, const char* mask, char* begin, intptr_t size, HANDLE hProc) {
    char* match{ nullptr };
    SIZE_T bytesRead;
    DWORD oldprotect;
    char* buffer{ nullptr };
    MEMORY_BASIC_INFORMATION mbi;
    mbi.RegionSize = 0x1000;

    VirtualQueryEx(hProc, (LPCVOID)begin, &mbi, sizeof(mbi));

    for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
    {
        if (!VirtualQueryEx(hProc, curr, &mbi, sizeof(mbi))) continue;
        if (mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS || mbi.Protect != PAGE_EXECUTE_READWRITE) continue;

        delete[] buffer;
        buffer = new char[mbi.RegionSize];

        if (VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect))
        {
            ReadProcessMemory(hProc, mbi.BaseAddress, buffer, mbi.RegionSize, &bytesRead);
            VirtualProtectEx(hProc, mbi.BaseAddress, mbi.RegionSize, oldprotect, &oldprotect);

            char* internalAddr = ScanBasic(pattern, mask, buffer, (intptr_t)bytesRead);

            if (internalAddr != nullptr) {
                match = curr + (internalAddr - buffer);
                break;
            }
        }
    }
    delete[] buffer;
    return match;
}

int main()
{
    system("color f");

    cout << "######################\n";
    cout << "#\n";
    cout << "#\n";
    cout << "#\n";
    cout << "#\n";
    cout << "######################\n";
    cout << "#\n";
    cout << "#\n";
    cout << "#\n";
    cout << "###################### \n\n\n\n";
    cout << "LISTA KOLOROW\n";
    cout << "1 = granatowy\n";
    cout << "2 = zielony ciemny\n";
    cout << "3 = niebieski ciemny 1\n";
    cout << "4 = czerwony ciemny\n";
    cout << "5 = fioletowy\n";
    cout << "6 = zloty\n";
    cout << "7 = szary\n";
    cout << "8 = ciemny szary\n";
    cout << "9 = niebieski ciemny 2\n";
    cout << "a = zielony\n";
    cout << "b = blekitny\n";
    cout << "c = czerwony\n";
    cout << "d = fioletowy\n";
    cout << "e = zolty\n";
    cout << "f = bialy (domyslny)\n";

    cout << "Wybierz kolor glowny: ";
    cin >> kolor;

    {
        if (kolor == "a")
            system("color a");
        if (kolor == "c")
            system("color c");
        if (kolor == "b")
            system("color b");
        if (kolor == "d")
            system("color d");
        if (kolor == "e")
            system("color e");
        if (kolor == "1")
            system("color 1");
        if (kolor == "2")
            system("color 2");
        if (kolor == "3")
            system("color 3");
        if (kolor == "4")
            system("color 4");
        if (kolor == "5")
            system("color 5");
        if (kolor == "6")
            system("color 6");
        if (kolor == "7")
            system("color 7");
        if (kolor == "8")
            system("color 8");
        if (kolor == "9")
            system("color 9");
    }
    


    cout << "\n\n\nExerchook wita!\n\n(login: admin\npassword: admin)\n";
    cout << "USERNAME: ";
    cin >> login;
    cout << "PASSWORD: ";
    cin >> haslo;

    if ((login == "admin") && (haslo == "admin"))
    {
        system("cls"); 
        cout << "Uruchomiono!\n\nREACH = HOME\nTRWAJĄ PRZYGOTOWANIA DO UPDATU 2.0";
        HWND hwnd = FindWindowA(("AAAA"), NULL);
        DWORD procId;
        GetWindowThreadProcessId(hwnd, &procId);
        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

        while (true) {
            if (GetAsyncKeyState(VK_HOME)) {
                void* addr = ScanEx("\xC5\xF3\x5A\xC8\xC5\xFA\x5A\xC1\x48\x83", "xxxxxxxx?x", (char*)0x1000000, 0x9000000, handle);
                WriteProcessMemory(handle, addr, "\x90\x90\x90\x90\xC5\xFA\x5A\xC1\x48\x83", 4, NULL);
                system("cls");
                cout << "Uruchomiono!\n\nREACH = HOME\n";
            }
        }
    }
    else
    {
        system("cls");
        system("color c");
        cout << "Zle dane.";
    }

    return 0;
}
