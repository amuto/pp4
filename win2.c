#include <gtk/gtk.h>
#include <math.h>

GtkWidget *win,*l2;
gboolean timeout_callback(gpointer gp);

gboolean draw_expose_callback (GtkWidget *w, GdkEventExpose *e __attribute__((unused)), gpointer p  __attribute__((unused)));
  
int main(int argc, char **argv)
{
  GtkWidget  *l1, *l3, *l4, *box1, *box2, *box3, *EXIT, *x, *w, *e, p,t;
  gtk_init(&argc, &argv);



  /* make a window */
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(win);

  box1 = gtk_vbox_new(FALSE,10);
  gtk_container_add(GTK_CONTAINER(win), box1);
  gtk_widget_show(box1);

  l1 = gtk_label_new("Label1");
  gtk_box_pack_start(GTK_BOX(box1), l1, FALSE, TRUE, 10);
  gtk_widget_show(l1);

  box2 = gtk_vbox_new(FALSE,10);
  gtk_box_pack_start(GTK_BOX(box1), box2, FALSE, TRUE, 10);
  gtk_widget_show(box2);

  l2 = gtk_drawing_area_new();
  gtk_box_pack_start(GTK_BOX(box2), l2, TRUE, FALSE,10);
  gtk_widget_set_size_request(l2, 400,200);
  g_timeout_add(100,timeout_callback, NULL);
  g_signal_connect(l2,"expose_event", G_CALLBACK(draw_expose_callback), NULL);
  gtk_widget_show(l2);
 
  box3 = gtk_hbox_new(FALSE,10);
  gtk_box_pack_start(GTK_BOX(box1), box3, FALSE, TRUE, 10);
  gtk_widget_show(box3);

  l3 = gtk_label_new("Label3");
  gtk_box_pack_start(GTK_BOX(box3), l3, TRUE, FALSE, 10);
  gtk_widget_show(l3);

  EXIT = gtk_label_new("EXIT");
  gtk_box_pack_start(GTK_BOX(box3), EXIT,TRUE, FALSE,10);
  gtk_widget_show(EXIT);

  l4 = gtk_button_new();
  gtk_box_pack_start(GTK_BOX(box3), EXIT, FALSE, TRUE, 10);
  g_signal_connect(win, "clicked", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show(l4);


  x = gtk_label_new("x");
  g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show(x);


 

  gtk_main_quit();
  gtk_main();

 
  return 0;
}

  gboolean 
     draw_expose_callback (GtkWidget *w, GdkEventExpose *e 
			  __attribute__((unused)), gpointer p __attribute__((unused)))

{
  int i;
  int width = 400;
  int height = 200;
  static int t;
  t = t + 1;
  t %= width;
  printf("ok!\n");
  for(i=0; i<= width;i++){
  gdk_draw_rectangle(w-> window, w->style->fg_gc[GTK_WIDGET_STATE(win)], TRUE,
		     i, height/2 *sin(2*M_PI*(i+t)/width*3)+height/2, 1, 1);
  }
  return TRUE;
}


gboolean timeout_callback(gpointer gp)
{
  gtk_widget_queue_draw(l2);
}
