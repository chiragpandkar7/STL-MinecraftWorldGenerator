// CubeItCreator.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "CubeItCreator.h"


// This is an example of an exported variable
CUBEITCREATOR_API int nCubeItCreator=0;

// This is an example of an exported function.
CUBEITCREATOR_API int fnCubeItCreator(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CubeItCreator::CubeItCreator()
{
    return;
}
