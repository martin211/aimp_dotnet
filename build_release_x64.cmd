:; set -eo pipefail
:; SCRIPT_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)
:; ${SCRIPT_DIR}/build.sh "$@"
:; exit $?

@ECHO OFF
powershell -ExecutionPolicy ByPass -NoProfile -File "%~dp0build.ps1" -Configuration Release -TargetPlatform x64
powershell -ExecutionPolicy ByPass -NoProfile -File "%~dp0build.ps1" -Configuration Release -TargetPlatform x64 --Target Pack