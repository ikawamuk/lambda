# lambda design
## 全体パイプライン
0. ソースコード文字列(入力)
1. **Lexer**: 文字列 → トークン列
2. **Parser**: トークン列 → Expr
3. **Evaluator**: Expr → Value
4. **Encoder**: Value → 終了ステータス
5. 終了ステータス(出力)

## データ構造
- ソースコード文字列: char*
- トークン列
	- TokenNode: ( data: Token, next: TokenNode* )
		- Token: ( type: TokenType, literal: char* )
			- TokenType: LAMBDA, DOT, LPAREN, RPAREN, IDENTIFIER
- Expr, Value
	- ASTNode: ( type: ASTType, data: ( Abstruction | Application | Identifier ))
		- ASTType: ABSTRUCTION, APPLICATION, IDENTIFIER
		- Abstruction: ( parameter: char*, body: ASTNode* )
		- Application: ( function: ASTNode*, argument: ASTNode* )
		- Identifier: ( index: size_t, name: char* )
<!-- - 終了ステータス: int -->

## モジュール設計

### Lexer
- 文字列からトークン列へ変換する

### Parser
- トークン列からASTを構築する。

### Evaluator
- ASTをβ-簡約などで正規化する。
- **正規順序評価**を用いる
- 関数適用(Application)の形が存在しなくなった時点で終了する。
- オメガコンビネータなどによる無限ループ防止のため最大還元回数に達した場合はエラー終了させる。

### Encoder
- 符号化を行う
	<!-- - Church数の符号化を行う -->
	<!-- - 真理値の符号化を行う -->

## その他
- [自作文字列ライブラリ](https://github.com/ikawamuk/string)を使用する。
