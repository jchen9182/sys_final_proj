#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fileinfo.h"
#include "execute.h"
#include "fileops.h"
#include <gtk/gtk.h>

static void on_button_clicked(GtkButton *btn, gpointer data) {
  gtk_button_set_label(btn, "You clicked me!");
}

static void on_app_activate(GApplication *app, gpointer data) {
  GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
  GtkWidget *btn = gtk_button_new_with_label("Hello World!");
  g_signal_connect(btn, "clicked", G_CALLBACK(on_button_clicked), NULL);
  gtk_container_add(GTK_CONTAINER(window), btn);
  gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc, char *argv[]) {
  GtkApplication *app = gtk_application_new(
    "org.mks65.fileexp",
    G_APPLICATION_FLAGS_NONE
  );

  g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc,argv);
  g_object_unref(app);
  return status;
}
