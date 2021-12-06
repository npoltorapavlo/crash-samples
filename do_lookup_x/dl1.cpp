#include <glib.h>

extern "C" {
void func() {
  GString *msg = g_string_new("123");

  g_string_free(msg, 1);
}
}
