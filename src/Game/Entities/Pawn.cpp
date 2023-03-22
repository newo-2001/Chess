#include "pch.h"
#include "Pawn.h"
#include <Game/Libraries/Models.h>

Pawn::Pawn(Color color, glm::vec3 position) :
    Piece(Models::Pawn, color, position)
{ }
