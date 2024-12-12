@REM @echo off

@REM :: 设置 Unreal Engine 安装路径和项目路径
@REM set UE_PATH="C:\Program Files\Epic Games\UE_4.27\Engine\Build\BatchFiles"
@REM set PROJECT_PATH="C:\Path\To\Your\Project\YourProject.uproject"

@REM :: 1. 生成 Visual Studio 项目文件
@REM echo Generating Visual Studio project files...
@REM cd /d %UE_PATH%
@REM GenerateProjectFiles.bat -project=%PROJECT_PATH% -game

@REM :: 2. 使用 MSBuild 编译项目（不进行清理，增量编译）
@REM echo Building the project...
@REM cd /d %PROJECT_PATH%
@REM msbuild YourProject.sln /p:Configuration=Development_Editor /p:Platform=Win64 /p:BuildProjectReferences=false

@REM :: 3. 完成
@REM echo Build process completed.

bin\Debug-windows-x86_64\StructFileGenerator\StructFileGenerator.exe -i %CD%\Input -o %CD%\Source\NetPacket\Public\Struct

pause
