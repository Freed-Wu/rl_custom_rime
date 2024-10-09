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

static RimeTraits get_traits() {
  RIME_STRUCT(RimeTraits, traits);
  wordexp_t exp;
  char shared_data_dir[256] = "";
  char *shared_data_dirs[] = {shared_data_dir, "/usr/local/share/rime-data",
                              "/run/current-system/sw/share/rime-data",
                              "/sdcard/rime-data"};
  char *prefix = getenv("PREFIX");
  if (prefix == NULL)
    prefix = "/usr";
  strcpy(shared_data_dirs[0], prefix);
  strcpy(shared_data_dirs[0] + strlen(shared_data_dirs[0]), "/share/rime-data");
  for (int i = 0; i < sizeof(shared_data_dirs) / sizeof(shared_data_dirs[0]);
       i++) {
    if (wordexp(shared_data_dirs[i], &exp, 0))
      continue;
    DIR *dir = opendir(exp.we_wordv[0]);
    if (dir && closedir(dir) == 0) {
      traits.shared_data_dir = strdup(exp.we_wordv[0]);
      wordfree(&exp);
      break;
    }
    wordfree(&exp);
  }
  traits.shared_data_dir = "/usr/share/rime-data";

  char *user_data_dirs[] = {"~/.config/ibus/rime", "~/.local/share/fcitx5/rime",
                            "~/.config/fcitx/rime", "/sdcard/rime"};
  for (int i = 0; i < sizeof(user_data_dirs) / sizeof(user_data_dirs[0]); i++) {
    if (wordexp(user_data_dirs[i], &exp, 0))
      continue;
    DIR *dir = opendir(exp.we_wordv[0]);
    if (dir && closedir(dir) == 0) {
      traits.user_data_dir = strdup(exp.we_wordv[0]);
      wordfree(&exp);
      break;
    }
    wordfree(&exp);
  }

  if (wordexp("~/.local/share/tmux/rime", &exp, 0) != 0)
    traits.log_dir = strdup(exp.we_wordv[0]);
  wordfree(&exp);
  g_mkdir_with_parents(traits.log_dir, 0755);
  traits.distribution_name = "Rime";
  traits.distribution_code_name = "rl_custom_rime";
  traits.distribution_version = rl_library_version;
  traits.app_name = "rime.rl_custom_rime";
  traits.min_log_level = 0;
  return traits;
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
    RimeTraits traits = get_traits();
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
