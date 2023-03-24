#include "pch.h"
#include "BufferedReader.h"

void StripEndl(std::string& str)
{
    while (str.back() == '\r' || str.back() == '\n')
    {
        str.pop_back();
    }
}

BufferedReader::BufferedReader(subprocess_s* process) :
    m_process(process)
{ }

std::string BufferedReader::ReadLine()
{
    if (!m_bufferedLines.empty())
    {
        std::string line = m_bufferedLines.front();
        m_bufferedLines.pop();
        return line;
    }

    char buffer[1024];
    int read = subprocess_read_stdout(m_process, buffer, 1024);
    
    std::stringstream ss(m_buffered + std::string(buffer, read));
    std::string line;
    
    m_buffered.clear();
    
    while (std::getline(ss, line))
    {
        if (line.ends_with('\r'))
        {
            line.pop_back();
        }

        m_bufferedLines.push(line);
    }
    
    return ReadLine();
}

