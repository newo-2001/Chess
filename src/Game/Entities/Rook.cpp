#include "pch.h"
#include "Rook.h"
#include <Game/Libraries/Models.h>

Rook::Rook(Color color, glm::vec3 position) :
    Piece(Models::Rook, color, position)
{ }
