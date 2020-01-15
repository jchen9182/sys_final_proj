#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fileinfo.h"
#include "execute.h"
#include "fileops.h"
#include <gtk/gtk.h>

void btn_press(GtkWidget *btn, GdkEventButton *event, gpointer userdata) {
  if (event -> type == GDK_BUTTON_PRESS && event -> button == 3) { //right mouse button
    GtkWidget *runfile = gtk_menu_item_new_with_label("Open");
    GtkWidget *delete = gtk_menu_item_new_with_label("Delete");
    GtkWidget *rename = gtk_menu_item_new_with_label("Rename...");

    GtkWidget *menu = gtk_menu_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), runfile);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), delete);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), rename);

    gtk_widget_show_all(menu);
    gtk_menu_popup_at_widget(GTK_MENU(menu), btn, 0, 0, NULL);
  }
}

static void activate(GtkApplication *app, gpointer data) {
  GtkWidget *window;
  GtkWidget *titlebar;
  GtkWidget *grid;
  char cwd[100];
  getcwd(cwd, 100);
  GtkWidget *cwdlabel = gtk_label_new(cwd);

  window = gtk_application_window_new(app);
  gtk_window_set_default_size(GTK_WINDOW(window), 900, 650);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  titlebar = gtk_header_bar_new();
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(titlebar), TRUE);
  gtk_header_bar_pack_start(GTK_HEADER_BAR(titlebar), cwdlabel);
  gtk_window_set_titlebar(GTK_WINDOW(window), titlebar);

  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 30);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(grid));

  int num_files = 0;
  char ** files = getfiles(&num_files);
  //GtkWidget *icon = gtk_image_new_from_file("finderico.png");
  int i;
  int row, col = 0;
  for (i = 0; i < num_files; i++) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *iconbutton = gtk_button_new();
    GtkWidget *iconimg = gtk_image_new_from_file("fileicon.png");

    gtk_button_set_always_show_image(GTK_BUTTON(iconbutton), TRUE);
    gtk_button_set_image(GTK_BUTTON(iconbutton), iconimg);
    g_signal_connect(iconbutton, "button-press-event", G_CALLBACK(btn_press), NULL);
    GtkWidget *filename = gtk_label_new(files[i]);
    //gtk_label_set_max_width_chars(GTK_LABEL(filename), 0); doesn't work
    gtk_box_pack_start(GTK_BOX(box), iconbutton, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), filename, FALSE, FALSE, 0);
    gtk_grid_attach(GTK_GRID(grid), box, col, row, 1, 1);

    col++;
    if (col == 7) {
      row++;
      col = 0;
    }
  }

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
