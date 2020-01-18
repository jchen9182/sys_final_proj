#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "fileinfo.h"
#include "execute.h"
#include "fileops.h"

#define MAX_FILE_LEN 50

struct data {
  char filename[50];
  GtkWidget *btn;
  int isDir;
};

int num_files;
char ** files;

void executefile(GtkWidget *menuitem, gpointer userdata) {
  struct data *d = (struct data *)userdata;
  char *filename = d -> filename;

  if (d -> isDir == 0)
    run_file(d -> filename);
  else
    printf("Opening folder \n");
}

void deletefile(GtkWidget *menuitem, gpointer userdata) {
  struct data *d = (struct data *)userdata;
  char *filename = d -> filename;
  remove_thing(filename);
  gtk_widget_destroy(d -> btn);
}

void renamefile(GtkWidget *menuitem, gpointer userdata) {
  struct data *d = (struct data *)userdata;
  char *filename = d -> filename;

  GtkWidget *popover = gtk_popover_new(d -> btn);
  gtk_popover_popup(GTK_POPOVER(popover));
  gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_BOTTOM);
  GtkWidget *entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry), MAX_FILE_LEN);

  //g_signal_connect(entry, "activate", G_CALLBACK(entry_callback), userdata);
}

gboolean btn_press(GtkWidget *btn, GdkEventButton *event, gpointer userdata) {
  if (event -> type == GDK_BUTTON_PRESS && event -> button == 3) { //right mouse button
    struct data *d = (struct data *)userdata;
    d -> btn = btn;

    GtkWidget *runfile = gtk_menu_item_new_with_label("Open");
    g_signal_connect(runfile, "activate", G_CALLBACK(executefile), userdata);

    GtkWidget *delete = gtk_menu_item_new_with_label("Delete");
    g_signal_connect(delete, "activate", G_CALLBACK(deletefile), userdata);

    GtkWidget *rename = gtk_menu_item_new_with_label("Rename...");
    g_signal_connect(rename, "activate", G_CALLBACK(renamefile), userdata);

    GtkWidget *menu = gtk_menu_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), runfile);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), delete);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), rename);

    gtk_widget_show_all(menu);
    gtk_menu_popup_at_pointer(GTK_MENU(menu), NULL);
    return TRUE;
  }

  else if (event -> type == GDK_2BUTTON_PRESS && event -> button == 1) { //double click
    struct data *d = (struct data *)userdata;
    if (d -> isDir == 0)
      run_file(d -> filename);
    else {
      printf("Opening folder \n");
      num_files = 0;
      files = getfiles(&num_files);
      gtk_main_iteration();
    }
  }

  return FALSE;
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

  num_files = 0;
  files = getfiles(&num_files);

  int i;
  int row, col = 0;
  for (i = 0; i < num_files; i++) {
    printf("%s \n", files[i]);
    struct data * d = malloc(sizeof(struct data));
    strncpy(d -> filename, files[i], MAX_FILE_LEN);

    struct fileprops metadata;
    get_props(files[i], &metadata);

    //Truncate file names that are too long
    char buf[35];
    if (strlen(files[i]) > 25) {
      strncpy(buf, files[i], 24);
      strncat(buf, "...", 4);
    } else {
      strncpy(buf, files[i], 25);
    }

    GtkWidget *iconbutton = gtk_button_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    if (metadata.isdir == 0) {
      GtkWidget *iconimg = gtk_image_new_from_file("fileicon.png");
      gtk_box_pack_start(GTK_BOX(box), iconimg, FALSE, FALSE, 0);
      d -> isDir = 0;
    } else {
      GtkWidget *folderimg = gtk_image_new_from_file("foldericon.png");
      gtk_box_pack_start(GTK_BOX(box), folderimg, FALSE, FALSE, 0);
      d -> isDir = 1;
    }

    GtkWidget *filename = gtk_label_new(buf);
    gtk_label_set_line_wrap(GTK_LABEL(filename), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(filename), 1);
    gtk_box_pack_start(GTK_BOX(box), filename, FALSE, FALSE, 1);

    g_signal_connect(iconbutton, "button_press_event", G_CALLBACK(btn_press), d);
    gtk_container_add(GTK_CONTAINER(iconbutton), box);
    gtk_grid_attach(GTK_GRID(grid), iconbutton, col, row, 1, 1);

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
