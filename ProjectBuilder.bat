bin\Debug-windows-x86_64\StructFileGenerator\StructFileGenerator.exe -i %CD%\Input -o %CD%\Source\NetPacket\Public\Struct

@REM 下列均为使用 Visual Studio

@REM 若要在UE中自动生成项目文件和编译生成，启用下面的命令行
@REM Generate Visual Studio project files "*.uproject"
@REM exe目录需修改为自己的目录，若不对: 注册表- 计算机\HKEY_CLASSES_ROOT\Unreal.ProjectFile\shell\rungenproj\command
@REM 后面的*.uproject需修改为你的项目目录文件
@REM "C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe" /projectfiles "%CD%\..\..\FZHT_Cpp.uproject"

@REM compile&build project - VS中生成(Build)
@REM 自己的UE目录 项目名称Editor(拼接) 平台 配置 所在.uproject项目 ...其余参数
@REM "D:\Unreal Engine\UE_5.1\Engine\Build\BatchFiles\Build.bat" FZHT_CppEditor Win64 DebugGame -Project="%CD%\..\..\FZHT_Cpp.uproject" -WaitMutex -FromMsBuild

@REM pause无用，Build.bat执行完成后会关闭窗口
pause

