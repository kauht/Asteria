@echo off
REM Build script for cs2-sdk Rust binary
REM This generates the C++ SDK headers

cd /d "C:\Users\macin\Desktop\asteria\vendor\cs2-sdk"
echo Building cs2-sdk Rust binary...
cargo run --release --bin cs2-sdk

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✓ cs2-sdk build completed successfully
    echo Headers should be in: C:\Users\macin\Desktop\asteria\vendor\cs2-sdk\include\sdk\
    echo.
    cd /d "C:\Users\macin\Desktop\asteria"
    echo Now building with xmake...
    xmake
) else (
    echo.
    echo ✗ cs2-sdk build failed
    exit /b 1
)
