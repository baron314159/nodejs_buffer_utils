
#include <node.h>
#include <node_buffer.h>
#include <v8.h>

using namespace v8;
using namespace node;

Handle<Value> IndexOf(const Arguments &args) {
	HandleScope scope;

	if (args.Length() < 3) {
		ThrowException(Exception::TypeError(
			String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}

	if (!Buffer::HasInstance(args[0])) {
		ThrowException(Exception::TypeError(
			String::New("Argument 1 must be a Buffer")));
		return scope.Close(Undefined());
	}

	if (!args[1]->IsNumber()) {
		ThrowException(Exception::TypeError(
			String::New("Argument 2 must be a number")));
		return scope.Close(Undefined());
	}

	if (!args[2]->IsNumber()) {
		ThrowException(Exception::TypeError(
			String::New("Argument 3 must be a number")));
		return scope.Close(Undefined());
	}

	Local<Object> bufferObj = args[0]->ToObject();
	char *data = Buffer::Data(bufferObj);
	size_t length = Buffer::Length(bufferObj);
	int64_t needle = args[1]->IntegerValue();
	int64_t start = args[2]->IntegerValue();

	for (size_t i=start; i < length; i++) {
		if (data[i] == needle) {
			return scope.Close(Number::New(i));
		}
	}

	return scope.Close(False());
}

void init(Handle<Object> target) {
	target->Set(String::NewSymbol("indexOf"),
		FunctionTemplate::New(IndexOf)->GetFunction());
}

NODE_MODULE(buffer_utils, init)
