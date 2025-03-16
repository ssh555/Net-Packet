# Configuration File Code Generation

## Input
### Input Directory
**Default Input Directory**: `%CD%\Input`, which is the directory where `ProjectBuilder.bat` is executed.

**Modify Directory**: Change the `-i` parameter after `StructFileGenerator.exe` in the `.bat` file.

### Input Files
**Requirements**: The file name must match the `classname` in the configuration file exactly.
**Location**: All files must be located in the input directory, **excluding** files in subfolders.

**Format**: The file extension must be `.np`, and the format must be `json`.

## Output
### Output Directory
**Default Output Directory**: `%CD%\Source\NetPacket\Public\Struct`, which is the directory where `ProjectBuilder.bat` is executed.

**Modify Directory**: Change the `-o` parameter after `StructFileGenerator.exe` in the `.bat` file.

### Output Files
**Location**: All files are located in the output directory.
**Files**: `NPStruct.h` contains all header files; all generated code files are `*.h`.

**Format**: The file extension is `.h`, and the format is `C++`.

## Template
### Naming Convention
**filename.np**
- The file extension must be `.np`.
- The file name must match the `classname` in the configuration content (for UE version).

### Template Location
`%CD%\Source\NetPacket\Public\Config\template.np`

### Template Description
**Do not add any comments in the JSON file, as it may fail to parse.**

#### classname
- Replace `Example` with the name of your custom data type.

#### mode
- `0`: Default, uses the standard C++ template.
- `1`: UE, uses the UE C++ template.

#### includes
- If referencing other custom data types, add them here.
- Replace `example` in `example.hpp` with the name of the referenced data type.
- For example, `Test` (here `Test` is **not automatically generated**, so it is located in `example.hpp`). Automatically generated files are located in `filename.h`.

#### basedata & arraydata
| Type | Description |
| ---- | ---- |
| **Standard C++** |
| uint8_t | unsigned char, 1 byte |
| int8_t | signed char, 1 byte |
| bool | boolean, 1 byte |
| int16_t | short, 2 bytes |
| uint16_t | unsigned short, 2 bytes |
| int32_t | int, 4 bytes |
| uint32_t | unsigned int, 4 bytes |
| int64_t | long long, 8 bytes |
| uint64_t | unsigned long long, 8 bytes |
| float | single-precision floating point, 4 bytes |
| double | double-precision floating point, 8 bytes |
| std::string | STL string |
| Test | Custom data type, refer to `include` usage. Replace with your custom `classname`. |
| char | character, 1 byte, equivalent to `int8_t` |
| std::byte | STL byte, equivalent to `int8_t` |
| **UE C++** |
| UE data types do not support standard C++ data types, only the following types are supported. |
| For UE version arrays, **length** can be any value. |
| Test | Custom data type, same as above. |
| FString | ... |
| FName | ... |
| FText | ... |
| int64 | Equivalent to `int64_t`, but cannot be mixed. |
| int32 | Equivalent to `int32_t`, but cannot be mixed. |
| uint8 | Equivalent to `uint8_t`, but cannot be mixed. |
| FVector | ... |
| FQuat | ... |
| FColor | ... |
| FIntPoint | ... |
| FVector2D | ... |
| FRotator | ... |
| FDateTime | ... |
| FTimespan | ... |
| FBox | ... |
| FMatrix | ... |
| FTransform | ... |
| FLinearColor | ... |

#### Example Templates
**Standard C++**
```json
{
    "classname" : "Example",
    "mode" : 0,
    "includes" : [
        {"name":"example.hpp"}
    ],
    "basedata" : [
        {"type":"uint8_t", "name":"ui8" },
        {"type":"int8_t", "name":"i8" },
        {"type":"bool", "name":"b" },
        {"type":"int16_t", "name":"i16" },
        {"type":"uint16_t", "name":"ui16" },
        {"type":"int32_t", "name":"i32" },
        {"type":"uint32_t", "name":"ui32" },
        {"type":"int64_t", "name":"i64" },
        {"type":"uint64_t", "name":"ui64" },
        {"type":"float", "name":"f" },
        {"type":"double", "name":"d" },
        {"type":"std::string", "name":"str" },
        {"type":"Test", "name":"test" },
        {"type":"char", "name":"ch" },
        {"type":"std::byte", "name":"bt" }
    ],
    "arraydata" : [
        {"type":"uint8_t", "name":"ui8a", "length":5 },
        {"type":"int8_t", "name":"i8a", "length":5 },
        {"type":"bool", "name":"ba", "length":5 },
        {"type":"int16_t", "name":"i16a", "length":5 },
        {"type":"uint16_t", "name":"ui16a", "length":5 },
        {"type":"int32_t", "name":"i32a", "length":5 },
        {"type":"uint32_t", "name":"ui32a", "length":5 },
        {"type":"int64_t", "name":"i64a", "length":5 },
        {"type":"uint64_t", "name":"ui64a", "length":5 },
        {"type":"float", "name":"fa", "length":5 },
        {"type":"double", "name":"da", "length":5 },
        {"type":"std::string", "name":"stra", "length":5 },
        {"type":"Test", "name":"testa", "length":5 },
        {"type":"char", "name":"cha", "length":5 },
        {"type":"std::byte", "name":"bta", "length":5 }
    ]
}
```

**UE C++**
```json
{
    "classname" : "template_ue",
    "mode" : 1,
    "includes" : [
        {"name":"example.hpp"}
    ],
    "basedata" : [
        {"type":"FString", "name":"str" },
        {"type":"FName", "name":"strN" },
        {"type":"FText", "name":"strT" },
        {"type":"int64", "name":"i64" },
        {"type":"int32", "name":"i32" },
        {"type":"uint8", "name":"ui8" },
        {"type":"FVector", "name":"vec" },
        {"type":"FQuat", "name":"q" },
        {"type":"FColor", "name":"color" },
        {"type":"FIntPoint", "name":"intp" },
        {"type":"FVector2D", "name":"vec2d" },
        {"type":"FRotator", "name":"rot" },
        {"type":"FDateTime", "name":"datetime" },
        {"type":"FTimespan", "name":"timespan" },
        {"type":"FBox", "name":"box" },
        {"type":"FMatrix", "name":"mat" },
        {"type":"FTransform", "name":"trans" },
        {"type":"FLinearColor", "name":"lcolor" }
    ],
    "arraydata" : [
        {"type":"FString", "name":"strA", "length":5},
        {"type":"FName", "name":"strNA", "length":5},
        {"type":"FText", "name":"strTA", "length":5},
        {"type":"int64", "name":"i64A", "length":5},
        {"type":"int32", "name":"i32A", "length":5},
        {"type":"uint8", "name":"ui8A", "length":5},
        {"type":"FVector", "name":"vecA", "length":5},
        {"type":"FQuat", "name":"qA", "length":5},
        {"type":"FColor", "name":"colorA", "length":5},
        {"type":"FIntPoint", "name":"intpA", "length":5},
        {"type":"FVector2D", "name":"vec2dA", "length":5},
        {"type":"FRotator", "name":"rotA", "length":5},
        {"type":"FDateTime", "name":"datetimeA", "length":5},
        {"type":"FTimespan", "name":"timespanA", "length":5},
        {"type":"FBox", "name":"boxA", "length":5},
        {"type":"FMatrix", "name":"matA", "length":5},
        {"type":"FTransform", "name":"transA", "length":5},
        {"type":"FLinearColor", "name":"lcolorA", "length":5}
    ]
}
```

## Usage
### ProjectBuilder.bat
Run `ProjectBuilder.bat` to automatically generate the files. After generation, import the output directory into your project (**requires including the NetPacket project, i.e., the DLL library, or directly using the source code**).

```bat
bin\Debug-windows-x86_64\StructFileGenerator\StructFileGenerator.exe -i %CD%\Input -o %CD%\Source\NetPacket\Public\Struct

@REM The following commands are for using Visual Studio.

@REM To automatically generate project files and compile in UE, enable the following command.
@REM Generate Visual Studio project files "*.uproject"
@REM Modify the exe directory to your own directory if incorrect: Registry - Computer\HKEY_CLASSES_ROOT\Unreal.ProjectFile\shell\rungenproj\command
@REM Modify the *.uproject to your project directory file.
"C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe" /projectfiles "%CD%\..\..\FZHT_Cpp.uproject"

@REM Compile & build project - Build in VS
@REM Your UE directory, project name Editor (concatenated), platform, configuration, .uproject project location, ...other parameters.
"D:\Unreal Engine\UE_5.1\Engine\Build\BatchFiles\Build.bat" FZHT_CppEditor Win64 DebugGame -Project="%CD%\..\..\FZHT_Cpp.uproject" -WaitMutex -FromMsBuild
@REM pause is useless, the window will close after Build.bat finishes.
pause
```

### Code Usage
- Include header file:
```C++
#include "NPStruct.h"
```
This header file contains all generated data types.

### UE Integration
- `1` Place the entire `NetPacket` folder in the `Plugins` folder of your project to use it as a plugin.
- `2` Add the module name `"NetPacket"` to `PublicDependencyModuleNames` in your project's `{ProjectName}.Build.cs` file.
- `3` Add the following code (module from `2`, and `include`):
```C#
        // Add plugin's public dependency modules
        PublicDependencyModuleNames.AddRange(
            new string[] {
                "NetPacket" // Add plugin module name
            }
        );
        // Add plugin's public and private include paths
        PublicIncludePaths.AddRange(
            new string[] {
                "../Plugins/NetPacket/Source/NetPacket/Public"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                "../Plugins/NetPacket/Source/NetPacket/Private"
            }
        );
```
- `4` Right-click `*.uproject` and generate VS Project File.
- `5` Compile & Build Project.
- `6` Note that the UE version does not have a namespace, while the rest of the library code has the namespace `NetPacket`.
- If compilation errors occur due to `*.cpp` and `*.hpp` first headers, delete the first line `#include "nppch.h"`.
- `Alternative configuration generation`: Modify the command line code in `NetPacket/ProjectBuilder.bat` to generate everything with one click.