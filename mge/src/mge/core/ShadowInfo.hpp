#ifndef SHADOWINFO_H
#define SHADOWINFO_H
#include <glm.hpp>

class ShadowInfo
{
public:
    ShadowInfo(const glm::mat4& pValue);
    ~ShadowInfo();
    void setLightMVP(const glm::mat4& pValue) { lightMVP = pValue; }
    glm::mat4 getLightMVP() { return lightMVP; }
protected:
private:
    glm::mat4 lightMVP;
};

#endif // SHADOWINFO_H
