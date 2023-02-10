#include <minishell.h>
#include <minunit.h>

#include "tokens/token.c"
#include "tokens/tokenizer.c"
#include "analyser/redirection.c"
#include "analyser/pipe.c"
#include "analyser/quoted.c"
#include "analyser/analyse.c"
#include "commands/new_command.c"
#include "commands/expansion.c"
#include "commands/quote_removal.c"
#include "commands/builtins/builtins.c"
#include "utils/envp.c"
#include "redirects/new_redirect.c"
#include "utils/args.c"

t_shell	g_minishell;

void	ft_child_exit_shell(t_list **commands, char status)
{}

int	main(int argc, char **argv)
{
	g_minishell.status = 127;
	g_minishell.envp = ft_split("double_equal='hello=world'\nquoted_var='hello'\nquoted_var2=\"hello\"\nSHELL=minishell\nAFTER_SHELL='its me'\nCOLORTERM=truecolor\nWSL2_GUI_APPS_ENABLED=1\nTERM_PROGRAM_VERSION=1.75.0\nNVM_IOJS_ORG_MIRROR=https://iojs.org/dist\nWSL_DISTRO_NAME=Ubuntu\nWT_SESSION=d5ed4336-a47a-402f-ac42-f62caa116b70\nNAME=Code\nPWD=/home/douglasfanucchi/42/minishell\nLOGNAME=douglasfanucchi\nMANPATH=/home/douglasfanucchi/.nvm/versions/node/v12.22.9/share/man:/usr/local/man:/usr/local/share/man:/usr/share/man\nVSCODE_GIT_ASKPASS_NODE=/home/douglasfanucchi/.vscode-server/bin/e2816fe719a4026ffa1ee0189dc89bdfdbafb164/node\nHOME=/home/douglasfanucchi\nLANG=C.UTF-8\nWSL_INTEROP=/run/WSL/48179_interop\nLS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:\nWAYLAND_DISPLAY=wayland-0\nGIT_ASKPASS=/home/douglasfanucchi/.vscode-server/bin/e2816fe719a4026ffa1ee0189dc89bdfdbafb164/extensions/git/dist/askpass.sh\nNVM_DIR=/home/douglasfanucchi/.nvm\nVSCODE_GIT_ASKPASS_EXTRA_ARGS=\nLESSCLOSE=/usr/bin/lesspipe %s %s\nTERM=xterm-256color\nLESSOPEN=| /usr/bin/lesspipe %s\nUSER=douglasfanucchi\nVSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-9c712d87cf.sock\nDISPLAY=:0\nSHLVL=2\nNVM_CD_FLAGS=\nXDG_RUNTIME_DIR=/run/user/1000/\nWSLENV=ELECTRON_RUN_AS_NODE/w:WT_SESSION::WT_PROFILE_ID\n\nVSCODE_GIT_ASKPASS_MAIN=/home/douglasfanucchi/.vscode-server/bin/e2816fe719a4026ffa1ee0189dc89bdfdbafb164/extensions/git/dist/askpass-main.js\nNVM_NODEJS_ORG_MIRROR=https://nodejs.org/dist\nXDG_DATA_DIRS=/usr/local/share:/usr/share:/var/lib/snapd/desktop\nPATH=/usr/bin:/usr/sbin\nDBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus\nNVM_BIN=/home/douglasfanucchi/.nvm/versions/node/v12.22.9/bin\nHOSTTYPE=x86_64\nPULSE_SERVER=/mnt/wslg/PulseServer\nWT_PROFILE_ID={2c4de342-38b7-51cf-b940-2309a097f518}\ncommand='echo'\nTERM_PROGRAM=vscode\nVSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-d8f5b9bf-205d-4ea5-a3c1-02adae173ca8.sock\n_=/usr/bin/env", '\n');

	MU_RUN_SUITE(test_tokens);
	MU_RUN_SUITE(test_tokenizer);
	MU_RUN_SUITE(test_redirections_analyser);
	MU_RUN_SUITE(test_pipe_analyser);
	MU_RUN_SUITE(test_quoted_analyser);
	MU_RUN_SUITE(test_analyse_token);
	MU_RUN_SUITE(test_new_command);
	MU_RUN_SUITE(test_redirections);
	MU_RUN_SUITE(test_utils_args);
	MU_RUN_SUITE(test_token_expansion);
	MU_RUN_SUITE(test_quote_removal);
	MU_RUN_SUITE(test_builtins);
	MU_RUN_SUITE(test_envp_utils);
	MU_REPORT();

	ft_del_envp(g_minishell.envp);
	return (MU_EXIT_CODE);
}
