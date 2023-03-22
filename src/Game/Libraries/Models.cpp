#include "pch.h"
#include "Models.h"
#include <Core/Rendering/Model.h>

std::shared_ptr<Model> LoadFile(const std::string& path)
{
    return std::make_shared<Model>("resources/models/" + path);
}

void Models::Load()
{
    Board = LoadFile("board/Board.obj");
    Pawn = LoadFile("pieces/pawn.fbx");
    Bishop = LoadFile("pieces/bishop.fbx");
    Rook = LoadFile("pieces/rook.fbx");
    Knight = LoadFile("pieces/knight.fbx");
    King = LoadFile("pieces/king.fbx");
    Queen = LoadFile("pieces/queen.fbx");
}


