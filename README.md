# rl_custom_rime

[![pre-commit.ci status](https://results.pre-commit.ci/badge/github/Freed-Wu/rl_custom_rime/main.svg)](https://results.pre-commit.ci/latest/github/Freed-Wu/rl_custom_rime/main)

[![github/downloads](https://shields.io/github/downloads/Freed-Wu/rl_custom_rime/total)](https://github.com/Freed-Wu/rl_custom_rime/releases)
[![github/downloads/latest](https://shields.io/github/downloads/Freed-Wu/rl_custom_rime/latest/total)](https://github.com/Freed-Wu/rl_custom_rime/releases/latest)
[![github/issues](https://shields.io/github/issues/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/issues)
[![github/issues-closed](https://shields.io/github/issues-closed/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/issues?q=is%3Aissue+is%3Aclosed)
[![github/issues-pr](https://shields.io/github/issues-pr/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/pulls)
[![github/issues-pr-closed](https://shields.io/github/issues-pr-closed/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/pulls?q=is%3Apr+is%3Aclosed)
[![github/discussions](https://shields.io/github/discussions/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/discussions)
[![github/milestones](https://shields.io/github/milestones/all/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/milestones)
[![github/forks](https://shields.io/github/forks/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/network/members)
[![github/stars](https://shields.io/github/stars/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/stargazers)
[![github/watchers](https://shields.io/github/watchers/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/watchers)
[![github/contributors](https://shields.io/github/contributors/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/graphs/contributors)
[![github/commit-activity](https://shields.io/github/commit-activity/w/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/graphs/commit-activity)
[![github/last-commit](https://shields.io/github/last-commit/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/commits)
[![github/release-date](https://shields.io/github/release-date/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/releases/latest)

[![github/license](https://shields.io/github/license/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime/blob/main/LICENSE)
[![github/languages](https://shields.io/github/languages/count/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime)
[![github/languages/top](https://shields.io/github/languages/top/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime)
[![github/directory-file-count](https://shields.io/github/directory-file-count/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime)
[![github/code-size](https://shields.io/github/languages/code-size/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime)
[![github/repo-size](https://shields.io/github/repo-size/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime)
[![github/v](https://shields.io/github/v/release/Freed-Wu/rl_custom_rime)](https://github.com/Freed-Wu/rl_custom_rime)

Rime for readline. For all programs depending on readline:

- bash without [ble.sh](https://github.com/akinomyoga/ble.sh)
- python without ptpython, ipython, ...
- tclsh/wish with [tclreadline](https://github.com/flightaware/tclreadline)
- lua with [luaprompt](https://github.com/dpapavas/luaprompt)
- perl with [reply](https://github.com/doy/reply)
- [sdcv](https://github.com/Dushistov/sdcv)
- ...

![screenshot](https://github.com/user-attachments/assets/88febfe0-3e32-48f6-a4c3-064759e16ca5)

## Install

### AUR

```sh
paru -S rl_custom_rime
```

## Build

```sh
xmake
```

## Dependence

- [rl_custom_function](https://github.com/lincheney/rl_custom_function)

`/etc/ld.so.preload`:

```sh
/usr/$LIB/librl_custom_function.so
```

See [shell.nix](shell.nix).

## Configure

```readline
$include function rl_custom_rime /the/path/of/librl_custom_rime.so
"\C-^": rl_custom_rime
```

## Todo

<!-- markdownlint-disable-next-line MD033 -->
- Support more special keys: <kbd>Up</kbd>, <kbd>Del</kbd>, <kbd>F1</kbd>, ...
- Pass hotkeys to readline directly when menu is empty

## Related Projects

- [rl_custom_isearch](https://github.com/lincheney/rl_custom_isearch)
- [fzf-tab-completion](https://github.com/lincheney/fzf-tab-completion)
