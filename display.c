/*
**
**	例題5：
**		住所録管理表・第6版
**
**		file name：	display.c
**
**		画面表示用関数
**		composed by Shinsuke Kobayashi
**					ver. 2.10.	2019.10.09.
**
*/
#include "denden.h"

/* init_disp */
/*----------------------------------------------------*/
/*
	書式：	void	init_disp( void )

	機能：	画面を消去し，第1行目にタイトルを書いておく
*/

void init_disp( void )
{
	setlocale(LC_ALL,"");			//  for UTF-8 setting
	initscr();								//  画面初期化
	clear();
	move( TITLE_LINE, TITLE_POS );
	printw( "住所管理表    第四版\n%s", LINE);
}


/* show_one_page */
/*----------------------------------------------------*/
/*
	書式：	void	show_one_page( void )

	機能：	1ページ分の住所録データを一画面に書く．
			1ページには，5件分のデータを書く．

*/

void show_one_page( void )
{
	int	start, end,				/* 表示開始，終了レコード番号 */
		line_pos = DATA_START;	/* 表示位置 */
	int	i;

	/* 前処理 */
	for( i = DATA_START ; i<= DATA_END ; i++ ){
		move( i, 0 );
		clrtoeol();
	}
	start = ((( cursor -1 ) / 5)*5 + 1);
	end = start + DISP_REC_MAX -1;
	if( end > rec_qty )
		end = rec_qty;

	/* 5件分のデータを書く */
	for( i = start ; i <= end ; i++ ){
		show_record( i, line_pos );
		line_pos += DATA_STEP;
	}
}


/* show_record */
/*----------------------------------------------------*/

void	show_record(
	int	num,	/* 表示したいレコード表号 */
	int	pos		/* 表示したい行位置 */
)
{
	int idx;

	move( pos, 1 );

	/* 注目マークをつける */
	if( num == cursor )
		printw( "*" );
	else
		printw( " " );

	idx = num-1;
	printw("%3d %-20s TEL %-15s \n" ,num, note[idx].j_name, note[idx].tel_no );
	printw("     %-20s 〒%-8s %s\n", note[idx].k_name, note[idx].zip, note[idx].address );
	printw( "%s", LINE );
}


/* del_lines */
/*----------------------------------------------------*/
/*
	書式：	void	del_lines( int start, int end )

	機能：	引数,start,endで指定された行を消す

	返値：	なし

*/

void	del_lines( start, end )
int		start, end;
{
	int		i;

	move( start, 1 );
	for( i = start ; i <= end; i++ ){
		clrtoeol();
		addch( '\n' );
	}
}


/* disp_err */
/*----------------------------------------------------*/
/*
	書式：	void	disp_err( char *msg )

	機能：	引数で渡されたエラーメッセージを表示し，なにかキーが押されるまで待つ．
			キーが押されたら，画面のメッセージ領域をクリアし，戻る．

	返値：	なし
*/

void	disp_err(
	char	*msg /* エラーメッセージ */
)
{
	char	buffer[BUFFER_LEN];

	printw( msg );
	printw( WAIT_MSG );
	getstr( buffer );
	del_lines( APPEND_LINE, APPEND_END_LINE );
}
