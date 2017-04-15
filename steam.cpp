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
#include <iomanip>
#include <sstream>

Steam::Steam()
{
    m_user_name = "";

    m_steam_available = SteamAPI_Init();
    
    if(m_steam_available)
    {
        const char *name = SteamFriends()->GetFriendPersonaName(SteamUser()->GetSteamID());
        m_user_name = name;
    }

}   // Steam

// ----------------------------------------------------------------------------
/** Destructor. Shuts down the SteamWorks API.
 */
Steam::~Steam()
{
    if(m_steam_available)
        SteamAPI_Shutdown();

    m_steam_available = false;
}   // ~Steam

// ----------------------------------------------------------------------------
/** Returns the (not necessarily unique) steam name of the user.
*/
const std::string &Steam::getUserName()
{
    assert(m_steam_available);
    return m_user_name;
}   // getUserName
// ----------------------------------------------------------------------------
/** Returns the unique steam id as a 16 character hex string, or the
 *  steam account id only as 8 character hex string (depending on
 *  #defines). It's not clear which id is better to use - steam
 *  seems to use the 32 bit account id only.
 */
std::string Steam::getSteamID()
{
    CSteamID sid = SteamUser()->GetSteamID();
    std::ostringstream stream;

#define USE_64_BIT_STEAM_ID
#ifdef USE_64_BIT_STEAM_ID
    uint64 id = sid.ConvertToUint64();
    stream << std::hex << std::setw(16) << std::setfill('0') << id;
#else
    int id = sid.GetAccountID();   // 32 bit id
    stream << std::hex << std::setw(8) << std::setfill('0') << id;
#endif
    return stream.str();
}   // getSteamID

// ----------------------------------------------------------------------------
/** Returns a vector with the name of all friends.
 */
std::vector<std::string> Steam::getFriends()
{
    std::vector<std::string> friends;

    int friend_count = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
    for (int i = 0; i < friend_count; i++)
    {
        CSteamID frnd = SteamFriends()->GetFriendByIndex(i, k_EFriendFlagImmediate);
        friends.push_back(SteamFriends()->GetFriendPersonaName(frnd));
    }
    return friends;
}   // getFriends

// ----------------------------------------------------------------------------
void Steam::loadedAvatar(AvatarImageLoaded_t *pAIL)
{
    m_avatar_war_loaded = true;
    m_avatar_index = pAIL->m_iImage;
}   // loadedAvatar

// ----------------------------------------------------------------------------
/** Downloads the avatar from steam and save it in a file.
 *  \param filename Name under which to save the avatar.
 */
int Steam::saveAvatarAs(const std::string filename)
{
//    CSteamID sid = SteamUser()->GetSteamID();
    m_avatar_war_loaded = false;
    CSteamID sid = SteamFriends()->GetFriendByIndex(1, k_EFriendFlagImmediate);
    m_avatar_index = SteamFriends()->GetLargeFriendAvatar(sid);
    if (m_avatar_index== 0)
    {
        return -1;
    }
    else if (m_avatar_index == -1)
    {
        printf("Image still needs to be loaded.\n");
        int count = 1000;
        while(count > 0)
        {
            SteamAPI_RunCallbacks();
            _sleep(1);
            if (m_avatar_war_loaded) break;
            count--;
        }
        if (count < 0)
        {
            printf("Not loaded :(\n");
            return -2;
        }
    }
    unsigned int width, height;
    SteamUtils()->GetImageSize(m_avatar_index, &width, &height);
    if (width > 0 && height > 0)
    {
        char *buffer = new char[width*height * 4];
        SteamUtils()->GetImageRGBA(m_avatar_index, (uint8*)buffer, width*height*4);
        FILE *f = fopen(filename.c_str(), "wb");
        if (!f)
        {
            fclose(f);
            return -2;
        }
        fwrite(buffer, 1, width*height * 4, f);
        fclose(f);
        return 0;
    }

    //SteamUtils::GetImageRGBA();
    return -1;
}   // saveAvatarAs