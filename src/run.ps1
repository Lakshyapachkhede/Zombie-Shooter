# PowerShell script to compile and run SDL2 project

$fileName = 'main'

# Define the commands
$compileCommand = "gcc $fileName.c -o $fileName -Isrc\include -Lsrc\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image"
$executeCommand = ".\$fileName.exe"

# Execute the compile command
Write-Host "Compiling the program..."
Invoke-Expression $compileCommand

# Check if the compilation succeeded
if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful. Running the program..."
    Invoke-Expression $executeCommand
} else {
    Write-Host "Compilation failed. Please check for errors."
}
