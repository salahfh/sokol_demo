#include "stdio.h"

// sokol
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"

// shaders
#define SOKOL_SHDC_IMPL
#include "shd.glsl.h"

static struct {
  sg_pipeline pip;
  sg_bindings bind;
  sg_pass_action pass_action;
} state;

void init(void) {
  sg_setup(&(sg_desc){
      .environment = sglue_environment(),
  });

  float vertices[] = {
      // position         //  colors
      0.0f,  0.5f,  0.5f, //  1.0f, 0.0f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f, //  0.0f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, //  0.0f, 0.0f, 1.0f, 1.0f};
  };

  state.bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
      .data = SG_RANGE(vertices),
      .label = "triangle_verties",
  });

  sg_shader shd = sg_make_shader(shd_shader_desc(sg_query_backend()));

  state.pip = sg_make_pipeline(&(sg_pipeline_desc){
      .shader = shd,
      .layout =
          {
              .attrs = {[ATTR_shd_pos].format = SG_VERTEXFORMAT_FLOAT3},

          },
      .label = "shader"});

  state.pass_action =
      (sg_pass_action){.colors[0] = {.load_action = SG_LOADACTION_CLEAR,
                                     .clear_value = {.2f, .2f, .2f, 1.0f}}};
}

void frame() {
  sg_begin_pass(&(sg_pass){
      .action = state.pass_action,
      .swapchain = sglue_swapchain(),
  });

  sg_apply_pipeline(state.pip);
  sg_apply_bindings(&state.bind);
  sg_draw(0, 3, 1);

  sg_end_pass();
  sg_commit();
}

void event(const sapp_event *ev) {
  if (ev->type == SAPP_EVENTTYPE_KEY_DOWN) {
    if (ev->key_code == SAPP_KEYCODE_ESCAPE) {
      printf("Goodbye!\n");
      sapp_quit();
    }
  }
};

void cleanup() { sg_shutdown(); }

sapp_desc sokol_main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {

  return (sapp_desc){
      .width = 640,
      .height = 480,
      .init_cb = init,
      .frame_cb = frame,
      .cleanup_cb = cleanup,
      .event_cb = event,
  };
}
