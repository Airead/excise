/**
 * @file parse_response.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/06/05 16:36:26
 */

#include <stdio.h>
#include <string.h>

#include "http_parser.h"

char request[] =
	"HTTP/1.1 301 Moved Permanently\r\n"
	"Location: http://www.google.com/\r\n"
	"Content-Type: text/html; charset=UTF-8\r\n"
	"Date: Sun, 26 Apr 2009 11:11:49 GMT\r\n"
	"Expires: Tue, 26 May 2009 11:11:49 GMT\r\n"
	"X-$PrototypeBI-Version: 1.6.0.3\r\n" /* $ char in header field */
	"Cache-Control: public, max-age=2592000\r\n"
	"Server: gws\r\n"
	"Content-Length:  219  \r\n"
	"\r\n"
	"<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\n"
	"<TITLE>301 Moved</TITLE></HEAD><BODY>\n"
	"<H1>301 Moved</H1>\n"
	"The document has moved\n"
	"<A HREF=\"http://www.google.com/\">here</A>.\r\n"
	"</BODY></HTML>\r\n";

#if 0
typedef int (*http_data_cb) (http_parser*, const char *at, size_t length);
typedef int (*http_cb) (http_parser*);

struct http_parser_settings {
	http_cb      on_message_begin;
	http_data_cb on_url;
	http_cb      on_status_complete;
	http_data_cb on_header_field;
	http_data_cb on_header_value;
	http_cb      on_headers_complete;
	http_data_cb on_body;
	http_cb      on_message_complete;
};
#endif

int message_begin_cb(http_parser *p)
{
	static int count = 0;

	fprintf(stdout, "  [%d] step into **message_begin_cb**\n", ++count);
	return 0;
}

int header_field_cb(http_parser *p, const char *at, size_t length)
{
	static int count = 0;

	fprintf(stdout, "    [%d] step into **header_field_cb**\n", ++count);
	fprintf(stdout, "      get header key: %.*s, len %lu\n", (int)length, at, length);
	return 0;
}

int header_value_cb(http_parser *p, const char *at, size_t length)
{
	static int count = 0;

	fprintf(stdout, "    [%d] step into **header_value_cb**\n", ++count);
	fprintf(stdout, "      get header value: %.*s, len %lu\n", (int)length, at, length);

	return 0;
}

int request_url_cb(http_parser *p, const char *at, size_t length)
{
	static int count = 0;

	fprintf(stdout, "    [%d] step into **request_url_cb**\n", ++count);
	fprintf(stdout, "      get header value: %.*s, len %lu\n", (int)length, at, length);

	return 0;
}

int body_cb(http_parser *p, const char *at, size_t length)
{
	static int count = 0;

	fprintf(stdout, "    [%d] step into **body_cb**\n", ++count);
	fprintf(stdout, "      get body:\n");
	fprintf(stdout, "----------------------\n");
	fprintf(stdout, "%.*s\n", (int)length, at);
	fprintf(stdout, "len %lu\n", length);
	fprintf(stdout, "----------------------\n");

	return 0;
}

int headers_complete_cb(http_parser *p)
{
	static int count = 0;

	fprintf(stdout, "    [%d] step into **headers_complete_cb**\n", ++count);

	return 0;
}

int message_complete_cb(http_parser *p)
{
	static int count = 0;

	fprintf(stdout, "  [%d] step into **message_complete_cb**\n", ++count);

	return 0;
}

int status_complete_cb(http_parser *p)
{
	static int count = 0;

	fprintf(stdout, "    [%d] step into **message_status_cb**\n", ++count);

	return 0;
}

static http_parser_settings settings = {
	.on_message_begin = message_begin_cb,
	.on_header_field = header_field_cb,
	.on_header_value = header_value_cb,
	.on_url = request_url_cb,
	.on_body = body_cb,
	.on_headers_complete = headers_complete_cb,
	.on_message_complete = message_complete_cb,
	.on_status_complete = status_complete_cb
};

int main(int argc, char *argv[])
{
	http_parser parser;
	size_t nparsed;

	fprintf(stdout, "ready to parse requset\n");
	fprintf(stdout, "=================================\n");
	fprintf(stdout, "%s", request);
	fprintf(stdout, "=================================\n");
	/* enum http_parser_type { HTTP_REQUEST, HTTP_RESPONSE, HTTP_BOTH }; */
	
	fprintf(stdout, "http_parser_init...\n");
	http_parser_init(&parser, HTTP_RESPONSE);

	fprintf(stdout, "===start http_parser_execute()\n");
	nparsed = http_parser_execute(&parser, &settings, request, strlen(request));
	fprintf(stdout, "===end http_parser_execute()\n");
	fprintf(stdout, "parsed %lu bytes\n", nparsed);
	if (HTTP_PARSER_ERRNO(&parser) != HPE_OK) {
		fprintf(stdout, "parsed error: %s\n", http_errno_description(HTTP_PARSER_ERRNO(&parser)));
	}
	fprintf(stdout, "parsed request successful\n");

	return 0;
}
