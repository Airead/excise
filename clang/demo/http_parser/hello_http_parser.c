/**
 * @file hello_http_parser.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/06/04 10:44:34
 */

#include "http_parser.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#undef TRUE
#define TRUE 1
#undef FALSE
#define FALSE 0

#define MAX_HEADERS 13
#define MAX_ELEMENT_SIZE 2048

#define MAIN(a, b) ((a) < (b) ? (a) : (b))

static http_parser *parser;

struct message {
	const char *name; // for debugging purposes
	const char *raw;
	enum http_parser_type type;
	enum http_method method;
	int status_code;
	char request_path[MAX_ELEMENT_SIZE];
	char request_url[MAX_ELEMENT_SIZE];
	char fragment[MAX_ELEMENT_SIZE];
	char query_string[MAX_ELEMENT_SIZE];
	char body[MAX_ELEMENT_SIZE];
	size_t body_size;
	const char *host;
	const char *userinfo;
	uint16_t port;
	int num_headers;
	enum { NONE=0, FIELD, VALUE } last_header_element;
	char headers [MAX_HEADERS][2][MAX_ELEMENT_SIZE];
	int should_keep_alive;

	const char *upgrade; // upgraded body

	unsigned short http_major;
	unsigned short http_minor;

	int message_begin_cb_called;
	int headers_complete_cb_called;
	int message_complete_cb_called;
	int message_complete_on_eof;
	int body_is_final;
};

/* strnlen() is a POSIX.2008 addition. Can't rely on it being available so
 * define it ourselves.
 */
size_t
strnlen(const char *s, size_t maxlen)
{
	const char *p;

	p = memchr(s, '\0', maxlen);
	if (p == NULL)
		return maxlen;

	return p - s;
}

size_t
strlncat(char *dst, size_t len, const char *src, size_t n)
{
	size_t slen;
	size_t dlen;
	size_t rlen;
	size_t ncpy;

	slen = strnlen(src, n);
	dlen = strnlen(dst, len);

	if (dlen < len) {
		rlen = len - dlen;
		ncpy = slen < rlen ? slen : (rlen - 1);
		memcpy(dst + dlen, src, ncpy);
		dst[dlen + ncpy] = '\0';
	}

	assert(len > slen + dlen);
	return slen + dlen;
}

static int currently_parsing_eof;

static struct message messages[5];
static int num_messages;

const struct message requests[] =
{ 
	{.name= "curl get"
	 ,.type= HTTP_REQUEST
	 ,.raw= "GET /test HTTP/1.1\r\n"
         "User-Agent: curl/7.18.0 (i486-pc-linux-gnu) libcurl/7.18.0 OpenSSL/0.9.8g zlib/1.2.3.3 libidn/1.1\r\n"
         "Host: 0.0.0.0=5000\r\n"
         "Accept: */*\r\n"
         "\r\n"
	 ,.should_keep_alive= TRUE
	 ,.message_complete_on_eof= FALSE
	 ,.http_major= 1
	 ,.http_minor= 1
	 ,.method= HTTP_GET
	 ,.query_string= ""
	 ,.fragment= ""
	 ,.request_path= "/test"
	 ,.request_url= "/test"
	 ,.num_headers= 3
	 ,.headers=
	 { { "User-Agent", "curl/7.18.0 (i486-pc-linux-gnu) libcurl/7.18.0 OpenSSL/0.9.8g zlib/1.2.3.3 libidn/1.1" }
	   , { "Host", "0.0.0.0=5000" }
	   , { "Accept", "*/*" }
	 }
	 ,.body= ""
	}
	,{.name = NULL}
};

void test_preserve_data(void)
{
	char my_data[] = "application-specific data";
	http_parser parser;
	parser.data = my_data;
	http_parser_init(&parser, HTTP_REQUEST);
	if (parser.data != my_data) {
		printf("\n*** parser.data not preserved accross http_parser_init ***\n\n");
		abort();
	}
}

struct url_test {
	const char *name;
	const char *url;
	int is_connect;
	struct http_parser_url u;
	int rv;
};

const struct url_test url_tests[] =
{
	{.name="complex URL from node js url parser doc"
	 ,.url="http://host.com:8080/p/a/t/h?query=string#hash"
	 ,.is_connect=0
	 ,.u=
	 {.field_set= (1<<UF_SCHEMA) | (1<<UF_HOST) | (1<<UF_PORT) | (1<<UF_PATH) |\
	  (1<<UF_QUERY) | (1<<UF_FRAGMENT)
	  ,.port=8080
	  ,.field_data=
	  {{  0,  4 } /* UF_SCHEMA */
	   ,{  7,  8 } /* UF_HOST */
	   ,{ 16,  4 } /* UF_PORT */
	   ,{ 20,  8 } /* UF_PATH */
	   ,{ 29, 12 } /* UF_QUERY */
	   ,{ 42,  4 } /* UF_FRAGMENT */
	   ,{  0,  0 } /* UF_USERINFO */
	  }
	 }
	 ,.rv=0
	}
};

void dump_url(const char *url, const struct http_parser_url *u)
{
	unsigned int i;

	printf("\tfield_set: 0x%x, port: %u\n", u->field_set, u->port);
	for (i = 0; i < UF_MAX; i++) {
		if ((u->field_set & (1 << i)) == 0) {
			printf("\tfield_data[%u]: unset\n", i);
			continue;
		}

		printf("\tfield_data[%u]: off: %u len %u part: \"%.*s\"\n",
			i,
			u->field_data[i].off,
			u->field_data[i].len,
			u->field_data[i].len,
			url + u->field_data[i].off);
	}
}

void test_parse_url(void)
{
	struct http_parser_url u;
	const struct url_test *test;
	unsigned int i;
	int rv;

	for (i = 0; i < (sizeof(url_tests) / sizeof(url_tests[0])); i++) {
		test = &url_tests[i];
		memset(&u, 0, sizeof(u));

		rv = http_parser_parse_url(test->url, 
					strlen(test->url),
					test->is_connect,
					&u);
		if (test->rv == 0) {
			if (rv != 0) {
				printf("\n*** http_parser_parse_url(\"%s\") \"%s\" test failed, "
					"unexpected rv %d ***\n\n", test->url, test->name, rv);
				abort();
			}

			if (memcmp(&u, &test->u, sizeof(u)) != 0) {
				printf("\n*** http_parser_parse_url(\"%s\") \"%s\" failed ***\n",
					test->url, test->name);

				printf("target http_parser_url:\n");
				dump_url(test->url, &test->u);
				printf("result http_parser_url:\n");
				dump_url(test->url, &u);

				abort();
			}
		} else {
			/* test->rv != 0 */
			if (rv == 0) {
				printf("\n*** http_parser_parse_url(\"%s\") \"%s\" test failed, "
					"unexpected rv %d ***\n\n", test->url, test->name, rv);
				abort();
			}
		}
	}
}

void test_method_str(void)
{
	assert(0 == strcmp("GET", http_method_str(HTTP_GET)));
	assert(0 == strcmp("<unknown>", http_method_str(1337)));
}

static http_parser_settings settings_null =
{
	.on_message_begin = 0
	,.on_header_field = 0
	,.on_header_value = 0
	,.on_url = 0
	,.on_body = 0
	,.on_headers_complete = 0
	,.on_message_complete = 0
};

void test_header_overflow_error(int req)
{
	http_parser parser;
	http_parser_init(&parser, req ? HTTP_REQUEST : HTTP_RESPONSE);
	size_t parsed;
	const char *buf;

	buf = req ? "GET / HTTP/1.1\r\n" : "HTTP/1.0 200 OK\r\n";
	parsed = http_parser_execute(&parser, &settings_null, buf, strlen(buf));
	assert(parsed == strlen(buf));

	buf = "header-key: header-value\r\n";
	size_t buflen = strlen(buf);

	int i;
	for (i = 0; i < 10000; i++) {
		parsed = http_parser_execute(&parser, &settings_null, buf, buflen);
		// fprintf(stderr, "error found on iter %d\n", i);
		if (parsed != buflen) {
			assert(HTTP_PARSER_ERRNO(&parser) == HPE_HEADER_OVERFLOW);
			return;
		}
	}

	fprintf(stderr, "\n*** Error expected but none in header overflow test ***\n");
	abort();
}

void test_no_overflow_long_body(int req, size_t length)
{
	http_parser parser;
	http_parser_init(&parser, req ? HTTP_REQUEST : HTTP_RESPONSE);
	size_t parsed;
	size_t i;
	char buf1[3000];
	size_t buf1len = sprintf(buf1, "%s\r\nConnection: Keep-Alive\r\nContent-Length: %lu\r\n\r\n",
				req ? "POST / HTTP/1.0" : "HTTP/1.0 200 OK", (unsigned long)length);
	parsed = http_parser_execute(&parser, &settings_null, buf1, buf1len);
	if (parsed != buf1len) {
		goto err;
	}

	for (i = 0; i < length; i++) {
		char foo = 'a';
		parsed = http_parser_execute(&parser, &settings_null, &foo, 1);
		if (parsed != 1) {
			goto err;
		}
	}
	
	// fprintf(stderr, "out of for\n");
	
	parsed = http_parser_execute(&parser, &settings_null, buf1, buf1len);
	// fprintf(stderr, "parsed = %lu\n", parsed);
	if (parsed != buf1len) {
		goto err;
	}

	return ;
err:
	fprintf(stderr,
		"\n*** error in test_no_overflow_long_body %s of length %lu ***\n",
		req ? "REQUEST" : "RESPONSE",
		(unsigned long)length);
	abort();
}

static void test_content_length_overflow(const char *buf, size_t buflen, int expect_ok)
{
	http_parser parser;
	http_parser_init(&parser, HTTP_RESPONSE);
	http_parser_execute(&parser, &settings_null, buf, buflen);

	if (expect_ok) {
		assert(HTTP_PARSER_ERRNO(&parser) == HPE_OK);
	} else {
		assert(HTTP_PARSER_ERRNO(&parser) == HPE_INVALID_CONTENT_LENGTH);
	}
}

void test_header_content_length_overflow_error(void)
{
#define X(size)					\
	"HTTP/1.1 200 OK\r\n"			\
		"Content-Length: " #size "\r\n"	\
		"\r\n"
	const char a[] = X(18446744073709551614); /* 2^64-2 */
	const char b[] = X(18446744073709551615); /* 2^64-1 */
	const char c[] = X(18446744073709551616); /* 2^64   */
#undef X
	test_content_length_overflow(a, sizeof(a) - 1, 1); /* expect ok      */
	test_content_length_overflow(b, sizeof(b) - 1, 0); /* expect failure */
	test_content_length_overflow(c, sizeof(c) - 1, 0); /* expect failure */

}

void test_chunk_content_length_overflow_error(void)
{
#define X(size)						\
	"HTTP/1.1 200 OK\r\n"				\
		"Transfer-Encoding: chunked\r\n"	\
		"\r\n"					\
		#size "\r\n"				\
		"..."
	const char a[] = X(FFFFFFFFFFFFFFFE);  /* 2^64-2 */
	const char b[] = X(FFFFFFFFFFFFFFFF);  /* 2^64-1 */
	const char c[] = X(10000000000000000); /* 2^64   */
#undef X
	test_content_length_overflow(a, sizeof(a) - 1, 1); /* expect ok      */
	test_content_length_overflow(b, sizeof(b) - 1, 0); /* expect failure */
	test_content_length_overflow(c, sizeof(c) - 1, 0); /* expect failure */
}

/* * R E S P O N S E S * */
const struct message responses[] =
{
#define GOOGLE_301 0
	{.name= "google 301"
	 ,.type= HTTP_RESPONSE
	 ,.raw= "HTTP/1.1 301 Moved Permanently\r\n"
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
	 "</BODY></HTML>\r\n"
	 ,.should_keep_alive= TRUE
	 ,.message_complete_on_eof= FALSE
	 ,.http_major= 1
	 ,.http_minor= 1
	 ,.status_code= 301
	 ,.num_headers= 8
	 ,.headers=
	 { { "Location", "http://www.google.com/" }
	   , { "Content-Type", "text/html; charset=UTF-8" }
	   , { "Date", "Sun, 26 Apr 2009 11:11:49 GMT" }
	   , { "Expires", "Tue, 26 May 2009 11:11:49 GMT" }
	   , { "X-$PrototypeBI-Version", "1.6.0.3" }
	   , { "Cache-Control", "public, max-age=2592000" }
	   , { "Server", "gws" }
	   , { "Content-Length", "219  " }
	 }
	 ,.body= "<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\n"
	 "<TITLE>301 Moved</TITLE></HEAD><BODY>\n"
	 "<H1>301 Moved</H1>\n"
	 "The document has moved\n"
	 "<A HREF=\"http://www.google.com/\">here</A>.\r\n"
	 "</BODY></HTML>\r\n"
	}
	,{.name = NULL}
};

int message_begin_cb(http_parser *p)
{
	assert(p == parser);
	messages[num_messages].message_begin_cb_called = TRUE;
	return 0;
}

int header_field_cb(http_parser *p, const char *buf, size_t len)
{
	assert(p == parser);
	struct message *m = &messages[num_messages];

	if (m->last_header_element != FIELD) {
		m->num_headers++;
	}

	strlncat(m->headers[m->num_headers - 1][0],
		sizeof(m->headers[m->num_headers - 1][0]),
		buf, len);

	m->last_header_element = FIELD;

	return 0;
}

int header_value_cb(http_parser *p, const char *buf, size_t len)
{
	assert(p == parser);
	struct message *m = &messages[num_messages];

	strlncat(m->headers[m->num_headers-1][1],
		sizeof(m->headers[m->num_headers-1][1]),
		buf, len);

	m->last_header_element = VALUE;

	return 0;
}

int request_url_cb(http_parser *p, const char *buf, size_t len)
{
	assert(p == parser);
	strlncat(messages[num_messages].request_url,
		sizeof(messages[num_messages].request_url),
		buf, len);
	return 0;
}

void check_body_is_final(const http_parser *p)
{
	if (messages[num_messages].body_is_final) {
		fprintf(stderr, "\n\n *** Error http_body_is_final() should return 1 "
			"on last on_body callback call "
			"but it doesn't! ***\n\n");
		assert(0);
		abort();
	}

	messages[num_messages].body_is_final = http_body_is_final(p);
}

int body_cb(http_parser *p, const char *buf, size_t len)
{
	assert(p == parser);
	strlncat(messages[num_messages].body,
		sizeof(messages[num_messages].body),
		buf, len);
	messages[num_messages].body_size += len;
	check_body_is_final(p);
	// printf("body_cb: '%s'\n", requests[num_messages].body);
	return 0;
}

int headers_complete_cb(http_parser *p)
{
	assert(p == parser);
	messages[num_messages].method = parser->method;
	messages[num_messages].status_code = parser->status_code;
	messages[num_messages].http_major = parser->http_major;
	messages[num_messages].http_minor = parser->http_minor;
	messages[num_messages].headers_complete_cb_called = TRUE;
	messages[num_messages].should_keep_alive = http_should_keep_alive(parser);
	return 0;
}

int message_complete_cb(http_parser *p)
{
	assert(p == parser);
	if (messages[num_messages].should_keep_alive != http_should_keep_alive(parser))
	{
		fprintf(stderr, "\n\n *** Error http_should_keep_alive() should have same "
			"value in both on_message_complete and on_headers_complete "
			"but it doesn't! ***\n\n");
		assert(0);
		abort();
	}

	if (messages[num_messages].body_size &&
		http_body_is_final(p) &&
		!messages[num_messages].body_is_final) {

		fprintf(stderr, "\n\n *** Error http_should_keep_alive() should have same "
			"value in both on_message_complete and on_headers_complete "
			"but it doesn't! ***\n\n");
		assert(0);
		abort();
	}

	messages[num_messages].message_complete_cb_called = TRUE;

	messages[num_messages].message_complete_on_eof = currently_parsing_eof;

	num_messages++;

	return 0;
}

static http_parser_settings settings =
{.on_message_begin = message_begin_cb
 ,.on_header_field = header_field_cb
 ,.on_header_value = header_value_cb
 ,.on_url = request_url_cb
 ,.on_body = body_cb
 ,.on_headers_complete = headers_complete_cb
 ,.on_message_complete = message_complete_cb
};

void parser_free(void)
{
	assert(parser);
	free(parser);
	parser = NULL;
}

size_t parse(const char *buf, size_t len)
{
	size_t nparsed;
	currently_parsing_eof = (len == 0);
	nparsed = http_parser_execute(parser, &settings, buf, len);
	return nparsed;
}

void parser_init(enum http_parser_type type)
{
	num_messages = 0;

	assert(parser == NULL);

	parser = malloc(sizeof(http_parser));

	http_parser_init(parser, type);

	memset(&messages, 0, sizeof messages);
}

static void print_error(const char *raw, size_t error_location)
{
	fprintf(stderr, "\n*** %s ***\n\n",
		http_errno_description(HTTP_PARSER_ERRNO(parser)));

	int this_line = 0, char_len = 0;
	size_t i, j, len = strlen(raw), error_location_line = 0;
	for (i = 0; i < len; i++) {
		if (i == error_location) this_line = 1;
		switch (raw[i]) {
		case '\r':
			char_len = 2;
			fprintf(stderr, "\\r");
			break;
		case '\n':
			char_len = 2;
			fprintf(stderr, "\\n\n");

			if (this_line) {
				goto print;	
			}

			error_location_line = 0;
			continue;
		default:
			char_len = 1;
			fputc(raw[i], stderr);
			break;
		}
		if (!this_line) {
			error_location_line += char_len;
		}
	}
	fprintf(stderr, "[eof]\n");

print:
	for (j = 0; j < error_location_line; j++) {
		fputc(' ', stderr);
	}
	fprintf(stderr, "^\n\nerror location: %u\n", (unsigned int)error_location);
}

static inline int
check_str_eq (const struct message *m,
	const char *prop,
	const char *expected,
	const char *found) {
	if ((expected == NULL) != (found == NULL)) {
		printf("\n*** Error: %s in '%s' ***\n\n", prop, m->name);
		printf("expected %s\n", (expected == NULL) ? "NULL" : expected);
		printf("   found %s\n", (found == NULL) ? "NULL" : found);
		return 0;
	}
	if (expected != NULL && 0 != strcmp(expected, found)) {
		printf("\n*** Error: %s in '%s' ***\n\n", prop, m->name);
		printf("expected '%s'\n", expected);
		printf("   found '%s'\n", found);
		return 0;
	}
	return 1;
}

static inline int
check_num_eq (const struct message *m,
	const char *prop,
	int expected,
	int found) {
	if (expected != found) {
		printf("\n*** Error: %s in '%s' ***\n\n", prop, m->name);
		printf("expected %d\n", expected);
		printf("   found %d\n", found);
		return 0;
	}
	return 1;
}

#define MESSAGE_CHECK_STR_EQ(expected, found, prop)			\
	if (!check_str_eq(expected, #prop, expected->prop, found->prop)) return 0

#define MESSAGE_CHECK_NUM_EQ(expected, found, prop)			\
	if (!check_num_eq(expected, #prop, expected->prop, found->prop)) return 0

#define MESSAGE_CHECK_URL_EQ(u, expected, found, prop, fn)		\
	do {								\
		char ubuf[256];						\
									\
		if ((u)->field_set & (1 << (fn))) {			\
			memcpy(ubuf, (found)->request_url + (u)->field_data[(fn)].off, \
				(u)->field_data[(fn)].len);		\
			ubuf[(u)->field_data[(fn)].len] = '\0';		\
		} else {						\
			ubuf[0] = '\0';					\
		}							\
									\
		check_str_eq(expected, #prop, expected->prop, ubuf);	\
	} while(0)

int message_eq(int index, const struct message *expected)
{
	int i;
	struct message *m = &messages[index];

	MESSAGE_CHECK_NUM_EQ(expected, m, http_major);
	MESSAGE_CHECK_NUM_EQ(expected, m, http_minor);

	if (expected->type == HTTP_REQUEST) {
		MESSAGE_CHECK_NUM_EQ(expected, m, method);
	} else {
		MESSAGE_CHECK_NUM_EQ(expected, m, status_code);
	}

	MESSAGE_CHECK_NUM_EQ(expected, m, should_keep_alive);
	MESSAGE_CHECK_NUM_EQ(expected, m, message_complete_on_eof);

	assert(m->message_begin_cb_called);
	assert(m->headers_complete_cb_called);
	assert(m->message_complete_cb_called);


	MESSAGE_CHECK_STR_EQ(expected, m, request_url);

	/* Check URL components; we can't do this w/ CONNECT since it doesn't
	 * send us a well-formed URL.
	 */
	if (*m->request_url && m->method != HTTP_CONNECT) {
		struct http_parser_url u;

		if (http_parser_parse_url(m->request_url, strlen(m->request_url), 0, &u)) {
			fprintf(stderr, "\n\n*** failed to parse URL %s ***\n\n",
				m->request_url);
			abort();
		}

		if (expected->host) {
			MESSAGE_CHECK_URL_EQ(&u, expected, m, host, UF_HOST);
		}

		if (expected->userinfo) {
			MESSAGE_CHECK_URL_EQ(&u, expected, m, userinfo, UF_USERINFO);
		}

		m->port = (u.field_set & (1 << UF_PORT)) ?
			u.port : 0;

		MESSAGE_CHECK_URL_EQ(&u, expected, m, query_string, UF_QUERY);
		MESSAGE_CHECK_URL_EQ(&u, expected, m, fragment, UF_FRAGMENT);
		MESSAGE_CHECK_URL_EQ(&u, expected, m, request_path, UF_PATH);
		MESSAGE_CHECK_NUM_EQ(expected, m, port);
	}

	if (expected->body_size) {
		MESSAGE_CHECK_NUM_EQ(expected, m, body_size);
	} else {
		MESSAGE_CHECK_STR_EQ(expected, m, body);
	}

	MESSAGE_CHECK_NUM_EQ(expected, m, num_headers);

	int r;
	for (i = 0; i < m->num_headers; i++) {
		r = check_str_eq(expected, "header field", expected->headers[i][0], m->headers[i][0]);
		if (!r) return 0;
		r = check_str_eq(expected, "header value", expected->headers[i][1], m->headers[i][1]);
		if (!r) return 0;
	}

	MESSAGE_CHECK_STR_EQ(expected, m, upgrade);

	return 1;
}

void test_message(const struct message *message)
{
	size_t raw_len = strlen(message->raw);
	size_t msg1len;

	for (msg1len = 0; msg1len < raw_len; msg1len++) {
		parser_init(message->type);

		size_t read;
		const char *msg1 = message->raw;
		const char *msg2 = msg1 + msg1len;
		size_t msg2len = raw_len - msg1len;

		if (msg1len) {
			read = parse(msg1, msg1len);

			if (message->upgrade && parser->upgrade) {
				messages[num_messages - 1].upgrade = msg1 + read;
				goto test;
			}

			if (read != msg1len) {
				print_error(msg1, read);
				abort();
			}
		}

		read = parse(msg2, msg2len);

		if (message->upgrade && parser->upgrade) {
			messages[num_messages - 1].upgrade = msg2 + read;
			goto test;
		}

		if (read != msg2len) {
			print_error(msg2, read);
			abort();
		}

		read = parse(NULL, 0);

		if (read != 0) {
			print_error(message->raw, read);
			abort();
		}

	test:
		if (num_messages != 1) {
			printf("\n*** num_messages != 1 after testing '%s' ***\n\n", message->name);
			abort();
		}

		if (!message_eq(0, message))
			abort();
		parser_free();
	} // end for
}

int main(int argc, char *argv[])
{
	parser = NULL;
	int i;
	int request_count;
	int response_count;

	printf("sizeof(http_parser) = %u\n", (unsigned int)sizeof(http_parser));

	for (request_count = 0; requests[request_count].name; request_count++);
	for (response_count = 0; responses[response_count].name; response_count++);

	test_preserve_data();
	test_parse_url();
	test_method_str();
	
	test_header_overflow_error(HTTP_REQUEST);
	test_no_overflow_long_body(HTTP_REQUEST, 1000);
	test_no_overflow_long_body(HTTP_REQUEST, 100000);

	test_header_overflow_error(HTTP_RESPONSE);
	test_no_overflow_long_body(HTTP_RESPONSE, 1000);
	test_no_overflow_long_body(HTTP_RESPONSE, 100000);
	
	test_header_content_length_overflow_error();
	test_chunk_content_length_overflow_error();

	//// RESPONSES

	for (i = 0; i < response_count; i++) {
		test_message(&responses[i]);
	}

	for (i = 0; requests[i].name; i++) {
		test_message(&requests[i]);
	}
	
	return 0;
}
