/* Copyright (c) 2013 The Squash Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *   Evan Nemerson <evan@coeus-group.com>
 */

#ifndef SQUASH_INI_H
#define SQUASH_INI_H

#if !defined (SQUASH_COMPILATION)
#error "This is internal API; you cannot use it."
#endif

#include <stdio.h>

typedef struct _SquashIniParser SquashIniParser;

typedef enum _SquashIniParserError {
  SQUASH_INI_PARSER_OK = 0,
  SQUASH_INI_PARSER_ERROR = -1,
  SQUASH_INI_PARSER_INVALID_ESCAPE_SEQUENCE = -2,
	SQUASH_INI_PARSER_UNEXPECTED_CHAR = -3,
  SQUASH_INI_PARSER_UNEXPECTED_EOF = -4
} SquashIniParserError;

typedef int  (* SquashIniParserSectionBeginFunc) (SquashIniParser* parser, const char* name, void* user_data);
typedef int  (* SquashIniParserSectionEndFunc)   (SquashIniParser* parser, const char* name, void* user_data);
typedef int  (* SquashIniParserKeyFunc)          (SquashIniParser* parser,
                                                  const char* section,
                                                  const char* key,
                                                  const char* detail,
                                                  const char* value,
                                                  void* user_data);
typedef int  (* SquashIniParserErrorFunc)        (SquashIniParser* parser,
                                                  SquashIniParserError error_code,
                                                  int line_number,
                                                  int offset,
                                                  const char* line,
                                                  void* user_data);
typedef int  (* SquashIniParserFileEndFunc)      (SquashIniParser* parser);
typedef void (* SquashIniParserDestroyNotify)    (void* user_data);

const char* squash_ini_parser_error_to_string (SquashIniParserError e);

struct _SquashIniParser {
  SquashIniParserSectionBeginFunc   section_begin;
  SquashIniParserSectionEndFunc     section_end;
  SquashIniParserKeyFunc            key_read;
	SquashIniParserErrorFunc          error_callback;

  void*                             user_data;
  void                            (*user_data_destroy) (void* user_data);
};

void squash_ini_parser_init    (SquashIniParser* parser,
                                SquashIniParserSectionBeginFunc section_begin,
                                SquashIniParserSectionEndFunc section_end,
                                SquashIniParserKeyFunc key_read,
                                SquashIniParserErrorFunc error_callback,
                                void* user_data,
                                SquashIniParserDestroyNotify user_data_destroy);
void squash_ini_parser_destroy (SquashIniParser* parser);
int  squash_ini_parser_parse   (SquashIniParser* parser, FILE* input);

#endif /* SQUASH_INI_H */
