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

#include "steam/steam_api.h"

#include <string>
#include <vector>

class Steam
{
    /** True if steam was initialised correctly. */
    bool m_steam_available;

    /** Used in a callback to indicate that an avatar
     *  image finished downloading. */
    bool m_avatar_war_loaded;

    /** Steam image number of the avatar to use. */
    int m_avatar_index;

    /** Steam user name. Only defined if m_steam_available. */
    std::string m_user_name;
public:
    Steam();
    ~Steam();

    const std::string &getUserName();
    std::string getSteamID();
    std::vector<std::string> getFriends();

    STEAM_CALLBACK(Steam, loadedAvatar, AvatarImageLoaded_t);

    int saveAvatarAs(const std::string filename);

    // ------------------------------------------------------------------------
    /** Returns true if the SteamWorks API could be initialised correctly. */
    bool isSteamAvailable() const { return m_steam_available;  }
};   // Steam
