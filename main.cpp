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

#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <string>

int main(int argc, char **argv)
{
    // Initialise steam (even before a command is issued)
    Steam *steam = new Steam();

    while (1)
    {
        std::string s;
        std::getline(std::cin, s);
        // First check valid commands even if steam is not enabled
        if (s == "init")
        {
            printf("%d\n", steam->isSteamAvailable() ? 0 : 1);
            continue;
        }   // init
        else if (s == "quit")
        {
            printf("quit.\n");
            break;
        }

        // Any other command should only be issued if steam is available
        assert(steam->isSteamAvailable());

        if (s == "name")
        {
            const std::string &name = steam->getUserName();
            printf("%d %s\n", name.size(), name.c_str());
        }
        else if (s == "id")
        {
            const std::string &id = steam->getSteamID();
            printf("%d %s\n", id.size(), id.c_str());
        }
        else if (s == "avatar")
        {
            steam->saveAvatarAs("XX");
        }
        else if (s == "friends")
        {
            std::vector<std::string> friends = steam->getFriends();
            printf("%d\n", friends.size());
            for (unsigned int i = 0; i < friends.size(); ++i)
            {
                printf("%d %s\n", friends[i].size(), friends[i].c_str());
            }
        }
    }   // while(1)

#ifdef XX
#endif
    delete steam;

    return 0;
}