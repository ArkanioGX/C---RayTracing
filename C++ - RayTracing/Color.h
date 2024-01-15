#pragma once
#include "Vector3.h"

//New Vector3 alias for color
using Color = Vector3;

void WriteColor(std::ostream& rOut, Color pixel)
{
    // Write the translated [0,255] value of each color component.
    rOut << static_cast<int>(255.999 * pixel.x) << ' '
        << static_cast<int>(255.999 * pixel.y) << ' '
        << static_cast<int>(255.999 * pixel.z) << '\n';
}
