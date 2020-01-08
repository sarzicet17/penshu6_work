#include "intern_client.h"
#include "com_isreg_func.h"

int isRegWindowShowFlag = 0;

G_MODULE_EXPORT void cb_com_isreg_winopen(GtkMenuItem *menuItem,gpointer data){
    GtkBuilder *builder;
    MainHandleData *hData;

    ComISRegHandledata *isreghData;

    if(isRegWindowShowFlag == 0){
    /* 引数(data)をメイン画面主要Widget保持用構造体型にキャスト */
    hData = (MainHandleData *)data;

    //企業インターン登録画面への格納構造体の領域確保
    isreghData = (ComISRegHandleData *)malloc(sizeof(ComISRegHandleData));

    //gladeファイルのロード
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder,"com_isreg.glade");

    //おもなウィジェットを保持
    isreghData->comRegWindow = GTK_WIDGET(gtk_builder_get_object(builder,"com_regis_window"));
    isreghData->IsfindList = GTK_TREE_VIEW(gtk_builder_get_object(builder,"isinfo_res_list"));
    hData->isreghData = isreghData;

    //インターンシップ情報登録画面へ飛ぶ
    gtk_builder_connect_signals(builder,hData);
    gtk_widget_show_all(isreghData->)


    }

}