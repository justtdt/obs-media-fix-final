#include <obs-module.h>
#include <string.h>

OBS_DECLARE_MODULE()
const char *obs_module_name() { return "Global Media Auto Fixer"; }

// 核心修复逻辑
static bool fix_source_callback(void *unused, obs_source_t *source) {
    if (!source) return true;

    const char *id = obs_source_get_unversioned_id(source);
    // 只针对媒体源 (ffmpeg_source)
    if (id && strcmp(id, "ffmpeg_source") == 0) {
        obs_data_t *settings = obs_source_get_settings(source);
        if (settings) {
            // 检查并强制设置
            obs_data_set_bool(settings, "hw_decode", true);
            obs_data_set_bool(settings, "close_when_inactive", true);
            obs_data_set_bool(settings, "restart_on_active", true);
            
            obs_source_update(source, settings);
            obs_data_release(settings);
        }
    }
    return true;
    (void)unused;
}

// 计时器：每秒执行一次全场扫描
static void timer_tick(void *param, uint64_t tick) {
    static int frame_count = 0;
    if (++frame_count >= 60) { // 假设 60fps，每秒执行一次
        frame_count = 0;
        obs_enum_sources(fix_source_callback, NULL);
    }
    (void)param; (void)tick;
}

bool obs_module_load(void) {
    obs_add_tick_callback(timer_tick, NULL);
    return true;
}

void obs_module_unload(void) {
    obs_remove_tick_callback(timer_tick, NULL);
}
