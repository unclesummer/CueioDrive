/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   knob_png;
    const int            knob_pngSize = 196036;

    extern const char*   background_png;
    const int            background_pngSize = 103343;

    extern const char*   ABoxFor2_ttf;
    const int            ABoxFor2_ttfSize = 94036;

    extern const char*   ABoxFor3_ttf;
    const int            ABoxFor3_ttfSize = 447212;

    extern const char*   ABoxFor_ttf;
    const int            ABoxFor_ttfSize = 94164;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
