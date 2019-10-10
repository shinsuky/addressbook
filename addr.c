/*
**
**	例題：
**		住所録管理表・第6版
**
**		file name：	addr.c
**
**		アドレスデータ編集用関数
**		composed by Shinsuke Kobayashi
**					ver. 2.10.	2019.10.09.
**
*/
#include "denden.h"

/*-----------------------*/
/*	住所録管理コマンド群 */
/*-----------------------*/

/* data_append */
/*----------------------------------------------------*/
/*
	書式：	void	data_append( void )

	機能：	住所録データの末尾に，新しいデータを追加する．

	返値：	なし
*/

void	data_append( void )
{
	move( APPEND_LINE, 1 );

	/* データが一杯かどうか調べる */
	if( rec_qty >= RECORD_MAX ){
		disp_err( ERR_APPEND );
		return;
	}

	/* データを入力する */
	printw( "名前		>>" );
	getnstr( note[rec_qty].j_name, NAME_LEN );
	printw( "フリガナ	>>" );
	getnstr( note[rec_qty].k_name, NAME_LEN );
	printw( "住所		>>" );
	getnstr( note[rec_qty].address, ADDR_LEN );
	printw( "郵便番号	>>" );
	getnstr( note[rec_qty].zip, ZIP_LEN );
	printw( "電話番号	>>" );
	getnstr( note[rec_qty].tel_no, TEL_LEN );

	cursor = ++rec_qty;

	/* 後始末 */
	del_lines( APPEND_LINE, APPEND_END_LINE );
}


/* data_edit */
/*----------------------------------------------------*/
/*
	書式：	void	data_edit( void )

	機能：	注目行のあるレコードに対して，編集作業を行う．
			まず，レコードのどの項目を修正するか入力する．
			入力された項目について，入力プロンプトを出力し，全部入力しなおす．
			もとのデータの一部分のみ，修正，変更，削除などは，サポートしない．
			編集項目の選択のところで，終了を選択すると，画面上の注目行のみ，再表
			示し，編集を終了する．

	返値：	なし
*/

void	data_edit( void )
{
	int	disp_pos;		/* 注目行の表示位置 */
	int	c;
	char	buffer[BUFFER_LEN];

	if( cursor == 0 )	/* データがない時の処理 */
		return;

	for( ; ; ){
		move( MSG_LINE, 1 );	/* 編集項目の選択 */
		printw( EDIT_MSG );
		move( MSG_LINE+2, 1 );
		printw( ">>" );
		getstr(buffer);
		if(( c = toupper( buffer[0] )) == QUIT )
			break;

		/* 各項目の編集 */
		switch( c ){
		case	NAME:
			printw("\n名前	>>");
			getnstr( note[cursor-1].j_name, NAME_LEN );
			break;
		case	KANA_NAME:
			printw("\nフリガナ	>>");
			getnstr( note[cursor-1].k_name, NAME_LEN );
			break;
		case	ADDR:
			printw("\n住所	>>");
			getnstr( note[cursor-1].address, ADDR_LEN );
			break;
		case	ZIP_NO:
			printw("\n郵便番号	>>");
			getnstr( note[cursor-1].zip, ZIP_LEN );
			break;
		case	TELPHONE:
			printw("\n電話番号	>>");
			getnstr( note[cursor-1].tel_no, TEL_LEN );
			break;
		default:
			break;
		}
		/* 注目行の再表示 */
		disp_pos = DATA_LINE + (( cursor-1 )% DISP_REC_MAX)*3;
		show_record( cursor, disp_pos );
		del_lines( MSG_LINE+2, MSG_LINE+4 );
	}
	del_lines( MSG_LINE, MSG_LINE+4 );
}


/* data_delete */
/*----------------------------------------------------*/
/*
	書式：	void	data_delete( void )

	機能：	注目行のデータを削除し，空いたところを詰め合わせる．

	返値：	なし
*/

void data_delete()
{
	CARD	*tmp;

	/* データ無しのチェック */
	if( cursor <= 0 )
		return;

	/* 注目行の削除 */
	pack_data( &cursor, &rec_qty );	/* まず，データの詰め合わせ */
	tmp = &note[rec_qty];
	tmp->k_name[0] = '\0';	/* 末尾データの削除 */
	tmp->j_name[0] = '\0';
	tmp->zip[0] = '\0';
	tmp->address[0] = '\0';
	tmp->tel_no[0] = '\0';
}

/* pack_data */
/*----------------------------------------------------*/
/*
	書式：	void	pack_data( int *rec_no, int *tail )

	機能：	指定されたレコード番号より後ろのデータを，前に詰め合わせる．指定した
			レコード番号のデータは，失われる．詰め合わせる最後のレコード番号も
			引数で指定する．

	返値：	なし
*/

void	pack_data(
	int		*rec_no,	/* 詰め合わせる最初のレコード番号 */
	int		*tail		/* 詰め合わせる最後のレコード番号 */
)
{
	int		i;

	if( *rec_no == *tail ){	/* 一番最後の要素を消す時 */
		*rec_no = *rec_no - 1;
		*tail = *tail - 1;
		return;
	}
	for( i = *rec_no - 1; i < *tail; i++ ){
		strcpy( note[i].j_name, note[i+1].j_name );
		strcpy( note[i].k_name, note[i+1].k_name );
		strcpy( note[i].tel_no, note[i+1].tel_no );
		strcpy( note[i].zip, note[i+1].zip );
		strcpy( note[i].address, note[i+1].address );
	}
	*tail = *tail - 1;
}
