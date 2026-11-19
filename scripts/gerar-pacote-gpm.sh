#!/usr/bin/env bash
# Gera um pacote .gpm a partir de um diretorio de payload.
# Uso: gerar-pacote-gpm.sh <nome> <versao> <release> <payload-dir> <saida-dir> \
#          [--depends a,b] [--conflicts c] [--descricao "texto"]
set -Eeuo pipefail
RAIZ="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
source "$RAIZ/scripts/biblioteca.sh"

[[ $# -ge 5 ]] || erro "uso: gerar-pacote-gpm.sh <nome> <versao> <release> <payload-dir> <saida-dir> [opcoes]"
nome=$1 versao=$2 release=$3 payload=$4 saida=$5
shift 5
depends=
conflicts=
descricao=
while (( $# )); do
    case "$1" in
        --depends) depends=$2; shift 2 ;;
        --conflicts) conflicts=$2; shift 2 ;;
        --descricao) descricao=$2; shift 2 ;;
        *) erro "opção desconhecida: $1" ;;
    esac
done

[[ "$nome" =~ ^[a-z0-9][a-z0-9+_.-]{0,127}$ ]] || erro "nome de pacote inválido: $nome"
[[ "$versao" =~ ^[A-Za-z0-9][A-Za-z0-9+_.~-]*$ ]] || erro "versão inválida: $versao"
[[ "$release" =~ ^[1-9][0-9]*$ ]] || erro "release inválido: $release"
[[ -d "$payload" ]] || erro "payload ausente: $payload"
[[ "$descricao" != *"|"* && "$descricao" != *$'\n'* ]] || erro "descrição não pode ter '|' nem quebra de linha"
for lista in "$depends" "$conflicts"; do
    [[ -z "$lista" || "$lista" =~ ^[a-z0-9][a-z0-9+_.-]*(,[a-z0-9][a-z0-9+_.-]*)*$ ]] || erro "lista de nomes inválida: $lista"
done

area="$(mktemp -d)"
trap 'rm -rf -- "$area"' EXIT
mkdir -p -- "$area/GPM" "$area/payload" "$saida"
# Copia o payload preservando modos e links; o dono vira root:root, como o instalador espera.
cp -a -- "$payload/." "$area/payload/"
find "$area/payload" -exec touch -h -d "@$SOURCE_DATE_EPOCH" {} +
cat > "$area/GPM/MANIFEST" <<EOF
Name=$nome
Version=$versao
Release=$release
Architecture=x86_64
Description=$descricao
Depends=$depends
Provides=
Conflicts=$conflicts
Replaces=
EOF

arquivo="$nome-$versao-$release-x86_64.gpm"
(
    cd -- "$area"
    tar --format=ustar --owner=0 --group=0 --numeric-owner --sort=name --mtime="@$SOURCE_DATE_EPOCH" \
        -cf - GPM/MANIFEST payload
) | gzip -n -9 > "$saida/$arquivo"
mensagem "Pacote gerado: $saida/$arquivo"
