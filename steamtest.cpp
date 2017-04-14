#include <stdio.h>

#include "steam/steam_api.h"

int main(int argc, char **argv)
{
    printf("Hello World\n");

    if (!SteamAPI_Init())
    {
        printf("Could not init steam :(\n");
        return 1;
    }
    const char *name = SteamFriends()->GetFriendPersonaName(SteamUser()->GetSteamID());
    const char *nick = SteamFriends()->GetPlayerNickname(SteamUser()->GetSteamID());
    printf("Name is '%s', nickname is '%s'.\n", name, nick);

    int friend_count = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
    printf("Number of friends: %d\n", friend_count);
    for (int i = 0; i < friend_count; i++)
    {
        CSteamID frnd = SteamFriends()->GetFriendByIndex(i, k_EFriendFlagImmediate);
        printf("%d: %s\n", i, SteamFriends()->GetFriendPersonaName(frnd));
    }
    SteamAPI_Shutdown();
    return 0;
}