#pragma once
#include <Core/Rendering/Renderable.h>

namespace Models
{
    inline std::shared_ptr<Renderable> Board;
    inline std::shared_ptr<Renderable> Pawn, King, Queen, Bishop, Rook, Knight;

    void Load();
}

