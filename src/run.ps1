# Define directories and file names
$sourceDir = ".\src"  # Directory containing source files
$outputDir = ".\bin"  # Output directory for the compiled executable
$outputFile = "game.exe"  # Output executable name
$sdlLibs = @("SDL2.dll", "SDL2_image.dll", "SDL2_mixer.dll", "SDL2_ttf.dll")  # SDL libraries to copy to output


# Paths for SDL2 headers and libraries (adjust these paths for your setup)
$sdlIncludePath = ".\libs\sdl2\include"
$sdlLibPath = ".\libs\sdl2\lib"

# Update compile flags to include paths



# Ensure output directory exists
if (!(Test-Path -Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir
}

# Find all source files
$sourceFiles = Get-ChildItem -Path $sourceDir -Filter "*.c" -Recurse | ForEach-Object { $_.FullName }

if (-not $sourceFiles) {
    Write-Host "No source files found in $sourceDir" -ForegroundColor Red
    exit 1
}

# Set compiler and flags
$compiler = "gcc"
$compileFlags = "-I$sdlIncludePath -L$sdlLibPath -L$sourceDir -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -std=c99 -Wall -Wextra -I$sourceDir"
$compileCommand = "$compiler $($sourceFiles -join ' ') $compileFlags -o $outputDir\$outputFile"

# Compile the source files
Write-Host "Compiling source files..." -ForegroundColor Yellow
Write-Host "Running: $compileCommand" -ForegroundColor Cyan

Invoke-Expression -Command $compileCommand

if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation failed!" -ForegroundColor Red
    exit 1
}

Write-Host "Compilation successful. Output: $outputDir\$outputFile" -ForegroundColor Green

# Copy SDL libraries to the output directory
foreach ($lib in $sdlLibs) {
    $libPath = Join-Path -Path $sourceDir -ChildPath $lib
    if (Test-Path -Path $libPath) {
        Copy-Item -Path $libPath -Destination $outputDir
        Write-Host "Copied $lib to $outputDir" -ForegroundColor Green
    } else {
        Write-Host "Warning: $lib not found in $sourceDir" -ForegroundColor Yellow
    }
}

# Run the executable
Write-Host "Running the program..." -ForegroundColor Yellow
Invoke-Expression -Command "cd $outputDir"
$executionCommand = ".\$outputFile"
Invoke-Expression -Command $executionCommand
Invoke-Expression -Command "cd ..\"
