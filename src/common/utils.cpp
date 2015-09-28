#include "edge_common.h"

Handle<Value> throwV8Exception(Handle<Value> exception)
{
    NanEscapableScope();
    NanThrowError(exception);
    return NanEscapeScope(exception);
}

Handle<Value> throwV8Exception(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	size_t size = vsnprintf(NULL, 0, format, args);
	char* message = new char[size + 1];

	vsnprintf(message, size + 1, format, args);

	NanEscapableScope();

	Handle<v8::Object> exception = NanNew<v8::Object>();
	exception->SetPrototype(v8::Exception::Error(NanNew<v8::String>(message)));

	Handle<v8::Value> exceptionValue = exception;
	NanThrowError(exceptionValue);

	return NanEscapeScope(exception);
}