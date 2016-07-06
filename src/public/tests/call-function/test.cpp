#include "tests/commons/common-posix.h"

void sampleMethod(JS_Value *params, int argc) {
  printf("Called\n");
  JS_Value obj;
  JS_New(obj);

  // return
  JS_SetObject(params[argc], obj);
  JS_Free(obj);
}

int main(int argc, char **args) {
  JS_StartEngine(argc, args);

  JS_SetProcessNative("sampleMethod", sampleMethod);

  while (JS_LoopOnce() != 0) usleep(1);

  JS_Value process;
  JS_GetProcessObject(process);

  JS_Value natives;
  JS_GetNamedProperty(process, "natives", natives);

  JS_Value smethod;
  JS_GetNamedProperty(natives, "sampleMethod", smethod);

  JS_Value out;
  JS_CallFunction(smethod, nullptr, 0, &out);

  assert(JS_IsUndefined(out));
  JS_Free(out);

  JS_StopEngine();
}
