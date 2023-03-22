#include "Logging.h"
#include "pch.h"

std::ostream& operator <<(std::ostream& out, const glm::vec2& vec)
{
    out << std::format("({}, {})", vec.x, vec.y);
    return out;
}

std::ostream& operator <<(std::ostream& out, const glm::vec3& vec)
{
    out << std::format("({}, {}, {})", vec.x, vec.y, vec.z);
    return out;
}

std::ostream& operator <<(std::ostream& out, const glm::vec4& vec)
{
    out << std::format("({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
    return out;
}