#ifndef GAMES_BL3_H
#define GAMES_BL3_H

#include "pch.h"

#include "games/game_hook.h"
#include "sigscan.h"

using unrealsdk::sigscan::Pattern;

namespace unrealsdk::games {

class BL3Hook : public GameHook {
    const Pattern gobjects_sig{
        "\x48\x8D\x0D\x00\x00\x00\x00\xC6\x05\x00\x00\x00\x00\x01\xE8\x00\x00\x00\x00\xC6\x05",
        "\xFF\xFF\xFF\x00\x00\x00\x00\xFF\xFF\x00\x00\x00\x00\xFF\xFF\x00\x00\x00\x00\xFF\xFF"};

   public:
    BL3Hook();
};

template <>
struct GameTraits<BL3Hook> {
    static constexpr bool IS_64BIT = true;
    static constexpr bool IS_UE4 = true;

    static bool matches_executable(const std::string& executable) {
        return executable == "Borderlands3.exe";
    }
};

}  // namespace unrealsdk::games

#endif /* GAMES_BL3_H */
