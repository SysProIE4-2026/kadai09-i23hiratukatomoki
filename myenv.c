/*
*  myenv.c : env コマンドのクローン
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include "myputenv.h"
#endif

int _putenv(char *str); // エラーが出ると面倒なのでプロトタイプ宣言
extern char **environ; // 前回の課題でも使ったやつ

int main(int argc, char *argv[]) {
  int i = 1;

  // name=value形式の引数を処理
  while(i < argc) { // とりあえず引数ごとに実行
    if(_putenv(argv[i]) != 0) { // name=valueでない引数が来たら
      break;
    }

    i++; // 忘れないようにiを加算
  }

  // 何らかのプログラムの実行
  if (i < argc) { // commandが書かれているか
    execvp(argv[i], &argv[i]); // &argv[i]はargvのi番目以降の配列全体を指す
    perror(argv[i]); // execvpが帰ってくる場合はエラー
    return -1;

  } else { // 書かれていなければ
    for(int j = 0; environ[j] != NULL; j++) { //一覧表示
      printf("%s\n", environ[j]); // name=value形式で表示
    }

  }

  return 0;
}

/* 実行例

ここに実行例を書く
コンパイル:
$ make
cc -D_GNU_SOURCE -Wall -std=c99 -o myenv myenv.c myputenv.c
# 問題なくコンパイルは通った

実行例:
1)env単体での呼び出し
#正規品
$ env
OSLogRateLimit=64
MallocNanoZone=0
USER=hiratsukatomoki
COMMAND_MODE=unix2003
__CFBundleIdentifier=com.microsoft.VSCode
PATH=/Users/hiratsukatomoki/.pyenv/shims
:/Users/hiratsukatomoki/Desktop/src:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/opt/homebrew/bin
:/opt/homebrew/bin
:/opt/homebrew/sbin
:/Library/Frameworks/Python.framework/Versions/3.11/bin
:/usr/local/bin
:/System/Cryptexes/App/usr/bin
:/usr/bin
:/bin
:/usr/sbin
:/sbin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
:/pkg/env/global/bin
:/Library/Apple/usr/bin
:/usr/local/go/bin:/Library/Frameworks/Mono.framework/Versions/Current/Commands
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/Users/hiratsukatomoki/.lmstudio/bin
:/bin:/Users/hiratsukatomoki/.lmstudio/bin
LOGNAME=hiratsukatomoki
SSH_AUTH_SOCK=/var/run/com.apple.launchd.zYafHJCPte/Listeners
HOME=/Users/hiratsukatomoki
SHELL=/bin/zsh
TMPDIR=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/
__CF_USER_TEXT_ENCODING=0x1F5:0x1:0xE
XPC_SERVICE_NAME=0
XPC_FLAGS=0x0
SHLVL=1
PWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
OLDPWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
LANG=C.UTF-8
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions
:/opt/homebrew/share/zsh/site-functions
:/usr/local/share/zsh/site-functions
:/usr/share/zsh/site-functions
:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:/opt/homebrew/share/info:
JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home
ANDROID_HOME=/Users/hiratsukatomoki/Library/Android/sdk
ANDROID_NDK=/Users/hiratsukatomoki/Library/Android/sdk/ndk/21.4.7075529
SELECTED_OP_LIST=new_mobile_model_2.yaml
PYENV_ROOT=/Users/hiratsukatomoki/.pyenv
PYENV_SHELL=zsh
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=1.126.0
COLORTERM=truecolor
GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
VSCODE_GIT_IPC_HANDLE=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/vscode-git-42e63c976d.sock
VSCODE_NONCE=fceee172-af0c-44d2-83ae-182974514f9b
TERM=xterm-256color
_=/usr/bin/env

#模造品(myenv)
$ ./myenv
OSLogRateLimit=64
MallocNanoZone=0
USER=hiratsukatomoki
COMMAND_MODE=unix2003
__CFBundleIdentifier=com.microsoft.VSCode
PATH=/Users/hiratsukatomoki/.pyenv/shims
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/opt/homebrew/bin
:/opt/homebrew/bin
:/opt/homebrew/sbin
:/Library/Frameworks/Python.framework/Versions/3.11/bin
:/usr/local/bin
:/System/Cryptexes/App/usr/bin
:/usr/bin
:/bin
:/usr/sbin
:/sbin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
:/pkg/env/global/bin
:/Library/Apple/usr/bin
:/usr/local/go/bin
:/Library/Frameworks/Mono.framework/Versions/Current/Commands
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/Users/hiratsukatomoki/.lmstudio/bin
:/bin
:/Users/hiratsukatomoki/.lmstudio/bin
LOGNAME=hiratsukatomoki
SSH_AUTH_SOCK=/var/run/com.apple.launchd.zYafHJCPte/Listeners
HOME=/Users/hiratsukatomoki
SHELL=/bin/zsh
TMPDIR=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/
__CF_USER_TEXT_ENCODING=0x1F5:0x1:0xE
XPC_SERVICE_NAME=0
XPC_FLAGS=0x0
SHLVL=1
PWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
OLDPWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
LANG=C.UTF-8
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions
:/opt/homebrew/share/zsh/site-functions
:/usr/local/share/zsh/site-functions
:/usr/share/zsh/site-functions
:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:/opt/homebrew/share/info:
JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home
ANDROID_HOME=/Users/hiratsukatomoki/Library/Android/sdk
ANDROID_NDK=/Users/hiratsukatomoki/Library/Android/sdk/ndk/21.4.7075529
SELECTED_OP_LIST=new_mobile_model_2.yaml
PYENV_ROOT=/Users/hiratsukatomoki/.pyenv
PYENV_SHELL=zsh
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=1.126.0
COLORTERM=truecolor
GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
VSCODE_GIT_IPC_HANDLE=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/vscode-git-42e63c976d.sock
VSCODE_NONCE=fceee172-af0c-44d2-83ae-182974514f9b
TERM=xterm-256color
_=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki/./myenv
# 同じ出力を得ることが出来ている。


2)env+環境変数の変更
//正規品
$ env JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-17-full.jdk/Contents/Home
OSLogRateLimit=64
MallocNanoZone=0
USER=hiratsukatomoki
COMMAND_MODE=unix2003
__CFBundleIdentifier=com.microsoft.VSCode
PATH=/Users/hiratsukatomoki/.pyenv/shims
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/opt/homebrew/bin
:/opt/homebrew/bin
:/opt/homebrew/sbin
:/Library/Frameworks/Python.framework/Versions/3.11/bin
:/usr/local/bin
:/System/Cryptexes/App/usr/bin
:/usr/bin
:/bin
:/usr/sbin
:/sbin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
:/pkg/env/global/bin
:/Library/Apple/usr/bin
:/usr/local/go/bin
:/Library/Frameworks/Mono.framework/Versions/Current/Commands
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/Users/hiratsukatomoki/.lmstudio/bin:/bin:/Users/hiratsukatomoki/.lmstudio/bin
LOGNAME=hiratsukatomoki
SSH_AUTH_SOCK=/var/run/com.apple.launchd.zYafHJCPte/Listeners
HOME=/Users/hiratsukatomoki
SHELL=/bin/zsh
TMPDIR=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/
__CF_USER_TEXT_ENCODING=0x1F5:0x1:0xE
XPC_SERVICE_NAME=0
XPC_FLAGS=0x0
SHLVL=1
PWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
OLDPWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
LANG=C.UTF-8
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions
:/opt/homebrew/share/zsh/site-functions
:/usr/local/share/zsh/site-functions
:/usr/share/zsh/site-functions
:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:/opt/homebrew/share/info:
JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-17-full.jdk/Contents/Home
ANDROID_HOME=/Users/hiratsukatomoki/Library/Android/sdk
ANDROID_NDK=/Users/hiratsukatomoki/Library/Android/sdk/ndk/21.4.7075529
SELECTED_OP_LIST=new_mobile_model_2.yaml
PYENV_ROOT=/Users/hiratsukatomoki/.pyenv
PYENV_SHELL=zsh
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=1.126.0
COLORTERM=truecolor
GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
VSCODE_GIT_IPC_HANDLE=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/vscode-git-42e63c976d.sock
VSCODE_NONCE=fceee172-af0c-44d2-83ae-182974514f9b
TERM=xterm-256color
_=/usr/bin/env

#模造品(myenv)
$ env JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-17-full.jdk/Contents/Home
OSLogRateLimit=64
MallocNanoZone=0
USER=hiratsukatomoki
COMMAND_MODE=unix2003
__CFBundleIdentifier=com.microsoft.VSCode
PATH=/Users/hiratsukatomoki/.pyenv/shims
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/opt/homebrew/bin
:/opt/homebrew/bin
:/opt/homebrew/sbin
:/Library/Frameworks/Python.framework/Versions/3.11/bin
:/usr/local/bin
:/System/Cryptexes/App/usr/bin
:/usr/bin
:/bin
:/usr/sbin
:/sbin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
:/pkg/env/global/bin
:/Library/Apple/usr/bin
:/usr/local/go/bin
:/Library/Frameworks/Mono.framework/Versions/Current/Commands
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/Users/hiratsukatomoki/.lmstudio/bin:/bin:/Users/hiratsukatomoki/.lmstudio/bin
LOGNAME=hiratsukatomoki
SSH_AUTH_SOCK=/var/run/com.apple.launchd.zYafHJCPte/Listeners
HOME=/Users/hiratsukatomoki
SHELL=/bin/zsh
TMPDIR=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/
__CF_USER_TEXT_ENCODING=0x1F5:0x1:0xE
XPC_SERVICE_NAME=0
XPC_FLAGS=0x0
SHLVL=1
PWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
OLDPWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
LANG=C.UTF-8
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions
:/opt/homebrew/share/zsh/site-functions
:/usr/local/share/zsh/site-functions
:/usr/share/zsh/site-functions
:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:/opt/homebrew/share/info:
JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-17-full.jdk/Contents/Home
ANDROID_HOME=/Users/hiratsukatomoki/Library/Android/sdk
ANDROID_NDK=/Users/hiratsukatomoki/Library/Android/sdk/ndk/21.4.7075529
SELECTED_OP_LIST=new_mobile_model_2.yaml
PYENV_ROOT=/Users/hiratsukatomoki/.pyenv
PYENV_SHELL=zsh
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=1.126.0
COLORTERM=truecolor
GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
VSCODE_GIT_IPC_HANDLE=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/vscode-git-42e63c976d.sock
VSCODE_NONCE=fceee172-af0c-44d2-83ae-182974514f9b
TERM=xterm-256color
_=/usr/bin/env
# いずれの場合もJAVA_HOMEのパスが変更できていた

3)3env+複数の環境変数の変更
#正規品
$ env JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-17-full.jdk/Contents/Home LC_TIME=ru_RU.UTF-8
OSLogRateLimit=64
MallocNanoZone=0
USER=hiratsukatomoki
COMMAND_MODE=unix2003
__CFBundleIdentifier=com.microsoft.VSCode
PATH=/Users/hiratsukatomoki/.pyenv/shims
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/opt/homebrew/bin
:/opt/homebrew/bin
:/opt/homebrew/sbin
:/Library/Frameworks/Python.framework/Versions/3.11/bin
:/usr/local/bin
:/System/Cryptexes/App/usr/bin
:/usr/bin
:/bin
:/usr/sbin
:/sbin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
:/pkg/env/global/bin
:/Library/Apple/usr/bin
:/usr/local/go/bin
:/Library/Frameworks/Mono.framework/Versions/Current/Commands
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/Users/hiratsukatomoki/.lmstudio/bin:/bin:/Users/hiratsukatomoki/.lmstudio/bin
LOGNAME=hiratsukatomoki
SSH_AUTH_SOCK=/var/run/com.apple.launchd.zYafHJCPte/Listeners
HOME=/Users/hiratsukatomoki
SHELL=/bin/zsh
TMPDIR=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/
__CF_USER_TEXT_ENCODING=0x1F5:0x1:0xE
XPC_SERVICE_NAME=0
XPC_FLAGS=0x0
SHLVL=1
PWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
OLDPWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
LANG=C.UTF-8
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions
:/opt/homebrew/share/zsh/site-functions
:/usr/local/share/zsh/site-functions
:/usr/share/zsh/site-functions
:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:/opt/homebrew/share/info:
JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-17-full.jdk/Contents/Home
ANDROID_HOME=/Users/hiratsukatomoki/Library/Android/sdk
ANDROID_NDK=/Users/hiratsukatomoki/Library/Android/sdk/ndk/21.4.7075529
SELECTED_OP_LIST=new_mobile_model_2.yaml
PYENV_ROOT=/Users/hiratsukatomoki/.pyenv
PYENV_SHELL=zsh
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=1.126.0
COLORTERM=truecolor
GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
VSCODE_GIT_IPC_HANDLE=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/vscode-git-42e63c976d.sock
VSCODE_NONCE=fceee172-af0c-44d2-83ae-182974514f9b
TERM=xterm-256color
_=/usr/bin/env
LC_TIME=ru_RU.UTF-8

#模造品(myenv)
$ ./myenv JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-17-full.jdk/Contents/Home LC_TIME=pt_PT.UTF-8
OSLogRateLimit=64
MallocNanoZone=0
USER=hiratsukatomoki
COMMAND_MODE=unix2003
__CFBundleIdentifier=com.microsoft.VSCode
PATH=/Users/hiratsukatomoki/.pyenv/shims
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/opt/homebrew/bin
:/opt/homebrew/bin
:/opt/homebrew/sbin
:/Library/Frameworks/Python.framework/Versions/3.11/bin
:/usr/local/bin
:/System/Cryptexes/App/usr/bin
:/usr/bin
:/bin
:/usr/sbin
:/sbin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
:/pkg/env/global/bin
:/Library/Apple/usr/bin
:/usr/local/go/bin
:/Library/Frameworks/Mono.framework/Versions/Current/Commands
:/Users/hiratsukatomoki/Desktop/src
:/Users/hiratsukatomoki/Library/Android/sdk/tools
:/Users/hiratsukatomoki/Library/Android/sdk/platform-tools
:/Library/Java/JavaVirtualMachines/liberica-jdk-25-full.jdk/Contents/Home/Contents/Home/bin
:/Users/hiratsukatomoki/.lmstudio/bin:/bin:/Users/hiratsukatomoki/.lmstudio/bin
LOGNAME=hiratsukatomoki
SSH_AUTH_SOCK=/var/run/com.apple.launchd.zYafHJCPte/Listeners
HOME=/Users/hiratsukatomoki
SHELL=/bin/zsh
TMPDIR=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/
__CF_USER_TEXT_ENCODING=0x1F5:0x1:0xE
XPC_SERVICE_NAME=0
XPC_FLAGS=0x0
SHLVL=1
PWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
OLDPWD=/Users/hiratsukatomoki/Desktop/github/Syspro/kadai09/kadai09-i23hiratukatomoki
LANG=C.UTF-8
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions
:/opt/homebrew/share/zsh/site-functions
:/usr/local/share/zsh/site-functions
:/usr/share/zsh/site-functions
:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:/opt/homebrew/share/info:
JAVA_HOME=/Library/Java/JavaVirtualMachines/liberica-jdk-17-full.jdk/Contents/Home
ANDROID_HOME=/Users/hiratsukatomoki/Library/Android/sdk
ANDROID_NDK=/Users/hiratsukatomoki/Library/Android/sdk/ndk/21.4.7075529
SELECTED_OP_LIST=new_mobile_model_2.yaml
PYENV_ROOT=/Users/hiratsukatomoki/.pyenv
PYENV_SHELL=zsh
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=1.126.0
COLORTERM=truecolor
GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js
VSCODE_GIT_IPC_HANDLE=/var/folders/q0/kbcp0j450pb72j6zyxrbcpdw0000gn/T/vscode-git-42e63c976d.sock
VSCODE_NONCE=fceee172-af0c-44d2-83ae-182974514f9b
TERM=xterm-256color
_=/usr/bin/env
LC_TIME=pt_PT.UTF-8
#両方とも複数の環境変数の変更が行えている。


4)env+コマンド
#正規品
$ env date
Tue Jun 30 11:48:44 JST 2026

#模造品(myenv)
$ ./myenv date
Tue Jun 30 11:55:53 JST 2026
#いずれの場合も同様の出力が得られている。

5)env+コマンド(引数付き)
#正規品
$ env sysctl hw.model
hw.model: Mac17,2

#模造品(myenv)
$ ./myenv sysctl hw.model
hw.model: Mac17,2
#いずれの場合も同様の出力が得られている。

6)エラー時の処理
#正規品
$ env abc
env: abc: No such file or directory

#模造品(myenv)
$ ./myenv abc
abc: No such file or directory
#エラー表示に若干の差異が生まれた

*/
