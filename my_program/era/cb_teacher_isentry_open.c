#include "intern_client.h"
#include "teacher_isentry_func.h"

int teacherisEntryWindowShowFlag = 0;

G_MODULE_EXPORT void cb_show_teacher_isentry(GtkButton *button, gpointer data){
    GtkBuilder *builder;
    MainHandleData *hData;
    
    TeacherISEntryWindowHandleData *isentryhData;

    if(teacherisEntryWindowShowFlag == 0){
        hData = (MainHandleData *)data;

        isentryhData = (TeacherISEntryWindowHandleData *)malloc(sizeof(TeacherISEntryWindowHandleData));
        builder = gtk_builder_new();
        gtk_builder_add_from_file(builder,"teacher_isentry.glade",NULL);

        //おもなウィジェットの保持(ウィンドウ)
        isentryhData->entryWindow = GTK_WIDGET(gtk_builder_get_object(builder,"teacher_isentry_window"));
        //エントリー登録
        isentryhData->stuIdEntry = GTK_ENTRY(gtk_builder_get_object(builder,"stu_id_entry_input"));
        isentryhData->isIdEntry = GTK_ENTRY(gtk_builder_get_object(builder,"intern_id_entry_input"));
        isentryhData->regStatLabel = GTK_LABEL(gtk_builder_get_object(builder,"reg_stat_label"));
        //年度別検索画面
        isentryhData->yearSearchTree = GTK_TREE_VIEW(gtk_builder_get_object(builder,"yearsearch_tree"));
        isentryhData->yearCombo = GTK_COMBO_BOX(gtk_builder_get_object(builder,"year_combo"));

        hData->isentryhData = isentryhData;

        gtk_builder_connect_signals(builder,hData);
        gtk_widget_show_all(isentryhData->entryWindow);

        teacherisEntryWindowShowFlag = 1;
    } 
}