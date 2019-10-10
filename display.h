/*
**
**	例題5：
**		住所録管理表・第6版
**
**		file name：	display.h
**
**		画面表示に関する定数宣言
**		composed by Shinsuke Kobayashi
**					ver. 2.10.	2019.10.09.
**
*/
#ifndef INCLUDED_DISPLAY
#define INCLUDED_DISPLAY

/*---------------------*/
/*	コマンド処理用部品 */
/*---------------------*/

#define		CMD_MSG_LINE	MSG_LINE
#define		CMD_ERR_LINE	MSG_LINE+1
#define		CMD_LINE		MSG_LINE+2

#define		CMD_MSG			"コマンド(A:追加 E:編集 X:削除 B:前 N:後 U:次頁 D:前頁 L:ロード S:セーブ Q:終了)"
#define		CMD_ERR_MSG		"不適当なコマンドでした"
#define		CMD_PROMPT		" >>"

// 住所録管理コマンド群  の定数宣言

#define		APPEND_LINE		MSG_LINE
#define		APPEND_END_LINE	MSG_LINE+4

#define		EDIT_MSG	"編集する項目を選んでください  N:名前 F:フリガナ A:住所 Z:郵便番号 T:電話 Q:終了"

#define		NAME		'N'
#define		KANA_NAME	'F'
#define		ADDR		'A'
#define		ZIP_NO		'Z'
#define		TELPHONE	'T'

#define		FBUF_MAX		200

#define		ERR_APPEND		"データが一杯で，もう追加できません．"
#define		ERR_FILE		"ファイルがオープンできません．"

#define		WAIT_MSG		"確認したら，好きなキーを押して下さい"


/*-----------------*/
/*	画面表示用部品 */
/*-----------------*/

#define		LINE		"----------------------------------------------------------------"

#define		TITLE_POS	25

#define		DATA_START	DATA_LINE		/* データ領域の開始行 */
#define		DATA_END	MSG_LINE-1		/* データ領域の最終行 */
#define		DATA_STEP	3				/* データの間隔 */

#endif  //  INCLUDED_DISPLAY
