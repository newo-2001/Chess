#include "pch.h"
#include "Queen.h"
#include <Game/Libraries/Models.h>

Queen::Queen(Color color, glm::vec3 position) :
    Piece(Models::Queen, color, position)
{ }
