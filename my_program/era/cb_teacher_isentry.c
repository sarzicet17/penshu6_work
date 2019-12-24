#include "intern_client.h"
#include "teacher_isentry_func.h"
G_MODULE_EXPORT void cb_show_teacher_isentry(GtkMenuItem *menuItem,gpointer data){
    GtkBuilder  *builder;
    MainHandleData *hData;
    TeacherISEntryWindowHandleData *isentryhData;

    hData = (MainHandleData *)data;
    isentryhData = (TeacherISEntryWindowHandleData *)malloc(sizeof(TeacherISEntryWindowHandleData));

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder,"teacher_isentry.glade",NULL);

    //主要なウィジェットセット

    isentryhData->entryWindow = GTK_WIDGET(gtk_builder_get_object(builder,"teacher_isentry_window"));

    hData->isentryhData = isentryhData;

    gtk_builder_connect_signals(builder,hData);

    gtk_widget_show_all(isentryhData->entryWindow);
}