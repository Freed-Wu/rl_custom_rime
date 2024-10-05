// readline miss FILE
#include <stdio.h>

#include <locale.h>
#include <readline/readline.h>
#include <rime_api.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "tmux-rime/tmux-rime.h"

#define DEFAULT_BUFFER_SIZE 1024

static void clear() {
  char str[DEFAULT_BUFFER_SIZE] = "";
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  memset(str, ' ', w.ws_col);
  printf("\e[s\r\n%s\r\n"
         "%s\e[u",
         str, str);
}

static RimeTraits get_traits() {
  RIME_STRUCT(RimeTraits, traits);
  traits.shared_data_dir = "/usr/share/rime-data";
  traits.user_data_dir = "/home/wzy/.config/ibus/rime";
  traits.log_dir = "/home/wzy/.local/share/tmux/rime";
  traits.distribution_name = "Rime";
  traits.distribution_code_name = "rl_custom_rime";
  traits.distribution_version = "0.0.1";
  traits.app_name = "rime.rl_custom_rime";
  traits.min_log_level = 3;
  return traits;
}

static void callback(char *left_padding, char *left, char *right,
                     char *left_padding2, char *str, char *cursor) {
  clear();
  printf("\e[s\r\n%s%s%s%s\r\n"
         "%s%s\e[u",
         left_padding, left, cursor, right, left_padding2, str);
}

int rl_custom_function(int count, int key) {
  static RimeSessionId session_id;
  if (session_id == 0) {
    RimeTraits traits = get_traits();
    setlocale(LC_CTYPE, "");
    RimeSetup(&traits);
    RimeInitialize(&traits);
    session_id = RimeCreateSession();
    if (session_id == 0)
      fputs("cannot create session", stderr);
  }
  RimeUI ui = {"<|", ">|", "[",
               "]",  "|",  {"①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "⑨", "⓪"}};
  RimeLoop(session_id, ui, key, rl_insert_text, callback);
  RimeClearComposition(session_id);
  clear();
  return EXIT_SUCCESS;
}
