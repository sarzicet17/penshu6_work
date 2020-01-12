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


    //送受信バッファ
    char sendBuf[BUFSIZE];
    char recvBuf[BUFSIZE_MAX];
    char *records[RECORD_MAX];
    char response[BUFSIZE];
    int recordCount;
    int sendLen,recvLen;

    //送信コマンド格納バッファ

    char send_command[BUFSIZE];
    char send_param1[BUFSIZE];
    char send_param2[BUFSIZE];
    char send_param3[BUFSIZE];
    

    //受信データ格納バッファ
    char recv_param1[BUFSIZE];
    char recv_param2[BUFSIZE];
    char recv_param3[BUFSIZE];
    char recv_param4[BUFSIZE];
    char recv_param5[BUFSIZE];
    char recv_param6[BUFSIZE];
    char recv_param7[BUFSIZE];
    //引数をメイン画面主要widget構造体型にキャスト
    hData = (MainHandleData *)data;
    ComISRegHandleData = hData->ComISRegHandleData;

    //model = GTK_LIST_STORE(gtk_tree_view_get_model(isreghData->isInfoResList));

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
    model = GTK_LIST_STORE(gtk_tree_view_get_model(isreghData->isInfoResList));

    if(g_soc > 0){
        sendLen = sprintf(sendBuf,"%s %s",ISLIST_C,ENTER);
        send(g_soc,sendbuf,sendLen,0);
        recvLen = recv_data(g_soc,recvBuf,BUFSIZE_MAX);
        //レコードに分割
        recordCount = record_division(recvBuf,records);

        memset(response,0,BUFSIZE);
        memset(recv_param1,0,BUFSIZE);
        memset(recv_param2,0,BUFSIZE);
        memset(recv_param3,0,BUFSIZE);
        memset(recv_param4,0,BUFSIZE);
        memset(recv_param5,0,BUFSIZE);
        memset(recv_param6,0,BUFSIZE);
        memset(recv_param7,0,BUFSIZE);

        n = sscanf(records[0],"%s %s",response,param1);

        //エラーチェック
        if(strcmp(responce,OK_STAT) != 0){
            ComRegIsErrorMessageShow;
        }

    }

    //自社インターンシップ情報取得画面の機能(ここまで)


    gtk_builder_connect_signals(builder,hData);

    gtk_widget_show_all(isreghData->comRegWindow);
}