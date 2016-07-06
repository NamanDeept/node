#include "node.h"
#include "node_internals.h"
#include "node_watchdog.h"
#include "base-object.h"
#include "base-object-inl.h"
#include "env.h"
#include "env-inl.h"
#include "util.h"
#include "util-inl.h"
#include "v8-debug.h"
#include <map>

namespace node {

using v8::Array;
using v8::ArrayBuffer;
using v8::Boolean;
using v8::Context;
using v8::Debug;
using v8::EscapableHandleScope;
using v8::External;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::HandleScope;
using v8::Integer;
using v8::Isolate;
using v8::Local;
using v8::Maybe;
using v8::MaybeLocal;
using v8::Name;
using v8::NamedPropertyHandlerConfiguration;
using v8::Object;
using v8::ObjectTemplate;
using v8::Persistent;
using v8::PropertyAttribute;
using v8::PropertyCallbackInfo;
using v8::Script;
using v8::ScriptCompiler;
using v8::ScriptOrigin;
using v8::String;
using v8::TryCatch;
using v8::Uint8Array;
using v8::UnboundScript;
using v8::V8;
using v8::Value;
using v8::WeakCallbackInfo;

static std::map<const char*, const char*> files;

void AddFile(const char *path, const char *contents) {
  files[path] = contents;
}

class NodeWrapVFile {
 public:
  static void GetFileData(const FunctionCallbackInfo<Value>& args) {
    Local<Boolean> value = True(args.GetIsolate());
    args.GetReturnValue().Set(value);
  }

  static void GetContents(const FunctionCallbackInfo<Value>& args) {
    Local<Boolean> value = True(args.GetIsolate());
    args.GetReturnValue().Set(value);
  }

  static void Init(Environment* env, Local<Object> target) {
    Local<FunctionTemplate> function_template =
        FunctionTemplate::New(env->isolate());
    function_template->InstanceTemplate()->SetInternalFieldCount(1);
    env->set_script_data_constructor_function(function_template->GetFunction());

    env->SetMethod(target, "getFileData", GetFileData);
    env->SetMethod(target, "getContents", GetContents);
  }
};

void VFileInitialize(Local<Object> target,
                    Local<Value> unused,
                    Local<Context> context) {
  Environment* env = Environment::GetCurrent(context);
  NodeWrapVFile::Init(env, target);
}

}  // namespace node

NODE_MODULE_CONTEXT_AWARE_BUILTIN(node_wrap_vfile, node::VFileInitialize)
