
#include "getting_started/shaders.h"

enum EnumFunction
{
    GETTING_STARTED_SHADERS
};

int main()
{
    EnumFunction func = EnumFunction::GETTING_STARTED_SHADERS;
    switch (func)
    {
    case EnumFunction::GETTING_STARTED_SHADERS:
        getting_started_shaders();
        break;
    default:
        break;
    }
    return 0;
}
