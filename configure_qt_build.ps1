$ErrorActionPreference = 'Stop'

# Change only local Qt Creator build paths, after the editor has saved its state.
if (Get-Process -Name qtcreator -ErrorAction SilentlyContinue) {
    Write-Host 'Please close Qt Creator completely, then run this launcher again.'
    exit 2
}

$projectRoot = 'C:\Users\35452\Desktop\DigitRecnition'
$settingsFile = Join-Path $projectRoot '.qtcreator\CMakeLists.txt.user'
if (Test-Path -LiteralPath $settingsFile) {
    [xml]$projectSettings = Get-Content -LiteralPath $settingsFile -Raw -Encoding UTF8
    $buildDirectoryNodes = $projectSettings.SelectNodes(
        '//value[@key="ProjectExplorer.BuildConfiguration.BuildDirectory"]')
    foreach ($directoryNode in $buildDirectoryNodes) {
        $typeNode = $directoryNode.ParentNode.SelectSingleNode('value[@key="CMake.Build.Type"]')
        if ($null -eq $typeNode) { continue }
        $buildType = $typeNode.InnerText
        if ($buildType -notmatch '^[A-Za-z0-9_-]+$') {
            throw 'Unexpected CMake build type.'
        }
        $directoryNode.InnerText = Join-Path $projectRoot ('build\' + $buildType)
    }
    $projectSettings.Save($settingsFile)
}
Write-Host 'Qt project: C:\Users\35452\Desktop\DigitRecnition\CMakeLists.txt'
Write-Host 'Debug build: C:\Users\35452\Desktop\DigitRecnition\build\Debug'
exit 0
