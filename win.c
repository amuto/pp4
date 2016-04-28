#include <gtk/gtk.h>
#include <math.h>

int main(int argc, char **argv)
{
  GtkWidget *win;
  gtk_init(&argc, &argv);

  /* make a window */
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(win);

  gtk_main();
  return 0;
}
