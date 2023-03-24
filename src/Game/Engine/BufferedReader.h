#pragma once
#include <subprocess.h>
#include <stack>

class BufferedReader
{
public:
    BufferedReader() {}
    BufferedReader(subprocess_s* process);

    std::string ReadLine();
private:
    subprocess_s* m_process;

    std::queue<std::string> m_bufferedLines;
    std::string m_buffered;
};
