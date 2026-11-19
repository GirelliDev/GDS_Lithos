#!/usr/bin/env bash
# Gera o indice do repositorio gpm a partir dos pacotes .gpm e assina com a chave de release.
# Uso: indexar-gpm.sh <dir-com-pacotes> <chave-privada.pem> <saida-dir>
# A chave privada NUNCA fica no servidor: o indice e assinado onde ela estiver.
set -Eeuo pipefail
RAIZ="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
source "$RAIZ/scripts/biblioteca.sh"

[[ $# -eq 3 ]] || erro "uso: indexar-gpm.sh <dir-com-pacotes> <chave-privada.pem> <saida-dir>"
pacotes=$1 chave=$2 saida=$3
[[ -d "$pacotes" ]] || erro "diretório de pacotes ausente: $pacotes"
[[ -f "$chave" ]] || erro "chave privada ausente: $chave"
exigir_comando openssl
exigir_comando sha256sum

mkdir -p -- "$saida"
indice="$saida/index"
: > "$indice.tmp"
shopt -s nullglob
for pacote in "$pacotes"/*.gpm; do
    arquivo=$(basename -- "$pacote")
    manifest=$(tar -xzOf "$pacote" GPM/MANIFEST 2>/dev/null) ||
        manifest=$(tar -xOf "$pacote" GPM/MANIFEST 2>/dev/null) ||
        erro "MANIFEST ilegível em $arquivo"
    # Campos vêm como Chave=Valor; cada um vira uma variavel por awk.
    campo() { printf '%s\n' "$manifest" | awk -F= -v k="$1" '$1==k {sub(/^[^=]*=/, ""); print; exit}'; }
    nome=$(campo Name); versao=$(campo Version); release=$(campo Release)
    depends=$(campo Depends); conflicts=$(campo Conflicts); descricao=$(campo Description)
    [[ "$arquivo" == "$nome-$versao-$release-x86_64.gpm" ]] || erro "nome de arquivo diverge do MANIFEST: $arquivo"
    [[ "$descricao" != *"|"* ]] || erro "descrição com '|' em $arquivo"
    hash=$(sha256sum "$pacote"); hash=${hash%% *}
    printf '%s|%s|%s|x86_64|%s|%s|%s|%s|%s\n' \
        "$nome" "$versao" "$release" "$arquivo" "$hash" "$depends" "$conflicts" "$descricao" >> "$indice.tmp"
done
sort -t'|' -k1,1 "$indice.tmp" > "$indice"
rm -f -- "$indice.tmp"

# Pacotes publicados em pacotes/ ficam no mesmo diretorio de saida do indice.
for pacote in "$pacotes"/*.gpm; do
    cp -- "$pacote" "$saida/"
    openssl pkeyutl -sign -inkey "$chave" -rawin -digest sha256 \
        -pkeyopt rsa_padding_mode:pss -pkeyopt rsa_pss_saltlen:digest \
        -in "$pacote" -out "$saida/$(basename -- "$pacote").sig"
done
openssl pkeyutl -sign -inkey "$chave" -rawin -digest sha256 \
    -pkeyopt rsa_padding_mode:pss -pkeyopt rsa_pss_saltlen:digest \
    -in "$indice" -out "$indice.sig"
mensagem "Índice e assinaturas gerados em $saida ($(wc -l < "$indice") pacote(s))"
