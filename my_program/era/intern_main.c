/**
 * intern_main.c
 **/

#include "intern_client.h"

int g_soc = -1;       //クライアントのソケットディスクリプタ
int g_permissionId = 0; //権限ID 教員:1 企業:2 学生:3

/** 
 * コールバック関数 
 * cb_intern_quit
 **/
G_MODULE_EXPORT void cb_intern_quit(GtkButton *button, gpointer data){
  if(g_soc > 0){
    /* サーバとの接続を切断 */
    close(g_soc);
  }
  gtk_main_quit();
}

int main(int argc, char *argv[]){
  GtkBuilder *builder;        //GtkBuilderオブジェクト
  MainHandleData *hData;      //メイン画面の主要Widget保持用
  char       labelBuf[BUFSIZE];
  int        port;
  
  //  if(argc != 3){
  //  printf("Usage: %s server-ipaddr port\n", argv[0]);
  //  exit(1);
  //}
 
  //port = atoi(argv[2]);

  /* サーバに接続要求 */
  //if((g_soc = setup_connect(argv[1], port)) < 0){
  //  exit(1);
  //}

  /* GTK+の初期化  */
  gtk_init(&argc, &argv);

  /* メイン画面の主要Widget保持用構造体を作成 */
  hData = (MainHandleData *)malloc(sizeof(MainHandleData));

  /* GtkBuilderオブジェクトの生成 */ 
  builder = gtk_builder_new();
  /* Gladeで作成したファイルからUIを読み込む */
  gtk_builder_add_from_file(builder, "intern_main.glade", NULL);

  /* 主要Widgetを保持 */
  hData->mainWindow           = GTK_WIDGET( gtk_builder_get_object(builder, "mainWindow") );
  hData->userIdLabel          = GTK_LABEL( gtk_builder_get_object(builder, "userIdLabel") );
  hData->userNameLabel        = GTK_LABEL( gtk_builder_get_object(builder, "userNameLabel") );
  hData->serverInfoLabel      = GTK_LABEL( gtk_builder_get_object(builder, "serverInfoLabel") );
  hData->studentRegisterButton  = GTK_BUTTON( gtk_builder_get_object(builder, "studentRegisterButton") );
  hData->companyRegisterButton  = GTK_BUTTON( gtk_builder_get_object(builder, "companyRegisterButton") );
  hData->internEntryButton      = GTK_BUTTON( gtk_builder_get_object(builder, "internEntryButton") );
  hData->internStudentDisplayButton = GTK_BUTTON( gtk_builder_get_object(builder, "internStudentDisplayButton") );
  hData->gradeDisplayButton     = GTK_BUTTON( gtk_builder_get_object(builder, "gradeDisplayButton") );
  hData->internRegisterButton   = GTK_BUTTON( gtk_builder_get_object(builder, "internRegisterButton") );
  hData->entryStudentDisplayButton = GTK_BUTTON( gtk_builder_get_object(builder, "entryStudentDisplayButton") );
  hData->particicationDecideButton = GTK_BUTTON( gtk_builder_get_object(builder, "particicationDecideButton") );
  hData->gradeInputButton       = GTK_BUTTON( gtk_builder_get_object(builder, "gradeInputButton") );
  hData->passwordChangeButton   = GTK_BUTTON( gtk_builder_get_object(builder, "passwordChangeButton") );
  hData->internDisplayButton    = GTK_BUTTON( gtk_builder_get_object(builder, "internDisplayButton") );
  hData->selfEvaluationButton   = GTK_BUTTON( gtk_builder_get_object(builder, "selfEvaluationButton") );
  hData->adviceDisplayButton    = GTK_BUTTON( gtk_builder_get_object(builder, "adviceDisplayButton") );
  hData->stuPasswordChangeButton= GTK_BUTTON( gtk_builder_get_object(builder, "stuPasswordChangeButton") );

  /* コネクション先のサーバ情報を表示 */
  //sprintf(labelBuf, "Server: %s Port: %d", argv[1], port);
  //gtk_label_set_text(hData->connectLabel, labelBuf);

  /* ログインなしを表示（UserID UserName) */

 
  /* 各機能ボタンを無効化 */
 
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->studentRegisterButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->companyRegisterButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->internEntryButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->internStudentDisplayButton), FALSE );
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->gradeDisplayButton ), FALSE );
    
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->internRegisterButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->entryStudentDisplayButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->particicationDecideButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->gradeInputButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->passwordChangeButton), FALSE );

  //gtk_widget_set_sensitive( GTK_WIDGET(hData->internDisplayButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->selfEvaluationButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->adviceDisplayButton), FALSE );  
  //gtk_widget_set_sensitive( GTK_WIDGET(hData->stuPasswordChangeButton), FALSE );  


  /* UIで設定されているシグナルに対するコールバック関数を登録 */
  gtk_builder_connect_signals(builder, hData);

  /* メイン・ウィンドウ上のすべてウィジェットを表示 */
  gtk_widget_show_all(hData->mainWindow);

  /* メインループ */
  gtk_main();

  return 0;
}


