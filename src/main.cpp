
#include "getting_started/shaders.h"
#include "getting_started/textures.h"

enum EnumFunction
{
    GETTING_STARTED_SHADERS,
    GETTING_STARTED_TEXTURES,
};

int main()
{
    EnumFunction func = EnumFunction::GETTING_STARTED_TEXTURES;
    switch (func)
    {
    case EnumFunction::GETTING_STARTED_SHADERS:
        getting_started_shaders();
        break;
    case EnumFunction::GETTING_STARTED_TEXTURES:
        getting_started_textures();
        break;
    default:
        break;
    }
    return 0;
}
