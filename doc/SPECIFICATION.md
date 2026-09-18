# lambda specification
## CLI仕様
- コマンド
```
$ lambda expr
```
<!-- ```
$ lambda [filename]
``` -->
<!-- - オプション
	- **ヘルプ(`help`)**: ヘルプを標準出力に表示する

- 終了ステータス
	- **正常終了**: 0
	- **システムエラー**: 1
	- **構文エラー**: 2
	- **評価時エラー**: 3 -->
<!-- 
## ファイル実行モード
第1引数にファイルパスが渡された場合、指定されたファイルを読み込んで実行する。

## REPLモード
コマンドライン引数なし（またはファイル名未指定）で起動した場合、対話型実行環境（REPL）を開始する。
### メタコマンド
ドット（.）で始まるコマンドは評価式ではなく、REPLの制御コマンドとして処理する。
- **`.exit`, `.quit`**: REPLセッションを終了する
- **`.env`**: 現在の環境にバインドされている変数・定義の一覧を表示する。
- **`.help`**: 利用可能なメタコマンド一覧を表示する。 -->

## 言語仕様
### 表記規則
以下の表記規則を使用する
- 正規表現
- **パターン1 | パターン2**: 選択
- **{ パターン }**: 0回以上の繰り返し
- **( パターン )**: グループ化
- **パターン1 - パターン2**: パターン1からパターン2を除外したもの

### 字句構文
```
TOKENS		=	{ LEXEME | WS }
LEXEME		=	LAMBDA | DOT | LPAREN | RPAREN | IDENTIFIER | EOS
WS			=	" " | "\t" | "\n"
LAMBDA		=	"\"
DOT			=	"."
LPAREN		=	"("
RPAREN		=	")"
IDENTIFIER	=	IDENT_CHAR+
IDENT_CHAR	=	PRINTABLE - ( LAMBDA | DOT | LPAREN | RPAREN | WS )
PRINTABLE	=	[\x21-\x7E]
```
<!-- ```
DEF			=	"def"
ASSIGN		=	"="
EOS			=	"\n"
``` -->

### 文脈自由構文
```
expr		=	abstraction | application
abstraction	=	LAMBDA IDENTIFIER DOT expr
primary		=	IDENTIFIER | LPAREN expr RPAREN
application	=	primary | application ( primary | abstraction)
```
<!-- ```
ast			=	{ definition EOS } [ expr ]
definision	=	DEF IDENTIFIER ASSIGN expr
``` -->
