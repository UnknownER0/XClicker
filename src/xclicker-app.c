#include <gtk/gtk.h>

#include "xclicker-app.h"
#include "mainwin.h"

struct _XClickerApp
{
	GtkApplication parent;
};

G_DEFINE_TYPE(XClickerApp, xclicker_app, GTK_TYPE_APPLICATION);

static void xclicker_app_init(XClickerApp *app)
{
}

static void xclicker_app_activate(GApplication *app)
{
	MainAppWindow *win;

	win = main_app_window_new(XCLICKER_APP(app));
	gtk_window_present(GTK_WINDOW(win));
}

static void xclicker_app_open(GApplication *app, GFile **files, int n_files, const char *hint)
{
	GList *windows;
	MainAppWindow *win;
	int i;

	windows = gtk_application_get_windows(GTK_APPLICATION(app));
	if (windows)
		win = XCLICKER_APP_WINDOW(windows->data);
	else
		win = main_app_window_new(XCLICKER_APP(app));

	for (i = 0; i < n_files; i++)
		main_app_window_open(win, files[i]);

	gtk_window_present(GTK_WINDOW(win));
}

static void xclicker_app_class_init(XClickerAppClass *class)
{
	G_APPLICATION_CLASS(class)->activate = xclicker_app_activate;
	G_APPLICATION_CLASS(class)->open = xclicker_app_open;
}

XClickerApp *xclicker_app_new(void)
{
	return g_object_new(XCLICKER_APP_TYPE, "application-id", "org.gtk.xclicker", "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
