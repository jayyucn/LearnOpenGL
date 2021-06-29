

#include "getting_started/shaders.h"
#include "getting_started/textures.h"

int main()
{

#ifdef GETTING_STARTED_SHADERS
    getting_started_shaders();
#endif
#ifdef GETTING_STARTED_TEXTURES
    getting_started_textures();
#endif
    // EnumFunction func = EnumFunction::E_GETTING_STARTED_TEXTURES;

    // switch (func)
    // {
    // case EnumFunction::E_GETTING_STARTED_SHADERS:
    //     break;
    // case EnumFunction::E_GETTING_STARTED_TEXTURES:
    //     break;
    // default:
    //     break;
    // }
    return 0;
}
