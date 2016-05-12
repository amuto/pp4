#include <gtk/gtk.h>
#include <math.h>

int main(int argc, char **argv)
{
  GtkWidget *win, *l1, *l2, *l3, *l4, *box1, *box2, *box3;
  gtk_init(&argc, &argv);

  /* make a window */
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  box1 = gtk_vbox_new(FALSE,10);
  gtk_container_add(GTK_CONTAINER(win), box1);
 
  l1 = gtk_label_new("Label1");
  gtk_box_pack_start(GTK_BOX(box1), l1, FALSE, TRUE, 10);

  l2 = gtk_label_new("Label2");
  gtk_box_pack_start(GTK_BOX(box1), l2, TRUE, FALSE, 10);
 
  box2 = gtk_vbox_new(FALSE,10);
  gtk_box_pack_start(GTK_BOX(box1), box2, FALSE, TRUE, 10);
 
  box3 = gtk_hbox_new(FALSE,10);
  gtk_box_pack_start(GTK_BOX(box1), box3, FALSE, TRUE, 10);

  l3 = gtk_label_new("Label3");
  gtk_box_pack_start(GTK_BOX(box3), l3, TRUE, FALSE, 10);
 
  l4 = gtk_label_new("Label4");
  gtk_box_pack_start(GTK_BOX(box3), l4, FALSE, TRUE, 10);

  gtk_widget_show(box1);
  gtk_widget_show(l1);
  gtk_widget_show(l2);
  gtk_widget_show(box2);
  gtk_widget_show(box3);
  gtk_widget_show(l3);
  gtk_widget_show(l4);
  gtk_widget_show(win);

  gtk_main();
  return 0;
}
