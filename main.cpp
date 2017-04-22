//  SteamSynchronManager - a simple wrapper around SteamWorks API
//  Copyright (C) 2017-2017 Joerg Henrichs
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "steam.hpp"

#include <windows.h>

#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>


// ----------------------------------------------------------------------------
std::string getLine(HANDLE hStdin)
{
    DWORD bytes_read;
    const int BUFFERSIZE = 1024;
    char buffer[BUFFERSIZE];
    bool success = ReadFile(hStdin, buffer, BUFFERSIZE - 1, &bytes_read, NULL) != 0;
    if (bytes_read < BUFFERSIZE)
        buffer[bytes_read] = 0;
    std::string s = buffer;
    return s;
}

// ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
    HANDLE hStdin, hStdout;
    bool enable_pipes = (argc == 2 && std::string(argv[1]) == "1");
    if (enable_pipes)
    {
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        hStdin = GetStdHandle(STD_INPUT_HANDLE);
        if ((hStdout == INVALID_HANDLE_VALUE) ||
            (hStdin == INVALID_HANDLE_VALUE))
        {
            printf("Error.\n");
            exit(-1);
        }
    }

    // Initialise steam (even before a command is issued)
    Steam *steam = new Steam();

    while (1)
    {
        std::string s;
        // In windows when using pipes we can't use getline to read,
        // we need to use ReadFile :(
        if (enable_pipes)
        {
            s = getLine(hStdin);
#ifdef XX
            DWORD bytes_read;
            const int BUFFERSIZE = 1024;
            char buffer[BUFFERSIZE];
            bool success = ReadFile(hStdin, buffer, BUFFERSIZE - 1, &bytes_read, NULL) != 0;
            if (bytes_read < BUFFERSIZE)
                buffer[bytes_read] = 0;
            s = buffer;
#endif
        }
        else
        {
            //std::getline(std::cin, s);
            std::cin >> s;
        }

        // First check valid commands even if steam is not enabled 
        if (s == "init")
        {
            printf("%d", steam->isSteamAvailable() ? 1 : 0);
            fflush(stdout);
            continue;
        }   // init
        else if (s == "quit")
        {
            printf("quit");
            fflush(stdout);
            break;
        }

        // Any other command should only be issued if steam is available
        assert(steam->isSteamAvailable());

        if (s == "name")
        {
            const std::string &name = steam->getUserName();
            printf("%d %s", name.size(), name.c_str());
            fflush(stdout);
        }
        else if (s == "id")
        {
            const std::string &id = steam->getSteamID();
            printf("%d %s", id.size(), id.c_str());
            fflush(stdout);
        }
        else if (s == "avatar")
        {
            printf("filename"); fflush(stdout);
            std::string filename = getLine(hStdin);
            steam->saveAvatarAs(filename);
        }
        else if (s == "friends")
        {
            std::vector<std::string> friends = steam->getFriends();
            printf("%d\n", friends.size());
            fflush(stdout);

            for (unsigned int i = 0; i < friends.size(); ++i)
            {
                printf("%d %s", friends[i].size(), friends[i].c_str());
                fflush(stdout);
            }
        }
    }   // while(1)

    delete steam;

    return 0;
}