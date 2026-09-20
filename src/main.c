#include "stdio.h"

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"

void init() {
  sg_setup(&(sg_desc){
      .environment = sglue_environment(),
  });
}

void frame() {}

void cleanup() { sg_shutdown(); }

void event(const sapp_event *ev) {
  if (ev->type == SAPP_EVENTTYPE_KEY_DOWN) {
    if (ev->key_code == SAPP_KEYCODE_ESCAPE) {
      printf("Goodbye!\n");
      sapp_quit();
    }
  }
};

sapp_desc sokol_main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
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
