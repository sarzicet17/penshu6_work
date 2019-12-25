#include "intern_client.h"
#include "com_isreg_func.h"

G_MODULE_EXPORT void cb_show_com_isreg(GtkMenuItem *menuItem,gpointer data){
    GtkBuilder *builder;
    MainHandleData *hData;
    
    ComISRegHandleData *isreghData;
    ComISRegInfo isregInfo;


    hData = (MainHandleData *)data;
    isreghData = (ComISRegHandleData *)malloc(sizeof(ComISRegHandleData));

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder,"com_isreg.glade",NULL);


    isreghData->comRegWindow = GTK_WIDGET(gtk_builder_get_object(builder,"com_regis_window"));
    isreghData->IsfindList = GTK_TREE_VIEW(gtk_builder_get_object(builder,"isinfo_res_list"));
    hData->isreghData = isreghData;

    


    gtk_builder_connect_signals(builder,hData);

    gtk_widget_show_all(isreghData->comRegWindow);
}