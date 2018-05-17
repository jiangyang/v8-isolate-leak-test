#include "v8/include/v8.h"
#include "v8/include/libplatform/libplatform.h"

int main(int argc, char* argv[]) {
  v8::V8::InitializeICUDefaultLocation(V8_LIB_FULL_PATH);
  v8::V8::InitializeExternalStartupData(V8_LIB_FULL_PATH);
  std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
  v8::V8::InitializePlatform(platform.get());
  v8::V8::Initialize();
  for (auto i = 0; i < 1000000000; ++i) {
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate* isolate = v8::Isolate::New(create_params);
    isolate->Dispose();
    delete create_params.array_buffer_allocator;
    isolate = nullptr;
  }
  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
}