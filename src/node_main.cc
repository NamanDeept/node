
#include "public/tests/commons/common-posix.h"

void sampleMethod(JS_Value *params, int argc) {
  JS_Value obj;
  JS_CreateEmptyObject(obj);
  JS_SetNamedProperty(obj, "i1", params[0]);
  JS_SetNamedProperty(obj, "i2", params[1]);

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

printf(">> closing %d \n", JS_IsFunction(smethod));
  JS_StopEngine();
}

// 
// #include "node.h"
// #include "public/node_internal_wrapper.h"
// 
// #ifdef _WIN32
// #include <VersionHelpers.h>
// 
// int wmain(int argc, wchar_t *wargv[]) {
//   if (!IsWindows7OrGreater()) {
//     fprintf(stderr, "This application is only supported on Windows 7, "
//                     "Windows Server 2008 R2, or higher.");
//     exit(1);
//   }
// 
//   // Convert argv to to UTF8
//   char** argv = new char*[argc + 1];
//   for (int i = 0; i < argc; i++) {
//     // Compute the size of the required buffer
//     DWORD size = WideCharToMultiByte(CP_UTF8,
//                                      0,
//                                      wargv[i],
//                                      -1,
//                                      nullptr,
//                                      0,
//                                      nullptr,
//                                      nullptr);
//     if (size == 0) {
//       // This should never happen.
//       fprintf(stderr, "Could not convert arguments to utf8.");
//       exit(1);
//     }
//     // Do the actual conversion
//     argv[i] = new char[size];
//     DWORD result = WideCharToMultiByte(CP_UTF8,
//                                        0,
//                                        wargv[i],
//                                        -1,
//                                        argv[i],
//                                        size,
//                                        nullptr,
//                                        nullptr);
//     if (result == 0) {
//       // This should never happen.
//       fprintf(stderr, "Could not convert arguments to utf8.");
//       exit(1);
//     }
//   }
//   argv[argc] = nullptr;
//   // Now that conversion is done, we can finally start.
//   return node::Start(argc, argv);
// }
// #else
// // UNIX
// int main(int argc, char *argv[]) {
//   setvbuf(stderr, NULL, _IOLBF, 1024);
//   node::__Start(argc, argv);
//   while(node::__Loop(true));
//   return node::__Shutdown();
// }
// #endif
