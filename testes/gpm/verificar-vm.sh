#!/bin/sh
set -eu
[ "$(id -u)" -eq 0 ]
base=/tmp/gpm-fixtures
mkdir -p "$base"
for file in index gpm-abi-test.gpm curl; do
    /usr/bin/curl --fail --max-time 20 "http://10.0.2.2:18991/compilacao/gpm-vm-fixtures/$file" -o "$base/$file"
done
chmod 755 "$base/curl"
# Raiz isolada e nova: o transporte é um double local, não o archive oficial.
GPM_ROOT=$(mktemp -d /tmp/gpm-vm.XXXXXX)
export GPM_ROOT
mkdir -p "$GPM_ROOT/etc/gpm/repos.d"
printf '[fixture]\nServer = https://fixtures.invalid/$arch\nEnabled = yes\nSigLevel = Optional\n' > "$GPM_ROOT/etc/gpm/repos.d/fixture.repo"
PATH="$base:$PATH"
export PATH
gpm update
gpm search DInAMICA
gpm info gpm-abi-test
gpm install gpm-abi-test
gpm list | grep '^gpm-abi-test 1.0-1$'
gpm info gpm-abi-test | grep 'Installed: yes'
/lib64/ld-linux-x86-64.so.2 --list "$GPM_ROOT/usr/bin/hello-gpm"
"$GPM_ROOT/usr/bin/hello-gpm"
gpm remove gpm-abi-test
[ ! -e "$GPM_ROOT/usr/bin/hello-gpm" ]
[ ! -e "$GPM_ROOT/var/lib/gpm/db/installed/gpm-abi-test" ]
[ ! -s "$GPM_ROOT/var/lib/gpm/db/ownership" ]
[ "$(gpm list | wc -l)" -eq 0 ]
echo GPM_VM_INSTALACAO_REMOCAO_OK
