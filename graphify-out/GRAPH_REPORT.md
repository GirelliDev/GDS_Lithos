# Graph Report - gds_lithos  (2026-11-18)

## Corpus Check
- Corpus is ~37,618 words - fits in a single context window. You may not need a graph.

## Summary
- 607 nodes · 962 edges · 78 communities (46 shown, 32 thin omitted)
- Extraction: 88% EXTRACTED · 12% INFERRED · 0% AMBIGUOUS · INFERRED: 112 edges (avg confidence: 0.69)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- Control Client Core
- NT Object Headers
- Build Config Scripts
- POSIX System Headers
- Process Supervisor Logic
- Python Stdlib Imports
- Toolchain Versions
- Build Helper Functions
- Base ABI Build Variables
- ELF Audit Scripts
- Toolchain Build Helpers
- CPM Package Rules
- Lithos CLI and Image Scripts
- Toolchain Stage Builds
- CoreLabs OS Feature Slides
- CorelabsOS Brand Poster
- Brand Slide Keywords
- KDE Branding Slide
- CoreLabs OS Focus Promo
- ELF Audit and Test Programs
- Popular and Stable Slide
- Mission and Hardware Requirements
- Open Source Slide
- Lithos Base ABI v1
- Support Channels Slide
- Installer and Boot Flow
- Security Audit Scripts
- Verification Scripts
- CPM Package Format
- Calamares Welcome Banner
- OEM Welcome Banner
- Monochrome Logo Set
- Kernel and QEMU Config
- ABI Audit Tests
- Shutdown Scripts
- Startup Scripts
- Supervisor Tests
- Icon Logo Mark
- Calamares Logo
- Corelabs Logo Set
- Inverted Logo Variant
- Inverted Logo Parts
- Monochrome Logo Parts
- Lithos Logo Set
- Package Database Lock
- Banner Renderer
- Installer Prep Script
- Logging Script
- Descendant Tests
- Premature Exit Tests
- Real Installer Tests
- Clcontrol Build Script
- Control Build Script
- Supervisor Build Script
- System Verify Script
- Mock ID Helper
- Mock MV Helper
- Mock Stat Helper
- VM Verify Script
- Service Order Tests
- Logo Mark Standalone

## God Nodes (most connected - your core abstractions)
1. `mensagem()` - 36 edges
2. `erro()` - 33 edges
3. `exigir_comando()` - 24 edges
4. `fail()` - 15 edges
5. `baixar_verificado()` - 14 edges
6. `Lithos` - 14 edges
7. `unpack()` - 12 edges
8. `apply()` - 11 edges
9. `preparar_diretorios()` - 10 edges
10. `compilar-toolchain.sh script` - 10 edges

## Surprising Connections (you probably didn't know these)
- `Arte ASCII em branding/system` --conceptually_related_to--> `Lithos`  [AMBIGUOUS]
  branding/system/ascii.txt → README.md
- `Lithos.sh script` --calls--> `kernel.sh script`  [EXTRACTED]
  Lithos.sh → scripts/kernel.sh
- `Lithos.sh script` --calls--> `imagem.sh script`  [EXTRACTED]
  Lithos.sh → scripts/imagem.sh
- `Lithos.sh script` --calls--> `initramfs.sh script`  [EXTRACTED]
  Lithos.sh → scripts/initramfs.sh
- `Lithos.sh script` --calls--> `rootfs.sh script`  [EXTRACTED]
  Lithos.sh → scripts/rootfs.sh

## Import Cycles
- None detected.

## Hyperedges (group relationships)
- **Cadeia de boot e disco** — readme_grub, readme_ovmf, readme_qemu, readme_rootfs_ext4, readme_disco_qcow2 [INFERRED 0.75]
- **Responsabilidades do supervisor** — fontes_clsupervisor_readme_inicializacao_processo, fontes_clsupervisor_readme_deteccao_encerramento, fontes_clsupervisor_readme_limite_reinicializacao, fontes_clsupervisor_readme_encaminhamento_sinais, fontes_clsupervisor_readme_aguardo_filhos, fontes_clsupervisor_readme_registro_eventos [INFERRED 0.75]
- **Pipeline de construcao da Base ABI v1** — documentacao_base_abi_v1_gcc, documentacao_base_abi_v1_glibc, documentacao_base_abi_v1_sysroot, documentacao_base_abi_v1_coreutils, documentacao_base_abi_v1_util_linux [EXTRACTED 1.00]
- **Cadeia de seguranca de instalacao do CPM** — documentacao_cpm_assinatura_rsa_pss, documentacao_cpm_index, documentacao_cpm_formato_pacote_cpm, documentacao_cpm_lock_flock, documentacao_cpm_transacoes_rollback [EXTRACTED 1.00]
- **Fluxo de instalacao e boot persistente** — documentacao_sistema_persistente_instalador_lithos, documentacao_sistema_persistente_initramfs_transicao, documentacao_sistema_persistente_boot_uefi, documentacao_sistema_persistente_teste_persistencia [INFERRED 0.75]
- **Provas de ABI da Base v1** — documentacao_validacao_base_abi_v1_hello_c, documentacao_validacao_base_abi_v1_hello_cpp, documentacao_validacao_base_abi_v1_auditoria_elf, documentacao_validacao_base_abi_v1_testes_negativos [INFERRED 0.75]
- **Gates de seguranca do CPM v0.2** — documentacao_validacao_cpm_v0_2_transacao_instalacao, documentacao_validacao_cpm_v0_2_helper_archive, documentacao_validacao_cpm_v0_2_protecao_ownership, documentacao_validacao_cpm_v0_2_locking_flock [INFERRED 0.75]
- **Corelabs Brand Identity on Welcome Slide** — branding_calamares_01_corelabs_logo, branding_calamares_01_corelabs_os, branding_calamares_01_tagline, branding_calamares_01_slogan [INFERRED 0.75]
- **Bundled KDE desktop app suite** — branding_calamares_03_dolphin, branding_calamares_03_kate, branding_calamares_03_spectacle, branding_calamares_03_okular, branding_calamares_03_preferences [INFERRED 0.75]
- **Corelabs docs and support channels** — branding_calamares_04_corelabs_os_howtos, branding_calamares_04_corelabs_discourse, branding_calamares_04_askcorelabs, branding_calamares_04_matrix_live_support [EXTRACTED 1.00]
- **Third-party apps featured on the CORELABS OS slide** — branding_calamares_05_firefox, branding_calamares_05_thunderbird, branding_calamares_05_libreoffice, branding_calamares_05_haruna, branding_calamares_05_discover [INFERRED 0.75]
- **User freedom pillars (privacy, no ads, update control, local accounts)** — branding_calamares_07_no_phone_home_privacy, branding_calamares_07_distraction_free_navigation, branding_calamares_07_uninterrupted_updates, branding_calamares_07_local_accounts [INFERRED 0.75]
- **Open source freedoms promoted by CoreLabs OS (install, study, modify, distribute, contribute)** — branding_calamares_09_open_source_software, branding_calamares_09_corelabs_os, branding_calamares_09_contribute_to_corelabs [INFERRED 0.75]
- **Logo lockup: emblem stacked above wordmark** — branding_logos_logo_invertida_orbital_emblem, branding_logos_logo_invertida_corelabs_systems [EXTRACTED 1.00]
- **CoreLabs Systems logo lockup** — branding_logos_logo_monocromatica_planet_ring_emblem, branding_logos_logo_monocromatica_corelabs_wordmark, branding_logos_logo_monocromatica_systems_subtitle [EXTRACTED 1.00]

## Communities (78 total, 32 thin omitted)

### Community 0 - "Control Client Core"
Cohesion: 0.07
Nodes (14): conectar(), main(), operacao_valida(), autorizado(), criar_socket(), grupo_presente(), main(), operacao_valida() (+6 more)

### Community 1 - "NT Object Headers"
Cohesion: 0.12
Nodes (19): OBJECT_HEADER, _OBJECT_HEADER, POBJECT_HEADER, default_destructor(), ObCloseHandle(), ObCreateObject(), ObDereferenceObject(), ObInitialize() (+11 more)

### Community 3 - "Build Config Scripts"
Cohesion: 0.09
Nodes (15): atualizar-identidade.sh script, LC_ALL, biblioteca.sh script, SOURCE_DATE_EPOCH, TZ, inspecionar-disco.sh script, instalar-sentinel.sh script, instalar.sh script (+7 more)

### Community 4 - "POSIX System Headers"
Cohesion: 0.23
Nodes (20): abi_file(), add_dir(), apply(), check(), copy_data(), fail(), field(), find_entry() (+12 more)

### Community 5 - "Process Supervisor Logic"
Cohesion: 0.09
Nodes (24): Arte ASCII em branding/system, Aguardar termino dos processos filhos, Deteccao de encerramento inesperado, Encaminhamento de sinais de encerramento, Inicializar processo supervisionado, Limites de reinicializacao, Lithos Supervisor, PID 1 (ciclo de vida geral do SO) (+16 more)

### Community 6 - "Python Stdlib Imports"
Cohesion: 0.11
Nodes (3): package(), run(), sign_server()

### Community 7 - "Toolchain Versions"
Cohesion: 0.10
Nodes (20): Comando auditar-elf (auditoria ELF com readelf), Autenticidade das fontes (gpgv, SHA-256 fixados), BusyBox estatico (/bin/busybox, ash), Coreutils 9.11, GCC 16.2.0 toolchain (C/C++), glibc 2.44 com upstream_fixes-2 e FHS, Target GNU x86_64-Lithos-linux-gnu, Lithos Base ABI v1 (+12 more)

### Community 8 - "Build Helper Functions"
Cohesion: 0.20
Nodes (13): baixar_verificado(), mensagem(), preparar_diretorios(), compilar-base-abi.sh script, compilar-bash.sh script, compilar-curl.sh script, compilar-openssl.sh script, compilar-sudo.sh script (+5 more)

### Community 9 - "Base ABI Build Variables"
Cohesion: 0.12
Nodes (15): AR, CC, CFLAGS, CPPFLAGS, CXX, CXXFLAGS, LC_ALL, LDFLAGS (+7 more)

### Community 10 - "ELF Audit Scripts"
Cohesion: 0.13
Nodes (9): LC_ALL, auditar-elf.sh script, exigir_comando(), compilar-cpm.sh script, preparar-emergencia.sh script, preparar-inspecao.sh script, LC_ALL, testar-base-abi.sh script (+1 more)

### Community 11 - "Toolchain Build Helpers"
Cohesion: 0.24
Nodes (10): erro(), numero_trabalhos(), executar_etapa(), publicar_loader(), compilar-toolchain.sh script, dependencias.sh script, executar_boot(), testar-persistencia.sh script (+2 more)

### Community 13 - "CPM Package Rules"
Cohesion: 0.18
Nodes (9): Archive oficial vazio (bloqueio de teste end-to-end), Gate scripts/auditar-seguranca.sh, Chave publica por repositorio em /etc/cpm/keyrings, CPM v0.2 (gerenciador de pacotes Lithos), Helper C de inspecao de archive ustar, Locking com flock, Protecao de ownership de arquivos, Transacao de instalacao com staging e journal (+1 more)

### Community 14 - "Lithos CLI and Image Scripts"
Cohesion: 0.24
Nodes (6): mostrar_ajuda(), Lithos.sh script, imagem.sh script, initramfs.sh script, definir_config(), rootfs.sh script

### Community 15 - "Toolchain Stage Builds"
Cohesion: 0.24
Nodes (5): CONFIG_SHELL, configurar_gcc(), gcc_final(), gcc_inicial(), LC_ALL

### Community 16 - "CoreLabs OS Feature Slides"
Cohesion: 0.22
Nodes (8): CORELABS OS, Discover (Software Center), Firefox (Web Browser), Haruna (Video Player), LibreOffice (Office Suite), Synaptic (package manager), Third-Party Apps: Best-in-class (slide), Thunderbird (Email Client)

### Community 17 - "CorelabsOS Brand Poster"
Cohesion: 0.31
Nodes (5): CorelabsOS Secure and Private Poster, Brand taglines (Open, Secure, Productive, Together; Freedom Today, A Brighter Tomorrow; People, Technology, Opportunity), CorelabsOS, Files App Window Mockup, No Ads Badge

### Community 18 - "Brand Slide Keywords"
Cohesion: 0.29
Nodes (5): Corelabs Systems Logo, Corelabs OS, Earth-from-Space Night Background, Slide Progress Indicator (01 / 09), Corelabs OS Welcome Slide (01/09)

### Community 19 - "KDE Branding Slide"
Cohesion: 0.46
Nodes (7): Corelabs OS KDE Branding Slide, Corelabs OS: KDE, Dolphin (File Manager), Kate (Text Editor), Okular (PDF Viewer), Preferences (System Settings), Spectacle (Screen Capture)

### Community 20 - "CoreLabs OS Focus Promo"
Cohesion: 0.32
Nodes (4): CoreLabs OS Focus: Systems for Pros promo slide, CoreLabs OS, CoreLabs OS Focus, Stable, Secure, Productive brand pillars

### Community 21 - "ELF Audit and Test Programs"
Cohesion: 0.25
Nodes (7): Auditoria ELF e separacao do host, Toolchain GCC 16.2.0 com Binutils 2.47, glibc 2.44, hello-Lithos C (programa de prova), hello-Lithos C++ (programa de prova), Sete fixtures negativas da auditoria ABI, Validacao da Lithos Base ABI v1 (2026-10-01)

### Community 22 - "Popular and Stable Slide"
Cohesion: 0.29
Nodes (7): Corelabs OS Popular and Stable slide, Application and driver compatibility, Corelabs OS, Corelabs Systems brand, LTS (Long Term Support), Target use cases: home, study, work, professional, Ubuntu LTS

### Community 23 - "Mission and Hardware Requirements"
Cohesion: 0.48
Nodes (5): Mission Tagline: Freedom Today. A Brighter Tomorrow. People. Technology. Opportunity., Brand Values: Open, Secure, Productive, Together, CoreLabs OS, Minimum Hardware Requirements (CPU 2.0 GHz 2-Core, GPU 256 MB 3D, Display 1024x768, RAM 4.0 GB, Disk 25.0 GB), Calamares Slide 06: Hardware Work Faster on Less

### Community 24 - "Open Source Slide"
Cohesion: 0.43
Nodes (6): CoreLabs OS Open Source Slide (09.png), Contributing changes to CoreLabs source code, corelabs.org, CoreLabs OS, Open Source Initiative, Open Source Software (free to use and modify)

### Community 25 - "Lithos Base ABI v1"
Cohesion: 0.29
Nodes (5): Lithos Base ABI v1, BusyBox 1.36.1 (estatico), Linux From Scratch 13.1 (referencia de versoes), Sysroot com runtime glibc/GCC, Toolchain GNU cruzada do Lithos

### Community 27 - "Support Channels Slide"
Cohesion: 0.47
Nodes (6): AskCorelabs, Corelabs Discourse forums, Corelabs OS Focus HOW-TOs, Corelabs Systems, Live support on Matrix (#corelabs-support:matrix.org), Docs and Support: Broad Coverage slide

### Community 28 - "Installer and Boot Flow"
Cohesion: 0.33
Nodes (5): Boot UEFI com OVMF, Initramfs de transicao, Instalador Lithos (./Lithos.sh instalar), Modo de recuperacao (boot direto Fase 0), Teste de persistencia (testar-persistencia)

### Community 29 - "Security Audit Scripts"
Cohesion: 0.40
Nodes (3): falhar(), LC_ALL, auditar-seguranca.sh script

### Community 30 - "Verification Scripts"
Cohesion: 0.73
Nodes (5): aviso(), falhou(), ok(), verificar.sh script, verificar_hash()

### Community 34 - "CPM Package Format"
Cohesion: 0.40
Nodes (4): Assinatura destacada RSA-PSS/SHA-256, Formato de pacote .cpm (tar ustar + CPM/MANIFEST), Indice de pacotes (formato de 7 campos), Configuracao de repositorios em /etc/cpm/repos.d

### Community 37 - "Calamares Welcome Banner"
Cohesion: 0.67
Nodes (4): Calamares Welcome Banner, CORELABS Hexagon Logo, CORELABS OS, CORELABS OS 26.04 LTS

### Community 38 - "OEM Welcome Banner"
Cohesion: 0.83
Nodes (4): welcome-oem.png (CoreLabs OS OEM welcome banner), CoreLabs OS, CoreLabs OS 26.04 LTS, OEM Installation Mode

### Community 39 - "Monochrome Logo Set"
Cohesion: 0.50
Nodes (4): CoreLabs Systems Logo (monochrome), CORELABS Wordmark, Planet-and-Ring Emblem, SYSTEMS Subtitle

### Community 40 - "Kernel and QEMU Config"
Cohesion: 0.50
Nodes (4): Kernel x86_64 (defconfig + kernel.config), Lithos.sh (orquestrador de operacoes), QEMU com KVM/TCG e rede NAT, Comando verificar (teste de boot real com timeout)

### Community 41 - "ABI Audit Tests"
Cohesion: 0.67
Nodes (3): esperar_rejeicao(), LC_ALL, testar-auditoria-abi.sh script

### Community 44 - "Shutdown Scripts"
Cohesion: 0.67
Nodes (3): PATH, registrar(), encerramento.sh script

### Community 45 - "Startup Scripts"
Cohesion: 0.67
Nodes (3): PATH, registrar(), inicializacao.sh script

### Community 47 - "Supervisor Tests"
Cohesion: 0.83
Nodes (3): executar(), falhar(), testar-supervisor.sh script

### Community 48 - "Icon Logo Mark"
Cohesion: 1.00
Nodes (3): CoreLabs Systems Logo Icon, Planet and Orbital Ring Emblem, CoreLabs Systems Brand

### Community 49 - "Calamares Logo"
Cohesion: 1.00
Nodes (3): Calamares Logo (Corelabs Systems), Corelabs Systems, Orbital Planet Emblem

### Community 50 - "Corelabs Logo Set"
Cohesion: 0.67
Nodes (3): Corelabs Systems Logo, CORELABS SYSTEMS Wordmark, Planet-and-Ring Emblem

### Community 51 - "Inverted Logo Variant"
Cohesion: 1.00
Nodes (3): Corelabs Systems logo (inverted variant), CORELABS SYSTEMS wordmark, Orbital sphere-and-hexagon emblem

### Community 52 - "Inverted Logo Parts"
Cohesion: 0.67
Nodes (3): Logo invertida sem fundo (lithos), Logo emblem (upper arc/mountain shape), Logo wordmark (lettering row)

### Community 53 - "Monochrome Logo Parts"
Cohesion: 1.00
Nodes (3): Lithos monochrome logo (no background), Logo emblem (arc and wave mark), Logo wordmark (letterforms)

### Community 54 - "Lithos Logo Set"
Cohesion: 1.00
Nodes (3): Lithos logo (Corelabs Systems), Corelabs Systems wordmark, Planet and orbit ring emblem

### Community 55 - "Package Database Lock"
Cohesion: 0.67
Nodes (3): Banco instalado /var/lib/cpm/db, Lock flock -n em fd 9, Transacoes com journal e rollback

### Community 56 - "Banner Renderer"
Cohesion: 0.67
Nodes (3): Renderizador de banner /usr/lib/Lithos/banner, Identidade oficial Lithos 0.3 Forge, /usr/lib/os-release (identificacao oficial)

## Ambiguous Edges - Review These
- `Lithos` → `Arte ASCII em branding/system`  [AMBIGUOUS]
  branding/system/ascii.txt · relation: conceptually_related_to
- `Lithos Base ABI v1` → `Planejamento historico com systemd (fora da Base ABI v1)`  [AMBIGUOUS]
  documentacao/toolchain.md · relation: conceptually_related_to
- `Build reproduzivel do initramfs` → `Gate scripts/auditar-seguranca.sh`  [AMBIGUOUS]
  documentacao/validacao-cpm-v0.2.md · relation: conceptually_related_to

## Knowledge Gaps
- **93 isolated node(s):** `LC_ALL`, `LC_ALL`, `LC_ALL`, `TZ`, `SOURCE_DATE_EPOCH` (+88 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 213 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **32 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `mensagem()` connect `Build Helper Functions` to `Build Config Scripts`, `ABI Audit Tests`, `ELF Audit Scripts`, `Toolchain Build Helpers`, `Lithos CLI and Image Scripts`, `Toolchain Stage Builds`, `Installer Prep Script`, `Security Audit Scripts`, `Verification Scripts`?**
  _High betweenness centrality (0.008) - this node is a cross-community bridge._
- **What connects `LC_ALL`, `LC_ALL`, `LC_ALL` to the rest of the system?**
  _93 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Control Client Core` be split into smaller, more focused modules?**
  _Cohesion score 0.0707070707070707 - nodes in this community are weakly interconnected._
- **Why does `erro()` connect `Toolchain Build Helpers` to `Build Config Scripts`, `Build Helper Functions`, `ABI Audit Tests`, `ELF Audit Scripts`, `Lithos CLI and Image Scripts`, `Security Audit Scripts`, `Verification Scripts`?**
  _High betweenness centrality (0.006) - this node is a cross-community bridge._
- **Should `NT Object Headers` be split into smaller, more focused modules?**
  _Cohesion score 0.1166429587482219 - nodes in this community are weakly interconnected._

### Low-confidence Hints
_AMBIGUOUS edges — the extractor was unsure. Verify before acting on these._

- **What is the exact relationship between `Lithos` and `Arte ASCII em branding/system`?**
  _Edge tagged AMBIGUOUS (relation: conceptually_related_to) - confidence is low._
- **What is the exact relationship between `Lithos Base ABI v1` and `Planejamento historico com systemd (fora da Base ABI v1)`?**
  _Edge tagged AMBIGUOUS (relation: conceptually_related_to) - confidence is low._