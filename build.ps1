
$OutputPath = "$PSScriptRoot\dist\"
$OutputName = "KEEPER.exe"
$SDLIncludePath = "E:\Development\SDL2\include"
$SDLLibPath = "E:\Development\SDL2\lib"

$SourcePrivate = @(
    "$PSScriptRoot\src\*.cpp",
    "$PSScriptRoot\src\ecs\*.cpp"
)
$SourcePublic = @(
    "$PSScriptRoot\src",
    "$PSScriptRoot\src\ecs"
)

# Ensure output path exists
New-Item -ItemType Directory -Force -Path $OutputPath | Out-Null

# Construct g++ command
$Command = "g++ -pipe -g "
ForEach ($Item in $SourcePrivate) {
    $Command += "$Item "
}
$Command += "-o " + $OutputPath + $OutputName + " "
ForEach ($Item in $SourcePublic) {
    $Command += "-I$Item "
}
$Command += "-I$SDLIncludePath -L$SDLLibPath -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image -mwindows"

Write-Host $Command
Invoke-Expression $Command