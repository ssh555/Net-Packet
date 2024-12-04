#include "nppch.h"

NP_API void __Dummy__()
{
	throw new std::exception("用于保证空的项目能正确生成dll和lib，不要调用");
}
