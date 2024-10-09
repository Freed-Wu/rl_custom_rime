// readline miss FILE
#include <stdio.h>

#include <dirent.h>
#include <glib.h>
#include <readline/readline.h>
#include <rime_api.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wordexp.h>

#include "tmux-rime/tmux-rime.h"

#define DEFAULT_BUFFER_SIZE 1024

static void clear(FILE *fp) {
  char str[DEFAULT_BUFFER_SIZE] = "";
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  memset(str, ' ', w.ws_col);
  fprintf(fp,
          "\e[s\n%s\n"
          "%s\e[u",
          str, str);
}

static void callback(char *left_padding, char *left, char *right,
                     char *left_padding2, char *str, char *cursor) {
  clear(stdout);
  char padding[DEFAULT_BUFFER_SIZE] = "";
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int extra_width = 0;
  if (strcmp(rl_readline_name, "python") == 0)
    extra_width += 2;
  memset(padding, ' ',
         (RimeWidth(rl_copy_text(0, DEFAULT_BUFFER_SIZE)) + extra_width) %
             w.ws_col);
  printf("\e[s\n%s%s%s%s%s\e[u\e[s\n\n"
         "%s%s%s\e[u",
         padding, left_padding, left, cursor, right, padding, left_padding2,
         str);
}

static int feed_keys(const char *keys) {
  if (RimeWidth((char *)keys) == -1)
    return 0;
  int status = rl_insert_text(keys);
  rl_refresh_line(1, 0);
  return status;
}

int rl_custom_function(int count, int key) {
  static RimeSessionId session_id;
  if (session_id == 0) {
    RimeTraits traits = RimeGetTraits();
    traits.distribution_code_name = "rl_custom_rime";
    traits.distribution_version = rl_library_version;
    traits.app_name = "rime.rl_custom_rime";
    // don't let error message disturb input
    fprintf(stderr, "\e[s\n");
    RimeSetup(&traits);
    RimeInitialize(&traits);
    session_id = RimeCreateSession();
    fprintf(stderr, "\e[u");
    /*clear(stderr);*/
    if (session_id == 0)
      fputs("cannot create session", stderr);
  }
  RimeUI ui = {"<|", ">|", "[",
               "]",  "|",  {"①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "⑨", "⓪"}};
  RimeLoop(session_id, ui, key, feed_keys, callback);
  RimeClearComposition(session_id);
  clear(stdout);
  return EXIT_SUCCESS;
}
