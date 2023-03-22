#include "pch.h"
#include "King.h"
#include <Game/Libraries/Models.h>

King::King(Color color, glm::vec3 position) :
    Piece(Models::King, color, position)
{ }
