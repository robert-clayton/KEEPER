
$OutputPath = "$PSScriptRoot\dist\"
$OutputName = "KEEPER.exe"
$SDLIncludePath = "E:\Development\SDL2\include"
$SDLLibPath = "E:\Development\SDL2\lib"

$SourcePrivate = @(
    "$PSScriptRoot\src\*.cpp",
    "$PSScriptRoot\src\ecs\*.cpp",
    "$PSScriptRoot\src\math\*.cpp"
)
$SourcePublic = @(
    "$PSScriptRoot\src",
    "$PSScriptRoot\src\ecs",
    "$PSScriptRoot\src\math"
)

# Ensure output path exists
New-Item -ItemType Directory -Force -Path $OutputPath | Out-Null

# Construct g++ command
$Command = "g++ -std=c++17 -O3 -g "
ForEach ($Item in $SourcePrivate) {
    $Command += "$Item "
}
$Command += "-o " + $OutputPath + $OutputName + " "
# $Command += "-c -o '$PSScriptRoot\dist' "
ForEach ($Item in $SourcePublic) {
    $Command += "-I$Item "
}
$Command += "-I$SDLIncludePath -L$SDLLibPath -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -mwindows"

Write-Host $Command
Invoke-Expression $Command
# Invoke-Expression "$OutputPath$OutputName"