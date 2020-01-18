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
  int isDir;
  GtkWidget *btn;
  GtkWidget *label;
  GtkWidget *popover;
  int called_from_popover;
  GtkWidget *box2;
  struct fileprops metadata;
};

int num_files;
char ** files;

void free_files() {
  int i;
  for (i = 0; i < num_files; i++)
    free(files[i]);

  free(files);
}

void executefile(GtkWidget *menuitem, gpointer userdata) {
  struct data *d = (struct data *)userdata;
  char *filename = d -> filename;

  if (d -> isDir == 0)
    run_file(d -> filename);
  else
    printf("Sorry, changing directories would require a massive rewrite of this program. \n");
}

void deletefile(GtkWidget *menuitem, gpointer userdata) {
  struct data *d = (struct data *)userdata;
  char *filename = d -> filename;
  remove_thing(filename);
  gtk_widget_destroy(d -> btn);
}

void entry_callback(GtkEntry *entry, gpointer userdata) {
  const gchar *entry_text = gtk_entry_get_text(entry);
  printf("Entry contents: %s \n", entry_text);
  struct data *d = (struct data *)userdata;
  char *filename = d -> filename;

  if (rename(filename, entry_text) == 0) {
    gtk_label_set_text(GTK_LABEL(d -> label), entry_text);

    //Truncate file names that are too long
    char buf[35];
    if (strlen(entry_text) > 25) {
      strncpy(buf, entry_text, 24);
      strncat(buf, "...", 4);
    } else {
      strncpy(buf, entry_text, 25);
    }

    strncpy(d -> filename, entry_text, MAX_FILE_LEN);
    if (d -> called_from_popover == 1)
      gtk_popover_popdown(GTK_POPOVER(d -> popover));
  } else {
    GtkWidget *label = gtk_label_new("A file with that name already exists.");
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);
    gtk_box_pack_start(GTK_BOX(d -> box2), label, FALSE, FALSE, 0);
    gtk_widget_show_all(d -> box2);
  }
}

void renamefile(GtkWidget *menuitem, gpointer userdata) {
  struct data *d = (struct data *)userdata;

  GtkWidget *entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry), MAX_FILE_LEN);
  gtk_entry_set_text(GTK_ENTRY(entry), d -> filename);

  GtkWidget *renamebutton = gtk_button_new_with_label("Rename");

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), renamebutton, FALSE, FALSE, 0);

  GtkWidget *label = gtk_label_new(NULL);
  const char *format = "<b>File name</b>";
  gtk_label_set_xalign(GTK_LABEL(label), 0.0);
  gtk_label_set_markup(GTK_LABEL(label), format);

  GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_set_border_width(GTK_CONTAINER(box2), 10);
  gtk_box_pack_start(GTK_BOX(box2), label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box2), box, FALSE, FALSE, 0);
  d -> box2 = box2;

  GtkWidget *popover = gtk_popover_new(d -> btn);
  gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_BOTTOM);
  gtk_container_add(GTK_CONTAINER(popover), box2);
  gtk_popover_popup(GTK_POPOVER(popover));
  d -> popover = popover;
  d -> called_from_popover = 1;

  g_signal_connect(entry, "activate", G_CALLBACK(entry_callback), userdata);
  gtk_widget_show_all(popover);
}

void view_props(GtkWidget *menuitem, gpointer userdata) {
  struct data *d = (struct data *)userdata;
  char *filename = d -> filename;
  struct fileprops metadata = d -> metadata;

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  char buf[MAX_FILE_LEN + 15];
  strncpy(buf, filename, MAX_FILE_LEN);
  strncat(buf, " Properties", 15);
  gtk_window_set_title(GTK_WINDOW(window), buf);

  GtkWidget *grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
  gtk_container_set_border_width(GTK_CONTAINER(grid), 20);

  if (metadata.isdir == 0) {
    GtkWidget *namelabel = gtk_label_new("Name: ");
    gtk_label_set_xalign(GTK_LABEL(namelabel), 0.0);
    GtkWidget *sizelabel = gtk_label_new("Size: ");
    gtk_label_set_xalign(GTK_LABEL(sizelabel), 0.0);

    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), MAX_FILE_LEN);
    gtk_entry_set_text(GTK_ENTRY(entry), d -> filename);
    d -> called_from_popover = 0;
    g_signal_connect(entry, "activate", G_CALLBACK(entry_callback), userdata);

    gtk_grid_attach(GTK_GRID(grid), namelabel, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), sizelabel, 0, 1, 1, 1);
  } else {
    GtkWidget *namelabel = gtk_label_new("Name: ");
    gtk_label_set_xalign(GTK_LABEL(namelabel), 0.0);

    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), MAX_FILE_LEN);
    gtk_entry_set_text(GTK_ENTRY(entry), d -> filename);
    d -> called_from_popover = 0;
    g_signal_connect(entry, "activate", G_CALLBACK(entry_callback), userdata);

    gtk_grid_attach(GTK_GRID(grid), namelabel, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);
  }

  gtk_container_add(GTK_CONTAINER(window), grid);
  gtk_widget_show_all(window);
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

    GtkWidget *viewprops = gtk_menu_item_new_with_label("Properties");
    g_signal_connect(viewprops, "activate", G_CALLBACK(view_props), userdata);

    GtkWidget *menu = gtk_menu_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), runfile);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), delete);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), rename);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), viewprops);

    gtk_widget_show_all(menu);
    gtk_menu_popup_at_pointer(GTK_MENU(menu), NULL);
    return TRUE;
  }

  else if (event -> type == GDK_2BUTTON_PRESS && event -> button == 1) { //double click
    struct data *d = (struct data *)userdata;
    if (d -> isDir == 0)
      run_file(d -> filename);
    else
      printf("Sorry, changing directories would require a massive rewrite of this program. \n");

    return TRUE;
  }

  return FALSE;
}

static void activate(GtkApplication *app, gpointer data) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_default_size(GTK_WINDOW(window), 900, 650);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  GtkWidget *titlebar;
  GtkWidget *grid;
  char cwd[100];
  getcwd(cwd, 100);
  GtkWidget *cwdlabel = gtk_label_new(cwd);

  titlebar = gtk_header_bar_new();
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(titlebar), TRUE);
  gtk_header_bar_pack_start(GTK_HEADER_BAR(titlebar), cwdlabel);
  gtk_window_set_titlebar(GTK_WINDOW(window), titlebar);

  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 50);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(grid), 20);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(grid));

  int i;
  int row, col = 0;
  for (i = 0; i < num_files; i++) {
    printf("%s \n", files[i]);
    struct data * d = malloc(sizeof(struct data));
    strncpy(d -> filename, files[i], MAX_FILE_LEN);

    struct fileprops metadata;
    get_props(files[i], &metadata);
    d -> metadata = metadata;

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

    //Truncate file names that are too long
    char buf[35];
    if (strlen(files[i]) > 25) {
      strncpy(buf, files[i], 24);
      strncat(buf, "...", 4);
    } else {
      strncpy(buf, files[i], 25);
    }

    GtkWidget *filename = gtk_label_new(buf);
    gtk_label_set_justify(GTK_LABEL(filename), GTK_JUSTIFY_CENTER);
    gtk_label_set_line_wrap(GTK_LABEL(filename), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(filename), 1);
    gtk_label_set_lines(GTK_LABEL(filename), 3);
    gtk_box_pack_start(GTK_BOX(box), filename, FALSE, FALSE, 0);
    d -> label = filename;

    g_signal_connect(iconbutton, "button_press_event", G_CALLBACK(btn_press), d);
    gtk_container_add(GTK_CONTAINER(iconbutton), box);
    gtk_grid_attach(GTK_GRID(grid), iconbutton, col, row, 1, 1);

    col++;
    if (col == 6) {
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

  num_files = 0;
  files = getfiles(&num_files);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  free_files();
  g_object_unref(app);

  return status;
}
