// See LICENSE file

#ifndef SRC_NODE_WRAPPER_H
#define SRC_NODE_WRAPPER_H

namespace node {

class Environment;

Environment* __GetNodeEnvironment();
void __StartNodeInstance(void* arg);
bool __Loop(bool once);
void __Start(int argc, char** argv);
int __Shutdown();

} // namespace node

#endif // SRC_NODE_WRAPPER_H
