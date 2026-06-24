$ErrorActionPreference = "Stop"

$clangFormat = Get-Command clang-format -ErrorAction SilentlyContinue

if (-not $clangFormat) {
    throw "clang-format was not found on PATH. Close/reopen PowerShell after adding it to PATH, then try again."
}

Get-ChildItem -Recurse -Include *.cpp,*.hpp,*.h,*.cc,*.cxx,*.hh,*.hxx,*.ixx |
    Where-Object {
        $_.FullName -notmatch '\\.git\\' -and
        $_.FullName -notmatch '\\build' -and
        $_.FullName -notmatch '\\out\\' -and
        $_.FullName -notmatch '\\third_party\\' -and
        $_.FullName -notmatch '\\external\\'
    } |
    ForEach-Object {
        Write-Host "Formatting $($_.FullName)"
        & $clangFormat.Source -i $_.FullName
    }

Write-Host "Formatting complete."