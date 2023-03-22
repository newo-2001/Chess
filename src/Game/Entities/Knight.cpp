#include "pch.h"
#include "Knight.h"
#include <Game/Libraries/Models.h>

Knight::Knight(Color color, glm::vec3 position) :
    Piece(Models::Knight, color, position)
{ }
