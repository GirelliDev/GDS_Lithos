#!/usr/bin/env bash
set -Eeuo pipefail
RAIZ="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
source "$RAIZ/scripts/biblioteca.sh"
for cmd in gcc python3 sh; do exigir_comando "$cmd"; done
mkdir -p "$COMPILACAO/gpm" "$LOGS"
# Native host test helper is never installed. Production uses compilar-gpm.sh.
gcc -std=c11 -O2 -Wall -Wextra -Werror -o "$COMPILACAO/gpm/arquivo-host-testes" "$FONTES/gpm/arquivo.c"
python3 "$RAIZ/testes/gpm/testar.py" | tee "$LOGS/gpm-unitarios.log"
