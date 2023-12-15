#!/bin/env bash

# shellcheck disable=SC2155
dir=$(dirname "$(readlink -f "$0")")

run106() {
    local executable=$1
    local executable_path="$dir/bin/$executable"

    if [[ -x $executable_path ]]; then
        echo "Running $executable..."
        "$executable_path" "$@"
    else
        echo "Executable $executable not found."
    fi
}

_run106_complete() {
    local executables=()
    for f in "$dir"/bin/*; do
        if [[ -x $f ]]; then
            executables+=("$(basename "$f")")
        fi
    done
    # shellcheck disable=SC2128
    _arguments "1:executable:($executables)"
}

# 注册 curses_run 的 zsh 完成脚本
compdef _run106_complete run106
