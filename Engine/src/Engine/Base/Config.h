#pragma once
#ifndef LIGHT_CONFIG_H
#define LIGHT_CONFIG_H

//
// you can uncomment any of these definitions to config the project to your
// liking
//

// suppress undefined debug trap
#define LIGHT_IGNORE_UNDEFINED_DEBUG_TRAP

// validation layers used in vulkan api
#define LT_VULKAN_VALIDATION_LAYERS "VK_LAYER_KHRONOS_validation"
#define LT_VULKAN_GLOBAL_EXTENSIONS VK_EXT_DEBUG_UTILS_EXTENSION_NAME


// log opengl shader compile info
// #define LIGHT_OPENGL_ENABLE_SHADER_INFO_LOG


#endif
