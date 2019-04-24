#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#define EASYCL_MAX_STRING_SIZE 256
#define EASYCL_MAX_PLATFORMS 64
#define EASYCL_MAX_DEVICES 64

// "_some" means "hidden from user"

/////////////////////////////////////////
//            Declarations
/////////////////////////////////////////

// Error
typedef struct _EclError{
    int code;
} _EclError;

void eclErrorCheck(_EclError* obj, const char* where);

// Platform
typedef struct EclPlatform{
    _EclError _error;

    cl_platform_id platform;
    char name[EASYCL_MAX_STRING_SIZE];

    cl_device_id _cpus[EASYCL_MAX_DEVICES];
    cl_device_id _gpus[EASYCL_MAX_DEVICES];
    cl_device_id _accs[EASYCL_MAX_DEVICES];
} EclPlatform;

// System
struct EclSystem{
    _EclError _error;

    EclPlatform platforms[EASYCL_MAX_PLATFORMS];
    uint32_t platforms_count;

    bool _initialized;
} EclSystem = {};

void eclSystemInit();
void eclSystemRelease();


/////////////////////////////////////////
//           Implementations
/////////////////////////////////////////

// Error
void eclErrorCheck(_EclError* obj, const char* where){
    if(obj->code < 0){
        const char* what;

        switch (obj->code)
        {
            case CL_DEVICE_NOT_FOUND:
                what = "device not found";
                break;
            case CL_DEVICE_NOT_AVAILABLE:
                what = "device not available";
                break;
            case CL_COMPILER_NOT_AVAILABLE:
                what = "compiler not available";
                break;
            case CL_MEM_OBJECT_ALLOCATION_FAILURE:
                what = "mem object allocation failure";
                break;
            case CL_OUT_OF_RESOURCES:
                what = "out of resources";
                break;
            case CL_OUT_OF_HOST_MEMORY:
                what = "out of host memory";
                break;
            case CL_PROFILING_INFO_NOT_AVAILABLE:
                what = "profiling info not available";
                break;
            case CL_MEM_COPY_OVERLAP:
                what = "mem copy overlap";
                break;
            case CL_IMAGE_FORMAT_MISMATCH:
                what = "image format mismatch";
                break;
            case CL_IMAGE_FORMAT_NOT_SUPPORTED:
                what = "image format not supported";
                break;
            case CL_BUILD_PROGRAM_FAILURE:
                what = "build program failure";
                break;
            case CL_MAP_FAILURE:
                what = "map failure";
                break;
            case CL_MISALIGNED_SUB_BUFFER_OFFSET:
                what = "misaligned sub buffer offset";
                break;
            case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
                what = "exec status error for events in wait list";
                break;
            case CL_COMPILE_PROGRAM_FAILURE:
                what = "compile program failure";
                break;
            case CL_LINKER_NOT_AVAILABLE:
                what = "linker not available";
                break;
            case CL_LINK_PROGRAM_FAILURE:
                what = "link program failure";
                break;
            case CL_DEVICE_PARTITION_FAILED:
                what = "device partition failed";
                break;
            case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
                what = "kernel argument info not available";
                break;
            case CL_INVALID_VALUE:
                what = "invalid value";
                break;
            case CL_INVALID_DEVICE_TYPE:
                what = "invalid device type";
                break;
            case CL_INVALID_PLATFORM:
                what = "invalid platform";
                break;
            case CL_INVALID_DEVICE:
                what = "invalid device";
                break;
            case CL_INVALID_CONTEXT:
                what = "invalid context";
                break;
            case CL_INVALID_QUEUE_PROPERTIES:
                what = "invalid queue properties";
                break;
            case CL_INVALID_COMMAND_QUEUE:
                what = "invalid command queue";
                break;
            case CL_INVALID_HOST_PTR:
                what = "invalid host ptr";
                break;
            case CL_INVALID_MEM_OBJECT:
                what = "invalid mem object";
                break;
            case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
                what = "invalid image format descriptor";
                break;
            case CL_INVALID_IMAGE_SIZE:
                what = "invalid image size";
                break;
            case CL_INVALID_SAMPLER:
                what = "invalid sampler";
                break;
            case CL_INVALID_BINARY:
                what = "invalid binary";
                break;
            case CL_INVALID_BUILD_OPTIONS:
                what = "invalid build options";
                break;
            case CL_INVALID_PROGRAM:
                what = "invalid program";
                break;
            case CL_INVALID_PROGRAM_EXECUTABLE:
                what = "invalid program executable";
                break;
            case CL_INVALID_KERNEL_NAME:
                what = "invalid kernel name";
                break;
            case CL_INVALID_KERNEL_DEFINITION:
                what = "invalid kernel definition";
                break;
            case CL_INVALID_KERNEL:
                what = "invalid kernel";
                break;
            case CL_INVALID_ARG_INDEX:
                what = "invalid argument index";
                break;
            case CL_INVALID_ARG_VALUE:
                what = "invalid argument value";
                break;
            case CL_INVALID_ARG_SIZE:
                what = "invalid argument size";
                break;
            case CL_INVALID_KERNEL_ARGS:
                what = "invalid kernel arguments";
                break;
            case CL_INVALID_WORK_DIMENSION:
                what = "invalid work dimension";
                break;
            case CL_INVALID_WORK_GROUP_SIZE:
                what = "invalid work group size";
                break;
            case CL_INVALID_WORK_ITEM_SIZE:
                what = "invalid work item size";
                break;
            case CL_INVALID_GLOBAL_OFFSET:
                what = "invalid global offset";
                break;
            case CL_INVALID_EVENT_WAIT_LIST:
                what = "invalid event wait list";
                break;
            case CL_INVALID_EVENT:
                what = "invalid event";
                break;
            case CL_INVALID_OPERATION:
                what = "invalid operation";
                break;
            case CL_INVALID_GL_OBJECT:
                what = "invalid gl object";
                break;
            case CL_INVALID_BUFFER_SIZE:
                what = "invalid buffer size";
                break;
            case CL_INVALID_MIP_LEVEL:
                what = "invalid mip level";
                break;
            case CL_INVALID_GLOBAL_WORK_SIZE:
                what = "invalid global work size";
                break;
            case CL_INVALID_PROPERTY:
                what = "invalid property";
                break;
            case CL_INVALID_IMAGE_DESCRIPTOR:
                what = "invalid image descriptor";
                break;
            case CL_INVALID_COMPILER_OPTIONS:
                what = "invalid compiler options";
                break;
            case CL_INVALID_LINKER_OPTIONS:
                what = "invalid linker options";
                break;
            case CL_INVALID_DEVICE_PARTITION_COUNT:
                what = "invalid device partition count";
                break;
            case CL_INVALID_PIPE_SIZE:
                what = "invalid pipe size";
                break;
            case CL_INVALID_DEVICE_QUEUE:
                what = "invalid device queue";
                break;
            case CL_INVALID_SPEC_ID:
                what = "invalid spec id";
                break;
            case CL_MAX_SIZE_RESTRICTION_EXCEEDED:
                what = "max size restriction exceeded";
                break;
            case -1000:
                what = "invalid gl sharegroup reference khr";
                break;
            case -1001:
                what = "platform not found khr";
                break;
            case -1002:
                what = "invalid d3d10 device khr";
                break;
            case -1003:
                what = "invalid d3d10 resource khr";
                break;
            case -1004:
                what = "d3d10 resource already acquired khr";
                break;
            case -1005:
                what = "d3d10 resource not acquired khr";
                break;
            default:
                what = "unknown opencl error";
                break;
        }

        fprintf(stderr, "%s: %s\n", where, what);
    }
}