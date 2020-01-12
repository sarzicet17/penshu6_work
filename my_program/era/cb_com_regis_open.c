#include "intern_client.h"
#include "com_isreg_func.h"
#include <gtk/gtk.h>
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

    //おもなウィジェットを保持(ウィンドウ)
    isreghData->comRegWindow = GTK_WIDGET(gtk_builder_get_object(builder,"com_regis_window"));

    //おもなウィジェットを保持(登録画面:コンボボックス,ラベル)
    isreghData->yearCombo = GTK_COMBO_BOX(gtk_builder_get_object(builder,"year_combo"));
    isreghData->yearLabel = GTK_LABEL(gtk_builder_get_object(builder,"year_label"));

    isreghData->monthCombo = GTK_COMBO_BOX(gtk_builder_get_object(builder,"month_combo"));
    isreghData->monthLabel = GTK_LABEL(gtk_builder_get_object(builder,"month_label"));

    isreghData->dayCombo = GTK_COMBO_BOX(gtk_builder_get_object(builder,"day_combo"));
    isreghData->dayLabel = GTK_LABEL(gtk_builder_get_object(builder,"day_label"));
    // isreghData->IsThemeEntry = GTK_


    // isreghData->daycountCombo = GTK_COMBO_BOX(gtk_builder_get_object(builder,"daycount_combo"));
    // isreghData->daycountLabel = GTK_LABEL(gtk_builder_get_object(builder,"daycount_label"));

    //おもなウィジェットを保持(自社IS参照画面:ツリービュー)
    isreghData->isResList = GTK_TREE_VIEW(gtk_builder_get_object(builder,"isinfo_res_list"));

    //構造体セット
    hData->isreghData = isreghData;

    //インターンシップ情報登録画面へ飛ぶ
    gtk_builder_connect_signals(builder,hData);
    gtk_widget_show_all(isreghData->comRegWindow);

    isRegWindowShowFlag = 1;

    }
}