SHELL := cmd.exe
CYGWIN=nontsec
export PATH := C:\Program Files\ImageMagick-7.0.9-Q8;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\DX-Union\bin\;C:\Program Files (x86)\GTK2-Runtime\bin;C:\Program Files (x86)\Python36-32;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\DTS\Binn\;C:\Program Files\MATLAB R2019b\runtime\win64;C:\Program Files\MATLAB R2019b\bin;C:\Users\grebiena18\AppData\Local\Microsoft\WindowsApps;C:\Users\grebiena18\AppData\Local\Microsoft\WindowsApps
export AS_BUILD_MODE := Rebuild
export AS_VERSION := 4.7.2.98
export AS_COMPANY_NAME := FH JOANNEUM Gesellschaft mbH
export AS_USER_NAME := grebiena18
export AS_PATH := C:/AutomationStudio/AS47
export AS_BIN_PATH := C:/AutomationStudio/AS47/bin-en
export AS_PROJECT_PATH := D:/ia/Foerderband
export AS_PROJECT_NAME := Foerderband
export AS_SYSTEM_PATH := C:/AutomationStudio/AS/System
export AS_VC_PATH := C:/AutomationStudio/AS47/AS/VC
export AS_TEMP_PATH := D:/ia/Foerderband/Temp
export AS_CONFIGURATION := station_6
export AS_BINARIES_PATH := D:/ia/Foerderband/Binaries
export AS_GNU_INST_PATH := C:/AutomationStudio/AS47/AS/GnuInst/V4.1.2
export AS_GNU_BIN_PATH := $(AS_GNU_INST_PATH)/bin
export AS_GNU_INST_PATH_SUB_MAKE := C:/AutomationStudio/AS47/AS/GnuInst/V4.1.2
export AS_GNU_BIN_PATH_SUB_MAKE := $(AS_GNU_INST_PATH_SUB_MAKE)/bin
export AS_INSTALL_PATH := C:/AutomationStudio/AS47
export WIN32_AS_PATH := "C:\AutomationStudio\AS47"
export WIN32_AS_BIN_PATH := "C:\AutomationStudio\AS47\bin-en"
export WIN32_AS_PROJECT_PATH := "D:\ia\Foerderband"
export WIN32_AS_SYSTEM_PATH := "C:\AutomationStudio\AS\System"
export WIN32_AS_VC_PATH := "C:\AutomationStudio\AS47\AS\VC"
export WIN32_AS_TEMP_PATH := "D:\ia\Foerderband\Temp"
export WIN32_AS_BINARIES_PATH := "D:\ia\Foerderband\Binaries"
export WIN32_AS_GNU_INST_PATH := "C:\AutomationStudio\AS47\AS\GnuInst\V4.1.2"
export WIN32_AS_GNU_BIN_PATH := "$(WIN32_AS_GNU_INST_PATH)\\bin" 
export WIN32_AS_INSTALL_PATH := "C:\AutomationStudio\AS47"

.suffixes:

ProjectMakeFile:

	@'$(AS_BIN_PATH)/BR.AS.AnalyseProject.exe' '$(AS_PROJECT_PATH)/Foerderband.apj' -t '$(AS_TEMP_PATH)' -c '$(AS_CONFIGURATION)' -o '$(AS_BINARIES_PATH)'   -sfas -buildMode 'Rebuild'   

