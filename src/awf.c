/**
 * Forked  M/10/03/2020
 * Updated D/25/10/2020
 *
 * Copyright 2020 | Fabrice Creuzot (luigifab) <code~luigifab~fr>
 * https://github.com/luigifab/awf-extended
 * https://www.luigifab.fr/gtk/awf-extended
 *
 * Forked from
 *  Copyright 2011-2017 | Valère Monseur (valr) <valere~monseur~ymail~com>
 *  https://github.com/valr/awf
 *
 * Forked from
 *  AWF is originally based on the code from The Widget Factory
 *  created by Richard Stellingwerff <remenic~gmail~com>
 *
 * This program is free software, you can redistribute it or modify
 * it under the terms of the GNU General Public License (GPL) as published
 * by the free software foundation, either version 3 of the license, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but without any warranty, without even the implied warranty of
 * merchantability or fitness for a particular purpose. See the
 * GNU General Public License (GPL) for more details.
 *
 *
 * Translations update:
 *  xgettext -d awf -o src/awf.pot -k_ -s src/awf.c
 *  msgmerge src/po/fr.po src/awf.pot -o src/po/fr.po
 *  msgfmt src/po/fr.po -o src/fr/LC_MESSAGES/awf.mo
 *
 * Tested with build.sh with:
 * i386
 *  Ubuntu 11.04 (live/768  MB) GTK 3.0  + GTK 2.24 + GLIB 2.28
 *  Ubuntu 11.10 (live/768  MB) GTK 3.2  + GTK 2.24 + GLIB 2.30
 *  Ubuntu 12.04 (live/1024 MB) GTK 3.4  + GTK 2.24 + GLIB 2.32
 *  Ubuntu 13.04 (live/1024 MB) GTK 3.6  + GTK 2.24 + GLIB 2.36
 *  Ubuntu 13.10 (live/1024 MB) GTK 3.8  + GTK 2.24 + GLIB 2.38
 *  Ubuntu 14.04 (live/1024 MB) GTK 3.10 + GTK 2.24 + GLIB 2.40
 *  Ubuntu 14.10 (live/1024 MB) GTK 3.12 + GTK 2.24 + GLIB 2.42
 *  Ubuntu 15.04 (live/1024 MB) GTK 3.14 + GTK 2.24 + GLIB 2.44
 *  Ubuntu 15.10 (live/1024 MB) GTK 3.16 + GTK 2.24 + GLIB 2.46
 *  Ubuntu 16.04 (live/1272 MB) GTK 3.18 + GTK 2.24 + GLIB 2.48
 *  Ubuntu 16.10 (live/1272 MB) GTK 3.20 + GTK 2.24 + GLIB 2.50
 *  Ubuntu 17.04 (live/1272 MB) GTK 3.22 + GTK 2.24 + GLIB 2.52
 * amd64
 *  Debian Testing   GTK 3.99 + GTK 3.24 + GTK 2.24 + GLIB 2.66
 *  Fedora 32                   GTK 3.24 + GTK 2.24 + GLIB 2.64
 */

// includes

#include <glib/gi18n.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>
#include <gtk/gtkunixprint.h>
#include <gdk/gdk.h>
#include <time.h>

#if GLIB_CHECK_VERSION (2,30,0)
	#include <glib-unix.h>
#endif

// defines

#define _(String) gettext (String)
#define AWF_OPEN "<AWF>/Test/Open"
#define AWF_RECE "<AWF>/Test/Recent"
#define AWF_CALE "<AWF>/Test/Calendar"
#define AWF_SAVE "<AWF>/Test/Save"
#define AWF_REFR "<AWF>/Test/Refresh"
#define AWF_PROP "<AWF>/Test/Properties"
#define AWF_PRSE "<AWF>/Test/PrintSetup"
#define AWF_PRIN "<AWF>/Test/Print"
#define AWF_ABOU "<AWF>/Test/About"
#define AWF_MCUT "<AWF>/Test/More/Cut"
#define AWF_MCOP "<AWF>/Test/More/Copy"
#define AWF_MPAS "<AWF>/Test/More/Past"
#define AWF_CLOS "<AWF>/Test/Close"
#define AWF_QUIT "<AWF>/Test/Quit"

#if GTK_CHECK_VERSION (3,90,0)
	#define TRUE_GTK_MAJOR_VERSION 4
	#define GETTEXT_PACKAGE "awf-gtk4"
	#define gtk_major_version gtk_get_major_version ()
	#define gtk_minor_version gtk_get_minor_version ()
	#define gtk_micro_version gtk_get_micro_version ()
	#define BOXH (gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0))
	#define BOXV (gtk_box_new (GTK_ORIENTATION_VERTICAL, 0))
	#define BOXHSEP (gtk_separator_new (GTK_ORIENTATION_HORIZONTAL))
	#define BOXVSEP (gtk_separator_new (GTK_ORIENTATION_VERTICAL))
	#define BOXHPANE (gtk_paned_new (GTK_ORIENTATION_HORIZONTAL))
	#define BOXVPANE (gtk_paned_new (GTK_ORIENTATION_VERTICAL))
#elif GTK_CHECK_VERSION (3,0,0)
	#define TRUE_GTK_MAJOR_VERSION 3
	#define GETTEXT_PACKAGE "awf-gtk3"
	#define gtk_major_version gtk_get_major_version ()
	#define gtk_minor_version gtk_get_minor_version ()
	#define gtk_micro_version gtk_get_micro_version ()
	#define BOXH (gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0))
	#define BOXV (gtk_box_new (GTK_ORIENTATION_VERTICAL, 0))
	#define BOXHSEP (gtk_separator_new (GTK_ORIENTATION_HORIZONTAL))
	#define BOXVSEP (gtk_separator_new (GTK_ORIENTATION_VERTICAL))
	#define BOXHPANE (gtk_paned_new (GTK_ORIENTATION_HORIZONTAL))
	#define BOXVPANE (gtk_paned_new (GTK_ORIENTATION_VERTICAL))
#else
	#define TRUE_GTK_MAJOR_VERSION 2
	#define GETTEXT_PACKAGE "awf-gtk2"
	#define BOXH (gtk_hbox_new (FALSE, 0))
	#define BOXV (gtk_vbox_new (FALSE, 0))
	#define BOXHSEP (gtk_hseparator_new ())
	#define BOXVSEP (gtk_vseparator_new ())
	#define BOXHPANE (gtk_hpaned_new ())
	#define BOXVPANE (gtk_vpaned_new ())
	#define GDK_KEY_F1 0xffbe
	//#define GDK_KEY_F2 0xffbf
	//#define GDK_KEY_F3 0xffc0
	//#define GDK_KEY_F4 0xffc1
	//#define GDK_KEY_F5 0xffc2
	//#define GDK_KEY_F6 0xffc3
	//#define GDK_KEY_F7 0xffc4
	//#define GDK_KEY_F8 0xffc5
	//#define GDK_KEY_F9 0xffc6
	//#define GDK_KEY_F10 0xffc7
	//#define GDK_KEY_F11 0xffc8
	#define GDK_KEY_F12 0xffc9
	#define GDK_KEY_Delete 0xffff
	#define GDK_KEY_KP_Delete 0xff9f
	#define GDK_KEY_BackSpace 0xff08
#endif

// global local variables

static char *current_theme = "";
static GSList *list_system_theme;
static GSList *list_user_theme;
static GtkWidget *window, *statusbar;
static GtkWidget *spinbutton1, *spinbutton2;
static GtkWidget *scale1, *scale2, *scale3, *scale4, *scale5, *scale6;
static GtkWidget *progressbar1, *progressbar2, *progressbar3, *progressbar4;
static GtkWidget *notebook1, *notebook2, *notebook3, *notebook4;
static GtkWidget *current_menuitem;
#if GTK_CHECK_VERSION (3,6,0)
static GtkWidget *levelbar1, *levelbar2, *levelbar3, *levelbar4, *levelbar5, *levelbar6, *levelbar7, *levelbar8;
#endif
static char *opt_screenshot;
static gboolean opt_startspinner = TRUE;
static gboolean allow_update_theme = TRUE;
static gboolean must_save_accels = FALSE;

// local functions

static void awf2_quit ();
static GSList* awf_load_theme (char *directory);
static void awf_exclude_theme (gpointer theme, gpointer unused);
static int awf_compare_theme (gconstpointer theme1, gconstpointer theme2);
static void awf2_set_theme (char *new_theme);
static void awf2_update_progressbars (GtkRange *range);
static void awf2_update_statusbar (char *text, gboolean withtime);
static void awf2_update_widgets ();
static gboolean awf2_sighup_handler ();
static gboolean awf2_take_screenshot ();
// widgets
static void awf2_create_window (gpointer app, char *theme);
static void awf2_boxpack (GtkBox *box, GtkWidget *widget, gboolean fill, gboolean expand, guint padding, guint spacing);
static void awf2_create_toolbar (GtkWidget *root);
static void awf2_create_combos_entries (GtkWidget *root);
static void awf2_create_spinbuttons (GtkWidget *root);
static void awf2_create_checkbuttons (GtkWidget *root);
static void awf2_create_radiobuttons (GtkWidget *root);
static void awf2_create_otherbuttons (GtkWidget *root);
static void awf2_create_progressbars (GtkWidget *root1, GtkWidget *root2, GtkWidget *root3, GtkWidget *root4);
static void awf2_create_labels (GtkWidget *root);
static void awf2_create_spinners (GtkWidget *root);
static void awf2_create_expander (GtkWidget *root);
static void awf2_create_frames (GtkWidget *root1, GtkWidget *root2);
static void awf2_create_notebooks (GtkWidget *root1, GtkWidget *root2);
static void awf2_create_notebook_tab (GtkWidget *notebook, char *text);
static void awf2_create_treview (GtkWidget *root);
// menuitems
#if GTK_CHECK_VERSION (3,90,0)
static void awf2_create_traditional_menubar (gpointer app, GMenu *root);
#else
static void awf2_create_traditional_menubar (GtkWidget *root);
static GtkWidget* awf2_new_menu (GtkWidget *root, char *text);
static GtkWidget* awf2_new_menu_tearoff (GtkWidget *menu);
static GtkWidget* awf2_new_menu_separator (GtkWidget *menu);
static GtkWidget* awf2_new_menu_check (GtkWidget *menu, char *text, gboolean checked, gboolean inconsistent, gboolean disabled);
static GtkWidget* awf2_new_menu_radio (GtkWidget *menu, char *text, gboolean checked, gboolean inconsistent, gboolean disabled, GSList *group);
static GtkWidget* awf2_new_menu_item (GtkWidget *menu, char *text, char *image, gboolean disabled);
// accelerators
static void awf2_accels_load ();
static void awf2_accels_select (GtkWidget *widget);
static void awf2_accels_deselect (GtkWidget *widget);
static void awf2_accels_change (GtkWidget *widget, GdkEventKey *event);
static void awf2_accels_save ();
#endif
// dialogs
static void awf2_show_dialog_open ();
static void awf2_show_dialog_open_recent ();
static void awf2_show_dialog_save ();
static void awf2_show_dialog_properties ();
static void awf2_show_dialog_page_setup ();
static void awf2_show_dialog_print ();
static void awf2_show_dialog_about ();
static void awf2_show_dialog_calendar ();
// gtk4/3
#if GTK_CHECK_VERSION (3,90,0)
static void awf2_gtk40_closedialog (GtkDialog *dialog);
static void awf2_gtk40_scrolltabs (GtkEventControllerScroll *event, double dx, double dy, GtkWidget *widget);
#elif GTK_CHECK_VERSION (3,4,0)
static void awf2_gtk34_scrolltabs (GtkWidget *widget, GdkEventScroll *event);
#endif

// run baby, run!

int main (int argc, char **argv) {

	int status = 0, opt;
	char *directory, *theme = "auto";
	GSList *iterator;

	// load available themes
	// todo replace GSLists?
	list_system_theme = awf_load_theme ("/usr/share/themes");
	list_system_theme = g_slist_sort (list_system_theme, (GCompareFunc)awf_compare_theme);

	directory = g_build_path ("/", g_getenv ("HOME"), ".themes", NULL);
	list_user_theme = awf_load_theme (directory);
	list_user_theme = g_slist_sort (list_user_theme, (GCompareFunc)awf_compare_theme);
	g_free (directory);

	g_slist_foreach (list_user_theme, awf_exclude_theme, NULL);

	// locale
	setlocale (LC_ALL, "");
	if (g_file_test ("/usr/share/locale", G_FILE_TEST_IS_DIR))
		bindtextdomain (GETTEXT_PACKAGE, "/usr/share/locale");
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	// init
	while ((opt = getopt (argc, argv, "vs:nt:lh")) != -1) {
		switch (opt) {
			case 'v':
				g_printf ("%s\n", VERSION);
				return status;
			case 's':
				opt_screenshot = optarg;
				break;
			case 'n':
				opt_startspinner = FALSE;
			case 't':
				if (g_slist_find_custom (list_system_theme, optarg, &awf_compare_theme) ||
					g_slist_find_custom (list_user_theme, optarg, &awf_compare_theme))
					theme = (char*)optarg;
				break;
			case 'l':
				for (iterator = list_system_theme; iterator; iterator = iterator->next)
					g_printf ("%s\n", (gchar*)iterator->data);
				for (iterator = list_user_theme; iterator; iterator = iterator->next)
					g_printf ("%s\n", (gchar*)iterator->data);
				return status;
			case 'h':
			default:
				g_printf ("\n%s\n %s\n %s\n\n%s\n  %s %s\n  %s %s\n  %s %s\n%s\n  %s %s\n  %s %s\n  %s %s\n  %s %s\n  %s %s\n",
					g_strdup_printf (_("A widget factory - GTK %d - %s"), TRUE_GTK_MAJOR_VERSION, VERSION),
					g_strdup_printf (_("compiled with gtk %d.%d.%d and glib %d.%d.%d"),
						GTK_MAJOR_VERSION, GTK_MINOR_VERSION, GTK_MICRO_VERSION,
						GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION),
					g_strdup_printf (_(" started with gtk %d.%d.%d and glib %d.%d.%d"),
						gtk_major_version, gtk_minor_version, gtk_micro_version,
						glib_major_version, glib_minor_version, glib_micro_version),
					_("Usage:"),
					"awf-gtk2      ", "(gtk 2.24+)",
					"awf-gtk3      ", "(gtk 3.00+)",
					"awf-gtk4      ", "(gtk 3.99+)",
					_("Options:"),
					"-v            ", _("Show version number"),
					"-l            ", _("List available themes"),
					"-n            ", _("Don't start spinners"),
					"-t <theme>    ", _("Run with the specified theme"),
					"-s <filename> ", g_strdup_printf (_("Run and save a png screenshot on %s"), "sighup")
				);
				return status;
		}
	}

	// create and show window
	#if GLIB_CHECK_VERSION (2,30,0)
		g_unix_signal_add (SIGHUP, awf2_sighup_handler, NULL); // glib >= 2.30
	#endif

	#if GTK_CHECK_VERSION (3,90,0)
		GtkApplication *app;
		app = gtk_application_new ("org.gtk.awf4", G_APPLICATION_FLAGS_NONE);
		g_signal_connect (app, "activate", G_CALLBACK (awf2_create_window), theme);
		g_application_register (G_APPLICATION (app), NULL, NULL);
		status = g_application_run (G_APPLICATION (app), 0, NULL); // todo (app, argc, argv)
		g_object_unref (app);
	#elif GTK_CHECK_VERSION (3,4,0)
		GtkApplication *app;
		app = gtk_application_new ("org.gtk.awf3", G_APPLICATION_FLAGS_NONE);
		g_signal_connect (app, "activate", G_CALLBACK (awf2_create_window), theme);
		status = g_application_run (G_APPLICATION (app), 0, NULL); // todo (app, argc, argv)
		g_object_unref (app);
	#else
		gtk_init (&argc, &argv);
		awf2_create_window (NULL, theme);
	#endif

	return status;
}

static void awf2_quit () {

	#if !GTK_CHECK_VERSION (3,90,0)
		awf2_accels_save ();
	#endif

	exit (0);
}

static GSList* awf_load_theme (char *directory) {

	GSList *list = NULL;

	g_return_val_if_fail (directory != NULL, NULL);

	if (g_file_test (directory, G_FILE_TEST_IS_DIR)) {

		GError *error = NULL;
		GDir *dir = g_dir_open (directory, 0, &error);

		if (dir) {
			char *theme = g_strdup (g_dir_read_name (dir));

			while (theme) {
				char *theme_path = g_build_path ("/", directory, g_strstrip (theme), NULL);

				if (g_file_test (theme_path, G_FILE_TEST_IS_DIR)) {
					char *theme_subpath = g_build_path ("/", theme_path, g_strdup_printf ("gtk-%d.0", TRUE_GTK_MAJOR_VERSION), NULL);
					if (g_file_test (theme_subpath, G_FILE_TEST_IS_DIR))
						list = g_slist_prepend (list, theme);
					g_free (theme_subpath);
				}

				g_free (theme_path);
				// don't free 'theme', it's the data part of GSList elements

				theme = g_strdup (g_dir_read_name (dir));
			}

			g_dir_close (dir);
		}

		if (error) {
			g_fprintf (stderr, "unable to open directory: %s (%s)\n", directory, error->message);
			g_error_free (error); error = NULL;
		}
	}

	if (list)
		list = g_slist_reverse (list);

	return list;
}

static void awf_exclude_theme (gpointer theme, gpointer unused) {

	GSList *found_theme = g_slist_find_custom (list_system_theme, (gconstpointer)theme, &awf_compare_theme);

	if (found_theme) {
		g_free (found_theme->data);
		list_system_theme = g_slist_delete_link (list_system_theme, found_theme);
	}
}

static int awf_compare_theme (gconstpointer theme1, gconstpointer theme2) {

	return g_strcmp0 ((char*)theme1, (char*)theme2);
}

static void awf2_set_theme (char *new_theme) {

	// we must ignore the activate signal when menubar is created
	if (!allow_update_theme)
		return;

	if (strcmp ((char*)new_theme, "refresh") == 0) {

		char *default_theme = NULL;
		if (g_slist_find_custom (list_system_theme, "Default", &awf_compare_theme))
			default_theme = "Default";
		else if (g_slist_find_custom (list_system_theme, "Raleigh", &awf_compare_theme))
			default_theme = "Raleigh";

		if (default_theme) {

			g_object_set (gtk_settings_get_default (), "gtk-theme-name", default_theme, NULL);
			g_usleep (G_USEC_PER_SEC / 2);
			g_object_set (gtk_settings_get_default (), "gtk-theme-name", current_theme, NULL);

			awf2_update_statusbar (g_strdup_printf (_("Theme %s reloaded at"), current_theme), TRUE);

			if (opt_screenshot)
				g_timeout_add_seconds (1, awf2_take_screenshot, NULL);
		}
	}
	else if (strcmp ((char*)new_theme, "auto") == 0) {
		g_object_get (gtk_settings_get_default (), "gtk-theme-name", &current_theme, NULL);
	}
	else if ((strcmp ((char*)current_theme, (char*)new_theme) != 0)) {

		g_object_set (gtk_settings_get_default (), "gtk-theme-name", new_theme,  NULL);
		g_object_get (gtk_settings_get_default (), "gtk-theme-name", &current_theme, NULL);

		gtk_window_resize (GTK_WINDOW (window), 50, 50);
		awf2_update_statusbar (g_strdup_printf (_("Theme %s loaded."), current_theme), FALSE);
	}
}

static void awf2_update_progressbars (GtkRange *range) {

	// https://developer.gnome.org/gtk3/stable/GtkProgressBar.html
	// https://developer.gnome.org/gtk3/stable/GtkLevelBar.html
	// https://developer.gnome.org/gtk3/stable/GtkScale.html

	double value;
	value = gtk_range_get_value (range);

	// range (0..1)
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar1), value / 100.0);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar2), value / 100.0);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar3), value / 100.0);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar4), value / 100.0);

	#if GTK_CHECK_VERSION (3,6,0)
		// range (0..1)
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar1), value / 100.0);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar2), value / 100.0);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar5), value / 100.0);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar6), value / 100.0);
		// range (0..5)
		// GTK 3.20.9 gtk_level_bar_set_value do nothing
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar3), value / 100.0 * gtk_level_bar_get_max_value (GTK_LEVEL_BAR (levelbar3)));
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar4), value / 100.0 * gtk_level_bar_get_max_value (GTK_LEVEL_BAR (levelbar4)));
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar7), value / 100.0 * gtk_level_bar_get_max_value (GTK_LEVEL_BAR (levelbar7)));
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar8), value / 100.0 * gtk_level_bar_get_max_value (GTK_LEVEL_BAR (levelbar8)));
	#endif

	// range (0..100)
	if (scale1 != (GtkWidget*)range) gtk_range_set_value (GTK_RANGE (scale1), value);
	if (scale2 != (GtkWidget*)range) gtk_range_set_value (GTK_RANGE (scale2), value);
	if (scale3 != (GtkWidget*)range) gtk_range_set_value (GTK_RANGE (scale3), value);
	if (scale4 != (GtkWidget*)range) gtk_range_set_value (GTK_RANGE (scale4), value);
	if (scale5 != (GtkWidget*)range) gtk_range_set_value (GTK_RANGE (scale5), value);
	if (scale6 != (GtkWidget*)range) gtk_range_set_value (GTK_RANGE (scale6), value);

	#if !GTK_CHECK_VERSION (3,0,0)
		if (gtk_progress_bar_get_text (GTK_PROGRESS_BAR (progressbar1))) {
			char *progress_text;
			progress_text = g_strdup_printf ("%i %%", (int)value);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar1), progress_text);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar3), progress_text);
			g_free (progress_text);
		}
	#endif
}

static void awf2_update_statusbar (char *text, gboolean withtime) {

	if (!statusbar)
		return;

	// https://developer.gnome.org/gtk3/stable/GtkStatusbar.html

	char buffer[12];
	time_t rawtime;
	struct tm *timeinfo;

	if (withtime) {
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		strftime (buffer, sizeof buffer, " %T.", timeinfo);

		gtk_statusbar_push (GTK_STATUSBAR (statusbar), gtk_statusbar_get_context_id (GTK_STATUSBAR (statusbar), "gné"),
			g_strdup_printf ("%s%s", text, buffer));
	}
	else {
		gtk_statusbar_push (GTK_STATUSBAR (statusbar), gtk_statusbar_get_context_id (GTK_STATUSBAR (statusbar), "gné"), text);
	}
}

static void awf2_update_widgets () {

	// https://developer.gnome.org/gtk3/stable/GtkNotebook.html
	// https://developer.gnome.org/gtk3/stable/GtkSpinButton.html
	// https://developer.gnome.org/gtk3/stable/GtkProgressBar.html
	// https://developer.gnome.org/gtk3/stable/GtkScale.html

	if (gtk_notebook_get_scrollable (GTK_NOTEBOOK (notebook1))) {

		gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook1), FALSE);
		gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook2), FALSE);
		gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook3), FALSE);
		gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook4), FALSE);

		#if GTK_CHECK_VERSION (3,6,0)
			gtk_orientable_set_orientation (GTK_ORIENTABLE (spinbutton1), GTK_ORIENTATION_HORIZONTAL);
			gtk_orientable_set_orientation (GTK_ORIENTABLE (spinbutton2), GTK_ORIENTATION_HORIZONTAL);
			gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar1), FALSE);
			gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar3), FALSE);
		#elif GTK_CHECK_VERSION (3,0,0)
			gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar1), FALSE);
			gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar3), FALSE);
		#else
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar1), NULL);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar3), NULL);
		#endif

		gtk_scale_set_draw_value (GTK_SCALE (scale1), FALSE);
		gtk_scale_clear_marks (GTK_SCALE (scale2));
		gtk_scale_set_draw_value (GTK_SCALE (scale3), FALSE);
		gtk_scale_set_draw_value (GTK_SCALE (scale4), FALSE);
		gtk_scale_clear_marks (GTK_SCALE (scale5));
		gtk_scale_clear_marks (GTK_SCALE (scale6));

		gtk_window_resize (GTK_WINDOW (window), 50, 50);
	}
	else {
		gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook1), TRUE);
		gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook2), TRUE);
		gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook3), TRUE);
		gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook4), TRUE);

		#if GTK_CHECK_VERSION (3,6,0)
			gtk_orientable_set_orientation (GTK_ORIENTABLE (spinbutton1), GTK_ORIENTATION_VERTICAL);
			gtk_orientable_set_orientation (GTK_ORIENTABLE (spinbutton2), GTK_ORIENTATION_VERTICAL);
			gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar1), TRUE);
			gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar3), TRUE);
		#elif GTK_CHECK_VERSION (3,0,0)
			gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar1), TRUE);
			gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar3), TRUE);
		#else
			char *progress_text;
			progress_text = g_strdup_printf ("%i %%", (int)gtk_range_get_value (GTK_RANGE (scale1)));
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar1), progress_text);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar3), progress_text);
			g_free (progress_text);
		#endif

		gtk_scale_set_draw_value (GTK_SCALE (scale1), TRUE);
		gtk_scale_add_mark (GTK_SCALE (scale2), 25, GTK_POS_TOP, NULL);
		gtk_scale_add_mark (GTK_SCALE (scale2), 50, GTK_POS_TOP, NULL);
		gtk_scale_add_mark (GTK_SCALE (scale2), 75, GTK_POS_TOP, NULL);
		gtk_scale_set_draw_value (GTK_SCALE (scale3), TRUE);
		gtk_scale_set_draw_value (GTK_SCALE (scale4), TRUE);
		gtk_scale_add_mark (GTK_SCALE (scale5), 25, GTK_POS_LEFT, "25");
		gtk_scale_add_mark (GTK_SCALE (scale5), 50, GTK_POS_LEFT, "50");
		gtk_scale_add_mark (GTK_SCALE (scale5), 75, GTK_POS_LEFT, "75");
		gtk_scale_add_mark (GTK_SCALE (scale6), 25, GTK_POS_RIGHT, "25");
		gtk_scale_add_mark (GTK_SCALE (scale6), 50, GTK_POS_RIGHT, "50");
		gtk_scale_add_mark (GTK_SCALE (scale6), 75, GTK_POS_RIGHT, "75");
	}
}

static gboolean awf2_sighup_handler () {

	awf2_set_theme ("refresh");

#if !defined (G_SOURCE_CONTINUE)
	return TRUE; // glib < 2.32
#else
	return G_SOURCE_CONTINUE;
#endif
}

static gboolean awf2_take_screenshot () {

	// https://developer.gnome.org/gdk2/stable/gdk2-Pixbufs.html
	// https://developer.gnome.org/gdk3/stable/gdk3-Pixbufs.html
	// https://developer.gnome.org/gdk4/stable/gdk4-Pixbufs.html
	// https://developer.gnome.org/gdk4/stable/gdk4-Cairo-Interaction.html

	GdkPixbuf *image;
	int width, height;
	// src/cairo-surface.c:1734: cairo_surface_mark_dirty_rectangle: assertion ! _cairo_surface_has_mime_data (surface) failed

	#if GTK_CHECK_VERSION (3,90,0)
		GdkSurface *root;
		cairo_surface_t *cairo_st;
		root   = gtk_native_get_surface (gtk_widget_get_native (window));
		width  = gdk_surface_get_width (root);
		height = gdk_surface_get_height (root);
		cairo_st = gdk_surface_create_similar_surface (root, CAIRO_CONTENT_COLOR, width, height);
		image    = gdk_pixbuf_get_from_surface (cairo_st, 0, 0, width, height);
		//cairo_surface_destroy (cairo_st);
		//cairo_destroy (cr);
	#elif GTK_CHECK_VERSION (3,0,0)
		GdkWindow *root;
		root  = gtk_widget_get_window (window);
		gtk_window_get_size (GTK_WINDOW (window), &width, &height);
		image = gdk_pixbuf_get_from_window (root, 0, 0, width, height);
	#else
		GdkWindow *root;
		root  = gtk_widget_get_window (window);
		gtk_window_get_size (GTK_WINDOW (window), &width, &height);
		image = gdk_pixbuf_get_from_drawable (NULL, root, gdk_colormap_get_system (), 0, 0, 0, 0, width, height);
	#endif

	if (image) {
 		gdk_pixbuf_save (image, opt_screenshot, "png", NULL, "compression", "9", NULL);
		awf2_update_statusbar (g_strdup_printf (_("Theme reloaded, then screenshot saved (%s) at"), opt_screenshot), TRUE);
		g_object_unref (image);
	}

	return FALSE;
}

// layout

static void awf2_create_window (gpointer app, char *theme) {

	// https://developer.gnome.org/gtk3/stable/GtkContainer.html
	// https://developer.gnome.org/gtk3/stable/GtkApplication.html
	// https://developer.gnome.org/gtk3/stable/gtk-getting-started.html

	GtkWidget *vbox_window, *menubar, *toolbar, *widgets;
	GtkWidget *hbox_columns = BOXH, *vseparator1 = BOXVSEP, *vseparator2 = BOXVSEP, *vseparator3 = BOXVSEP, *hseparator1 = BOXHSEP;
	GtkWidget *vbox_column1 = BOXV, *vbox_combo_entry = BOXV, *hbox_spin = BOXH, *hbox_check_radio = BOXH, *vbox_check = BOXV, *vbox_radio = BOXV;
	GtkWidget *vbox_column2 = BOXV, *vbox_buttons = BOXV;
	GtkWidget *vbox_column3 = BOXV, *vbox_progressbar1 = BOXV, *vbox_progressbar2 = BOXV, *hbox_progressbar1 = BOXH, *hbox_progressbar2 = BOXH;
	GtkWidget *vbox_column4 = BOXV, *vbox_others = BOXV, *hbox_label = BOXH, *hbox_spinner = BOXH;
	GtkWidget *vpane = BOXVPANE, *hpane1 = BOXHPANE, *hpane2 = BOXHPANE;
	GtkWidget *hbox_frame1 = BOXH, *hbox_frame2 = BOXH, *hbox_notebook1 = BOXH, *hbox_notebook2 = BOXH;

	// base
	#if GTK_CHECK_VERSION (3,4,0)
		window = gtk_application_window_new (GTK_APPLICATION (app));
	#else
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	#endif

	gtk_window_set_title (GTK_WINDOW (window), g_strdup_printf (_("A widget factory - GTK %d - %s"), TRUE_GTK_MAJOR_VERSION, VERSION));
	gtk_window_set_icon_name (GTK_WINDOW (window), g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION));
	awf2_set_theme (theme);
	allow_update_theme = FALSE;

	// base layout
	vbox_window = BOXV;
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_window_set_child (GTK_WINDOW (window), vbox_window);
	#else
		gtk_container_add (GTK_CONTAINER (window), vbox_window);
	#endif

		#if GTK_CHECK_VERSION (3,90,0)
			GMenu *gmm;
			gmm = g_menu_new ();
			awf2_create_traditional_menubar (app, gmm);
			gtk_application_set_menubar (app, G_MENU_MODEL (gmm));
			gtk_application_window_set_show_menubar (GTK_APPLICATION_WINDOW (window), TRUE);
			g_object_unref (gmm);

			toolbar = BOXH;
			awf2_boxpack (GTK_BOX (vbox_window), toolbar, FALSE, FALSE, 0, 0);
			awf2_create_toolbar (toolbar);
		#else
			menubar = gtk_menu_bar_new ();
			awf2_create_traditional_menubar (menubar);
			awf2_boxpack (GTK_BOX (vbox_window), menubar, FALSE, FALSE, 0, 0);

			toolbar = gtk_toolbar_new ();
			awf2_boxpack (GTK_BOX (vbox_window), toolbar, FALSE, FALSE, 0, 0);
			awf2_create_toolbar (toolbar);
		#endif

		widgets = BOXV;
		awf2_boxpack (GTK_BOX (vbox_window), widgets, TRUE, TRUE, 0, 0);

	statusbar = gtk_statusbar_new ();
	awf2_boxpack (GTK_BOX (vbox_window), statusbar, FALSE, FALSE, 0, 0);
	awf2_update_statusbar (g_strdup_printf (_("Theme %s loaded."), current_theme), FALSE);

	// columns layout
	awf2_boxpack (GTK_BOX (widgets), hbox_columns, TRUE, TRUE, 0, 0);

		// column 1
		awf2_boxpack (GTK_BOX (hbox_columns), vbox_column1, TRUE, TRUE, 5, 0);
			awf2_boxpack (GTK_BOX (vbox_column1), vbox_combo_entry, FALSE, TRUE, 5, 3);
				awf2_create_combos_entries (vbox_combo_entry);
			awf2_boxpack (GTK_BOX (vbox_column1), hbox_spin, FALSE, FALSE, 5, 0);
				awf2_create_spinbuttons (hbox_spin);
			awf2_boxpack (GTK_BOX (vbox_column1), hbox_check_radio, FALSE, TRUE, 5, 0);
				awf2_boxpack (GTK_BOX (hbox_check_radio), vbox_check, TRUE, TRUE, 0, 0);
					awf2_create_checkbuttons (vbox_check);
				awf2_boxpack (GTK_BOX (hbox_check_radio), vbox_radio, TRUE, TRUE, 0, 0);
					awf2_create_radiobuttons (vbox_radio);
		awf2_boxpack (GTK_BOX (hbox_columns), vseparator1, FALSE, FALSE, 0, 0);

		// column 2
		awf2_boxpack (GTK_BOX (hbox_columns), vbox_column2, TRUE, TRUE, 5, 0);
			awf2_boxpack (GTK_BOX (vbox_column2), vbox_buttons, FALSE, TRUE, 5, 3);
				awf2_create_otherbuttons (vbox_buttons);
		awf2_boxpack (GTK_BOX (hbox_columns), vseparator2, FALSE, FALSE, 0, 0);

		// column 3
		awf2_boxpack (GTK_BOX (hbox_columns), vbox_column3, TRUE, TRUE, 5, 0);
			awf2_boxpack (GTK_BOX (vbox_column3), vbox_progressbar1, FALSE, TRUE, 6, 10);
			awf2_boxpack (GTK_BOX (vbox_column3), hbox_progressbar1, FALSE, FALSE, 5, 10);
			awf2_boxpack (GTK_BOX (vbox_column3), hbox_progressbar2, FALSE, FALSE, 5, 10);
			awf2_boxpack (GTK_BOX (vbox_column3), vbox_progressbar2, FALSE, TRUE, 5, 10);
				awf2_create_progressbars (vbox_progressbar1, vbox_progressbar2, hbox_progressbar1, hbox_progressbar2);
		awf2_boxpack (GTK_BOX (hbox_columns), vseparator3, FALSE, FALSE, 0, 0);

		// column 4
		awf2_boxpack (GTK_BOX (hbox_columns), vbox_column4, TRUE, TRUE, 5, 0);
			awf2_boxpack (GTK_BOX (vbox_column4), vbox_others, FALSE, TRUE, 5, 3);
				awf2_create_treview (vbox_others);
				awf2_boxpack (GTK_BOX (vbox_others), hbox_label, FALSE, TRUE, 5, 0);
					awf2_create_labels (hbox_label);
				awf2_boxpack (GTK_BOX (vbox_others), hbox_spinner, FALSE, TRUE, 5, 0);
					awf2_create_spinners (hbox_spinner);
				awf2_create_expander (vbox_others);

	awf2_boxpack (GTK_BOX (widgets), hseparator1, FALSE, FALSE, 0, 0);

	// paned layout
	awf2_boxpack (GTK_BOX (widgets), vpane, TRUE, TRUE, 0, 0);

		#if GTK_CHECK_VERSION (3,90,0)
			gtk_paned_set_start_child (GTK_PANED (vpane), hpane1);
		#else
			gtk_paned_pack1 (GTK_PANED (vpane), hpane1, TRUE, FALSE);
		#endif

			gtk_box_set_homogeneous (GTK_BOX (hbox_frame1), TRUE);
			gtk_box_set_spacing (GTK_BOX (hbox_frame1), 3);
			#if GTK_CHECK_VERSION (3,12,0)
				gtk_widget_set_size_request (hbox_frame1, -1, 50);
				gtk_widget_set_margin_start (hbox_frame1, 10);
				gtk_widget_set_margin_end (hbox_frame1, 10);
				gtk_widget_set_margin_top (hbox_frame1, 10);
				gtk_widget_set_margin_bottom (hbox_frame1, 10);
			#else
				gtk_widget_set_size_request (hbox_frame1, -1, 70);
				gtk_container_set_border_width (GTK_CONTAINER (hbox_frame1), 10);
			#endif
			#if GTK_CHECK_VERSION (3,90,0)
				gtk_paned_set_start_child (GTK_PANED (hpane1), hbox_frame1);
			#else
				gtk_paned_add1 (GTK_PANED (hpane1), hbox_frame1);
			#endif

			gtk_box_set_homogeneous (GTK_BOX (hbox_frame2), TRUE);
			gtk_box_set_spacing (GTK_BOX (hbox_frame2), 3);
			#if GTK_CHECK_VERSION (3,12,0)
				gtk_widget_set_size_request (hbox_frame2, -1, 50);
				gtk_widget_set_margin_start (hbox_frame2, 10);
				gtk_widget_set_margin_end (hbox_frame2, 10);
				gtk_widget_set_margin_top (hbox_frame2, 10);
				gtk_widget_set_margin_bottom (hbox_frame2, 10);
			#else
				gtk_widget_set_size_request (hbox_frame2, -1, 70);
				gtk_container_set_border_width (GTK_CONTAINER (hbox_frame2), 10);
			#endif
			#if GTK_CHECK_VERSION (3,90,0)
				gtk_paned_set_end_child (GTK_PANED (hpane1), hbox_frame2);
			#else
				gtk_paned_add2 (GTK_PANED (hpane1), hbox_frame2);
			#endif

			awf2_create_frames (hbox_frame1, hbox_frame2);

		#if GTK_CHECK_VERSION (3,90,0)
			gtk_paned_set_end_child (GTK_PANED (vpane), hpane2);
		#else
			gtk_paned_pack2 (GTK_PANED (vpane), hpane2, TRUE, FALSE);
		#endif

			gtk_box_set_homogeneous (GTK_BOX (hbox_notebook1), TRUE);
			gtk_box_set_spacing (GTK_BOX (hbox_notebook1), 3);
			#if GTK_CHECK_VERSION (3,12,0)
				gtk_widget_set_margin_start (hbox_notebook1, 10);
				gtk_widget_set_margin_end (hbox_notebook1, 10);
				gtk_widget_set_margin_top (hbox_notebook1, 10);
				gtk_widget_set_margin_bottom (hbox_notebook1, 10);
			#else
				gtk_container_set_border_width (GTK_CONTAINER (hbox_notebook1), 10);
			#endif
			#if GTK_CHECK_VERSION (3,90,0)
				gtk_paned_set_start_child (GTK_PANED (hpane2), hbox_notebook1);
			#else
				gtk_paned_add1 (GTK_PANED (hpane2), hbox_notebook1);
			#endif

			gtk_box_set_homogeneous (GTK_BOX (hbox_notebook2), TRUE);
			gtk_box_set_spacing (GTK_BOX (hbox_notebook2), 3);
			#if GTK_CHECK_VERSION (3,12,0)
				gtk_widget_set_margin_start (hbox_notebook2, 10);
				gtk_widget_set_margin_end (hbox_notebook2, 10);
				gtk_widget_set_margin_top (hbox_notebook2, 10);
				gtk_widget_set_margin_bottom (hbox_notebook2, 10);
			#else
				gtk_container_set_border_width (GTK_CONTAINER (hbox_notebook2), 10);
			#endif
			#if GTK_CHECK_VERSION (3,90,0)
				gtk_paned_set_end_child (GTK_PANED (hpane2), hbox_notebook2);
			#else
				gtk_paned_add2 (GTK_PANED (hpane2), hbox_notebook2);
			#endif

			awf2_create_notebooks (hbox_notebook1, hbox_notebook2);

	allow_update_theme = TRUE;

	// go
	g_signal_connect (window, "destroy", G_CALLBACK (awf2_quit), NULL);

	#if GTK_CHECK_VERSION (3,90,0)
		gtk_style_context_add_class (gtk_widget_get_style_context (toolbar), "primary-toolbar-gtk4");
		gtk_widget_show (window);
	#elif GTK_CHECK_VERSION (3,4,0)
		gtk_style_context_add_class (gtk_widget_get_style_context (toolbar), "primary-toolbar");
		gtk_widget_show_all (window);
	#elif GTK_CHECK_VERSION (3,0,0)
		gtk_style_context_add_class (gtk_widget_get_style_context (toolbar), "primary-toolbar");
		gtk_widget_show_all (window);
		gtk_main ();
	#else
		gtk_widget_show_all (window);
		gtk_main ();
	#endif
}

static void awf2_boxpack (GtkBox *box, GtkWidget *widget, gboolean fill, gboolean expand, guint padding, guint spacing) {

	// https://developer.gnome.org/gtk3/stable/GtkBox.html
	// https://developer.gnome.org/gtk4/stable/GtkBox.html

	#if GTK_CHECK_VERSION (3,90,0)
		if (fill) {
			gtk_widget_set_halign (widget, GTK_ALIGN_FILL);
			gtk_widget_set_valign (widget, GTK_ALIGN_FILL);
		}
		if (expand) {
			gtk_widget_set_hexpand (widget, TRUE);
			gtk_widget_set_vexpand (widget, TRUE);
		}
		if (GTK_IS_BOX (widget) && (padding > 0)) { // todo
			gtk_widget_set_margin_start (widget, padding);
			gtk_widget_set_margin_end (widget, padding);
			gtk_widget_set_margin_top (widget, padding);
			gtk_widget_set_margin_bottom (widget, padding);
		}
		if (GTK_IS_BOX (widget) && (spacing > 0)) {
			gtk_box_set_spacing (GTK_BOX (widget), spacing);
		}
		gtk_box_append (box, widget);
	#else
		if (GTK_IS_INFO_BAR (box))
			box = GTK_BOX (gtk_info_bar_get_content_area (GTK_INFO_BAR (box)));
		if (GTK_IS_CONTAINER (widget) && (padding > 0))
			gtk_container_set_border_width (GTK_CONTAINER (widget), padding);
		if (GTK_IS_BOX (widget) && (spacing > 0))
			gtk_box_set_spacing (GTK_BOX (widget), spacing);
		gtk_box_pack_start (box, widget, fill, expand, 0);
	#endif
}

static void awf2_create_toolbar (GtkWidget *root) {

	#if GTK_CHECK_VERSION (3,90,0)

		// https://developer.gnome.org/gtk4/stable/GtkButton.html
		// https://developer.gnome.org/gtk4/stable/GtkToggleButton.html

		GtkWidget *icon1, *icon2, *icon3, *icon4, *icon5, *icon6, *icon7, *menu;

		icon1 = gtk_button_new_from_icon_name ("gtk-open");
		gtk_widget_set_size_request (icon1, 36, 36);
		gtk_style_context_add_class (gtk_widget_get_style_context (icon1), "flat");
		g_signal_connect_swapped (icon1, "clicked", G_CALLBACK (awf2_show_dialog_open), NULL);

		icon2 = gtk_button_new_from_icon_name ("gtk-open");
		gtk_widget_set_size_request (icon2, 36, 36);
		gtk_style_context_add_class (gtk_widget_get_style_context (icon2), "flat");
		g_signal_connect_swapped (icon2, "clicked", G_CALLBACK (awf2_show_dialog_open_recent), NULL);

		icon3 = gtk_button_new_from_icon_name ("gtk-save");
		gtk_widget_set_size_request (icon3, 36, 36);
		gtk_style_context_add_class (gtk_widget_get_style_context (icon3), "flat");
		g_signal_connect_swapped (icon3, "clicked", G_CALLBACK (awf2_show_dialog_save), NULL);

		icon4 = gtk_button_new_from_icon_name ("gtk-refresh");
		gtk_widget_set_size_request (icon4, 36, 36);
		gtk_style_context_add_class (gtk_widget_get_style_context (icon4), "flat");
		g_signal_connect_swapped (icon4, "clicked", G_CALLBACK (awf2_set_theme), "refresh");

		icon5 = gtk_button_new_from_icon_name ("gtk-goto-first");
		gtk_widget_set_size_request (icon5, 36, 36);
		gtk_style_context_add_class (gtk_widget_get_style_context (icon5), "flat");

		icon6 = gtk_button_new_from_icon_name ("gtk-goto-last");
		gtk_widget_set_size_request (icon6, 36, 36);
		gtk_style_context_add_class (gtk_widget_get_style_context (icon6), "flat");
		gtk_widget_set_sensitive (icon6, FALSE);

		icon7 = gtk_toggle_button_new ();
		gtk_button_set_icon_name (GTK_BUTTON (icon7), "gtk-add");
		gtk_widget_set_size_request (icon7, 36, 36);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (icon7), TRUE);
		gtk_style_context_add_class (gtk_widget_get_style_context (icon7), "flat");
		g_signal_connect_swapped (icon7, "clicked", G_CALLBACK (awf2_update_widgets), NULL);

		awf2_boxpack (GTK_BOX (root), icon1, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root), icon2, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root), icon3, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root), icon4, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root), BOXVSEP, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root), icon5, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root), icon6, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root), BOXVSEP, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root), icon7, FALSE, FALSE, 0, 0);
	#else
		// https://developer.gnome.org/gtk3/stable/GtkToolbar.html
		// https://developer.gnome.org/gtk3/stable/GtkMenuToolButton.html
		// https://developer.gnome.org/gtk3/stable/GtkToolButton.html
		// https://developer.gnome.org/gtk3/stable/GtkSeparatorToolItem.html
		// https://developer.gnome.org/gtk3/stable/GtkToggleToolButton.html
		// https://developer.gnome.org/gtk3/stable/GtkMenu.html
		// https://developer.gnome.org/gtk3/stable/GtkMenuItem.html

		GtkWidget *icon1, *icon2, *icon3, *icon4, *icon5, *icon6, *icon7, *menu;

		icon1 = GTK_WIDGET (gtk_menu_tool_button_new (NULL, NULL));
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon1), "gtk-open");
		g_signal_connect_swapped (icon1, "clicked", G_CALLBACK (awf2_show_dialog_open), NULL);

		icon2 = GTK_WIDGET (gtk_menu_tool_button_new (NULL, NULL));
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon2), "gtk-open");
		menu = gtk_menu_new ();
		awf2_new_menu_item (menu, "Menu item", "", FALSE);
		gtk_widget_show_all (menu); // very important
		gtk_menu_tool_button_set_menu (GTK_MENU_TOOL_BUTTON (icon2), menu);
		g_signal_connect_swapped (icon2, "clicked", G_CALLBACK (awf2_show_dialog_open_recent), NULL);

		icon3 = GTK_WIDGET (gtk_tool_button_new (NULL, NULL));
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon3), "gtk-save");
		g_signal_connect_swapped (icon3, "clicked", G_CALLBACK (awf2_show_dialog_save), NULL);

		icon4 = GTK_WIDGET (gtk_tool_button_new (NULL, NULL));
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon4), "gtk-refresh");
		g_signal_connect_swapped (icon4, "clicked", G_CALLBACK (awf2_set_theme), "refresh");

		#if GTK_CHECK_VERSION (3,14,0)
			icon5 = GTK_WIDGET (gtk_tool_button_new (NULL, NULL));
			gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon5), "gtk-goto-first");
		#else
			icon5 = GTK_WIDGET (gtk_tool_button_new_from_stock ("gtk-goto-first"));
		#endif

		#if GTK_CHECK_VERSION (3,14,0)
			icon6 = GTK_WIDGET (gtk_tool_button_new (NULL, NULL));
			gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon6), "gtk-goto-last");
			gtk_widget_set_sensitive (icon6, FALSE);
		#else
			icon6 = GTK_WIDGET (gtk_tool_button_new_from_stock ("gtk-goto-last"));
			gtk_widget_set_sensitive (icon6, FALSE);
		#endif

		icon7 = GTK_WIDGET (gtk_toggle_tool_button_new ());
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon7), "gtk-add");
		gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (icon7), TRUE);
		g_signal_connect_swapped (icon7, "clicked", G_CALLBACK (awf2_update_widgets), NULL);

		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon1), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon2), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon3), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon4), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), gtk_separator_tool_item_new (), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon5), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon6), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), gtk_separator_tool_item_new (), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon7), -1);
	#endif
}

static void awf2_create_combos_entries (GtkWidget *root) {

	// https://developer.gnome.org/gtk3/stable/GtkComboBoxText.html
	// https://developer.gnome.org/gtk3/stable/GtkComboBox.html
	// https://developer.gnome.org/gtk3/stable/GtkEntry.html
	// https://developer.gnome.org/gtk4/stable/GtkEditable.html

	GtkWidget *combo1, *combo2, *combo3, *combo4, *entry1, *entry2, *entry3, *entry4;

	combo1 = gtk_combo_box_text_new_with_entry ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo1), "Combo box entry 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo1), "Combo box entry 2");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combo1), 0);

	combo2 = gtk_combo_box_text_new_with_entry ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo2), "Combo box entry 1 (disabled)");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo2), "Combo box entry 2 (disabled)");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combo2), 0);
	gtk_widget_set_sensitive (combo2, FALSE);

	combo3 = gtk_combo_box_text_new ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo3), "Combo box 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo3), "Combo box 2");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combo3), 0);

	combo4 = gtk_combo_box_text_new ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo4), "Combo box 1 (disabled)");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo4), "Combo box 2 (disabled)");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combo4), 0);
	gtk_widget_set_sensitive (combo4, FALSE);

	entry1 = gtk_entry_new ();
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_editable_set_text (GTK_EDITABLE (entry1), "Entry");
	#else
		gtk_entry_set_text (GTK_ENTRY (entry1), "Entry");
	#endif

	entry2 = gtk_entry_new ();
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_editable_set_text (GTK_EDITABLE (entry2), "Entry (disabled)");
	#else
		gtk_entry_set_text (GTK_ENTRY (entry2), "Entry (disabled)");
	#endif
	gtk_widget_set_sensitive (entry2, FALSE);

	entry3 = gtk_entry_new ();
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_editable_set_text (GTK_EDITABLE (entry3), "Entry");
	#else
		gtk_entry_set_text (GTK_ENTRY (entry3), "Entry");
	#endif
	gtk_entry_set_icon_from_icon_name (GTK_ENTRY (entry3), GTK_ENTRY_ICON_PRIMARY, "gtk-clear");
	gtk_entry_set_icon_from_icon_name (GTK_ENTRY (entry3), GTK_ENTRY_ICON_SECONDARY, "gtk-find");
	gtk_entry_set_icon_tooltip_text (GTK_ENTRY (entry3), GTK_ENTRY_ICON_PRIMARY, "gtk-clear");
	gtk_entry_set_icon_tooltip_text (GTK_ENTRY (entry3), GTK_ENTRY_ICON_SECONDARY, "gtk-find");

	entry4 = gtk_entry_new ();
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_editable_set_text (GTK_EDITABLE (entry4), "Entry (disabled)");
	#else
		gtk_entry_set_text (GTK_ENTRY (entry4), "Entry (disabled)");
	#endif
	gtk_entry_set_icon_from_icon_name (GTK_ENTRY (entry4), GTK_ENTRY_ICON_PRIMARY, "gtk-clear");
	gtk_entry_set_icon_from_icon_name (GTK_ENTRY (entry4), GTK_ENTRY_ICON_SECONDARY, "gtk-find");
	gtk_entry_set_icon_tooltip_text (GTK_ENTRY (entry4), GTK_ENTRY_ICON_PRIMARY, "gtk-clear");
	gtk_entry_set_icon_tooltip_text (GTK_ENTRY (entry4), GTK_ENTRY_ICON_SECONDARY, "gtk-find");
	gtk_widget_set_sensitive (entry4, FALSE);

	#if GTK_CHECK_VERSION (3,2,0)
		gtk_entry_set_placeholder_text (GTK_ENTRY (entry1), "Placeholder");
		gtk_entry_set_placeholder_text (GTK_ENTRY (entry3), "Placeholder");
	#endif

	awf2_boxpack (GTK_BOX (root), combo1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), combo2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), combo3, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), combo4, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), entry1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), entry2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), entry3, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), entry4, FALSE, FALSE, 0, 0);
}

static void awf2_create_spinbuttons (GtkWidget *root) {

	// https://developer.gnome.org/gtk3/stable/GtkSpinButton.html

	spinbutton1 = gtk_spin_button_new_with_range (-100, 100, 1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinbutton1), 1);
	gtk_widget_set_tooltip_text (spinbutton1, "spin button");

	spinbutton2 = gtk_spin_button_new_with_range (-100, 100, 1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinbutton2), 1);
	gtk_widget_set_tooltip_text (spinbutton2, "spin button");
	gtk_widget_set_sensitive (spinbutton2, FALSE);

	awf2_boxpack (GTK_BOX (root), spinbutton1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
	awf2_boxpack (GTK_BOX (root), spinbutton2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
}

static void awf2_create_checkbuttons (GtkWidget *root) {

	// https://developer.gnome.org/gtk3/stable/GtkCheckButton.html

	GtkWidget *checkbutton1, *checkbutton2, *checkbutton3, *checkbutton4, *checkbutton5, *checkbutton6;

	checkbutton1 = gtk_check_button_new_with_label ("Check button 1");

	checkbutton2 = gtk_check_button_new_with_label ("Check button 2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton2), TRUE);

	checkbutton3 = gtk_check_button_new_with_label ("Check button 3");
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_check_button_set_inconsistent (GTK_CHECK_BUTTON (checkbutton3), TRUE);
	#else
		gtk_toggle_button_set_inconsistent (GTK_TOGGLE_BUTTON (checkbutton3), TRUE);
	#endif

	checkbutton4 = gtk_check_button_new_with_label ("Check button 4");
	gtk_widget_set_sensitive (checkbutton4, FALSE);

	checkbutton5 = gtk_check_button_new_with_label ("Check button 5");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton5), TRUE);
	gtk_widget_set_sensitive (checkbutton5, FALSE);

	checkbutton6 = gtk_check_button_new_with_label ("Check button 6");
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_check_button_set_inconsistent (GTK_CHECK_BUTTON (checkbutton6), TRUE);
	#else
		gtk_toggle_button_set_inconsistent (GTK_TOGGLE_BUTTON (checkbutton6), TRUE);
	#endif
	gtk_widget_set_sensitive (checkbutton6, FALSE);

	awf2_boxpack (GTK_BOX (root), checkbutton1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), checkbutton2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), checkbutton3, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), checkbutton4, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), checkbutton5, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), checkbutton6, FALSE, FALSE, 0, 0);
}

static void awf2_create_radiobuttons (GtkWidget *root) {

	// https://developer.gnome.org/gtk3/stable/GtkRadioButton.html

	GtkWidget *radio1, *radio2, *radio3, *radio4;
	GtkWidget *radiobutton1, *radiobutton2, *radiobutton3, *radiobutton4, *radiobutton5, *radiobutton6;

	radio1 = gtk_radio_button_new (NULL);
	radio2 = gtk_radio_button_new (NULL);
	radio3 = gtk_radio_button_new (NULL);
	radio4 = gtk_radio_button_new (NULL);

	radiobutton1 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1), "Radio button 1");

	radiobutton2 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio1), "Radio button 2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton2), TRUE);

	radiobutton3 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio2), "Radio button 3");
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_check_button_set_inconsistent (GTK_CHECK_BUTTON (radiobutton3), TRUE);
	#else
		gtk_toggle_button_set_inconsistent (GTK_TOGGLE_BUTTON (radiobutton3), TRUE);
	#endif

	radiobutton4 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio3), "Radio button 4");
	gtk_widget_set_sensitive (radiobutton4, FALSE);

	radiobutton5 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio3), "Radio button 5");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton5), TRUE);
	gtk_widget_set_sensitive (radiobutton5, FALSE);

	radiobutton6 = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio4), "Radio button 6");
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_check_button_set_inconsistent (GTK_CHECK_BUTTON (radiobutton6), TRUE);
	#else
		gtk_toggle_button_set_inconsistent (GTK_TOGGLE_BUTTON (radiobutton6), TRUE);
	#endif
	gtk_widget_set_sensitive (radiobutton6, FALSE);

	awf2_boxpack (GTK_BOX (root), radiobutton1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), radiobutton2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), radiobutton3, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), radiobutton4, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), radiobutton5, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), radiobutton6, FALSE, FALSE, 0, 0);
}

static void awf2_create_otherbuttons (GtkWidget *root) {

	const char *scale_icons[] = { g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION), NULL };
	GtkWidget *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9, *button10, *button11, *button12;
	#if !GTK_CHECK_VERSION (3,0,0)
		GtkWidget *combomenu1, *combomenu2;
	#endif

	// https://developer.gnome.org/gtk3/stable/GtkButton.html

	button1 = gtk_button_new_with_label ("Button 1");

	button2 = gtk_button_new_with_label ("Button 2");
	gtk_widget_set_sensitive (button2, FALSE);

	// https://developer.gnome.org/gtk3/stable/GtkToggleButton.html

	button3 = gtk_toggle_button_new_with_label ("Toggle button 1");

	button4 = gtk_toggle_button_new_with_label ("Toggle button 2");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button3), TRUE);
	gtk_widget_set_sensitive (button4, FALSE);

	// https://developer.gnome.org/gtk3/stable/GtkColorButton.html

	#if GTK_CHECK_VERSION (3,0,0)
		GdkRGBA color;
		gdk_rgba_parse (&color, "#7796ba");
		button5 = gtk_color_button_new_with_rgba (&color);
	#else
		GdkColor color;
		gdk_color_parse ("#7796ba", &color);
		button5 = gtk_color_button_new_with_color (&color);
	#endif

	button6 = gtk_font_button_new ();
	gtk_widget_set_size_request (button5, 175, -1);

	button7 = gtk_file_chooser_button_new ("GtkFileChooserDialog", GTK_FILE_CHOOSER_ACTION_OPEN);

	button8 = gtk_file_chooser_button_new ("GtkFileChooserDialog", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);

	#if GTK_CHECK_VERSION (3,0,0)
		button9 = gtk_switch_new ();
		gtk_switch_set_active (GTK_SWITCH (button9), TRUE);

		button10 = gtk_switch_new ();
		gtk_switch_set_active (GTK_SWITCH (button10), FALSE);
		gtk_widget_set_sensitive (button10, FALSE);
	#else
		combomenu1 = gtk_menu_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu1), gtk_menu_item_new_with_label ("Option 1"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu1), gtk_menu_item_new_with_label ("Option 2"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu1), gtk_menu_item_new_with_label ("Option 3"));

		button9 = gtk_option_menu_new ();
		gtk_option_menu_set_menu (GTK_OPTION_MENU (button9), combomenu1);

		combomenu2 = gtk_menu_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu2), gtk_menu_item_new_with_label ("Option 1"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu2), gtk_menu_item_new_with_label ("Option 2"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu2), gtk_menu_item_new_with_label ("Option 3"));

		button10 = gtk_option_menu_new ();
		gtk_option_menu_set_menu (GTK_OPTION_MENU (button10), combomenu2);
		gtk_widget_set_sensitive (button10, FALSE);
	#endif

	button11 = gtk_link_button_new_with_label ("https://github.com/luigifab/awf-extended", "Link button");

	// https://developer.gnome.org/gtk3/stable/GtkScaleButton.html

	#if GTK_CHECK_VERSION (3,90,0)
		button12 = gtk_scale_button_new (1, 10, 1, scale_icons);
	#else
		button12 = gtk_scale_button_new (GTK_ICON_SIZE_BUTTON, 1, 10, 1, scale_icons);
	#endif

	awf2_boxpack (GTK_BOX (root), button1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button3, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button4, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button5, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button6, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button7, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button8, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button9, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button10, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button11, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), button12, FALSE, FALSE, 0, 0);
}

static void awf2_create_progressbars (GtkWidget *root1, GtkWidget *root2, GtkWidget *root3, GtkWidget *root4) {

	// https://developer.gnome.org/gtk3/stable/GtkProgressBar.html
	// https://developer.gnome.org/gtk3/stable/GtkLevelBar.html
	// https://developer.gnome.org/gtk3/stable/GtkScale.html

	#if GTK_CHECK_VERSION (3,0,0)
		progressbar1 = gtk_progress_bar_new ();
		gtk_widget_set_size_request (progressbar1, 175, -1);
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar1), 0.5);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (progressbar1), GTK_ORIENTATION_HORIZONTAL);
		gtk_widget_set_tooltip_text (progressbar1, "progress bar");
	#else
		progressbar1 = gtk_progress_bar_new ();
		gtk_widget_set_size_request (progressbar1, 175, -1);
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar1), 0.5);
		gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (progressbar1), GTK_PROGRESS_LEFT_TO_RIGHT);
		gtk_widget_set_tooltip_text (progressbar1, "progress bar");
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		progressbar2 = gtk_progress_bar_new ();
		gtk_widget_set_size_request (progressbar2, 175, -1);
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar2), 0.5);
		gtk_progress_bar_set_inverted (GTK_PROGRESS_BAR (progressbar2), TRUE);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (progressbar2), GTK_ORIENTATION_HORIZONTAL);
		gtk_widget_set_tooltip_text (progressbar2, "progress bar");
	#else
		progressbar2 = gtk_progress_bar_new ();
		gtk_widget_set_size_request (progressbar2, 175, -1);
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar2), 0.5);
		gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (progressbar2), GTK_PROGRESS_RIGHT_TO_LEFT);
		gtk_widget_set_tooltip_text (progressbar2, "progress bar");
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		scale1 = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
		gtk_widget_set_size_request (scale1, 175, -1);
		gtk_range_set_value (GTK_RANGE (scale1), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale1), FALSE);
		gtk_widget_set_tooltip_text (scale1, "scale");
		g_signal_connect (scale1, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#else
		scale1 = gtk_hscale_new_with_range (0, 100, 1);
		gtk_widget_set_size_request (scale1, 175, -1);
		gtk_range_set_value (GTK_RANGE (scale1), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale1), FALSE);
		gtk_widget_set_tooltip_text (scale1, "scale");
		g_signal_connect (scale1, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		scale2 = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
		gtk_widget_set_size_request (scale2, 175, -1);
		gtk_range_set_value (GTK_RANGE (scale2), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale2), FALSE);
		gtk_range_set_inverted (GTK_RANGE (scale2), TRUE);
		gtk_widget_set_tooltip_text (scale2, "scale");
		g_signal_connect (scale2, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#else
		scale2 = gtk_hscale_new_with_range (0, 100, 1);
		gtk_widget_set_size_request (scale2, 175, -1);
		gtk_range_set_value (GTK_RANGE (scale2), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale2), FALSE);
		gtk_range_set_inverted (GTK_RANGE (scale2), TRUE);
		gtk_widget_set_tooltip_text (scale2, "scale");
		g_signal_connect (scale2, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		progressbar3 = gtk_progress_bar_new ();
		gtk_widget_set_size_request (progressbar3, -1, 100);
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar3), 0.5);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (progressbar3), GTK_ORIENTATION_VERTICAL);
		gtk_widget_set_tooltip_text (progressbar3, "progress bar");
	#else
		progressbar3 = gtk_progress_bar_new ();
		gtk_widget_set_size_request (progressbar3, -1, 100);
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar3), 0.5);
		gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (progressbar3), GTK_PROGRESS_TOP_TO_BOTTOM);
		gtk_widget_set_tooltip_text (progressbar3, "progress bar");
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		progressbar4 = gtk_progress_bar_new ();
		gtk_widget_set_size_request (progressbar4, -1, 100);
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar4), 0.5);
		gtk_progress_bar_set_inverted (GTK_PROGRESS_BAR (progressbar4), TRUE);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (progressbar4), GTK_ORIENTATION_VERTICAL);
		gtk_widget_set_tooltip_text (progressbar4, "progress bar");
	#else
		progressbar4 = gtk_progress_bar_new ();
		gtk_widget_set_size_request (progressbar4, -1, 100);
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar4), 0.5);
		gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (progressbar4), GTK_PROGRESS_BOTTOM_TO_TOP);
		gtk_widget_set_tooltip_text (progressbar4, "progress bar");
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		scale3 = gtk_scale_new_with_range (GTK_ORIENTATION_VERTICAL, 0, 100, 1);
		gtk_widget_set_size_request (scale3, -1, 100);
		gtk_range_set_value (GTK_RANGE (scale3), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale3), FALSE);
		gtk_widget_set_tooltip_text (scale3, "scale");
		g_signal_connect (scale3, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#else
		scale3 = gtk_vscale_new_with_range (0, 100, 1);
		gtk_widget_set_size_request (scale3, -1, 100);
		gtk_range_set_value (GTK_RANGE (scale3), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale3), FALSE);
		gtk_widget_set_tooltip_text (scale3, "scale");
		g_signal_connect (scale3, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		scale4 = gtk_scale_new_with_range (GTK_ORIENTATION_VERTICAL, 0, 100, 1);
		gtk_widget_set_size_request (scale4, -1, 100);
		gtk_range_set_value (GTK_RANGE (scale4), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale4), FALSE);
		gtk_range_set_inverted (GTK_RANGE (scale4), TRUE);
		gtk_widget_set_tooltip_text (scale4, "scale");
		g_signal_connect (scale4, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#else
		scale4 = gtk_vscale_new_with_range (0, 100, 1);
		gtk_widget_set_size_request (scale4, -1, 100);
		gtk_range_set_value (GTK_RANGE (scale4), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale4), FALSE);
		gtk_range_set_inverted (GTK_RANGE (scale4), TRUE);
		gtk_widget_set_tooltip_text (scale4, "scale");
		g_signal_connect (scale4, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		scale5 = gtk_scale_new_with_range (GTK_ORIENTATION_VERTICAL, 0, 100, 1);
		gtk_widget_set_size_request (scale5, -1, 100);
		gtk_range_set_value (GTK_RANGE (scale5), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale5), FALSE);
		gtk_widget_set_tooltip_text (scale5, "scale");
		g_signal_connect (scale5, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#else
		scale5 = gtk_vscale_new_with_range (0, 100, 1);
		gtk_widget_set_size_request (scale5, -1, 100);
		gtk_range_set_value (GTK_RANGE (scale5), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale5), FALSE);
		gtk_widget_set_tooltip_text (scale5, "scale");
		g_signal_connect (scale5, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		scale6 = gtk_scale_new_with_range (GTK_ORIENTATION_VERTICAL, 0, 100, 1);
		gtk_widget_set_size_request (scale6, -1, 100);
		gtk_range_set_value (GTK_RANGE (scale6), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale6), FALSE);
		gtk_range_set_inverted (GTK_RANGE (scale6), TRUE);
		gtk_widget_set_tooltip_text (scale6, "scale");
		g_signal_connect (scale6, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#else
		scale6 = gtk_vscale_new_with_range (0, 100, 1);
		gtk_widget_set_size_request (scale6, -1, 100);
		gtk_range_set_value (GTK_RANGE (scale6), 50);
		gtk_scale_set_draw_value (GTK_SCALE (scale6), FALSE);
		gtk_range_set_inverted (GTK_RANGE (scale6), TRUE);
		gtk_widget_set_tooltip_text (scale6, "scale");
		g_signal_connect (scale6, "value_changed", G_CALLBACK (awf2_update_progressbars), NULL);
	#endif

	#if GTK_CHECK_VERSION (3,6,0)
		levelbar1 = gtk_level_bar_new ();
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar1), GTK_LEVEL_BAR_MODE_CONTINUOUS);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar1), 0.5);
		gtk_widget_set_tooltip_text (levelbar1, "level bar");

		levelbar2 = gtk_level_bar_new ();
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar2), GTK_LEVEL_BAR_MODE_CONTINUOUS);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar2), 0.5);
		#if GTK_CHECK_VERSION (3,8,0)
			gtk_level_bar_set_inverted (GTK_LEVEL_BAR (levelbar2), TRUE);
		#endif
		gtk_widget_set_tooltip_text (levelbar2, "level bar");

		// GTK 3.20.9 gtk_level_bar_set_value do nothing
		levelbar3 = gtk_level_bar_new_for_interval (0, 5);
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar3), GTK_LEVEL_BAR_MODE_DISCRETE);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar3), 2);
		gtk_widget_set_tooltip_text (levelbar3, "level bar");

		// GTK 3.20.9 gtk_level_bar_set_value do nothing
		levelbar4 = gtk_level_bar_new_for_interval (0, 5);
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar4), GTK_LEVEL_BAR_MODE_DISCRETE);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar4), 2);
		#if GTK_CHECK_VERSION (3,8,0)
			gtk_level_bar_set_inverted (GTK_LEVEL_BAR (levelbar4), TRUE);
		#endif
		gtk_widget_set_tooltip_text (levelbar4, "level bar");

		levelbar5 = gtk_level_bar_new ();
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar5), GTK_LEVEL_BAR_MODE_CONTINUOUS);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar5), 0.5);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (levelbar5), GTK_ORIENTATION_VERTICAL);
		gtk_widget_set_tooltip_text (levelbar5, "level bar");

		levelbar6 = gtk_level_bar_new ();
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar6), GTK_LEVEL_BAR_MODE_CONTINUOUS);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar6), 0.5);
		#if GTK_CHECK_VERSION (3,8,0)
			gtk_level_bar_set_inverted (GTK_LEVEL_BAR (levelbar6), TRUE);
		#endif
		gtk_orientable_set_orientation (GTK_ORIENTABLE (levelbar6), GTK_ORIENTATION_VERTICAL);
		gtk_widget_set_tooltip_text (levelbar6, "level bar");

		// GTK 3.20.9 gtk_level_bar_set_value do nothing
		levelbar7 = gtk_level_bar_new_for_interval (0, 5);
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar7), GTK_LEVEL_BAR_MODE_DISCRETE);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar7), 2);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (levelbar7), GTK_ORIENTATION_VERTICAL);
		gtk_widget_set_tooltip_text (levelbar7, "level bar");

		// GTK 3.20.9 gtk_level_bar_set_value do nothing
		levelbar8 = gtk_level_bar_new_for_interval (0, 5);
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar8), GTK_LEVEL_BAR_MODE_DISCRETE);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar8), 2);
		#if GTK_CHECK_VERSION (3,8,0)
			gtk_level_bar_set_inverted (GTK_LEVEL_BAR (levelbar8), TRUE);
		#endif
		gtk_orientable_set_orientation (GTK_ORIENTABLE (levelbar8), GTK_ORIENTATION_VERTICAL);
		gtk_widget_set_tooltip_text (levelbar8, "level bar");
	#endif

	awf2_boxpack (GTK_BOX (root1), progressbar1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root1), progressbar2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root1), scale1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root1), scale2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root3), progressbar3, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root3), progressbar4, FALSE, FALSE, 0, 0);
	#if GTK_CHECK_VERSION (3,6,0)
		awf2_boxpack (GTK_BOX (root3), levelbar5, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root3), levelbar6, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root3), levelbar7, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root3), levelbar8, FALSE, FALSE, 0, 0);
	#endif
	awf2_boxpack (GTK_BOX (root4), scale3, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root4), scale4, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root4), scale5, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root4), scale6, FALSE, FALSE, 0, 0);
	#if GTK_CHECK_VERSION (3,6,0)
		awf2_boxpack (GTK_BOX (root2), levelbar1, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root2), levelbar2, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root2), levelbar3, FALSE, FALSE, 0, 0);
		awf2_boxpack (GTK_BOX (root2), levelbar4, FALSE, FALSE, 0, 0);
	#endif
}

static void awf2_create_labels (GtkWidget *root) {

	// https://developer.gnome.org/gtk3/stable/GtkLabel.html

	GtkWidget *label1, *label2;

	label1 = gtk_label_new ("Label 1");
	gtk_widget_set_tooltip_text (label1, "label");

	label2 = gtk_label_new ("Label 2");
	gtk_widget_set_tooltip_text (label2, "label");
	gtk_widget_set_sensitive (label2, FALSE);

	awf2_boxpack (GTK_BOX (root), label1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
	awf2_boxpack (GTK_BOX (root), label2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
}

static void awf2_create_spinners (GtkWidget *root) {

	// https://developer.gnome.org/gtk3/stable/GtkSpinner.html

	GtkWidget *spinner1, *spinner2;

	spinner1 = gtk_spinner_new ();
	gtk_widget_set_size_request (spinner1, 20, 20);
	gtk_widget_set_tooltip_text (spinner1, "spinner");
	if (opt_startspinner)
		gtk_spinner_start (GTK_SPINNER (spinner1));

	spinner2 = gtk_spinner_new ();
	gtk_widget_set_size_request (spinner2, 20, 20);
	gtk_widget_set_tooltip_text (spinner2, "spinner");
	gtk_widget_set_sensitive (spinner2, FALSE);
	if (opt_startspinner)
		gtk_spinner_start (GTK_SPINNER (spinner2));

	awf2_boxpack (GTK_BOX (root), spinner1, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
	awf2_boxpack (GTK_BOX (root), spinner2, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
}

static void awf2_create_expander (GtkWidget *root) {

	// https://developer.gnome.org/gtk3/stable/GtkExpander.html
	// https://developer.gnome.org/gtk3/stable/GtkScrolledWindow.html
	// https://developer.gnome.org/gtk3/stable/GtkTextView.html

	GtkWidget *expander, *scrolled_window, *tv;
	GtkTextBuffer *buffer;

	expander = gtk_expander_new (_("More..."));
	//#if GTK_CHECK_VERSION (3,20,0)
	//	set label width to 100% impossible?
	//#endif

	#if GTK_CHECK_VERSION (3,90,0)
		scrolled_window = gtk_scrolled_window_new ();
	#else
		scrolled_window = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window), GTK_SHADOW_IN);
	#endif
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_widget_set_size_request (scrolled_window, -1, 120);

	tv = gtk_text_view_new ();
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (tv), GTK_WRAP_WORD);
	gtk_text_buffer_set_text (GTK_TEXT_BUFFER (buffer), g_strdup_printf ("%s ~ %s", _("A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme."), _("A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme.")), -1);

	#if GTK_CHECK_VERSION (3,90,0)
		gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scrolled_window), tv);
		gtk_expander_set_child (GTK_EXPANDER (expander), scrolled_window);
	#else
		gtk_container_add (GTK_CONTAINER (scrolled_window), tv);
		gtk_container_add (GTK_CONTAINER (expander), scrolled_window);
	#endif
	awf2_boxpack (GTK_BOX (root), expander, FALSE, FALSE, 0, 0);
}

static void awf2_create_frames (GtkWidget *root1, GtkWidget *root2) {

	// https://developer.gnome.org/gtk3/stable/GtkFrame.html

	GtkWidget *frame1, *frame2, *frame3, *frame4;

	#if GTK_CHECK_VERSION (3,90,0)
		frame1 = gtk_frame_new ("Frame (shadow in)");
		gtk_style_context_add_class (gtk_widget_get_style_context (frame1), "border-inset");
	#elif GTK_CHECK_VERSION (3,0,0)
		frame1 = gtk_frame_new ("Frame (shadow in)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_IN);
		gtk_style_context_add_class (gtk_widget_get_style_context (frame1), "border-inset");
	#else
		frame1 = gtk_frame_new ("Frame (shadow in)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_IN);
	#endif

	#if GTK_CHECK_VERSION (3,90,0)
		frame2 = gtk_frame_new ("Frame (shadow out)");
		gtk_style_context_add_class (gtk_widget_get_style_context (frame2), "border-outset");
	#elif GTK_CHECK_VERSION (3,0,0)
		frame2 = gtk_frame_new ("Frame (shadow out)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame2), GTK_SHADOW_OUT);
		gtk_style_context_add_class (gtk_widget_get_style_context (frame2), "border-outset");
	#else
		frame2 = gtk_frame_new ("Frame (shadow out)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame2), GTK_SHADOW_OUT);
	#endif

	#if GTK_CHECK_VERSION (3,90,0)
		frame3 = gtk_frame_new ("Frame (shadow etched in)");
		gtk_style_context_add_class (gtk_widget_get_style_context (frame3), "border-groove");
	#elif GTK_CHECK_VERSION (3,0,0)
		frame3 = gtk_frame_new ("Frame (shadow etched in)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame3), GTK_SHADOW_ETCHED_IN);
		gtk_style_context_add_class (gtk_widget_get_style_context (frame3), "border-groove");
	#else
		frame3 = gtk_frame_new ("Frame (shadow etched in)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame3), GTK_SHADOW_ETCHED_IN);
	#endif

	#if GTK_CHECK_VERSION (3,90,0)
		frame4 = gtk_frame_new ("Frame (shadow etched out)");
		gtk_style_context_add_class (gtk_widget_get_style_context (frame4), "border-ridge");
	#elif GTK_CHECK_VERSION (3,0,0)
		frame4 = gtk_frame_new ("Frame (shadow etched out)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame4), GTK_SHADOW_ETCHED_OUT);
		gtk_style_context_add_class (gtk_widget_get_style_context (frame4), "border-ridge");
	#else
		frame4 = gtk_frame_new ("Frame (shadow etched out)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame4), GTK_SHADOW_ETCHED_OUT);
	#endif

	awf2_boxpack (GTK_BOX (root1), frame1, TRUE, TRUE, 0, 0);
	awf2_boxpack (GTK_BOX (root1), frame2, TRUE, TRUE, 0, 0);
	awf2_boxpack (GTK_BOX (root2), frame3, TRUE, TRUE, 0, 0);
	awf2_boxpack (GTK_BOX (root2), frame4, TRUE, TRUE, 0, 0);
}

static void awf2_create_notebooks (GtkWidget *root1, GtkWidget *root2) {

	// https://developer.gnome.org/gtk3/stable/GtkNotebook.html
	// https://developer.gnome.org/gtk3/stable/GtkEventControllerScroll.html

	notebook1 = gtk_notebook_new ();
	notebook2 = gtk_notebook_new ();
	notebook3 = gtk_notebook_new ();
	notebook4 = gtk_notebook_new ();

	#if GTK_CHECK_VERSION (3,90,0)
	// this does not work, because scroll is possible from content
	//	GtkEventController *event1, *event2, *event3, *event4;
	//	event1 = gtk_event_controller_scroll_new (GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES | GTK_EVENT_CONTROLLER_SCROLL_DISCRETE);
	//	g_signal_connect (event1, "scroll", G_CALLBACK (awf2_gtk40_scrolltabs), notebook1);
	//	gtk_widget_add_controller (notebook1, event1);
	//	event2 = gtk_event_controller_scroll_new (GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES);
	//	g_signal_connect (event2, "scroll", G_CALLBACK (awf2_gtk40_scrolltabs), notebook2);
	//	gtk_widget_add_controller (notebook2, event2);
	//	event3 = gtk_event_controller_scroll_new (GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES);
	//	g_signal_connect (event3, "scroll", G_CALLBACK (awf2_gtk40_scrolltabs), notebook3);
	//	gtk_widget_add_controller (notebook3, event3);
	//	event4 = gtk_event_controller_scroll_new (GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES);
	//	g_signal_connect (event4, "scroll", G_CALLBACK (awf2_gtk40_scrolltabs), notebook4);
	//	gtk_widget_add_controller (notebook4, event4);
	//elif GTK_CHECK_VERSION (3,24,0)
	// this works but there is a delay (first scroll is ignored)
	//	GtkEventController *event1, *event2, *event3, *event4;
	//	event1 = gtk_event_controller_scroll_new (notebook1, GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES | GTK_EVENT_CONTROLLER_SCROLL_DISCRETE);
	//	g_signal_connect (event1, "scroll", G_CALLBACK (awf2_gtk40_scrolltabs), notebook1);
	//	event2 = gtk_event_controller_scroll_new (notebook2, GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES);
	//	g_signal_connect (event2, "scroll", G_CALLBACK (awf2_gtk40_scrolltabs), notebook2);
	//	event3 = gtk_event_controller_scroll_new (notebook3, GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES);
	//	g_signal_connect (event3, "scroll", G_CALLBACK (awf2_gtk40_scrolltabs), notebook3);
	//	event4 = gtk_event_controller_scroll_new (notebook4, GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES);
	//	g_signal_connect (event4, "scroll", G_CALLBACK (awf2_gtk40_scrolltabs), notebook4);
	#elif GTK_CHECK_VERSION (3,4,0)
		gtk_widget_add_events (notebook1, GDK_SCROLL_MASK);
		g_signal_connect (notebook1, "scroll-event", G_CALLBACK (awf2_gtk34_scrolltabs), NULL);
		gtk_widget_add_events (notebook2, GDK_SCROLL_MASK);
		g_signal_connect (notebook2, "scroll-event", G_CALLBACK (awf2_gtk34_scrolltabs), NULL);
		gtk_widget_add_events (notebook3, GDK_SCROLL_MASK);
		g_signal_connect (notebook3, "scroll-event", G_CALLBACK (awf2_gtk34_scrolltabs), NULL);
		gtk_widget_add_events (notebook4, GDK_SCROLL_MASK);
		g_signal_connect (notebook4, "scroll-event", G_CALLBACK (awf2_gtk34_scrolltabs), NULL);
	#endif

	gtk_notebook_popup_enable (GTK_NOTEBOOK (notebook1));
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook1), FALSE);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook1), GTK_POS_TOP);
		awf2_create_notebook_tab (notebook1, "tab1");
		awf2_create_notebook_tab (notebook1, "tab2");
		awf2_create_notebook_tab (notebook1, "tab3");
		awf2_create_notebook_tab (notebook1, "tab4");

	gtk_notebook_popup_enable (GTK_NOTEBOOK (notebook2));
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook2), FALSE);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook2), GTK_POS_BOTTOM);
		awf2_create_notebook_tab (notebook2, "tab1");
		awf2_create_notebook_tab (notebook2, "tab2");
		awf2_create_notebook_tab (notebook2, "tab3");
		awf2_create_notebook_tab (notebook2, "tab4");

	gtk_notebook_popup_enable (GTK_NOTEBOOK (notebook3));
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook3), FALSE);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook3), GTK_POS_LEFT);
		awf2_create_notebook_tab (notebook3, "tab1");
		awf2_create_notebook_tab (notebook3, "tab2");
		awf2_create_notebook_tab (notebook3, "tab3");
		awf2_create_notebook_tab (notebook3, "tab4");

	gtk_notebook_popup_enable (GTK_NOTEBOOK (notebook4));
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook4), FALSE);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook4), GTK_POS_RIGHT);
		awf2_create_notebook_tab (notebook4, "tab1");
		awf2_create_notebook_tab (notebook4, "tab2");
		awf2_create_notebook_tab (notebook4, "tab3");
		awf2_create_notebook_tab (notebook4, "tab4");

	awf2_boxpack (GTK_BOX (root1), notebook1, TRUE, TRUE, 0, 0);
	awf2_boxpack (GTK_BOX (root1), notebook2, TRUE, TRUE, 0, 0);
	awf2_boxpack (GTK_BOX (root2), notebook3, TRUE, TRUE, 0, 0);
	awf2_boxpack (GTK_BOX (root2), notebook4, TRUE, TRUE, 0, 0);
}

static void awf2_create_notebook_tab (GtkWidget *notebook, char *text) {

	// https://developer.gnome.org/gtk3/stable/GtkNotebook.html
	// https://developer.gnome.org/gtk3/stable/GtkEventControllerScroll.html

	GtkWidget *head, *content;

	head = gtk_label_new (text);
	content = BOXV;

	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), content, head);
	gtk_notebook_set_tab_reorderable (GTK_NOTEBOOK (notebook), content, TRUE);

	#if GTK_CHECK_VERSION (3,90,0)
		// this works but there is a delay (first scroll is ignored)
		GtkEventController *event;
		event = gtk_event_controller_scroll_new (GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES | GTK_EVENT_CONTROLLER_SCROLL_DISCRETE);
		g_signal_connect (event, "scroll", G_CALLBACK (awf2_gtk40_scrolltabs), notebook);
		gtk_widget_add_controller (gtk_widget_get_parent (head), event);
	#endif
}

static void awf2_create_treview (GtkWidget *root) {

	GtkWidget *scrolled_window, *view;
	GtkCellRenderer *renderer;
	GtkTreeModel *model;
	GtkListStore *store;
	GtkTreeIter iter;

	view = gtk_tree_view_new ();
	gtk_widget_set_size_request (view, 200, 200);

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "Longer column 1", renderer, "text", 0, NULL);

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1, "Longer column 2", renderer, "text", 1, NULL);

	store = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_STRING);
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter, 0, "Longer cell 1.1", 1, "Longer cell 1.2", -1);
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter, 0, "Longer cell 2.1", 1, "Longer cell 2.2", -1);
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter, 0, "Longer cell 3.1", 1, "Longer cell 3.2", -1);
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter, 0, "Longer cell 4.1", 1, "Longer cell 4.2", -1);

	model = GTK_TREE_MODEL (store);
	gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

	#if GTK_CHECK_VERSION (3,90,0)
		scrolled_window = gtk_scrolled_window_new ();
	#else
		scrolled_window = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window), GTK_SHADOW_IN);
	#endif
	gtk_widget_set_size_request (scrolled_window, 200, 200);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);

	#if GTK_CHECK_VERSION (3,90,0)
		awf2_boxpack (GTK_BOX (scrolled_window), view, FALSE, FALSE, 0, 0);
	#else
		gtk_container_add (GTK_CONTAINER (scrolled_window), view);
	#endif
	awf2_boxpack (GTK_BOX (root), scrolled_window, FALSE, FALSE, 0, 0);
}

// menuitems

#if GTK_CHECK_VERSION (3,90,0)

static void awf2_create_traditional_menubar (gpointer app, GMenu *root) {

	// https://developer.gnome.org/gio/stable/GMenu.html
	// https://developer.gnome.org/gio/stable/GActionMap.html

	GMenu *menu, *submenu, *section;
	GMenuItem *menuitem;
	GSimpleAction *action;
	GSList *iterator;

	g_action_group_activate_action (G_ACTION_GROUP (app), "menubar", NULL);

	// system
	menu = g_menu_new ();
	g_menu_append_submenu (root, _("_System theme"), G_MENU_MODEL (menu));
	for (iterator = list_system_theme; iterator; iterator = iterator->next) {
		menuitem = g_menu_item_new (iterator->data, NULL);
		g_menu_item_set_attribute_value (menuitem, G_MENU_ATTRIBUTE_TARGET, FALSE);
		g_menu_append_item (menu, menuitem);
		//g_menu_item_set_action_and_target_value (menuitem, "awf2_set_theme", iterator->data);
		//if (strcmp ((char*)current_theme, (char*)iterator->data) == 0)
		//	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
	}

	if (!list_system_theme)
		g_menu_append (menu, _("No themes found"), "disabled");

	g_object_unref (menu);

	// user
	menu = g_menu_new ();
	g_menu_append_submenu (root, _("_User theme"), G_MENU_MODEL (menu));
	for (iterator = list_user_theme; iterator; iterator = iterator->next) {
		menuitem = g_menu_item_new (iterator->data, NULL);
		g_menu_item_set_attribute_value (menuitem, G_MENU_ATTRIBUTE_TARGET, FALSE);
		g_menu_append_item (menu, menuitem);
		//g_menu_item_set_action_and_target_value (menuitem, "awf2_set_theme", iterator->data);
		//if (strcmp ((char*)current_theme, (char*)iterator->data) == 0)
		//	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
	}

	if (!list_user_theme)
		g_menu_append (menu, _("No themes found"), "disabled");

	g_object_unref (menu);

	// options
	menu = g_menu_new ();
	g_menu_append_submenu (root, _("_Options"), G_MENU_MODEL (menu));

		menuitem = g_menu_item_new (_("gtk-open"), NULL);
		g_menu_item_set_attribute (menuitem, "accel", "s", "<Control>O", NULL);
		g_menu_append_item (menu, menuitem);
		// G_CALLBACK (awf2_show_dialog_open), AWF_OPEN

		menuitem = g_menu_item_new (_("Open recent file"), NULL);
		g_menu_append_item (menu, menuitem);
		// G_CALLBACK (awf2_show_dialog_open_recent), AWF_RECE

		menuitem = g_menu_item_new (_("Calendar"), NULL);
		g_menu_append_item (menu, menuitem);
		// G_CALLBACK (awf2_show_dialog_calendar), AWF_CALE

		menuitem = g_menu_item_new (_("gtk-save"), NULL);
		g_menu_item_set_attribute (menuitem, "accel", "s", "<Control>S", NULL);
		g_menu_append_item (menu, menuitem);
		// G_CALLBACK (awf2_show_dialog_save), AWF_SAVE

		menuitem = g_menu_item_new (_("Refresh theme"), NULL); // "gtk-refresh"
		g_menu_item_set_attribute (menuitem, "accel", "s", "F5", NULL);
		g_menu_append_item (menu, menuitem);
		// (G_CALLBACK (awf2_set_theme), "refresh"), AWF_REFR

		menuitem = g_menu_item_new (_("gtk-properties"), NULL);
		g_menu_item_set_attribute (menuitem, "accel", "s", "<Alt>Return", NULL);
		g_menu_append_item (menu, menuitem);
		// G_CALLBACK (awf2_show_dialog_properties), AWF_PROP

		menuitem = g_menu_item_new (_("gtk-page-setup"), NULL);
		g_menu_append_item (menu, menuitem);
		// G_CALLBACK (awf2_show_dialog_page_setup), AWF_PRSE

		menuitem = g_menu_item_new (_("gtk-print"), NULL);
		g_menu_item_set_attribute (menuitem, "accel", "s", "<Control>P", NULL);
		g_menu_append_item (menu, menuitem);
		// G_CALLBACK (awf2_show_dialog_print), AWF_PRIN

		action = g_simple_action_new ("win.gtk-about", NULL);
		g_signal_connect (action, "activate", G_CALLBACK (awf2_show_dialog_about), app);
		g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (action));
		g_object_unref (action);

		menuitem = g_menu_item_new (_("gtk-about"), "win.gtk-about");
		g_menu_item_set_attribute (menuitem, "accel", "s", "F1", NULL);
		g_menu_append_item (menu, menuitem);
		// G_CALLBACK (awf2_show_dialog_about), AWF_ABOU);

		submenu = g_menu_new ();
		g_menu_append_submenu (menu, _("More..."), G_MENU_MODEL (submenu));

			menuitem = g_menu_item_new (_("gtk-cut"), NULL);
			g_menu_item_set_attribute (menuitem, "accel", "s", "<Control>X", NULL);
			g_menu_append_item (submenu, menuitem);
			// AWF_MCUT

			menuitem = g_menu_item_new (_("gtk-copy"), NULL);
			g_menu_item_set_attribute (menuitem, "accel", "s", "<Control>C", NULL);
			g_menu_append_item (submenu, menuitem);
			// AWF_MCOP

			menuitem = g_menu_item_new (_("gtk-paste"), NULL);
			g_menu_item_set_attribute (menuitem, "accel", "s", "<Control>V", NULL);
			g_menu_append_item (submenu, menuitem);
			// AWF_MPAS

		g_object_unref (submenu);

		section = g_menu_new ();
		g_menu_append_section (menu, NULL, G_MENU_MODEL (section));

			menuitem = g_menu_item_new (g_strdup_printf ("Check 1 %s", _("(unchecked)")), NULL); // FALSE, FALSE, FALSE
			g_menu_append_item (section, menuitem);

			menuitem = g_menu_item_new (g_strdup_printf ("Check 2 %s", _("(checked)")), NULL); // TRUE, FALSE, FALSE
			g_menu_append_item (section, menuitem);

			menuitem = g_menu_item_new (g_strdup_printf ("Check 3 %s", _("(inconsistent)")), NULL); // FALSE, TRUE, FALSE
			g_menu_append_item (section, menuitem);

		g_object_unref (section);

		section = g_menu_new ();
		g_menu_append_section (menu, NULL, G_MENU_MODEL (section));

			menuitem = g_menu_item_new (g_strdup_printf ("Check 1 %s", _("(unchecked)")), "disabled"); // FALSE, FALSE
			g_menu_append_item (section, menuitem);

			menuitem = g_menu_item_new (g_strdup_printf ("Check 2 %s", _("(checked)")), "disabled"); // TRUE, FALSE
			g_menu_append_item (section, menuitem);

			menuitem = g_menu_item_new (g_strdup_printf ("Check 3 %s", _("(inconsistent)")), "disabled"); // FALSE, TRUE
			g_menu_append_item (section, menuitem);

		g_object_unref (section);

		section = g_menu_new ();
		g_menu_append_section (menu, NULL, G_MENU_MODEL (section));

			menuitem = g_menu_item_new (g_strdup_printf ("Radio 1 %s", _("(unchecked)")), NULL); // FALSE, FALSE, FALSE, NULL
			g_menu_item_set_attribute_value (menuitem, G_MENU_ATTRIBUTE_TARGET, FALSE);
			g_menu_append_item (section, menuitem);

			menuitem = g_menu_item_new (g_strdup_printf ("Radio 2 %s", _("(checked)")), NULL); // TRUE, FALSE, FALSE, group
			g_menu_item_set_attribute_value (menuitem, G_MENU_ATTRIBUTE_TARGET, FALSE);
			g_menu_append_item (section, menuitem);

			menuitem = g_menu_item_new (g_strdup_printf ("Radio 3 %s", _("(inconsistent)")), NULL); // FALSE, TRUE, FALSE, NULL
			g_menu_item_set_attribute_value (menuitem, G_MENU_ATTRIBUTE_TARGET, FALSE);
			g_menu_append_item (section, menuitem);

		g_object_unref (section);

		section = g_menu_new ();
		g_menu_append_section (menu, NULL, G_MENU_MODEL (section));

			menuitem = g_menu_item_new (g_strdup_printf ("Radio 1 %s", _("(unchecked)")), "disabled"); // FALSE, FALSE, NULL
			g_menu_item_set_attribute_value (menuitem, G_MENU_ATTRIBUTE_TARGET, FALSE);
			g_menu_append_item (section, menuitem);

			menuitem = g_menu_item_new (g_strdup_printf ("Radio 2 %s", _("(checked)")), "disabled"); // TRUE, FALSE, group
			g_menu_item_set_attribute_value (menuitem, G_MENU_ATTRIBUTE_TARGET, FALSE);
			g_menu_append_item (section, menuitem);

			menuitem = g_menu_item_new (g_strdup_printf ("Radio 3 %s", _("(inconsistent)")), "disabled"); // FALSE, TRUE, NULL
			g_menu_item_set_attribute_value (menuitem, G_MENU_ATTRIBUTE_TARGET, FALSE);
			g_menu_append_item (section, menuitem);

		g_object_unref (section);

		section = g_menu_new ();
		g_menu_append_section (menu, NULL, G_MENU_MODEL (section));

			menuitem = g_menu_item_new (_("gtk-close"), "disabled");
			g_menu_item_set_attribute (menuitem, "accel", "s", "<Control>W", NULL);
			g_menu_append_item (section, menuitem);
			// AWF_CLOS

			menuitem = g_menu_item_new (_("gtk-quit"), NULL);
			g_menu_item_set_attribute (menuitem, "accel", "s", "<Control>Q", NULL);
			g_menu_append_item (section, menuitem);
			// G_CALLBACK (awf2_quit), AWF_QUIT

		g_object_unref (section);

	g_object_unref (menu);
}

#else

static void awf2_create_traditional_menubar (GtkWidget *root) {

	// https://developer.gnome.org/gtk3/stable/GtkMenu.html
	// https://developer.gnome.org/gtk3/stable/GtkMenuItem.html
	// https://developer.gnome.org/gtk3/stable/GtkRadioMenuItem.html
	// https://developer.gnome.org/gtk3/stable/gtk3-Keyboard-Accelerators.html

	GtkWidget *menu, *submenu, *menuitem;
	GSList *iterator, *group = NULL;
	GtkAccelGroup *accels = gtk_accel_group_new ();
	GdkModifierType mods;
	guint key;

	gtk_window_add_accel_group (GTK_WINDOW (window), accels);

	// system
	menu = awf2_new_menu (root, _("_System theme"));
	for (iterator = list_system_theme; iterator; iterator = iterator->next) {
		menuitem = awf2_new_menu_radio (menu, iterator->data, FALSE, FALSE, FALSE, group);
		group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
		if (strcmp ((char*)current_theme, (char*)iterator->data) == 0)
			gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_set_theme), iterator->data);
	}

	if (!list_system_theme)
		awf2_new_menu_item (menu, _("No themes found"), "", TRUE);

	// user
	menu = awf2_new_menu (root, _("_User theme"));
	for (iterator = list_user_theme; iterator; iterator = iterator->next) {
		menuitem = awf2_new_menu_radio (menu, iterator->data, FALSE, FALSE, FALSE, group);
		group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
		if (strcmp ((char*)current_theme, (char*)iterator->data) == 0)
			gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_set_theme), iterator->data);
	}

	if (!list_user_theme)
		awf2_new_menu_item (menu, _("No themes found"), "", TRUE);

	// options
	menu = awf2_new_menu (root, _("_Options"));
	gtk_menu_set_accel_group (GTK_MENU (menu), accels); // very important

		awf2_new_menu_tearoff (menu);

		menuitem = awf2_new_menu_item (menu, "", "gtk-open", FALSE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_show_dialog_open), NULL);
		gtk_accelerator_parse ("<Control>O", &key, &mods);
		gtk_accel_map_add_entry (AWF_OPEN, key, mods);
		gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_OPEN);

		menuitem = awf2_new_menu_item (menu, _("Open recent file"), "", FALSE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_show_dialog_open_recent), NULL);
		gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_RECE);

		menuitem = awf2_new_menu_item (menu, _("Calendar"), "", FALSE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_show_dialog_calendar), NULL);
		gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_CALE);

		menuitem = awf2_new_menu_item (menu, "", "gtk-save", FALSE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_show_dialog_save), NULL);
		gtk_accelerator_parse ("<Control>S", &key, &mods);
		gtk_accel_map_add_entry (AWF_SAVE, key, mods);
		gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_SAVE);

		menuitem = awf2_new_menu_item (menu, _("Refresh theme"), "gtk-refresh", FALSE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_set_theme), "refresh");
		gtk_accelerator_parse ("F5", &key, &mods);
		gtk_accel_map_add_entry (AWF_REFR, key, mods);
		gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_REFR);

		menuitem = awf2_new_menu_item (menu, "", "gtk-properties", FALSE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_show_dialog_properties), NULL);
		gtk_accelerator_parse ("<Alt>Return", &key, &mods);
		gtk_accel_map_add_entry (AWF_PROP, key, mods);
		gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_PROP);

		menuitem = awf2_new_menu_item (menu, "", "gtk-page-setup", FALSE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_show_dialog_page_setup), NULL);
		gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_PRSE);

		menuitem = awf2_new_menu_item (menu, "", "gtk-print", FALSE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_show_dialog_print), NULL);
		gtk_accelerator_parse ("<Control>P", &key, &mods);
		gtk_accel_map_add_entry (AWF_PRIN, key, mods);
		gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_PRIN);

		menuitem = awf2_new_menu_item (menu, "", "gtk-about", FALSE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_show_dialog_about), NULL);
		gtk_accelerator_parse ("F1", &key, &mods);
		gtk_accel_map_add_entry (AWF_ABOU, key, mods);
		gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_ABOU);

		submenu = awf2_new_menu (menu, _("More..."));
		gtk_menu_set_accel_group (GTK_MENU (submenu), accels); // very important

			menuitem = awf2_new_menu_item (submenu, "", "gtk-cut", FALSE);
			gtk_accelerator_parse ("<Control>X", &key, &mods);
			gtk_accel_map_add_entry (AWF_MCUT, key, mods);
			gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_MCUT);

			menuitem = awf2_new_menu_item (submenu, "", "gtk-copy", FALSE);
			gtk_accelerator_parse ("<Control>C", &key, &mods);
			gtk_accel_map_add_entry (AWF_MCOP, key, mods);
			gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_MCOP);

			menuitem = awf2_new_menu_item (submenu, "", "gtk-paste", FALSE);
			gtk_accelerator_parse ("<Control>V", &key, &mods);
			gtk_accel_map_add_entry (AWF_MPAS, key, mods);
			gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_MPAS);

		awf2_new_menu_separator (menu);

			awf2_new_menu_check (menu, g_strdup_printf ("Check 1 %s", _("(unchecked)")), FALSE, FALSE, FALSE);
			awf2_new_menu_check (menu, g_strdup_printf ("Check 2 %s", _("(checked)")), TRUE, FALSE, FALSE);
			awf2_new_menu_check (menu, g_strdup_printf ("Check 3 %s", _("(inconsistent)")), FALSE, TRUE, FALSE);

		awf2_new_menu_separator (menu);

			awf2_new_menu_check (menu, g_strdup_printf ("Check 1 %s", _("(unchecked)")), FALSE, FALSE, TRUE);
			awf2_new_menu_check (menu, g_strdup_printf ("Check 2 %s", _("(checked)")), TRUE, FALSE, TRUE);
			awf2_new_menu_check (menu, g_strdup_printf ("Check 3 %s", _("(inconsistent)")), FALSE, TRUE, TRUE);

		awf2_new_menu_separator (menu);

			menuitem = awf2_new_menu_radio (menu, g_strdup_printf ("Radio 1 %s", _("(unchecked)")), FALSE, FALSE, FALSE, NULL);
			group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
					 awf2_new_menu_radio (menu, g_strdup_printf ("Radio 2 %s", _("(checked)")), TRUE, FALSE, FALSE, group);
					 awf2_new_menu_radio (menu, g_strdup_printf ("Radio 3 %s", _("(inconsistent)")), FALSE, TRUE, FALSE, NULL);

		awf2_new_menu_separator (menu);

			menuitem = awf2_new_menu_radio (menu, g_strdup_printf ("Radio 1 %s", _("(unchecked)")), FALSE, FALSE, TRUE, NULL);
			group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
					 awf2_new_menu_radio (menu, g_strdup_printf ("Radio 2 %s", _("(checked)")), TRUE, FALSE, TRUE, group);
					 awf2_new_menu_radio (menu, g_strdup_printf ("Radio 3 %s", _("(inconsistent)")), FALSE, TRUE, TRUE, NULL);

		awf2_new_menu_separator (menu);

			menuitem = awf2_new_menu_item (menu, "", "gtk-close", TRUE);
			gtk_accelerator_parse ("<Control>W", &key, &mods);
			gtk_accel_map_add_entry (AWF_CLOS, key, mods);
			gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_CLOS);

			menuitem = awf2_new_menu_item (menu, "", "gtk-quit", FALSE);
			g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (awf2_quit), NULL);
			gtk_accelerator_parse ("<Control>Q", &key, &mods);
			gtk_accel_map_add_entry (AWF_QUIT, key, mods);
			gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), AWF_QUIT);

	awf2_accels_load ();

	// disabled to get same thing between GTK 2.24/3.0 and 3.2-3.24
	// gtk-can-change-accels for GTK 2.24 and GTK 3.0 only
	//#if !GTK_CHECK_VERSION (3,2,0)
	//	g_signal_connect_swapped (gtk_accel_map_get (), "changed", G_CALLBACK (awf2_...), NULL);
	//	g_object_set (gtk_settings_get_default (), "gtk-can-change-accels", TRUE, NULL);
	//
	//	static void awf2_... (GtkAccelMap *accel_map, char *accel_path, guint accel_key, GdkModifierType accel_mods)
	//		if (accel_path != NULL)
	//			gtk_accel_map_change_entry (accel_path, accel_key, accel_mods, TRUE);
	//#endif
	g_object_set (gtk_settings_get_default (), "gtk-can-change-accels", FALSE, NULL);
}

static GtkWidget* awf2_new_menu (GtkWidget *root, char *text) {

	// https://developer.gnome.org/gtk3/stable/GtkMenu.html
	// https://developer.gnome.org/gtk3/stable/GtkMenuItem.html

	GtkWidget *menu, *menuitem;

	menu = gtk_menu_new ();
	menuitem = gtk_menu_item_new_with_mnemonic (text);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), menu);
	gtk_menu_shell_append (GTK_MENU_SHELL (root), menuitem);

	// disabled to get same thing between GTK 2.24/3.0 and 3.2-3.24
	// gtk-can-change-accels for GTK 3.2-3.24
	//#if GTK_CHECK_VERSION (3,2,0)
		gtk_widget_set_events (menu, GDK_KEY_RELEASE_MASK);
		g_signal_connect (menu, "key-release-event", G_CALLBACK (awf2_accels_change), NULL);
	//#endif

	return menu;
}

static GtkWidget* awf2_new_menu_tearoff (GtkWidget *menu) {

	// https://developer.gnome.org/gtk3/stable/GtkTearoffMenuItem.html

	GtkWidget *menuitem;

	#if GTK_CHECK_VERSION (3,0,0)
		menuitem = gtk_tearoff_menu_item_new ();
		gtk_style_context_add_class (gtk_widget_get_style_context (menuitem), "tearoff");
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
	#else
		menuitem = gtk_tearoff_menu_item_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
	#endif

	return menuitem;
}

static GtkWidget* awf2_new_menu_separator (GtkWidget *menu) {

	// https://developer.gnome.org/gtk3/stable/GtkSeparatorMenuItem.html

	GtkWidget *menuitem;

	menuitem = gtk_separator_menu_item_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

	return menuitem;
}

static GtkWidget* awf2_new_menu_check (GtkWidget *menu, char *text, gboolean checked, gboolean inconsistent, gboolean disabled) {

	// https://developer.gnome.org/gtk3/stable/GtkCheckMenuItem.html

	GtkWidget *menuitem;

	menuitem = gtk_check_menu_item_new_with_mnemonic (text);
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), checked);
	gtk_check_menu_item_set_inconsistent (GTK_CHECK_MENU_ITEM (menuitem), inconsistent);
	gtk_widget_set_sensitive (menuitem, !disabled);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

	return menuitem;
}

static GtkWidget* awf2_new_menu_radio (GtkWidget *menu, char *text, gboolean checked, gboolean inconsistent, gboolean disabled, GSList *group) {

	// https://developer.gnome.org/gtk3/stable/GtkRadioMenuItem.html

	GtkWidget *menuitem;

	menuitem = gtk_radio_menu_item_new_with_mnemonic (group, text);
	gtk_check_menu_item_set_inconsistent (GTK_CHECK_MENU_ITEM (menuitem), inconsistent);
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), checked);
	gtk_widget_set_sensitive (menuitem, !disabled);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

	return menuitem;
}

static GtkWidget* awf2_new_menu_item (GtkWidget *menu, char *text, char *image, gboolean disabled) {

	// https://developer.gnome.org/gtk3/stable/GtkMenuItem.html
	// https://developer.gnome.org/gtk3/stable/GtkImageMenuItem.html

	GtkWidget *menuitem;

	if (strlen (image) > 0)
		menuitem = gtk_image_menu_item_new_from_stock (image, NULL);
	else
		menuitem = gtk_menu_item_new_with_mnemonic (text);

	gtk_widget_set_sensitive (menuitem, !disabled);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

	// disabled to get same thing between GTK 2.24/3.0 and 3.2-3.24
	// gtk-can-change-accels for GTK 3.2-3.24
	//#if GTK_CHECK_VERSION (3,2,0)
		g_signal_connect (menuitem, "select", G_CALLBACK (awf2_accels_select), NULL);
		g_signal_connect (menuitem, "deselect", G_CALLBACK (awf2_accels_deselect), NULL);
	//#endif

	return menuitem;
}

// accelerators

static void awf2_accels_load () {

	// https://developer.gnome.org/gtk3/stable/gtk3-Accelerator-Maps.html

	char *path;
	path = g_build_filename ("/", g_getenv ("HOME"), ".awf-gtk-accels", NULL);

	if (g_file_test (path, G_FILE_TEST_IS_REGULAR))
		gtk_accel_map_load (path);

	g_free (path);
}

static void awf2_accels_select (GtkWidget *widget) {
	current_menuitem = widget;
}

static void awf2_accels_deselect (GtkWidget *widget) {
	if (current_menuitem == widget)
		current_menuitem = NULL;
}

static void awf2_accels_change (GtkWidget *widget, GdkEventKey *event) {

	// disabled to get same thing between GTK 2.24/3.0 and 3.2-3.24
	// gtk-can-change-accels for GTK 3.2-3.24
	//#if GTK_CHECK_VERSION (3,2,0)

		// https://developer.gnome.org/gdk3/stable/gdk3-Keyboard-Handling.html
		// https://gitlab.gnome.org/GNOME/gtk/-/commit/2d79334bb069224966b3dcd8456967c9800e8fd0

		if (!current_menuitem)
			return;

		GtkMenuItem *menuitem = GTK_MENU_ITEM (current_menuitem);
		char *key = gdk_keyval_name (event->keyval);

		if (
			!gtk_menu_item_get_accel_path (menuitem) ||
			(strcmp (key, "Control_L") == 0) || (strcmp (key, "Control_R") == 0) ||
			(strcmp (key, "Shift_L") == 0) || (strcmp (key, "Shift_R") == 0) ||
			(strcmp (key, "Super_L") == 0) || (strcmp (key, "Super_R") == 0) ||
			(strcmp (key, "Alt_L") == 0) || (strcmp (key, "Alt_R") == 0)
		) {
			return;
		}

		if (
			(event->keyval == GDK_KEY_Delete) ||
			(event->keyval == GDK_KEY_KP_Delete) ||
			(event->keyval == GDK_KEY_BackSpace) ||
			// f1..12
			((event->keyval >= GDK_KEY_F1) && (event->keyval <= GDK_KEY_F12)) ||
			// crtl/shift/super/alt + ?
			(event->state & GDK_CONTROL_MASK) || (event->state & GDK_SHIFT_MASK) ||
			(event->state & GDK_SUPER_MASK) || (event->state & GDK_MOD1_MASK)
		) {
			must_save_accels = TRUE;

			if ((event->keyval == GDK_KEY_Delete) || (event->keyval == GDK_KEY_KP_Delete) || (event->keyval == GDK_KEY_BackSpace))
				gtk_accel_map_change_entry (gtk_menu_item_get_accel_path (menuitem), 0, 0, TRUE);
			else
				gtk_accel_map_change_entry (
					gtk_menu_item_get_accel_path (menuitem),
					gdk_keyval_to_lower (event->keyval),
					event->state & gtk_accelerator_get_default_mod_mask (),
					TRUE);
		}
	//#endif
}

static void awf2_accels_save () {

	// https://developer.gnome.org/gtk3/stable/gtk3-Accelerator-Maps.html

	if (must_save_accels) {

		char *path;

		path = g_build_filename ("/", g_getenv ("HOME"), ".awf-gtk-accels", NULL);
		gtk_accel_map_save (path);

		g_free (path);
	}
}

#endif

// dialogs

static void awf2_show_dialog_open () {

	// https://developer.gnome.org/gtk3/stable/GtkFileChooserDialog.html

	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new (
		"GtkFileChooserDialog",
		GTK_WINDOW (window),
		GTK_FILE_CHOOSER_ACTION_OPEN,
		"gtk-cancel",
		GTK_RESPONSE_CANCEL,
		"gtk-open",
		GTK_RESPONSE_ACCEPT,
		NULL);

	gtk_window_set_icon_name (GTK_WINDOW (dialog), g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION));
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_widget_show (dialog); // todo
		g_signal_connect (dialog, "response", G_CALLBACK (awf2_gtk40_closedialog), NULL);
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void awf2_show_dialog_open_recent () {

	// https://developer.gnome.org/gtk3/stable/GtkRecentChooserDialog.html

	GtkWidget *dialog;

	#if !GTK_CHECK_VERSION (3,90,0)

		dialog = gtk_recent_chooser_dialog_new (
			"GtkRecentChooserDialog",
			GTK_WINDOW (window),
			"gtk-cancel",
			GTK_RESPONSE_CANCEL,
			"gtk-open",
			GTK_RESPONSE_ACCEPT,
			NULL);

		gtk_window_set_icon_name (GTK_WINDOW (dialog), g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION));
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void awf2_show_dialog_save () {

	// https://developer.gnome.org/gtk3/stable/GtkFileChooserDialog.html

	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new (
		"GtkFileChooserDialog",
		GTK_WINDOW (window),
		GTK_FILE_CHOOSER_ACTION_SAVE,
		"gtk-cancel",
		GTK_RESPONSE_CANCEL,
		"gtk-save",
		GTK_RESPONSE_ACCEPT,
		NULL);

	gtk_window_set_icon_name (GTK_WINDOW (dialog), g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION));
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_widget_show (dialog); // todo
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void awf2_show_dialog_properties () {

	// https://developer.gnome.org/gtk3/stable/GtkMessageDialog.html

	GtkWidget *dialog;

	dialog = gtk_message_dialog_new (
		GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_YES_NO,
		"GtkMessageDialog");

	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), _("A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme."));

	gtk_window_set_title (GTK_WINDOW (dialog), "GtkMessageDialog");
	gtk_window_set_icon_name (GTK_WINDOW (dialog), g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION));
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_widget_show (dialog); // todo
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void awf2_show_dialog_page_setup () {

	// https://developer.gnome.org/gtk3/stable/GtkPageSetupUnixDialog.html

	GtkWidget *dialog;

	dialog = gtk_page_setup_unix_dialog_new (
		"GtkPageSetupUnixDialog",
		GTK_WINDOW (window));

	gtk_window_set_icon_name (GTK_WINDOW (dialog), g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION));
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_widget_show (dialog); // todo
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void awf2_show_dialog_print () {

	// https://developer.gnome.org/gtk3/stable/GtkPrintUnixDialog.html

	GtkWidget *dialog;

	dialog = gtk_print_unix_dialog_new (
		"GtkPrintUnixDialog",
		GTK_WINDOW (window));

	gtk_window_set_icon_name (GTK_WINDOW (dialog), g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION));
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_widget_show (dialog); // todo
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void awf2_show_dialog_about () {

	// https://developer.gnome.org/gtk3/stable/GtkAboutDialog.html

	gtk_show_about_dialog (GTK_WINDOW (window),
		"version", VERSION,
		"comments", g_strdup_printf ("%s\n\n%s\n%s\n\n%s\n%s",
			_("A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme."),
			g_strdup_printf (_("Remove %s file"), "~/.awf-gtk-accels"),
			_("to reset keyboard shortcuts."),
			g_strdup_printf (_("compiled with gtk %d.%d.%d and glib %d.%d.%d"),
				GTK_MAJOR_VERSION, GTK_MINOR_VERSION, GTK_MICRO_VERSION,
				GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION),
			g_strdup_printf (_(" started with gtk %d.%d.%d and glib %d.%d.%d"),
				gtk_major_version, gtk_minor_version, gtk_micro_version,
				glib_major_version, glib_minor_version, glib_micro_version)),
		"website", "https://github.com/luigifab/awf-extended",
		"copyright", "Copyright © 2020 Fabrice Creuzot (luigifab)\nCopyright © 2011-2017 Valère Monseur (valr)",
		"icon-name", g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION),
		"logo-icon-name", g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION),
		"license", "A widget factory is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.",
		"wrap-license", TRUE,
		NULL);
}

static void awf2_show_dialog_calendar () {

	// https://developer.gnome.org/gtk3/stable/GtkDialog.html
	// https://developer.gnome.org/gtk3/stable/GtkInfoBar.html
	// https://developer.gnome.org/gtk3/stable/GtkCalendar.html
	// https://developer.gnome.org/gtk4/stable/GtkCalendar.html

	GtkWidget *dialog, *infobar, *label, *calendar, *vbox = BOXV, *area;

	dialog = gtk_dialog_new_with_buttons (
		NULL,
		GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		NULL,
		NULL);

	gtk_widget_set_size_request (dialog, 350, -1);

	// info bars
	infobar = gtk_info_bar_new_with_buttons ("gtk-ok", GTK_RESPONSE_OK, NULL);
	gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_INFO);
	label = gtk_label_new (_("This is an info bar."));
	awf2_boxpack (GTK_BOX (infobar), label, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

	infobar = gtk_info_bar_new_with_buttons (_("Ok"), GTK_RESPONSE_OK, NULL);
	gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_QUESTION);
	label = gtk_label_new (_("This is a question bar."));
	awf2_boxpack (GTK_BOX (infobar), label, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

	infobar = gtk_info_bar_new ();
	gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_WARNING);
	label = gtk_label_new (_("This is a warning bar."));
	awf2_boxpack (GTK_BOX (infobar), label, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

	infobar = gtk_info_bar_new ();
	gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_ERROR);
	label = gtk_label_new (_("This is an error bar."));
	awf2_boxpack (GTK_BOX (infobar), label, FALSE, FALSE, 0, 0);
	awf2_boxpack (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

	// calendar
	calendar = gtk_calendar_new ();
	#if !GTK_CHECK_VERSION (3,90,0)
		gtk_calendar_set_display_options (GTK_CALENDAR (calendar), GTK_CALENDAR_SHOW_HEADING |
			GTK_CALENDAR_SHOW_DAY_NAMES | GTK_CALENDAR_SHOW_WEEK_NUMBERS);
	#endif
	awf2_boxpack (GTK_BOX (vbox), calendar, FALSE, FALSE, 0, 0);

	// dialog
	area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	awf2_boxpack (GTK_BOX (area), vbox, FALSE, FALSE, 5, 5);

	gtk_dialog_add_button (GTK_DIALOG (dialog), "gtk-cancel", 0);
	gtk_dialog_add_button (GTK_DIALOG (dialog), "gtk-ok", 0);

	#if GTK_CHECK_VERSION (3,90,0)
		gtk_widget_show (dialog);
	#else
		gtk_widget_show_all (dialog);
	#endif

	gtk_window_set_title (GTK_WINDOW (dialog), "GtkDialog");
	gtk_window_set_icon_name (GTK_WINDOW (dialog), g_strdup_printf ("awf-gtk%d", TRUE_GTK_MAJOR_VERSION));
	#if GTK_CHECK_VERSION (3,90,0)
		gtk_widget_show (dialog); // todo
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

// https://github.com/mate-desktop/mate-control-center/blob/master/capplets/common/capplet-util.c
// for awf2_gtk34_scrolltabs source function is capplet_dialog_page_scroll_event_cb
// of mate-appearance-properties from mate-control-center, GNU GPL 2+

#if GTK_CHECK_VERSION (3,90,0)

static void awf2_gtk40_closedialog (GtkDialog *dialog) {
	gtk_window_destroy (GTK_WINDOW (dialog));
}

static void awf2_gtk40_scrolltabs (GtkEventControllerScroll *event, double dx, double dy, GtkWidget *widget) {

	GtkNotebook *notebook;
	GtkWidget *child, *event_widget, *action_widget;

	//g_printf ("go\n");
	while (!GTK_IS_NOTEBOOK (widget))
		widget = gtk_widget_get_parent (widget);

	notebook = GTK_NOTEBOOK (widget);

	child = gtk_notebook_get_nth_page (notebook, gtk_notebook_get_current_page (notebook));
	if (child == NULL)
		return;

	// ignore scroll events from the content of the page
	event_widget = gtk_event_controller_get_widget (GTK_EVENT_CONTROLLER (event));
	if (event_widget == NULL || event_widget == child || gtk_widget_is_ancestor (event_widget, child))
		return;

	// and also from the action widgets
	action_widget = gtk_notebook_get_action_widget (notebook, GTK_PACK_START);
	if (event_widget == action_widget || (action_widget != NULL && gtk_widget_is_ancestor (event_widget, action_widget)))
		return;
	action_widget = gtk_notebook_get_action_widget (notebook, GTK_PACK_END);
	if (event_widget == action_widget || (action_widget != NULL && gtk_widget_is_ancestor (event_widget, action_widget)))
		return;

	if ((dy > 0) || (dx > 0))
		gtk_notebook_next_page (notebook);
	else if ((dy < 0) || (dx < 0))
		gtk_notebook_prev_page (notebook);
}

#elif GTK_CHECK_VERSION (3,4,0)

static void awf2_gtk34_scrolltabs (GtkWidget *widget, GdkEventScroll *event) {

	GtkNotebook *notebook = GTK_NOTEBOOK (widget);
	GtkWidget *child, *event_widget, *action_widget;

	child = gtk_notebook_get_nth_page (notebook, gtk_notebook_get_current_page (notebook));
	if (child == NULL)
		return;

	// ignore scroll events from the content of the page
	event_widget = gtk_get_event_widget ((GdkEvent*) event);
	if (event_widget == NULL || event_widget == child || gtk_widget_is_ancestor (event_widget, child))
		return;

	// and also from the action widgets
	action_widget = gtk_notebook_get_action_widget (notebook, GTK_PACK_START);
	if (event_widget == action_widget || (action_widget != NULL && gtk_widget_is_ancestor (event_widget, action_widget)))
		return;
	action_widget = gtk_notebook_get_action_widget (notebook, GTK_PACK_END);
	if (event_widget == action_widget || (action_widget != NULL && gtk_widget_is_ancestor (event_widget, action_widget)))
		return;

	switch (event->direction) {
		case GDK_SCROLL_RIGHT:
		case GDK_SCROLL_DOWN:
			gtk_notebook_next_page (notebook);
			break;
		case GDK_SCROLL_LEFT:
		case GDK_SCROLL_UP:
			gtk_notebook_prev_page (notebook);
			break;
		case GDK_SCROLL_SMOOTH:
			switch (gtk_notebook_get_tab_pos (notebook)) {
				case GTK_POS_LEFT:
				case GTK_POS_RIGHT:
					if (event->delta_y > 0)
						gtk_notebook_next_page (notebook);
					else if (event->delta_y < 0)
						gtk_notebook_prev_page (notebook);
					break;
				case GTK_POS_TOP:
				case GTK_POS_BOTTOM:
					if (event->delta_x > 0)
						gtk_notebook_next_page (notebook);
					else if (event->delta_x < 0)
						gtk_notebook_prev_page (notebook);
					break;
			}
			break;
	}
}

#endif

