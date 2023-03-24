#include "pch.h"
#include "Stockfish.h"

#ifdef _WIN32
#define NEWLINE "\r\n"
#elif defined macintosh // OS 9
#define NEWLINE "\r"
#else
#define NEWLINE "\n" // Mac OS X uses \n
#endif

Stockfish::Stockfish(const std::string& executablePath)
{
    const char* arguments[] { executablePath.c_str(), NULL };
    
    if (subprocess_create(arguments, subprocess_option_enable_async, &m_process) != 0)
    {
        throw std::runtime_error("Failed to spawn Stockfish process");
    }

    m_stdout = BufferedReader(&m_process);

    Read();
    Ready();

    Write("uci");
    while (!Read().ends_with("uciok"));

    Reset();
}

Stockfish::~Stockfish()
{
    if (subprocess_alive(&m_process))
    {
        Write("quit");
    }
}

void Stockfish::Ready()
{
    Write("isready");
    Read("readyok");
}

void Stockfish::Reset()
{
    Ready();
    Write("ucinewgame");
}

Move Stockfish::GetBestMove()
{
    Ready();
    Write("go depth 5");
    
    std::string move = Read();
    std::string uci = move.substr(sizeof("best move ") - 2);

    return Move::FromUci(uci);
}

bool Stockfish::IsValid(Move move)
{
    Ready();
    Write("go depth 1 searchmoves " + move.ToUci());
    std::string best = Read().substr(sizeof("best move ") - 2);
    
    return !best.starts_with("(none)");
}

void Stockfish::SetState(const std::vector<Move>& moves)
{
    std::string state = "position startpos moves";
    state.reserve(moves.size() * 5);

    for (const Move& move : moves)
    {
        state += ' ' + move.ToUci();
    }

    Ready();

    Write(state);
}

std::string Stockfish::Read()
{
    std::string data;

    do
    {
        data = m_stdout.ReadLine();
        std::cout << "[Stockfish] " << data << std::endl;
    } while (data.starts_with("info"));
    
    return data;
}

void Stockfish::Read(const std::string& expected)
{
    std::string response = Read();
    if (response != expected)
    {
        throw std::runtime_error(std::format("Expected stockfish to reply with '{}', but got '{}'", expected, response));
    }
}

void Stockfish::Write(std::string str)
{
    str += NEWLINE;
    std::cout << "[Game] " + str;

    FILE* handle = subprocess_stdin(&m_process);
    fputs(str.c_str(), handle);
    fflush(handle);
}
