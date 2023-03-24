#include "pch.h"
#include "Move.h"

std::string Uci(glm::ivec2 pos)
{
    const char buff[] { 'a' + (char) pos.x, '1' + (char) pos.y };
    return std::string(buff, 2);
}

glm::ivec2 Pos(const std::string& uci)
{
    return glm::ivec2(uci[0] - 'a', uci[1] - '1');
}

std::string Move::ToUci() const
{
    return Uci(From) + Uci(To);
}

Move Move::FromUci(const std::string& uci)
{
    return { Pos(uci.substr(0, 2)), Pos(uci.substr(2, 2)) };
}