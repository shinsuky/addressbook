/*
**
**	例題5：
**		住所録管理表・第6版
**
**		file name：	denden.h
**
**		header file
**		composed by Shinsuke Kobayashi
**					ver. 2.10.	2019.10.09.
**
*/
#ifndef INCLUDED_DENDEN    //  include guard
#define INCLUDED_DENDEN

//  グローバル変数、関数の場合に、定義部以外では extern に変更
#ifdef GLOBAL_VALUE_DEFINE
  #define GLOBAL
  #define GLOBAL_VAL(v) = (v)
#else
  #define GLOBAL extern
  #define GLOBAL_VAL(v)
#endif

/*-----------------------------*/
/*	ヘッダーファイルの読み込み */
/*-----------------------------*/

#include	<stdio.h>
#include	<ctype.h>
#include	<ncurses.h>
#include 	<locale.h>
#include	<string.h>
#include  <stdlib.h>

/*---------------------*/
/*	システム定数の宣言 */
/*---------------------*/

#define		TRUE				1
#define		FALSE				0

#define		BUFFER_LEN			80		/* 入力バッファの文字数 */

#define		RECORD_MAX			20		/* 最大データ件数 */
#define		NAME_LEN			40		/* 名前の文字数 */
#define		ADDR_LEN			60		/* 住所の文字数 */
#define		TEL_LEN				15		/* 電話番号の文字数 */
#define		ZIP_LEN				9		/* 郵便番号の文字数 */

#define		TITLE_LINE			1		/* タイトル行の位置 */
#define		DATA_LINE			3		/* データ表示行の先頭位置 */
#define		DISP_REC_MAX		5		/* 1ページに書くデータ件数 */
#define		MSG_LINE			18		/* メッセージ行の先頭位置 */

#define		UP					1		/* 前ページ */
#define		DOWN				0		/* 次ページ */

#define		FNAME_MAX			128		/* ファイル名の最大長さ */

/* コマンドの定義 */

#define		CMD_MAX				10		/* 第4版 */

#define		APPEND				'A'		/* データの追加 */
#define		EDIT				'E'		/* データの編集 */
#define		DELETE				'X'		/* データの削除 */
#define		BEFORE				'B'		/* 前のデータへ */
#define		NEXT				'N'		/* 次のデータへ */
#define		UP_PAGE				'U'		/* 前ページへ */
#define		DOWN_PAGE			'D'		/* 次ページへ */
#define		LOAD				'L'		/* データのロード */
#define		SAVE				'S'		/* データのセーブ */
#define		QUIT				'Q'		/* 終了 */

GLOBAL char	cmd_list[];  // マクロ内でマクロはかけないので仮変数としておく


/*-----------------------*/
/*	グローバル変数の宣言 */
/*-----------------------*/

GLOBAL int		cursor GLOBAL_VAL(0);						/* 注目行 */
GLOBAL int		rec_qty GLOBAL_VAL(0);					/* データの数 */

typedef	struct {
	char	j_name[NAME_LEN];	/* 名前（漢字） */
	char	k_name[NAME_LEN];	/* 名前（フリガナ） */
	char	address[ADDR_LEN];	/* 住所 */
	char	tel_no[TEL_LEN];	/* 電話番号 */
	char	zip[ZIP_LEN];		/* 郵便番号 */
}	CARD;

GLOBAL CARD	note[RECORD_MAX];

GLOBAL char	data_file[FNAME_MAX];			/* データファイル名 */

/*---------------------*/
/*	使用する関数の宣言 */
/*---------------------*/

/* コマンド処理用部品 */
char	input_cmd( void );
void	exec_cmd( char cmd );

/* 住所録管理コマンド */
void	data_append( void );
void	data_edit( void );
void	data_delete( void );
void	paging( int direction );
void	cur_move( int direction );
void	data_load( void );
void	data_save( void );
void	pack_data( int *rec_no, int *tail );

void  init_buff();

/* 画面表示用部品 */
void	init_disp( void );
void	show_one_page( void );
void	show_record( int num, int pos );
void	del_lines( int start, int end );
void	disp_err( char *msg );

//  その他、定数定義
#include "display.h"

#endif    //  include guard
