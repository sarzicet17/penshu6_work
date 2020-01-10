#include "intern_client.h"
#include "teacher_isentry_func.h"

int teacherisEntryWindowShowFlag = 0;

G_MODULE export void cb_teacher_isentry_winopen(GtkMenuItem *menuItem,gpointer data){
    GtkBuilder *builder;
    MainHandleData *hData;

    TeacherISEntryWindowHandleData *TeIsEntryhData;

    if(teacherisEntryWindowShowFlag == 0){
        hData = (MainHandleData *)data;

        TeIsEntryhData  = (TeacherISEntryWindowHandleData *)malloc(sizeof(TeacherISEntryWindowHandleData));

        builder = gtk_builder_new();
        gtk_builder_add_from_file(builder,"teacher_isentry.glade");


    }

}