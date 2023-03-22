#include "pch.h"
#include "Bishop.h"
#include <Game/Libraries/Models.h>

Bishop::Bishop(Color color, glm::vec3 position) :
    Piece(Models::Bishop, color, position)
{ }
