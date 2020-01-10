#include "intern_client.h"
#include "com_isreg_func.h"


extern int isRegWindowShowFlag = 0; //インターン登録画面表示フラグ

G_MODULE_EXPORT void cb_show_com_isreg(GtkMenuItem *menuItem,gpointer data){
    GtkBuilder *builder;
    MainHandleData *hData;

    GtkTreeSelection *isreg_selection; //Selectionオブジェクト(自社インターン情報取得画面用)
    GtkTreeIter isreg_iter;
    GtkTreeModel *isreg_model;
    gboolean isreg_success;
    gboolean isfind_success;

    ComISRegHandleData *isreghData; //ウィジェット格納構造体
    ComISRegInfo isregInfo; //ツリービューへの格納構造体

    char buffer[BUFSIZE];

    //送信コマンド格納バッファ

    char send_command[BUFSIZE];
    char send_param1[BUFSIZE];
    char send_param2[BUFSIZE];
    char send_param3[BUFSIZE];
    

    // hData = (MainHandleData *)data;
    // isreghData = (ComISRegHandleData *)malloc(sizeof(ComISRegHandleData));

    // //gladeファイルの読み込み
    // builder = gtk_builder_new();
    // gtk_builder_add_from_file(builder,"com_isreg.glade",NULL);

    
    // isreghData->comRegWindow = GTK_WIDGET(gtk_builder_get_object(builder,"com_regis_window"));
    // isreghData->IsfindList = GTK_TREE_VIEW(gtk_builder_get_object(builder,"isinfo_res_list"));
    // hData->isreghData = isreghData;


    //インターンシップ情報登録画面の機能

    


    //インターンシップ情報登録画面機能（ここまで）


    //自社インターンシップ情報取得画面の機能
    isreg_selection = gtk_tree_view_get_selection(hData->treeView);
    if(!selection) return;
    
    model = GTK_TREE_MODEL(gtk_tree_view_get_model(hData->treeView));
    isfind_success = gtk_tree_selection_get_selected(selection,NULL,isreg_iter);

    if(isfind_succcess){
        gtk_tree_model_get()
    }

    //自社インターンシップ情報取得画面の機能(ここまで)


    gtk_builder_connect_signals(builder,hData);

    gtk_widget_show_all(isreghData->comRegWindow);
}