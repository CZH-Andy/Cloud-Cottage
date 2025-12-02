@echo off
chcp 65001 >nul
echo 正在编译 Cloud Cottage 程序...
echo.

g++ -o CloudCottage.exe main.cpp User.cpp Room.cpp Order.cpp Comment.cpp System.cpp Utils.cpp AdminMenu.cpp TouristMenu.cpp -std=c++20 2>error.log

if %errorlevel% equ 0 (
    echo [成功] 编译成功！
    echo.
    echo 可执行文件: CloudCottage.exe
    if exist error.log del error.log
) else (
    echo [失败] 编译失败！
    echo.
    echo 请查看 error.log 文件了解详细错误信息。
    echo.
    type error.log
)

echo.
pause
