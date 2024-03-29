# Prerequisites
1. boost librarie must be installed and added to system variables path
    To Install Boost System-Wide:
        1. Download the Boost library source code from the official website (https://www.boost.org/).
        2. Extract the downloaded package to a directory on your computer.
        . Navigate to the Boost directory in your command-line interface.
        4. Run the Boost.Build installation by executing the bootstrap.bat (for Windows) or bootstrap.sh (for Unix-like systems) script.
        5. After bootstrapping, run the b2 command (or bjam for older versions) to build the Boost libraries. You may need to specify additional options such as toolset and installation directory.
        6. Finally, run b2 install to install Boost libraries globally on your system.
    Add boost lib and header paths to system variables (paths may diferent, depending on your instalation):
        1. C:\Boost\lib
        2. C:\Boost\include\boost-1_84
2. CMake build system installed
3. Windows SDK https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/


