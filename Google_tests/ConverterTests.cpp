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
static void assert_has_type(cJSON *object_item, int expect_type){
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

TEST_F(CjsonFixture, parse_empty_objects){
    assert_parse_object("{}");
    assert_parse_object("{\n\t}");
}

TEST_F(CjsonFixture, parse_object_should_parse_objects_with_one_element){
    assert_parse_object("{\"one\":1}");
//    assert_is_child(item->child, "one", cJSON_Number);
    reset(item);

    assert_parse_object("{\"hello\":\"world!\"}");
//    assert_is_child(item->child, "hello", cJSON_String);
    reset(item);

    assert_parse_object("{\"array\":[]}");
//    assert_is_child(item->child, "array", cJSON_Array);
    reset(item);

    assert_parse_object("{\"null\":null}");
//    assert_is_child(item->child, "null", cJSON_NULL);
    reset(item);
}
TEST_F(CjsonFixture, parse_object_should_parse_objects_with_multiple_elements)
{
    assert_parse_object("{\"one\":1\t,\t\"two\"\n:2, \"three\":3}");
//    assert_is_child(item->child, "one", cJSON_Number);
//    assert_is_child(item->child->next, "two", cJSON_Number);
//    assert_is_child(item->child->next->next, "three", cJSON_Number);
    reset(item);

    {
        size_t i = 0;
        cJSON *node = NULL;
        int expected_types[7] =
                {
                        cJSON_Number,
                        cJSON_NULL,
                        cJSON_True,
                        cJSON_False,
                        cJSON_Array,
                        cJSON_String,
                        cJSON_Object
                };
        const char *expected_names[7] =
                {
                        "one",
                        "NULL",
                        "TRUE",
                        "FALSE",
                        "array",
                        "world",
                        "object"
                };
        assert_parse_object("{\"one\":1, \"NULL\":null, \"TRUE\":true, \"FALSE\":false, \"array\":[], \"world\":\"hello\", \"object\":{}}");

        node = item->child;
        for (
                i = 0;
                (i < (sizeof(expected_types)/sizeof(int)))
                && (node != NULL);
                (void)i++, node = node->next)
        {
//            assert_is_child(node, expected_names[i], expected_types[i]);
        }
//        TEST_ASSERT_EQUAL_INT(i, 7);
        reset(item);
    }
}

static void assert_parse_array(const char *json)
{
    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
    buffer.content = (const unsigned char*)json;
    buffer.length = strlen(json) + sizeof("");
    buffer.hooks = global_hooks;

    ASSERT_TRUE(parse_array(item, &buffer));
//    assert_is_array(item);
}

TEST_F(CjsonFixture, parse_array_should_parse_empty_arrays)
//static void parse_array_should_parse_empty_arrays(void)
{
    assert_parse_array("[]");
//    assert_has_no_child(item);

    assert_parse_array("[\n\t]");
//    assert_has_no_child(item);
}
TEST_F(CjsonFixture, parse_array_should_parse_arrays_with_one_element)
{

    assert_parse_array("[1]");
//    assert_has_child(item);
    assert_has_type(item->child, cJSON_Number);
    reset(item);

    assert_parse_array("[\"hello!\"]");
//    assert_has_child(item);
    assert_has_type(item->child, cJSON_String);
    ASSERT_STREQ("hello!", item->child->valuestring);
    reset(item);

    assert_parse_array("[[]]");
//    assert_has_child(item);
//    assert_is_array(item->child);
//    assert_has_no_child(item->child);
    reset(item);

    assert_parse_array("[null]");
//    assert_has_child(item);
    assert_has_type(item->child, cJSON_NULL);
    reset(item);
}
TEST_F(CjsonFixture, parse_array_should_parse_arrays_with_multiple_elements)
{
    assert_parse_array("[1\t,\n2, 3]");
//    assert_has_child(item);
//    TEST_ASSERT_NOT_NULL(item->child->next);
//    TEST_ASSERT_NOT_NULL(item->child->next->next);
//    TEST_ASSERT_NULL(item->child->next->next->next);
    assert_has_type(item->child, cJSON_Number);
    assert_has_type(item->child->next, cJSON_Number);
    assert_has_type(item->child->next->next, cJSON_Number);
    reset(item);

    {
        size_t i = 0;
        cJSON *node = NULL;
        int expected_types[7] =
                {
                        cJSON_Number,
                        cJSON_NULL,
                        cJSON_True,
                        cJSON_False,
                        cJSON_Array,
                        cJSON_String,
                        cJSON_Object
                };
        assert_parse_array("[1, null, true, false, [], \"hello\", {}]");

        node = item->child;
        for (
                i = 0;
                (i < (sizeof(expected_types)/sizeof(int)))
                && (node != NULL);
                (void)i++, node = node->next)
        {
//            TEST_ASSERT_BITS(0xFF, expected_types[i], node->type);
        }
//        TEST_ASSERT_EQUAL_INT(i, 7);
        reset(item);
    }
}

static void assert_parse_number(const char *string, int integer, double real)
{
    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
    buffer.content = (const unsigned char*)string;
    buffer.length = strlen(string) + sizeof("");

    ASSERT_TRUE(parse_number(item, &buffer));
//    assert_is_number(item);
    ASSERT_EQ(integer, item->valueint);
    ASSERT_DOUBLE_EQ(real, item->valuedouble);
}
TEST_F(CjsonFixture, parse_number_should_parse_zero)
{
    assert_parse_number("0", 0, 0);
    assert_parse_number("0.0", 0, 0.0);
    assert_parse_number("-0", 0, -0.0);
}

TEST_F(CjsonFixture, parse_number_should_parse_negative_integers)
{
    assert_parse_number("-1", -1, -1);
    assert_parse_number("-32768", -32768, -32768.0);
    assert_parse_number("-2147483648", (int)-2147483648.0, -2147483648.0);
}

static void parse_number_should_parse_positive_integers(void)
{
    assert_parse_number("1", 1, 1);
    assert_parse_number("32767", 32767, 32767.0);
    assert_parse_number("2147483647", (int)2147483647.0, 2147483647.0);
}
TEST_F(CjsonFixture, parse_number_should_parse_positive_reals)
{
    assert_parse_number("0.001", 0, 0.001);
    assert_parse_number("10e-10", 0, 10e-10);
    assert_parse_number("10E-10", 0, 10e-10);
    assert_parse_number("10e10", INT_MAX, 10e10);
    assert_parse_number("123e+127", INT_MAX, 123e127);
    assert_parse_number("123e-128", 0, 123e-128);
}
TEST_F(CjsonFixture, parse_number_should_parse_negative_reals)
{
    assert_parse_number("-0.001", 0, -0.001);
    assert_parse_number("-10e-10", 0, -10e-10);
    assert_parse_number("-10E-10", 0, -10e-10);
    assert_parse_number("-10e20", INT_MIN, -10e20);
    assert_parse_number("-123e+127", INT_MIN, -123e127);
    assert_parse_number("-123e-128", 0, -123e-128);
}


