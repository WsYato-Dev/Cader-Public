@echo off
set "VulkanPath=VK_SDK_PATH"

set "CompileDir=../Compiled"
echo Compile Directory set to '%CompileDir%'
echo.

echo Commands:
echo -cdir 'dir':   Sets the compile to directory relative to the current directory
echo -s 'file':     Compiles a single file
echo -all:          Compiles every .vert and .frag file
echo -q:            Quit
echo.

:COMMAND
set /p "Command=Command: "

if "%Command:~0, 6%" == "-cdir " (
	set CompileDir="%Command:~6%"
	echo %CompileDir%
	echo.
	goto COMMAND
) else if "%Command:~0, 3%" == "-s " (
	echo Compiling '%Command:~3%'
	call "%%%VulkanPath%%%\Bin\glslc.exe" "%Command:~3%" -o "%CompileDir%/%Command:~3%.spv"
	echo Compiled '%Command:~3%' To '%Command:~3%.spv'
	echo.
	goto COMMAND
) else if "%Command%" == "-all" (
	for %%v in (*.vert) do (
		echo Compiling '%%v'
		call "%%%VulkanPath%%%\Bin\glslc.exe" "%%v" -o "%CompileDir%/%%v.spv"
		echo Compiled '%%v' To '%%v.spv'
		echo.
	)

	for %%f in (*.frag) do (
		echo Compiling '%%f'
		call "%%%VulkanPath%%%\Bin\glslc.exe" "%%f" -o "%CompileDir%/%%f.spv"
		echo Compiled '%%f' To '%%f.spv'
		echo.
	)
)else if "%Command%" == "-q" (
	goto eof
) else (
	echo Unknown command: '%Command%'
	echo.
	goto COMMAND
)

pause