bin\Debug-windows-x86_64\StructFileGenerator\StructFileGenerator.exe -i %CD%\Input -o %CD%\Source\NetPacket\Public\Struct

@REM 下列均为使用 Visual Studio

@REM 若要在UE中自动生成项目文件和编译生成，启用下面的命令行
@REM Generate Visual Studio project files "*.uproject"
@REM exe目录需修改为自己的目录，若不对: 注册表- 计算机\HKEY_CLASSES_ROOT\Unreal.ProjectFile\shell\rungenproj\command
@REM 后面的*.uproject需修改为你的项目目录文件
"C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe" /projectfiles "%CD%\..\..\FZHT_Cpp.uproject"

@REM compile&build project - VS中生成(Build)
@REM 修改为自己的MSBuild.exe路径 自己的解决方案和配置 若要清理然后Build，使用Rebuild
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" %CD%\..\..\FZHT_Cpp.sln /p:Configuration=DebugGame /p:Platform=Win64 /t:Build


pause