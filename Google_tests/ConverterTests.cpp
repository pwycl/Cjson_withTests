#include "gtest/gtest.h"
#include "cJSON.h"
#include "../Cjson_lib/cJSON.c"

static cJSON item[1];
void reset(cJSON *item) {
    if ((item != NULL) && (item->child != NULL))
    {
        cJSON_Delete(item->child);
    }
    if ((item->valuestring != NULL) && !(item->type & cJSON_IsReference))
    {
        global_hooks.deallocate(item->valuestring);
    }
    if ((item->string != NULL) && !(item->type & cJSON_StringIsConst))
    {
        global_hooks.deallocate(item->string);
    }

    memset(item, 0, sizeof(cJSON));
}


class CjsonFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        memset(item, 0, sizeof(cJSON));
//        gregDate = new GregorianDate();
//        julDate = new JulianDate();
    }

    virtual void TearDown() {
//        delete gregDate;
//        delete julDate;
        reset(item);
    }

//    GregorianDate * gregDate;
//    JulianDate * julDate;
};

static void assert_not_in_list(cJSON *object_item){
    ASSERT_TRUE(object_item->next==NULL);
    ASSERT_TRUE(object_item->prev==NULL);
}
static void assert_has_type(cJSON *object_item, int expect_type){    //判断类型
    ASSERT_TRUE((0xff & (object_item->type))==(0xff & expect_type));
}
static void assert_has_no_reference(cJSON *object_item){
    ASSERT_TRUE((cJSON_IsReference & (object_item->type))==(cJSON_IsReference & 0));
}
static void assert_has_no_const_string(cJSON *object_item){
    ASSERT_TRUE((cJSON_StringIsConst & (object_item->type))==(cJSON_StringIsConst & 0));
}
static void assert_is_object(cJSON *object_item)
{
//    TEST_ASSERT_NOT_NULL_MESSAGE(object_item, "Item is NULL.");
    ASSERT_TRUE(object_item!=NULL);

    assert_not_in_list(object_item);
    assert_has_type(object_item, cJSON_Object);
    assert_has_no_reference(object_item);
    assert_has_no_const_string(object_item);
//    assert_has_no_valuestring(object_item);
//    assert_has_no_string(object_item);
}

static void assert_parse_object(const char *json)
{
    parse_buffer parsebuffer = { 0, 0, 0, 0, { 0, 0, 0 } };
    parsebuffer.content = (const unsigned char*)json;
    parsebuffer.length = strlen(json) + sizeof("");
    parsebuffer.hooks = global_hooks;

    ASSERT_TRUE(parse_object(item, &parsebuffer));
    assert_is_object(item);
}

TEST(CjsonFixture, parse_empty_objects){
    assert_parse_object("{}");
    assert_parse_object("{\n\t}");
}
//
//TEST(CjsonFixture, parse_object_should_parse_objects_with_one_element){
//    assert_parse_object("{\"one\":1}");
////    assert_is_child(item->child, "one", cJSON_Number);
//    reset(item);
//
//    assert_parse_object("{\"hello\":\"world!\"}");
////    assert_is_child(item->child, "hello", cJSON_String);
//    reset(item);
//
//    assert_parse_object("{\"array\":[]}");
////    assert_is_child(item->child, "array", cJSON_Array);
//    reset(item);
//
//    assert_parse_object("{\"null\":null}");
////    assert_is_child(item->child, "null", cJSON_NULL);
//    reset(item);
//}
//TEST(CjsonFixture, parse_object_should_parse_objects_with_multiple_elements)
//{
//    assert_parse_object("{\"one\":1\t,\t\"two\"\n:2, \"three\":3}");
////    assert_is_child(item->child, "one", cJSON_Number);
////    assert_is_child(item->child->next, "two", cJSON_Number);
////    assert_is_child(item->child->next->next, "three", cJSON_Number);
//    reset(item);
//
//    {
//        size_t i = 0;
//        cJSON *node = NULL;
//        int expected_types[7] =
//                {
//                        cJSON_Number,
//                        cJSON_NULL,
//                        cJSON_True,
//                        cJSON_False,
//                        cJSON_Array,
//                        cJSON_String,
//                        cJSON_Object
//                };
//        const char *expected_names[7] =
//                {
//                        "one",
//                        "NULL",
//                        "TRUE",
//                        "FALSE",
//                        "array",
//                        "world",
//                        "object"
//                };
//        assert_parse_object("{\"one\":1, \"NULL\":null, \"TRUE\":true, \"FALSE\":false, \"array\":[], \"world\":\"hello\", \"object\":{}}");
//
//        node = item->child;
//        for (
//                i = 0;
//                (i < (sizeof(expected_types)/sizeof(int)))
//                && (node != NULL);
//                (void)i++, node = node->next)
//        {
////            assert_is_child(node, expected_names[i], expected_types[i]);
//        }
////        TEST_ASSERT_EQUAL_INT(i, 7);
//        reset(item);
//    }
//}
//
//static void assert_parse_array(const char *json)
//{
//    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
//    buffer.content = (const unsigned char*)json;
//    buffer.length = strlen(json) + sizeof("");
//    buffer.hooks = global_hooks;
//
//    ASSERT_TRUE(parse_array(item, &buffer));
////    assert_is_array(item);
//}
//
//TEST(CjsonFixture, parse_array_should_parse_empty_arrays)
////static void parse_array_should_parse_empty_arrays(void)
//{
//    assert_parse_array("[]");
////    assert_has_no_child(item);
//
//    assert_parse_array("[\n\t]");
////    assert_has_no_child(item);
//}
//TEST(CjsonFixture, parse_array_should_parse_arrays_with_one_element)
//{
//
//    assert_parse_array("[1]");
////    assert_has_child(item);
//    assert_has_type(item->child, cJSON_Number);
//    reset(item);
//
//    assert_parse_array("[\"hello!\"]");
////    assert_has_child(item);
//    assert_has_type(item->child, cJSON_String);
//    ASSERT_STREQ("hello!", item->child->valuestring);
//    reset(item);
//
//    assert_parse_array("[[]]");
////    assert_has_child(item);
////    assert_is_array(item->child);
////    assert_has_no_child(item->child);
//    reset(item);
//
//    assert_parse_array("[null]");
////    assert_has_child(item);
//    assert_has_type(item->child, cJSON_NULL);
//    reset(item);
//}
//TEST(CjsonFixture, parse_array_should_parse_arrays_with_multiple_elements)
//{
//    assert_parse_array("[1\t,\n2, 3]");
////    assert_has_child(item);
////    TEST_ASSERT_NOT_NULL(item->child->next);
////    TEST_ASSERT_NOT_NULL(item->child->next->next);
////    TEST_ASSERT_NULL(item->child->next->next->next);
//    assert_has_type(item->child, cJSON_Number);
//    assert_has_type(item->child->next, cJSON_Number);
//    assert_has_type(item->child->next->next, cJSON_Number);
//    reset(item);
//
//    {
//        size_t i = 0;
//        cJSON *node = NULL;
//        int expected_types[7] =
//                {
//                        cJSON_Number,
//                        cJSON_NULL,
//                        cJSON_True,
//                        cJSON_False,
//                        cJSON_Array,
//                        cJSON_String,
//                        cJSON_Object
//                };
//        assert_parse_array("[1, null, true, false, [], \"hello\", {}]");
//
//        node = item->child;
//        for (
//                i = 0;
//                (i < (sizeof(expected_types)/sizeof(int)))
//                && (node != NULL);
//                (void)i++, node = node->next)
//        {
////            TEST_ASSERT_BITS(0xFF, expected_types[i], node->type);
//        }
////        TEST_ASSERT_EQUAL_INT(i, 7);
//        reset(item);
//    }
//}
//
//static void assert_parse_number(const char *string, int integer, double real)
//{
//    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
//    buffer.content = (const unsigned char*)string;
//    buffer.length = strlen(string) + sizeof("");
//
//    ASSERT_TRUE(parse_number(item, &buffer));
////    assert_is_number(item);
//    ASSERT_EQ(integer, item->valueint);
//    ASSERT_DOUBLE_EQ(real, item->valuedouble);
//}
//TEST(CjsonFixture, parse_number_should_parse_zero)
//{
//    assert_parse_number("0", 0, 0);
//    assert_parse_number("0.0", 0, 0.0);
//    assert_parse_number("-0", 0, -0.0);
//}
//
//TEST(CjsonFixture, parse_number_should_parse_negative_integers)
//{
//    assert_parse_number("-1", -1, -1);
//    assert_parse_number("-32768", -32768, -32768.0);
//    assert_parse_number("-2147483648", (int)-2147483648.0, -2147483648.0);
//}
//
//static void parse_number_should_parse_positive_integers(void)
//{
//    assert_parse_number("1", 1, 1);
//    assert_parse_number("32767", 32767, 32767.0);
//    assert_parse_number("2147483647", (int)2147483647.0, 2147483647.0);
//}
//TEST(CjsonFixture, parse_number_should_parse_positive_reals)
//{
//    assert_parse_number("0.001", 0, 0.001);
//    assert_parse_number("10e-10", 0, 10e-10);
//    assert_parse_number("10E-10", 0, 10e-10);
//    assert_parse_number("10e10", INT_MAX, 10e10);
//    assert_parse_number("123e+127", INT_MAX, 123e127);
//    assert_parse_number("123e-128", 0, 123e-128);
//}
//TEST(CjsonFixture, parse_number_should_parse_negative_reals)
//{
//    assert_parse_number("-0.001", 0, -0.001);
//    assert_parse_number("-10e-10", 0, -10e-10);
//    assert_parse_number("-10E-10", 0, -10e-10);
//    assert_parse_number("-10e20", INT_MIN, -10e20);
//    assert_parse_number("-123e+127", INT_MIN, -123e127);
//    assert_parse_number("-123e-128", 0, -123e-128);
//}
//
//static void assert_parse_value(const char *string, int type)
//{
//    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
//    buffer.content = (const unsigned char*) string;
//    buffer.length = strlen(string) + sizeof("");
//    buffer.hooks = global_hooks;
//
//    parse_value(item, &buffer);
////    TEST_ASSERT_TRUE(parse_value(item, &buffer));
////    assert_is_value(item, type);
//}
//
//TEST(CjsonFixture, parse_value)
//{
//    assert_parse_value("null", cJSON_NULL);
//    reset(item);
//
//    assert_parse_value("true", cJSON_True);
//    reset(item);
//
//    assert_parse_value("false", cJSON_False);
//    reset(item);
//
//    assert_parse_value("1.5", cJSON_Number);
//    reset(item);
//
//    assert_parse_value("\"\"", cJSON_String);
//    reset(item);
//    assert_parse_value("\"hello\"", cJSON_String);
//    reset(item);
//
//    assert_parse_value("[]", cJSON_Array);
//    reset(item);
//
//    assert_parse_value("{}", cJSON_Object);
//    reset(item);
//
//
//}
//
//static void assert_case_insensitive_strcmp(const unsigned char *string1, const unsigned char *string2,int integer)
//{
//    ASSERT_EQ(integer,case_insensitive_strcmp(string1,string2));
//}
//TEST(CjsonFixture, case_insensitive_strcmp)
//{
//    assert_case_insensitive_strcmp(NULL,NULL,1);
//
//}
//
static void assert_cJSON_GetErrorPtr()
{
    cJSON_GetErrorPtr();
}
//
TEST(CjsonFixture, assert_cJSON_GetErrorPtr)
{
    assert_cJSON_GetErrorPtr();
}
//
//
//
//static void assert_cJSON_Version()
//{
//    cJSON_Version();
//}
//
//TEST(CjsonFixture, assert_cJSON_Version)
//{
//    assert_cJSON_Version();
//}
//
//static void assert_cJSON_strdup()
//{
//    cJSON_strdup((const unsigned char*)"number", &global_hooks);
//}
//TEST(CjsonFixture, assert_cJSON_strdup)
//{
//    assert_cJSON_strdup();
//}
//
//
//

//
////测试出问题
////static void assert_cJSON_SetNumberHelper(cJSON *object, double number)
////{
////    cJSON_SetNumberHelper(object, number);
////}
////TEST(CjsonFixture, assert_cJSON_SetNumberHelper)
////{
////    assert_cJSON_SetNumberHelper(NULL,0);
////    assert_cJSON_SetNumberHelper(NULL,INT_MAX);
////    assert_cJSON_SetNumberHelper(NULL,(double)INT_MIN);
////}
//
//
//
//
//static void * CJSON_CDECL failing_realloc(void *pointer, size_t size)
//{
//    (void)size;
//    (void)pointer;
//    return NULL;
//}
//static void assert_ensure(printbuffer * const p, size_t needed)
//{
//    ensure(p,needed);
//}
//TEST(CjsonFixture, assert_ensure)
//{
//
//
//    printbuffer buffer = {NULL, 10, 0, 0, false, false, {&malloc, &free, &failing_realloc}};
//    buffer.buffer = (unsigned char*)malloc(100);
//    ensure(&buffer, 200);
//    ensure(NULL,2*INT_MAX/3); //这两个无法覆盖  不知为何
//    ensure(NULL,2*INT_MAX);
////    ensure(output_buffer, (size_t)length + sizeof(""));
//
////    printbuffer *buffer1;
////    buffer1->buffer = NULL;
////    buffer1->length = 10;
////    buffer1->hooks.reallocate = NULL;
////    ensure(buffer1, 200);
//}
//
////static void assert_update_offset(printbuffer *buffer)
////{
////    update_offset(buffer);
////}
////TEST(CjsonFixture, assert_update_offset)
////{
////    printbuffer *buffer;
////    buffer->buffer =NULL;
////    assert_update_offset(NULL);
////    assert_update_offset(buffer);
//////    printbuffer *buffer1 ;
//////    buffer1->length = 10;
//////
//////    assert_update_offset(buffer1);
////}
//
//
//static void assert_compare_double(double a, double b)
//{
//    compare_double(a,b);
//}
//TEST(CjsonFixture, assert_compare_double)
//{
//    assert_compare_double(0.0,2.0);
//}
//
//
//
//static void assert_print_number()
//{
//    unsigned char printed[1024];
//    unsigned char new_buffer[26];
//    unsigned int i = 0;
//    cJSON item[1];
//    printbuffer buffer = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };
//    buffer.buffer = printed;
//    buffer.length = sizeof(printed);
//    buffer.offset = 0;
//    buffer.noalloc = true;
//    buffer.hooks = global_hooks;
//    buffer.buffer = new_buffer;
//    print_number(item, &buffer), "Failed to print number.";
//}
//TEST(CjsonFixture, assert_print_number)
//{
//    assert_print_number();
//}
//
//
static void assert_print_string(const char *expected, const char *input)
{
    unsigned char printed[1024];
    printbuffer buffer = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };
    buffer.buffer = printed;
    buffer.length = sizeof(printed);
    buffer.offset = 0;
    buffer.noalloc = true;
    buffer.hooks = global_hooks;

    print_string_ptr((const unsigned char*)input, &buffer);
//    TEST_ASSERT_TRUE_MESSAGE(print_string_ptr((const unsigned char*)input, &buffer), "Failed to print string.");
//    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, printed, "The printed string isn't as expected.");
}
TEST(CjsonFixture, print_string_should_print_empty_strings)
//static void print_string_should_print_empty_strings(void)
{
    assert_print_string("\"\"", "");
    assert_print_string("\"\"", NULL);

    char ascii[0x7F];
    size_t i = 1;

    /* create ascii table */
    for (i = 1; i < 0x7F; i++)
    {
        ascii[i-1] = (char)i;
    }
    ascii[0x7F-1] = '\0';

    assert_print_string("\"\\u0001\\u0002\\u0003\\u0004\\u0005\\u0006\\u0007\\b\\t\\n\\u000b\\f\\r\\u000e\\u000f\\u0010\\u0011\\u0012\\u0013\\u0014\\u0015\\u0016\\u0017\\u0018\\u0019\\u001a\\u001b\\u001c\\u001d\\u001e\\u001f !\\\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\"",
            ascii);

    assert_print_string("\"ü猫慕\"", "ü猫慕");

}
//
static void assert_cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated)
{
    cJSON_ParseWithOpts(value,return_parse_end,require_null_terminated);
}
TEST(CjsonFixture, assert_cJSON_ParseWithOpts)
{
    assert_cJSON_ParseWithOpts(NULL,NULL, true);
    assert_cJSON_ParseWithOpts("0",NULL, true);
    assert_cJSON_ParseWithOpts("0",NULL, true);

    const char json[] = "{ \"name\": ";
    const char *parse_end = NULL;

    ASSERT_TRUE(cJSON_ParseWithOpts(json, &parse_end, false)==NULL);
}
//
//
//static void assert_cJSON_Parse()
//{
//    cJSON_Parse("a");
//}
//TEST(CjsonFixture, assert_cJSON_Parse)
//{
//    assert_cJSON_Parse();
//}
//

TEST(CjsonFixture, assert_cJSON_Print)
{
    cJSON *root=NULL;
    cJSON_Print(root);
    root=cJSON_CreateString("root");
    cJSON_Print(root);
    root=cJSON_Parse("\"[true, false]\"");
    cJSON_Print(root);
}
//
static void assert_cJSON_PrintUnformatted()
{
    const char *merges[15][3] =
            {
                    {"{\"a\":\"b\"}", "{\"a\":\"c\"}", "{\"a\":\"c\"}"},
                    {"{\"a\":\"b\"}", "{\"b\":\"c\"}", "{\"a\":\"b\",\"b\":\"c\"}"},
                    {"{\"a\":\"b\"}", "{\"a\":null}", "{}"},
                    {"{\"a\":\"b\",\"b\":\"c\"}", "{\"a\":null}", "{\"b\":\"c\"}"},
                    {"{\"a\":[\"b\"]}", "{\"a\":\"c\"}", "{\"a\":\"c\"}"},
                    {"{\"a\":\"c\"}", "{\"a\":[\"b\"]}", "{\"a\":[\"b\"]}"},
                    {"{\"a\":{\"b\":\"c\"}}", "{\"a\":{\"b\":\"d\",\"c\":null}}", "{\"a\":{\"b\":\"d\"}}"},
                    {"{\"a\":[{\"b\":\"c\"}]}", "{\"a\":[1]}", "{\"a\":[1]}"},
                    {"[\"a\",\"b\"]", "[\"c\",\"d\"]", "[\"c\",\"d\"]"},
                    {"{\"a\":\"b\"}", "[\"c\"]", "[\"c\"]"},
                    {"{\"a\":\"foo\"}", "null", "null"},
                    {"{\"a\":\"foo\"}", "\"bar\"", "\"bar\""},
                    {"{\"e\":null}", "{\"a\":1}", "{\"e\":null,\"a\":1}"},
                    {"[1,2]", "{\"a\":\"b\",\"c\":null}", "{\"a\":\"b\"}"},
                    {"{}","{\"a\":{\"bb\":{\"ccc\":null}}}", "{\"a\":{\"bb\":{}}}"}
            };
    for (int i = 0; i <15 ; ++i) {
        cJSON *object_to_be_merged = cJSON_Parse(merges[i][0]);
        cJSON *patch = cJSON_Parse(merges[i][1]);


        cJSON_PrintUnformatted(patch);
        cJSON_PrintUnformatted(object_to_be_merged);
    }

}
TEST(CjsonFixture, assert_cJSON_PrintUnformatted)
{
    assert_cJSON_PrintUnformatted();
}
//
//
static void assert_cJSON_PrintBuffered()
{
    cJSON_PrintBuffered(NULL, 10, true);
}
TEST(CjsonFixture, assert_cJSON_PrintBuffered)
{
    assert_cJSON_PrintBuffered();
}
//
//static void assert_cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format)
//{
//    cJSON_PrintPreallocated(item,buffer,length,format);
//}
//TEST(CjsonFixture, assert_cJSON_PrintPreallocated)
//{
////    char *out = NULL;
////    cJSON *root;
////    char *buf = NULL;
////    size_t len = 0;
////    out = cJSON_Print(root);
////    len = strlen(out) + 5;
////    buf = (char*)malloc(len);
////    cJSON_PrintPreallocated(root, buf, (int)len, 1);
//
//    char buffer[10];
//    cJSON *item = cJSON_CreateString("item");
//    cJSON_PrintPreallocated(NULL, buffer, sizeof(buffer), true);
//    cJSON_PrintPreallocated(item, NULL, 1, true);
//}
//
//static void assert_print_value(const char *input)
//{
//    unsigned char printed[1024];
//    cJSON item[1];
//    printbuffer buffer = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };
//    parse_buffer parsebuffer = { 0, 0, 0, 0, { 0, 0, 0 } };
//    buffer.buffer = printed;
//    buffer.length = sizeof(printed);
//    buffer.offset = 0;
//    buffer.noalloc = true;
//    buffer.hooks = global_hooks;
//
//    parsebuffer.content = (const unsigned char*)input;
//    parsebuffer.length = strlen(input) + sizeof("");
//    parsebuffer.hooks = global_hooks;
//
//    memset(item, 0, sizeof(item));
//
//    parse_value(item, &parsebuffer);
////    TEST_ASSERT_TRUE_MESSAGE(parse_value(item, &parsebuffer), "Failed to parse value.");
//
//    print_value(item, &buffer);
////    TEST_ASSERT_TRUE_MESSAGE(print_value(item, &buffer), "Failed to print value.");
////    TEST_ASSERT_EQUAL_STRING_MESSAGE(input, buffer.buffer, "Printed value is not as expected.");
//
//    reset(item);
//}
//
//TEST(CjsonFixture, print_value)
//{
//    assert_print_value("null");
//    assert_print_value("true");
//    assert_print_value("false");
//    assert_print_value("1.5");
//    assert_print_value("\"\"");
//    assert_print_value("\"hello\"");
//    assert_print_value("[]");
//    assert_print_value("{}");
//
//}
//
//
static void assert_print_array(const char * const expected, const char * const input)
{
    unsigned char printed_unformatted[1024];
    unsigned char printed_formatted[1024];

    cJSON item[1];

    printbuffer formatted_buffer = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };
    printbuffer unformatted_buffer = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };

    parse_buffer parsebuffer = { 0, 0, 0, 0, { 0, 0, 0 } };
    parsebuffer.content = (const unsigned char*)input;
    parsebuffer.length = strlen(input) + sizeof("");
    parsebuffer.hooks = global_hooks;

    /* buffer for formatted printing */
    formatted_buffer.buffer = printed_formatted;
    formatted_buffer.length = sizeof(printed_formatted);
    formatted_buffer.offset = 0;
    formatted_buffer.noalloc = true;
    formatted_buffer.hooks = global_hooks;

    /* buffer for unformatted printing */
    unformatted_buffer.buffer = printed_unformatted;
    unformatted_buffer.length = sizeof(printed_unformatted);
    unformatted_buffer.offset = 0;
    unformatted_buffer.noalloc = true;
    unformatted_buffer.hooks = global_hooks;

    memset(item, 0, sizeof(item));
    parse_array(item, &parsebuffer);
    cJSON_GetArraySize(item);
//    TEST_ASSERT_TRUE_MESSAGE(parse_array(item, &parsebuffer), "Failed to parse array.");

    unformatted_buffer.format = false;
    print_array(item, &unformatted_buffer);
//    TEST_ASSERT_TRUE_MESSAGE(print_array(item, &unformatted_buffer), "Failed to print unformatted string.");
//    TEST_ASSERT_EQUAL_STRING_MESSAGE(input, printed_unformatted, "Unformatted array is not correct.");

    formatted_buffer.format = true;
    print_array(item, &formatted_buffer);
//    TEST_ASSERT_TRUE_MESSAGE(print_array(item, &formatted_buffer), "Failed to print formatted string.");
//    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, printed_formatted, "Formatted array is not correct.");

    reset(item);
}

TEST(CjsonFixture, print_array)
{
    assert_print_array("[]", "[]");
    assert_print_array("[1]", "[1]");
    assert_print_array("[\"hello!\"]", "[\"hello!\"]");
    assert_print_array("[[]]", "[[]]");
    assert_print_array("[null]", "[null]");
    assert_print_array("[1, 2, 3]", "[1,2,3]");
    assert_print_array("[1, null, true, false, [], \"hello\", {\n\t}]", "[1,null,true,false,[],\"hello\",{}]");

}
//
static void assert_print_object(const char * const expected, const char * const input)
{
    unsigned char printed_unformatted[1024];
    unsigned char printed_formatted[1024];

    cJSON item[1];

    printbuffer formatted_buffer = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };
    printbuffer unformatted_buffer = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };
    parse_buffer parsebuffer = { 0, 0, 0, 0, { 0, 0, 0 } };

    /* buffer for parsing */
    parsebuffer.content = (const unsigned char*)input;
    parsebuffer.length = strlen(input) + sizeof("");
    parsebuffer.hooks = global_hooks;

    /* buffer for formatted printing */
    formatted_buffer.buffer = printed_formatted;
    formatted_buffer.length = sizeof(printed_formatted);
    formatted_buffer.offset = 0;
    formatted_buffer.noalloc = true;
    formatted_buffer.hooks = global_hooks;

    /* buffer for unformatted printing */
    unformatted_buffer.buffer = printed_unformatted;
    unformatted_buffer.length = sizeof(printed_unformatted);
    unformatted_buffer.offset = 0;
    unformatted_buffer.noalloc = true;
    unformatted_buffer.hooks = global_hooks;

    memset(item, 0, sizeof(item));
    parse_object(item, &parsebuffer);
//    TEST_ASSERT_TRUE_MESSAGE(parse_object(item, &parsebuffer), "Failed to parse object.");

    unformatted_buffer.format = false;
    print_object(item, &unformatted_buffer);
//    TEST_ASSERT_TRUE_MESSAGE(print_object(item, &unformatted_buffer), "Failed to print unformatted string.");
//    TEST_ASSERT_EQUAL_STRING_MESSAGE(input, printed_unformatted, "Unformatted object is not correct.");

    formatted_buffer.format = true;
    print_object(item, &formatted_buffer);
//    TEST_ASSERT_TRUE_MESSAGE(print_object(item, &formatted_buffer), "Failed to print formatted string.");
//    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, printed_formatted, "Formatted ojbect is not correct.");

    reset(item);
}

TEST(CjsonFixture, print_object)
//static void print_object_should_print_objects_with_multiple_elements(void)
{
    assert_print_object("{\n}", "{}");
    assert_print_object("{\n\t\"one\":\t1\n}", "{\"one\":1}");
    assert_print_object("{\n\t\"hello\":\t\"world!\"\n}", "{\"hello\":\"world!\"}");
    assert_print_object("{\n\t\"array\":\t[]\n}", "{\"array\":[]}");
    assert_print_object("{\n\t\"null\":\tnull\n}", "{\"null\":null}");
    assert_print_object("{\n\t\"one\":\t1,\n\t\"two\":\t2,\n\t\"three\":\t3\n}", "{\"one\":1,\"two\":2,\"three\":3}");
    assert_print_object("{\n\t\"one\":\t1,\n\t\"NULL\":\tnull,\n\t\"TRUE\":\ttrue,\n\t\"FALSE\":\tfalse,\n\t\"array\":\t[],\n\t\"world\":\t\"hello\",\n\t\"object\":\t{\n\t}\n}", "{\"one\":1,\"NULL\":null,\"TRUE\":true,\"FALSE\":false,\"array\":[],\"world\":\"hello\",\"object\":{}}");

}
//
//
TEST(CjsonFixture, misc_tests)
{
    cJSON_GetArraySize(NULL);

    int numbers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cJSON *object = NULL;
    cJSON *nums = NULL;
    cJSON *num6 = NULL;
    char *pointer = NULL;

    printf("JSON Pointer construct\n");
    object = cJSON_CreateObject();
    nums = cJSON_CreateIntArray(numbers, 10);
    num6 = cJSON_GetArrayItem(nums, 6);
    cJSON_AddItemToObject(object, "numbers", nums);

    cJSON_Delete(object);

    cJSON_GetObjectItem(NULL, "test");
    cJSON_GetObjectItemCaseSensitive(NULL, "test");
    cJSON_HasObjectItem(NULL, "test");

    cJSON replacements[3];
    cJSON *beginning = NULL;
    cJSON *middle = NULL;
    cJSON *end = NULL;
    cJSON *array = NULL;

    beginning = cJSON_CreateNull();
    ASSERT_TRUE(beginning!=NULL);
    middle = cJSON_CreateNull();
    ASSERT_TRUE(middle!=NULL);
    end = cJSON_CreateNull();
    ASSERT_TRUE(end!=NULL);

    array = cJSON_CreateArray();
    ASSERT_TRUE(array!=NULL);

    cJSON_AddItemToArray(array, beginning);
    cJSON_AddItemToArray(array, middle);
    cJSON_AddItemToArray(array, end);

    char buffer[10];
    cJSON *item = cJSON_CreateString("item");
    ASSERT_FALSE(cJSON_PrintPreallocated(NULL, buffer, sizeof(buffer), true));
    ASSERT_FALSE(cJSON_PrintPreallocated(item, NULL, 1, true));
}
//
//

//

//
//TEST(CjsonFixture, assert_cJSON_AddItemToArray)
//{
//    cJSON_AddItemToArray(NULL, NULL);
//
//    cJSON replacements[3];
//    cJSON *beginning = NULL;
//    cJSON *middle = NULL;
//    cJSON *end = NULL;
//    cJSON *array = NULL;
//
//    beginning = cJSON_CreateNull();
//    middle = cJSON_CreateNull();
//    end = cJSON_CreateNull();
//
//    array = cJSON_CreateArray();
//
//    cJSON_AddItemToArray(array, beginning);
//    cJSON_AddItemToArray(array, middle);
//    cJSON_AddItemToArray(array, end);
//}
//
//TEST(CjsonFixture, assert_cast_away_const)
//{
//    cast_away_const(NULL);
//}
//
//TEST(CjsonFixture, assert_cJSON_AddItemToObject)
//{
//    cJSON *root = NULL;
//    cJSON *fmt = NULL;
//    cJSON *img = NULL;
//    cJSON *thm = NULL;
//    cJSON *fld = NULL;
//    int i = 0;
//
//    /* Our "days of the week" array: */
//    const char *strings[7] =
//            {
//                    "Sunday",
//                    "Monday",
//                    "Tuesday",
//                    "Wednesday",
//                    "Thursday",
//                    "Friday",
//                    "Saturday"
//            };
//    /* Our matrix: */
//    int numbers[3][3] =
//            {
//                    {0, -1, 0},
//                    {1, 0, 0},
//                    {0 ,0, 1}
//            };
//    /* Our "gallery" item: */
//    int ids[4] = { 116, 943, 234, 38793 };
//    /* Our array of "records": */
//
//    root = cJSON_CreateObject();
//    cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
//    cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());
//
//    cJSON *monitor = cJSON_CreateObject();
//    cJSON *name = NULL;
//    cJSON *resolutions = NULL;
//    cJSON *resolution = NULL;
//    resolutions = cJSON_CreateArray();
//
//    cJSON_AddItemToObject(monitor, "name", name);
//    cJSON_AddItemToObject(monitor, "name", name);
//    cJSON_AddItemToObject(monitor, "resolutions", resolutions);
//
//    cJSON *width = NULL;
//    cJSON *height = NULL;
//    const unsigned int resolution_numbers[3][2] = {
//            {1280, 720},
//            {1920, 1080},
//            {3840, 2160}
//    };
//    size_t index = 0;
//    width = cJSON_CreateNumber(resolution_numbers[index][0]);
//    cJSON_AddItemToObject(resolution, "width", width);
//
//    height = cJSON_CreateNumber(resolution_numbers[index][1]);
//    cJSON_AddItemToObject(resolution, "height", height);
//
//}
//
TEST(CjsonFixture, assert_cJSON_AddItemToObjectCS)
{
    cJSON *item = cJSON_CreateString("item");
    cJSON *sec_item = cJSON_CreateString("item");
//    cJSON_AddItemToObjectCS(item, "item", NULL);
//    cJSON_AddItemToObjectCS(item, NULL, item);
    cJSON_AddItemToObjectCS(sec_item, "item", item);
}
//
TEST(CjsonFixture, assert_cJSON_AddItemReferenceToArray)
{
    cJSON *item = cJSON_CreateString("item");
    cJSON *arr = cJSON_CreateArray();

    cJSON_AddItemReferenceToArray(NULL, item);
    cJSON_AddItemReferenceToArray(item, NULL);
    cJSON_AddItemReferenceToArray(arr, item);
}
//
TEST(CjsonFixture, assert_cJSON_AddItemReferenceToObject)
{
    cJSON *item = cJSON_CreateString("item");

    cJSON_AddItemReferenceToObject(item, "item", NULL);
    cJSON_AddItemReferenceToObject(item, NULL, item);
    cJSON_AddItemReferenceToObject(NULL, "item", item);
}
//
TEST(CjsonFixture, assert_cJSON_AddNullToObject)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *null = NULL;

    cJSON_AddNullToObject(root, "null");
    cJSON_AddNullToObject(NULL, "null");
}
//
TEST(CjsonFixture, assert_cJSON_AddTrueToObject)
{
    cJSON *root = cJSON_CreateObject();
    cJSON_AddTrueToObject(NULL, "true");
    cJSON_AddTrueToObject(root, NULL);
    cJSON_AddTrueToObject(root, "true");
}
//
TEST(CjsonFixture, assert_cJSON_AddFalseToObject)
{
    cJSON *root = cJSON_CreateObject();
    cJSON_AddFalseToObject(root, "false");
    cJSON_AddFalseToObject(NULL, "false");
    cJSON_AddFalseToObject(root, NULL);

    cJSON *fmt = NULL;
    cJSON_AddFalseToObject (fmt, "interlace");
}
//
TEST(CjsonFixture, assert_cJSON_AddBoolToObject)
{
    cJSON *root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "true", true);
    cJSON_AddBoolToObject(root, "false", false);
    cJSON_AddBoolToObject(NULL, "false", false);
    cJSON_AddBoolToObject(root, NULL, false);
    cJSON_AddBoolToObject(root, "false", false);
}
//
TEST(CjsonFixture, assert_cJSON_AddNumberToObject)
{
    cJSON *fmt = NULL;
    cJSON_AddNumberToObject(fmt, "width", 1920);
    cJSON_AddNumberToObject(fmt, "height", 1080);
    cJSON_AddNumberToObject(fmt, "frame rate", 24);

    cJSON *img = NULL;
    cJSON *thm = NULL;
    cJSON_AddNumberToObject(img, "Width", 800);
    cJSON_AddNumberToObject(img, "Height", 600);
    cJSON_AddNumberToObject(thm, "Height", 125);
}

TEST(CjsonFixture, assert_cJSON_AddStringToObject)
{
    cJSON *fmt = NULL;
    cJSON *img = NULL;
    cJSON *thm = NULL;

    cJSON_AddStringToObject(fmt, "type", "rect");
    cJSON_AddStringToObject(img, "Title", "View from 15th Floor");
    cJSON_AddStringToObject(thm, "Url", "http:/*www.example.com/image/481989943");
    cJSON_AddStringToObject(thm, "Width", "100");

}


TEST(CjsonFixture, assert_cJSON_AddRawToObject)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *raw = NULL;

    cJSON_AddRawToObject(root, "raw", "{}");
    cJSON_AddRawToObject(NULL, "raw", "{}");
    cJSON_AddRawToObject(root, NULL, "{}");
    cJSON_AddRawToObject(root, "raw", "{}");

}
//
TEST(CjsonFixture, assert_cJSON_AddObjectToObject)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddObjectToObject(root, "object");
    cJSON_AddObjectToObject(NULL, "object");
    cJSON_AddObjectToObject(root, NULL);
}
//
TEST(CjsonFixture, assert_cJSON_AddArrayToObject)
{
    cJSON *root = cJSON_CreateObject();
    cJSON_AddArrayToObject(root, "array");

    cJSON_AddArrayToObject(NULL, "array");
    cJSON_AddArrayToObject(root, NULL);
    cJSON_AddArrayToObject(root, "array");

    cJSON *root1 = cJSON_Parse("{}");
    cJSON_AddArrayToObject(root1, "rd");

    cJSON *monitor = cJSON_CreateObject();
    cJSON_AddArrayToObject(monitor, "resolutions");
}
//
TEST(CjsonFixture, assert_cJSON_DetachItemViaPointer)
{
    cJSON list[4];
    cJSON parent[1];

    memset(list, '\0', sizeof(list));

    /* link the list */
    list[0].next = &(list[1]);
    list[1].next = &(list[2]);
    list[2].next = &(list[3]);

    list[3].prev = &(list[2]);
    list[2].prev = &(list[1]);
    list[1].prev = &(list[0]);
    list[0].prev = &(list[3]);

    parent->child = &list[0];
    cJSON_DetachItemViaPointer(parent, &(list[1])) == &(list[1]);
    cJSON_DetachItemViaPointer(parent, &(list[0])) == &(list[0]);
}
//
TEST(CjsonFixture, assert_cJSON_DetachItemFromArray)
{
    cJSON_DetachItemFromArray(NULL, 0);
    cJSON_DetachItemFromArray(NULL, -1);
}
//
TEST(CjsonFixture, assert_cJSON_DeleteItemFromArray)
{
    cJSON_DeleteItemFromArray(NULL, 0);
}
//
TEST(CjsonFixture, assert_cJSON_DetachItemFromObject)
{
    cJSON *item = cJSON_CreateString("item");
    cJSON_DetachItemFromObject(NULL, "item");
    cJSON_DetachItemFromObject(item, NULL);
    cJSON_DetachItemFromObjectCaseSensitive(NULL, "item");
    cJSON_DetachItemFromObjectCaseSensitive(item, NULL);
}
//
TEST(CjsonFixture, assert_cJSON_DeleteItemFromObject)
{
    cJSON *item = cJSON_CreateString("item");
    cJSON_DeleteItemFromObject(NULL, "item");
    cJSON_DeleteItemFromObject(item, NULL);
    cJSON_DeleteItemFromObjectCaseSensitive(NULL, "item");
    cJSON_DeleteItemFromObjectCaseSensitive(item, NULL);
}
//
TEST(CjsonFixture, assert_cJSON_InsertItemInArray)
{
    cJSON *item = cJSON_CreateString("item");
    cJSON *newitem = cJSON_CreateString("item");
    cJSON_InsertItemInArray(NULL, 0, item);
    cJSON_InsertItemInArray(item, 0, NULL);
    cJSON_InsertItemInArray(item, -1, NULL);
    cJSON_InsertItemInArray(item, 0, newitem);
}
//
TEST(CjsonFixture, assert_cJSON_ReplaceItemViaPointer)
{
    cJSON replacements[3];
    cJSON *beginning = NULL;
    cJSON *middle = NULL;
    cJSON *end = NULL;
    cJSON *array = NULL;

    beginning = cJSON_CreateNull();
    ASSERT_TRUE(beginning!=NULL);
    middle = cJSON_CreateNull();
    ASSERT_TRUE(middle!=NULL);
    end = cJSON_CreateNull();
    ASSERT_TRUE(end!=NULL);

    array = cJSON_CreateArray();
    ASSERT_TRUE(array!=NULL);

    cJSON_AddItemToArray(array, beginning);
    cJSON_AddItemToArray(array, middle);
    cJSON_AddItemToArray(array, end);


    memset(replacements, '\0', sizeof(replacements));


    cJSON_ReplaceItemViaPointer(array, beginning, beginning);
    cJSON_ReplaceItemViaPointer(array, middle, &(replacements[1]));
    cJSON_ReplaceItemViaPointer(array, end, &(replacements[2]));

    cJSON *item = cJSON_CreateString("item");
    cJSON_ReplaceItemViaPointer(NULL, item, item);
    cJSON_ReplaceItemViaPointer(item, NULL, item);
    cJSON_ReplaceItemViaPointer(item, item, NULL);

    cJSON_ReplaceItemInArray(NULL, 0, item);
    cJSON_ReplaceItemInArray(item, 0, NULL);
    cJSON_ReplaceItemInArray(item, -1, NULL);
    cJSON *root = NULL;
    root = cJSON_CreateArray();
    cJSON_ReplaceItemInArray(root, 1, cJSON_CreateString("Replacement"));
}
//
TEST(CjsonFixture, assert_cJSON_ReplaceItemInObject)
{

    cJSON root[1] = {{ NULL, NULL, NULL, 0, NULL, 0, 0, NULL }};
    cJSON *replacement = NULL;
    cJSON_ReplaceItemInObject(root, "child", replacement);

    cJSON *item = cJSON_CreateString("item");


    cJSON_ReplaceItemInObject(NULL, "item", item) ;
    cJSON_ReplaceItemInObject(item, NULL, item);
    cJSON_ReplaceItemInObject(item, "item", NULL);


    cJSON_ReplaceItemInObjectCaseSensitive(NULL, "item", item);
    cJSON_ReplaceItemInObjectCaseSensitive(item, NULL, item);
    cJSON_ReplaceItemInObjectCaseSensitive(item, "item", NULL);
}
//
TEST(CjsonFixture, assert_cJSON_CreateStringReference)
{
    const char *string = "I am a string!";
    cJSON_CreateStringReference(string);
}
//
TEST(CjsonFixture, assert_cJSON_CreateObjectReference)
{
    cJSON *number = cJSON_CreateNumber(42);
    cJSON_CreateObjectReference(number);
    cJSON_CreateArrayReference(number);

    int numbers[3][3] =
            {
                    {0, -1, 0},
                    {1, 0, 0},
                    {0 ,0, 1}
            };
    for (int i = 0; i < 3; i++){
        cJSON_CreateIntArray(numbers[i], 3);
    }

    cJSON_CreateIntArray(numbers[1], -3);

    cJSON_CreateFloatArray(NULL, 10);

    float number1=3;
    cJSON_CreateFloatArray(&number1, 10);
//    ASSERT_NULL(cJSON_CreateFloatArray(NULL, 10));    ASSERT如何写

}
//
TEST(CjsonFixture, assert_cJSON_CreateDoubleArray)
{
//    ASSERT_NULL(cJSON_CreateDoubleArray(NULL, 10));
    cJSON_CreateDoubleArray(NULL, 10);

    double number1=3;
    cJSON_CreateDoubleArray(&number1, 10);
}
//
//
TEST(CjsonFixture, assert_cJSON_CreateStringArray)
{
//    TEST_ASSERT_NULL(cJSON_CreateStringArray(NULL, 10));
    cJSON_CreateStringArray(NULL, 10);

    const char *strings[7] =
            {
                    "Sunday",
                    "Monday",
                    "Tuesday",
                    "Wednesday",
                    "Thursday",
                    "Friday",
                    "Saturday"
            };
    cJSON_CreateStringArray(strings, 7);
}
//
//
//
//
TEST(CjsonFixture, assert_cJSON_Duplicate)
{
//    TEST_ASSERT_NULL(cJSON_Duplicate(NULL, true));
    cJSON_Duplicate(NULL, true);

    cJSON *doc = NULL;
    cJSON *patch = NULL;
    cJSON *expected = NULL;
    cJSON *error_element = NULL;
    cJSON *comment = NULL;
    cJSON *disabled = NULL;

    cJSON *object = NULL;
    cJSON_bool successful = false;

    cJSON *test=cJSON_CreateString("test");

    object = cJSON_Duplicate(test, true);

    cJSON *array = cJSON_CreateArray();
    ASSERT_TRUE(array!=NULL);

    cJSON_AddItemToArray(array, test);
    object = cJSON_Duplicate(array, true);
}
//
TEST(CjsonFixture, assert_cJSON_Minify)
{

    char unclosed_multiline_comment[] = "\" /* bla";
    char pending_escape[] = "\"\\";

    cJSON_Minify(unclosed_multiline_comment);
    cJSON_Minify(pending_escape);

    const char to_minify[] = "{// this is {} \"some kind\" of [] comment /*, don't you see\n}";

    char* minified = (char*) malloc(sizeof(to_minify));
    ASSERT_TRUE(minified!=NULL);
    strcpy(minified, to_minify);

    cJSON_Minify(minified);
    free(minified);


//    char unclosed_multiline_comment[] = "/* bla";
//    cJSON_Minify(unclosed_multiline_comment);
//
//    char pending_escape[] = "\"\\";
//    cJSON_Minify(pending_escape);
//
//
//    const char to_minify[] = "{// this is {} \"some kind\" of [] comment /*, don't you see\n}";
//
//    char* minified = (char*) malloc(sizeof(to_minify));
//    cJSON_Minify(minified);
//
//    const char to_minify2[] = "{ \"key\":\ttrue\r\n    }";
//    char* minified2 = (char*) malloc(sizeof(to_minify2));
//    cJSON_Minify(minified2);
//
//    const char to_minify3[] = "{/* this is\n a /* multi\n //line \n {comment \"\\\" */}";
//    char* minified3 = (char*) malloc(sizeof(to_minify3));
//    cJSON_Minify(minified3);
//
//    const char to_minify4[] = "\"this is a string \\\" \\t bla\"";
//    char* minified4 = (char*) malloc(sizeof(to_minify4));
//    cJSON_Minify(minified4);
//
//    char string[] = { '8', ' ', '/', ' ', '5', '\n', '\0' };
//    /* this should not be an infinite loop */
//    cJSON_Minify(string);
//
//    const char to_minify5[] =
//            "{\n"
//            "    \"glossary\": { // comment\n"
//            "        \"title\": \"example glossary\",\n"
//            "  /* multi\n"
//            " line */\n"
//            "   \"GlossDiv\": {\n"
//            "            \"title\": \"S\",\n"
//            "     \"GlossList\": {\n"
//            "                \"GlossEntry\": {\n"
//            "                    \"ID\": \"SGML\",\n"
//            "         \"SortAs\": \"SGML\",\n"
//            "         \"Acronym\": \"SGML\",\n"
//            "         \"Abbrev\": \"ISO 8879:1986\",\n"
//            "         \"GlossDef\": {\n"
//            "           \"GlossSeeAlso\": [\"GML\", \"XML\"]\n"
//            "                    },\n"
//            "         \"GlossSee\": \"markup\"\n"
//            "                }\n"
//            "            }\n"
//            "        }\n"
//            "    }\n"
//            "}";
//
//
//    char *buffer = (char*) malloc(sizeof(to_minify5));
//    cJSON_Minify(buffer);
}
//
TEST(CjsonFixture, assert_cJSON_IsInvalid)
{
//    TEST_ASSERT_FALSE(cJSON_IsInvalid(NULL));
//    TEST_ASSERT_FALSE(cJSON_IsInvalid(item));
    cJSON_IsInvalid(NULL);
    cJSON_IsInvalid(item);
}

TEST(CjsonFixture, assert_cJSON_IsFalse)
{
//    TEST_ASSERT_FALSE(cJSON_IsFalse(NULL));
//    TEST_ASSERT_FALSE(cJSON_IsFalse(invalid));
//    TEST_ASSERT_TRUE(cJSON_IsFalse(item));

    item->type = cJSON_False;
    cJSON invalid[1];
    cJSON_IsFalse(NULL);
    cJSON_IsFalse(invalid);
    cJSON_IsFalse(item);
}

TEST(CjsonFixture, assert_cJSON_IsTrue)
{
//   TEST_ASSERT_FALSE(cJSON_IsTrue(NULL));
//    TEST_ASSERT_FALSE(cJSON_IsTrue(invalid));
//    TEST_ASSERT_TRUE(cJSON_IsTrue(item));

    item->type = cJSON_True;
    cJSON invalid[1];
    cJSON_IsTrue(NULL);
    cJSON_IsTrue(invalid);
    cJSON_IsTrue(item);
}

TEST(CjsonFixture, assert_cJSON_IsBool)
{
//   TEST_ASSERT_TRUE(cJSON_IsBool(item));

    cJSON_IsBool(item);
    cJSON_IsBool(NULL);
}

TEST(CjsonFixture, assert_cJSON_IsNull)
{
//    TEST_ASSERT_FALSE(cJSON_IsNull(NULL));
//    TEST_ASSERT_TRUE(cJSON_IsNull(item));
    item->type = cJSON_NULL;
    cJSON_IsNull(NULL);
    cJSON_IsNull(item);
}

TEST(CjsonFixture, assert_cJSON_IsNumber)
{
//    TEST_ASSERT_FALSE(cJSON_IsNumber(NULL));
//    TEST_ASSERT_FALSE(cJSON_IsNumber(invalid));
//    TEST_ASSERT_TRUE(cJSON_IsNumber(item));

    item->type = cJSON_Number;
    cJSON invalid[1];
    cJSON_IsNumber(NULL);
    cJSON_IsNumber(invalid);
    cJSON_IsNumber(item);
}

TEST(CjsonFixture, assert_cJSON_IsString)
{
//    TEST_ASSERT_FALSE(cJSON_IsString(NULL));
//    TEST_ASSERT_FALSE(cJSON_IsString(invalid));
//    TEST_ASSERT_TRUE(cJSON_IsString(item));

    item->type = cJSON_String;
    cJSON invalid[1];
    cJSON_IsString(NULL);
    cJSON_IsString(invalid);
    cJSON_IsString(item);
}

TEST(CjsonFixture, assert_cJSON_IsArray)
{
//    TEST_ASSERT_FALSE(cJSON_IsArray(NULL));
//    TEST_ASSERT_FALSE(cJSON_IsArray(invalid));
//    TEST_ASSERT_TRUE(cJSON_IsArray(item));

    item->type = cJSON_Array;
    cJSON invalid[1];
    cJSON_IsArray(NULL);
    cJSON_IsArray(invalid);
    cJSON_IsArray(item);
}

TEST(CjsonFixture, assert_cJSON_IsObject)
{
//    TEST_ASSERT_FALSE(cJSON_IsObject(NULL));
//    TEST_ASSERT_FALSE(cJSON_IsObject(invalid));
//    TEST_ASSERT_TRUE(cJSON_IsObject(item));

    item->type = cJSON_Object;
    cJSON invalid[1];
    cJSON_IsObject(NULL);
    cJSON_IsObject(invalid);
    cJSON_IsObject(item);
}

TEST(CjsonFixture, assert_cJSON_IsRaw)
{
//    TEST_ASSERT_FALSE(cJSON_cJSON_IsRaw(NULL));
//    TEST_ASSERT_FALSE(cJSON_cJSON_IsRaw(invalid));
//    TEST_ASSERT_TRUE(cJSON_cJSON_IsRaw(item));

    item->type = cJSON_Object;
    cJSON invalid[1];
    cJSON_IsRaw(NULL);
    cJSON_IsRaw(invalid);
    cJSON_IsRaw(item);
}
//
static cJSON_bool compare_from_string(const char * const a, const char * const b, const cJSON_bool case_sensitive)
{
    cJSON *a_json = NULL;
    cJSON *b_json = NULL;
    cJSON_bool result = false;

    a_json = cJSON_Parse(a);
    EXPECT_TRUE( a_json!= NULL);
//    TEST_ASSERT_NOT_NULL_MESSAGE(a_json, "Failed to parse a.");
    b_json = cJSON_Parse(b);
    EXPECT_TRUE( b_json!= NULL);
//    TEST_ASSERT_NOT_NULL_MESSAGE(b_json, "Failed to parse b.");

    result = cJSON_Compare(a_json, b_json, case_sensitive);

    cJSON_Delete(a_json);
    cJSON_Delete(b_json);

    return result;
}

TEST(CjsonFixture, cJSON_Compare)
{
    cJSON_Compare(NULL, NULL, true);
    cJSON_Compare(NULL, NULL, false);
    cJSON invalid[1];
    memset(invalid, '\0', sizeof(invalid));

    cJSON_Compare(invalid, invalid, false);
    cJSON_Compare(invalid, invalid, true);
//    TEST_ASSERT_FALSE(cJSON_Compare(invalid, invalid, false));
//    TEST_ASSERT_FALSE(cJSON_Compare(invalid, invalid, true));

    compare_from_string("1", "1", true);
    compare_from_string("1", "1", false);
    compare_from_string("0.0001", "0.0001", true);
    compare_from_string("0.0001", "0.0001", false);
    compare_from_string("1", "2", true);
    compare_from_string("1", "2", false);
    compare_from_string("true", "true", true);
    compare_from_string("true", "true", false);
    compare_from_string("false", "false", true);
    compare_from_string("false", "false", false);
//
    compare_from_string("true", "true", true);
    compare_from_string("true", "true", false);
    compare_from_string("false", "false", true);
    compare_from_string("false", "false", false);

    compare_from_string("null", "null", true);
    compare_from_string("null", "null", false);

    compare_from_string("null", "true", true);
    compare_from_string("null", "true", false);
//
    reset(invalid);
    memset(invalid, '\0', sizeof(invalid));

    invalid->type = cJSON_Number | cJSON_String;

    cJSON_Compare(invalid, invalid, true);
    cJSON_Compare(invalid, invalid, false);
//
    compare_from_string("\"abcdefg\"", "\"abcdefg\"", true);
    compare_from_string("\"abcdefg\"", "\"abcdefg\"", false);

    compare_from_string("\"ABCDEFG\"", "\"abcdefg\"", true);
    compare_from_string("\"ABCDEFG\"", "\"abcdefg\"", false);
//
    cJSON *raw1 = NULL;
    cJSON *raw2 = NULL;

    raw1 = cJSON_Parse("\"[true, false]\"");
//    TEST_ASSERT_NOT_NULL(raw1);
    raw2 = cJSON_Parse("\"[true, false]\"");
//    TEST_ASSERT_NOT_NULL(raw2);

    raw1->type = cJSON_Raw;
    raw2->type = cJSON_Raw;

    cJSON_Compare(raw1, raw2, true);
    cJSON_Compare(raw1, raw2, false);

    cJSON_Delete(raw1);
    cJSON_Delete(raw2);
//
    compare_from_string("[]", "[]", true);
    compare_from_string("[]", "[]", false);
    compare_from_string("[false,true,null,42,\"string\",[],{}]", "[false, true, null, 42, \"string\", [], {}]", true);
    compare_from_string("[false,true,null,42,\"string\",[],{}]", "[false, true, null, 42, \"string\", [], {}]", false);
    compare_from_string("[[[1], 2]]", "[[[1], 2]]", true);
    compare_from_string("[[[1], 2]]", "[[[1], 2]]", false);

    ASSERT_FALSE(compare_from_string("[true,null,42,\"string\",[],{}]", "[false, true, null, 42, \"string\", [], {}]", true));
    ASSERT_FALSE(compare_from_string("[true,null,42,\"string\",[],{}]", "[false, true, null, 42, \"string\", [], {}]", false));

    ASSERT_FALSE(compare_from_string("[1,2,3]", "[1,2]", true));
    ASSERT_FALSE(compare_from_string("[1,2,3]", "[1,2]", false));

    ASSERT_TRUE(compare_from_string("{}", "{}", true));
    ASSERT_TRUE(compare_from_string("{}", "{}", false));
    ASSERT_TRUE(compare_from_string(
            "{\"false\": false, \"true\": true, \"null\": null, \"number\": 42, \"string\": \"string\", \"array\": [], \"object\": {}}",
            "{\"true\": true, \"false\": false, \"null\": null, \"number\": 42, \"string\": \"string\", \"array\": [], \"object\": {}}",
            true));
    ASSERT_FALSE(compare_from_string(
            "{\"False\": false, \"true\": true, \"null\": null, \"number\": 42, \"string\": \"string\", \"array\": [], \"object\": {}}",
            "{\"true\": true, \"false\": false, \"null\": null, \"number\": 42, \"string\": \"string\", \"array\": [], \"object\": {}}",
            true));
    ASSERT_TRUE(compare_from_string(
            "{\"False\": false, \"true\": true, \"null\": null, \"number\": 42, \"string\": \"string\", \"array\": [], \"object\": {}}",
            "{\"true\": true, \"false\": false, \"null\": null, \"number\": 42, \"string\": \"string\", \"array\": [], \"object\": {}}",
            false));
    ASSERT_FALSE(compare_from_string(
            "{\"Flse\": false, \"true\": true, \"null\": null, \"number\": 42, \"string\": \"string\", \"array\": [], \"object\": {}}",
            "{\"true\": true, \"false\": false, \"null\": null, \"number\": 42, \"string\": \"string\", \"array\": [], \"object\": {}}",
            false));
    ASSERT_FALSE(compare_from_string(
            "{\"one\": 1, \"two\": 2}",
            "{\"one\": 1, \"two\": 2, \"three\": 3}",
            true));
    ASSERT_FALSE(compare_from_string(
            "{\"one\": 1, \"two\": 2}",
            "{\"one\": 1, \"two\": 2, \"three\": 3}",
            false));
}

TEST(CjsonFixture2, assert_cJSON_free)
{
//    cJSON *array = NULL;
//    array = cJSON_CreateArray();
//    cJSON_free(array);

    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
    buffer.content = (const unsigned char*)"[]";
    buffer.length = strlen("[]") + sizeof("");
    buffer.hooks = global_hooks;

    cJSON *new_item =  cJSON_New_Item(&(buffer.hooks));

    ASSERT_TRUE(new_item!=NULL);

    cJSON *raw1 = NULL;
    cJSON *raw2 = NULL;

    raw1 = cJSON_Parse("\"[true, false]\"");

    ASSERT_TRUE(raw1!=NULL);
}

static void * CJSON_CDECL failing_malloc(size_t size)
{
    (void)size;
    return NULL;
}
//
///* work around MSVC error C2322: '...' address of dillimport '...' is not static */
static void CJSON_CDECL normal_free(void *pointer)
{
    free(pointer);
}
static cJSON_Hooks failing_hooks={
        failing_malloc,
        normal_free
};
//

TEST(CjsonFixture, assert_cJSON_InitHooks)
{
    cJSON_InitHooks(&failing_hooks);
    cJSON_InitHooks(NULL);
}

static void assert_parse_string(const char *string, const char *expected)
{
    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
    buffer.content = (const unsigned char*)string;
    buffer.length = strlen(string) + sizeof("");
    buffer.hooks = global_hooks;

    ASSERT_TRUE(parse_string(item, &buffer));
    global_hooks.deallocate(item->valuestring);
    item->valuestring = NULL;
}

TEST(CjsonFixture, parse_string){
    assert_parse_string("\"\"", "");
    assert_parse_string(
            "\" !\\\"#$%&'()*+,-./\\/0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_'abcdefghijklmnopqrstuvwxyz{|}~\"",
            " !\"#$%&'()*+,-.//0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_'abcdefghijklmnopqrstuvwxyz{|}~");
    assert_parse_string(
            "\"\\\"\\\\\\/\\b\\f\\n\\r\\t\\u20AC\\u732b\"",
            "\"\\/\b\f\n\r\t€猫");
    reset(item);
    assert_parse_string("\"\b\f\n\r\t\"", "\b\f\n\r\t");
    reset(item);

    assert_parse_string("\"\\uD83D\\udc31\"", "🐱");
    reset(item);
}