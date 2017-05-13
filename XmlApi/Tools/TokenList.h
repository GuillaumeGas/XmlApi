#pragma once

/* TokenList example
#define LEX_TOKEN_LIST				\
	LEX_TOKEN (EXAMPLE_1, "ex1")		\
	// The lexer need theses following tokens !
	LEX_TOKEN (_EOF_, "<lex::eof>")		\
	LEX_TOKEN (OTHER, "<lex::other>")
*/

#define LEX_TOKEN_LIST				\
    LEX_TOKEN (SLASH, "/")			\
    LEX_TOKEN (LEFT_ARROW, "<")				\
    LEX_TOKEN (RIGHT_ARROW, ">")				\
    LEX_TOKEN (EQUAL, "=")			\
    LEX_TOKEN (COLON, ":")			\
    LEX_TOKEN (DOUBLE_QUOTE, "\"")		\
    LEX_TOKEN (CR, "\n")			    \
	LEX_TOKEN (INTERROGATION, "?")              \
    LEX_TOKEN (_EOF_, "<lex::eof>")		\
    LEX_TOKEN (OTHER, "<lex::other>")
