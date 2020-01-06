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
  GtkWidget *file = gtk_button_new_with_label("File Explorer");
  gtk_grid_attach(GTK_GRID(grid), file, 1, 1, 1, 1);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(grid));

  gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
  GtkApplication *app = gtk_application_new(
    "org.mks65.fileexp",
    G_APPLICATION_FLAGS_NONE
  );

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
