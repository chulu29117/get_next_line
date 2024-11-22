parse_git_branch() {
    git branch 2>/dev/null | sed -n '/\* /s///p'
    }

    PS1='${debian_chroot:+($debian_chroot)}\[\e[31m\][\[\e[m\]\[\e[38;5;172m\]\u\[\e[m\]@\[\e[38;5;153m\]\h\[\e[m\] \[\e[38;5;214m\]$(parse_git_branch)\[\e[m\] \[\e[38;5;214m\]\W\[\e[m\]\[\e[31m\]]\[\e[m\]\\$ '
alias mini='~/mini-moulinette/mini-moul.sh'
alias ccall='cc -Wall -Wextra -Werror'
alias norm='norminette'
alias gitall='git add . ; git commit -m "files added" ; git push'
alias francinette='~/francinette/tester.sh'
alias paco='~/francinette/tester.sh'
alias code="flatpak run com.visualstudio.code"
alias vscode="/Applications/Visual\ Studio\ Code.app/contents/Resources/app/bin/code"
alias val="valgrind --leak-check=full --show-leak-kinds=all --verbose"
