#pragma once

#include "pch.h"

struct Move
{
    glm::ivec2 From;
    glm::ivec2 To;

    static Move FromUci(const std::string& uci);
    std::string ToUci() const;
};
