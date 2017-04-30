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

#include <assert.h>
#include <stddef.h>
#include <string>
#include <vector>

class Steam
{
    /** Singleton pointer. */
    static Steam  *m_steam;

    /** True if steam was initialised correctly. */
    bool m_steam_available;

    /** Used in a callback to indicate that an avatar
     *  image finished downloading. */
    bool m_avatar_war_loaded;

    // Irrlicht is not included in the standalone SSM.
#ifdef HAS_IRRLICHT
    /** User name as irr::stringw (wchar), which is used in STK. */
    irr::core::stringw m_user_name_wchar;
#endif

    /** Steam image number of the avatar to use. */
    int m_avatar_index;

    /** Steam user name. Only defined if m_steam_available. */
    std::string m_user_name;

    /** Unique steam id. */
    std::string m_steam_id;

    std::string getSteamIDInternal();

    STEAM_CALLBACK(Steam, loadedAvatar, AvatarImageLoaded_t);


     Steam();
    ~Steam();

public:
    /** Creates a singleton. */
    static void create()
    {
        assert(!m_steam);
        m_steam = new Steam();
    }   // create;

    // ------------------------------------------------------------------------
    /** Returns the singleton pf the Steam class. */
    static Steam *get()
    {
        assert(m_steam);
        return m_steam;
    }   // get

    // ------------------------------------------------------------------------
    /** Destroys the singleton of the Steam class. */
    static void destroy()
    {
        assert(m_steam);
        delete m_steam;
        m_steam = NULL;
    }   // destroy

    // ------------------------------------------------------------------------

    const std::string &getUserName();
    const std::string &getSteamID();
    std::vector<std::string> getFriends();

    int saveAvatarAs(const std::string &filename);
#ifdef HAS_IRRLICHT
    // ------------------------------------------------------------------------
    /** Returns the user name as wide string. */
    const irr::core::stringw& getUserNameWchar()
    {
        assert(m_steam_available);
        return m_user_name_wchar;
    }   // getUserNameWchar
#endif

    // ------------------------------------------------------------------------
    /** Returns true if the SteamWorks API could be initialised correctly. */
    bool isSteamAvailable() const { return m_steam_available;  }
};   // Steam
