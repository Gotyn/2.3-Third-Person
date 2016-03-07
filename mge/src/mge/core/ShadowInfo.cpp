#include "ShadowInfo.hpp"

ShadowInfo::ShadowInfo(const glm::mat4& pValue)
{
    lightMVP = pValue;
}

ShadowInfo::~ShadowInfo()
{
    //dtor
}
