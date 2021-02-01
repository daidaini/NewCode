#ifndef __h_test_common_h__
#define __h_test_common_h__

extern char message_buffer[4096];

void throw_exception(const char* msg);

#define ASSERT_TRUE(value1) \
	if (!(value1)){				\
		::memset(message_buffer, 0, sizeof(message_buffer));	\
		sprintf(message_buffer, "%s(%d), (%s)\n", __FILE__, __LINE__, #value1);\
		throw_exception(message_buffer);	\
		}

#define ASSERT_FALSE(value1) \
	if ((value1)){				\
		::memset(message_buffer, 0, sizeof(message_buffer));	\
		sprintf(message_buffer, "%s(%d), (%s)\n", __FILE__, __LINE__, #value1);\
		throw_exception(message_buffer);	\
			}

#define ASSERT_NOT_EQUAL(value1, value2)	\
	if ((value1) == (value2)){				\
		::memset(message_buffer, 0, sizeof(message_buffer));	\
		sprintf(message_buffer, "%s(%d), (%s) == (%s)\n", __FILE__, __LINE__, #value1, #value2);\
		throw_exception(message_buffer);	\
	}

#define ASSERT_EQUAL(value1, value2)		\
	if ((value1) != (value2)){				\
		::memset(message_buffer, 0, sizeof(message_buffer));	\
		sprintf(message_buffer, "%s(%d), (%s) != (%s)\n", __FILE__, __LINE__, #value1, #value2);\
		throw_exception(message_buffer);	\
	}

#define ASSERT_LESS(value1, value2)			\
	if ((value1) >= (value2)){				\
		::memset(message_buffer, 0, sizeof(message_buffer));	\
		sprintf(message_buffer, "%s(%d), (%s) >= (%s)\n", __FILE__, __LINE__, #value1, #value2);\
		throw_exception(message_buffer);	\
	}

#define ASSERT_LESS_EQUAL(value1, value2)	\
	if ((value1) > (value2)){				\
		::memset(message_buffer, 0, sizeof(message_buffer));	\
		sprintf(message_buffer, "%s(%d), (%s) > (%s)\n", __FILE__, __LINE__, #value1, #value2);	\
		throw_exception(message_buffer);	\
	}

#define ASSERT_GREAT(value1, value2)		\
	if ((value1) <= (value2)){				\
		::memset(message_buffer, 0, sizeof(message_buffer));	\
		sprintf(message_buffer, "%s(%d), (%s) <= (%s)\n", __FILE__, __LINE__, #value1, #value2);\
		throw_exception(message_buffer);	\
	}

#define ASSERT_GREAT_EQUAL(value1, value2)	\
	if ((value1) < (value2)){				\
		::memset(message_buffer, 0, sizeof(message_buffer));	\
		sprintf(message_buffer, "%s(%d), (%s) < (%s)\n", __FILE__, __LINE__, #value1, #value2);	\
		throw_exception(message_buffer);	\
	}


#endif