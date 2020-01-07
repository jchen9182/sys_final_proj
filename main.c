#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fileinfo.h"
#include "execute.h"
#include "fileops.h"
#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer data) {
  GtkWidget *window;
  GtkWidget *grid;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "File Explorer");
  gtk_window_set_default_size(GTK_WINDOW(window), 900, 650);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(grid));
  int num_files = 0;
  char ** files = getfiles(&num_files);
  GtkWidget *icon = gtk_image_new_from_file("finderico.png");

  int i;
  for (i = 0; i < 5; i++) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    GtkWidget *iconbutton = gtk_button_new();
    gtk_button_set_always_show_image(GTK_BUTTON(iconbutton), TRUE);
    gtk_button_set_image(GTK_BUTTON(iconbutton), icon);
    GtkWidget *filename = gtk_button_new_with_label(files[i]);
    gtk_box_pack_start(GTK_BOX(box), iconbutton, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), filename, FALSE, FALSE, 0);
    gtk_grid_attach(GTK_GRID(grid), box, i, i, 1, 1);
  }

  gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
  GtkApplication *app = gtk_application_new(
    "org.mks65.fileexp",
    G_APPLICATION_FLAGS_NONE
  );

  GtkCssProvider *provider = gtk_css_provider_new();
  /*
  gtk_css_provider_load_from_path(provider, "style.css", NULL);
  gtk_style_context_add_provider_for_screen(
    gdk_screen_get_default(),
    GTK_STYLE_PROVIDER(provider),
    GTK_STYLE_PROVIDER_PRIORITY_USER
  );
  */

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
