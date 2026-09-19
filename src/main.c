#include "stdio.h"

#define SOKOL_IMPL
#include "sokol_app.h"

void init() {}

void frame() {}

void cleanup() {}

void event([[maybe_unused]] const sapp_event *event) {};

sapp_desc sokol_main([[maybe_unused]]int argc,[[maybe_unused]] char *argv[]) {
  printf("Hello world \n");

  return (sapp_desc){
      .width = 640,
      .height = 480,
      .init_cb = init,
      .frame_cb = frame,
      .cleanup_cb = cleanup,
      .event_cb = event,
  };
}
