/**
 * cb_login_open.c
 **/

#include "intern_client.h"
#include "login.h"

/**
 * コールバック関数
 * cb_login_win_open
 **/
G_MODULE_EXPORT void cb_login_win_open(GtkMenuItem *menuItem, gpointer data){
  GtkBuilder      *builder;
  MainHandleData  *hData;      //メイン画面の主要Widget保持用
  LoginHandleData *loginHData; //ログイン画面の主要Widget保持用
  const gchar *loginStr;

  
  /* 引数(data)をメイン画面主要Widget保持用構造体型にキャスト */
  hData = (MainHandleData *)data;

  /* ログイン画面の主要Widget保持用構造体を作成 */
  loginHData = (LoginHandleData *)malloc(sizeof(LoginHandleData));

  /* login.gladeを読み込む */
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "login.glade", NULL);
  /* 主要Widgetを保持 */
  loginHData->loginWindow     = GTK_WIDGET( gtk_builder_get_object(builder, "loginWindow") );
  loginHData->loginLabel      = GTK_LABEL( gtk_builder_get_object(builder, "loginLabel") );
  loginHData->idEntry         = GTK_ENTRY( gtk_builder_get_object(builder, "idEntry") );
  loginHData->passwordEntry   = GTK_ENTRY( gtk_builder_get_object(builder, "passwordEntry") );
  loginHData->errorLabel      = GTK_LABEL( gtk_builder_get_object(builder, "errorLabel") );

  /* メイン画面の主要Widget保持用のメンバーとしてログイン画面主要Widget保持用構造体をセット */
  hData->loginHData = loginHData;

  /* menuItemのラベルを取得してログインラベルにセット */
  loginStr = gtk_menu_item_get_label(menuItem);
  gtk_label_set_text(loginHData->loginLabel, loginStr);
  
  /* シグナル、シグナルハンドラ、ユーザデータ登録 */
  gtk_builder_connect_signals(builder, hData);
  /* ログイン画面表示 */
  gtk_widget_show_all(loginHData->loginWindow);

}//END cb_login_win_open()
