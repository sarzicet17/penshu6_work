#include "intern_client.h"
#include "com_isreg_func.h"

int isRegWindowShowFlag = 0;

G_MODULE_EXPORT void cb_com_isreg_winopen(GtkMenuItem *menuItem,gpointer data){
    GtkBuilder *builder;
    MainHandleData *hData;

    ComISRegHandleData *isreghData;

    if(isRegWindowShowFlag == 0){
    /* 引数(data)をメイン画面主要Widget保持用構造体型にキャスト */
    hData = (MainHandleData *)data;

    //企業インターン登録画面への格納構造体の領域確保
    isreghData = (ComISRegHandleData *)malloc(sizeof(ComISRegHandleData));

    //gladeファイルのロード
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder,"com_isreg.glade",NULL);

    //おもなウィジェットを保持(ウィンドウ)
    isreghData->comRegWindow = GTK_WIDGET(gtk_builder_get_object(builder,"com_regis_window"));

    //おもなウィジェットを保持(登録画面:エントリ,ラベル)
    isreghData->IsThemeEntry = GTK_ENTRY(gtk_builder_get_object(builder,"istheme_entry"));
    isreghData->yearEntry = GTK_ENTRY(gtk_builder_get_object(builder,"year_entry"));
    isreghData->monthEntry = GTK_ENTRY(gtk_builder_get_object(builder,"month_entry"));
    isreghData->dayEntry = GTK_ENTRY(gtk_builder_get_object(builder,"date_entry"));
    isreghData->daycountEntry = GTK_ENTRY(gtk_builder_get_object(builder,"daycount_entry"));
    isreghData->comisRegStatLabel = GTK_LABEL(gtk_builder_get_object(builder,"com_isreg_stat_label"));


    //おもなウィジェットを保持(自社IS参照画面:ツリービュー)
    isreghData->isResList = GTK_TREE_VIEW(gtk_builder_get_object(builder,"isinfo_res_list"));
    isreghData->isListStatusLabel = GTK_LABEL(gtk_builder_get_object(builder,"islist_status_label"));
    //構造体セット
    hData->isreghData = isreghData;

    //インターンシップ情報登録画面へ飛ぶ
    gtk_builder_connect_signals(builder,hData);
    gtk_widget_show_all(isreghData->comRegWindow);

    isRegWindowShowFlag = 1;

    }
}