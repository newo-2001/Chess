#pragma once

#include "pch.h"
#include <Game/Move.h>
#include "BufferedReader.h"

class Stockfish
{
public:
    Stockfish(const std::string& executablePath);
    ~Stockfish();

    Move GetBestMove();
    void SetState(const std::vector<Move>& moves);
    bool IsValid(Move move);

    void Reset();
private:
    BufferedReader m_stdout;
    subprocess_s m_process;
    
    void Ready();
    
    std::string Read();
    void Read(const std::string& expected);
    void Write(std::string str);
};

