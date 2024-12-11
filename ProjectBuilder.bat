@echo off

:: 设置 Unreal Engine 安装路径和项目路径
set UE_PATH="C:\Program Files\Epic Games\UE_4.27\Engine\Build\BatchFiles"
set PROJECT_PATH="C:\Path\To\Your\Project\YourProject.uproject"

:: 1. 生成 Visual Studio 项目文件
echo Generating Visual Studio project files...
cd /d %UE_PATH%
GenerateProjectFiles.bat -project=%PROJECT_PATH% -game

:: 2. 使用 MSBuild 编译项目（不进行清理，增量编译）
echo Building the project...
cd /d %PROJECT_PATH%
msbuild YourProject.sln /p:Configuration=Development_Editor /p:Platform=Win64 /p:BuildProjectReferences=false

:: 3. 完成
echo Build process completed.
pause
