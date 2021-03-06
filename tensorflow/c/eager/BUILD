# Experimental extensions to the C API for eager execution of kernels.

load(
    "//tensorflow:tensorflow.bzl",
    "tf_cc_test",
    "tf_copts",
    "tf_cuda_cc_test",
    "tf_cuda_library",
    "tfe_xla_copts",
)
load(
    "//tensorflow/core/platform:build_config.bzl",
    "tf_kernel_tests_linkstatic",
)
load(
    "//tensorflow/core/platform:build_config_root.bzl",
    "tf_cuda_tests_tags",
)

package(
    licenses = ["notice"],  # Apache 2.0
)

tf_cuda_library(
    name = "c_api",
    srcs = [
        "c_api.cc",
        "c_api_debug.cc",
        "c_api_experimental.h",
        "c_api_internal.h",
        "c_api_unified_experimental.h",
    ],
    hdrs = ["c_api.h"],
    copts = tf_copts() + tfe_xla_copts(),
    visibility = ["//visibility:public"],
    deps = select({
        "//tensorflow:android": [
            "//tensorflow/core:portable_tensorflow_lib_lite",
        ],
        "//conditions:default": [
            ":immediate_execution_context",
            ":immediate_execution_operation",
            ":immediate_execution_tensor_handle",
            ":abstract_tensor_handle",
            ":tfe_context_internal",
            ":tfe_cancellation_manager_internal",
            ":tfe_executor_internal",
            ":tfe_monitoring_internal",
            ":tfe_op_attrs_internal",
            ":tfe_op_internal",
            ":tfe_tensor_debug_info_internal",
            ":tfe_tensorhandle_internal",
            "@com_google_absl//absl/algorithm:container",
            "@com_google_absl//absl/types:span",
            "@com_google_absl//absl/types:variant",
            "//tensorflow/c:c_api",
            "//tensorflow/c:c_api_internal",
            "//tensorflow/c:tf_status_internal",
            "//tensorflow/c:tf_tensor_internal",
            "//tensorflow/core:core_cpu",
            "//tensorflow/core/common_runtime/eager:attr_builder",
            "//tensorflow/core/common_runtime/eager:context",
            "//tensorflow/core/common_runtime/eager:core",
            "//tensorflow/core/common_runtime/eager:eager_executor",
            "//tensorflow/core/common_runtime/eager:execute",
            "//tensorflow/core/common_runtime/eager:tensor_handle",
            "//tensorflow/core:core_cpu_internal",
            "//tensorflow/core:framework",
            "//tensorflow/core:framework_internal",
            "//tensorflow/core:lib",
            "//tensorflow/core:lib_internal",
            "//tensorflow/core:protos_all_cc",
            "//tensorflow/core/profiler/lib:traceme",
        ],
    }) + select({
        "//tensorflow:with_xla_support": [
            "//tensorflow/compiler/tf2xla:xla_compiler",
            "//tensorflow/compiler/jit",
            "//tensorflow/compiler/jit:xla_device",
        ],
        "//conditions:default": [],
    }) + [
        "@com_google_absl//absl/memory",
        "//tensorflow/core/common_runtime/eager:eager_operation",
        "//tensorflow/core/distributed_runtime/eager:remote_mgr",
        "//tensorflow/core/distributed_runtime/eager:cluster_function_library_runtime",
        "//tensorflow/core/distributed_runtime/eager:eager_client",
        "//tensorflow/core/distributed_runtime/rpc/eager:grpc_eager_client",
        "//tensorflow/core/distributed_runtime/rpc:grpc_channel",
        "//tensorflow/core/distributed_runtime/rpc:grpc_server_lib",
        "//tensorflow/core/distributed_runtime/rpc:grpc_worker_cache",
        "//tensorflow/core/distributed_runtime/rpc:grpc_worker_service",
        "//tensorflow/core/distributed_runtime/rpc:rpc_rendezvous_mgr",
        "//tensorflow/core/distributed_runtime:remote_device",
        "//tensorflow/core/distributed_runtime:server_lib",
        "//tensorflow/core/distributed_runtime:worker_env",
        "//tensorflow/core:gpu_runtime",
    ],
    alwayslink = 1,
)

filegroup(
    name = "pywrap_required_hdrs",
    srcs = [
        "abstract_context.h",
        "abstract_function.h",
        "abstract_operation.h",
        "abstract_tensor_handle.h",
        "c_api_experimental.h",
        "c_api_internal.h",
        "c_api_unified_experimental.h",
        "dlpack.h",
        "immediate_execution_context.h",
        "immediate_execution_operation.h",
        "immediate_execution_tensor_handle.h",
        "tfe_cancellation_manager_internal.h",
        "tfe_executor_internal.h",
        "tfe_monitoring_internal.h",
        "tfe_op_attrs_internal.h",
        "tfe_tensor_debug_info_internal.h",
    ],
    visibility = [
        "//tensorflow/core:__pkg__",
        "//tensorflow/python:__pkg__",
    ],
)

cc_library(
    name = "c_api_internal",
    hdrs = [
        "c_api_experimental.h",
        "c_api_internal.h",
    ],
    visibility = [
        "//learning/deepmind/courier:__subpackages__",
        "//tensorflow:internal",
    ],
    deps = [
        ":c_api",
        ":tfe_cancellation_manager_internal",
        ":tfe_context_internal",
        ":tfe_executor_internal",
        ":tfe_monitoring_internal",
        ":tfe_op_attrs_internal",
        ":tfe_op_internal",
        ":tfe_tensor_debug_info_internal",
        ":tfe_tensorhandle_internal",
        "//tensorflow/c:c_api_internal",
    ],
)

cc_library(
    name = "c_api_unified_internal",
    hdrs = [
        "c_api_unified_experimental_internal.h",
    ],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":abstract_context",
        ":abstract_operation",
        ":abstract_tensor_handle",
        ":c_api",
        ":c_api_experimental",
        "//tensorflow/c:c_api_internal",
        "//tensorflow/c:conversion_macros",
        "//tensorflow/c:tf_status",
        "//tensorflow/core/platform:casts",
        "//tensorflow/core/platform:types",
    ],
)

cc_library(
    name = "gradients",
    srcs = [
        "gradients.cc",
        "gradients_internal.h",
    ],
    hdrs = [
        "gradients.h",
    ],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":abstract_context",
        ":abstract_operation",
        ":abstract_tensor_handle",
        ":c_api_unified_internal",
        ":tape",
        "//tensorflow/core/common_runtime/eager:attr_builder",
        "//tensorflow/core/lib/llvm_rtti",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "gradients_internal",
    srcs = [
        "gradients.cc",
    ],
    hdrs = [
        "gradients.h",
        "gradients_internal.h",
    ],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":abstract_context",
        ":abstract_operation",
        ":abstract_tensor_handle",
        ":c_api_unified_internal",
        ":tape",
        "//tensorflow/core/common_runtime/eager:attr_builder",
        "//tensorflow/core/lib/llvm_rtti",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/strings",
    ],
)

tf_cuda_cc_test(
    name = "gradients_test",
    size = "small",
    srcs = [
        "gradients_test.cc",
    ],
    args = ["--heap_check=local"],
    extra_copts = tfe_xla_copts(),
    linkstatic = tf_kernel_tests_linkstatic(),
    tags = tf_cuda_tests_tags() + ["nomac"],
    deps = [
        ":abstract_tensor_handle",
        ":c_api_experimental",
        ":c_api_test_util",
        ":c_api_unified_internal",
        ":gradients_internal",
        "//tensorflow/c:c_api",
        "//tensorflow/c:c_test_util",
        "//tensorflow/c:tf_status_helper",
        "//tensorflow/cc/profiler",
        "//tensorflow/compiler/mlir/tensorflow/c:mlir_c_api_registration",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core:test",
        "//tensorflow/core:test_main",
        "//tensorflow/core/lib/llvm_rtti",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:span",
    ],
)

cc_library(
    name = "abstract_tensor_handle",
    hdrs = ["abstract_tensor_handle.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        "//tensorflow/core:protos_all_cc",
    ],
)

cc_library(
    name = "immediate_execution_tensor_handle",
    hdrs = ["immediate_execution_tensor_handle.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":abstract_tensor_handle",
        "//tensorflow/c:tensor_interface",
        "//tensorflow/core:framework",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
    ],
)

cc_library(
    name = "abstract_operation",
    hdrs = ["abstract_operation.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":abstract_tensor_handle",
        "//tensorflow/c:tensor_interface",
        "//tensorflow/core:framework",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "@com_google_absl//absl/types:span",
    ],
)

cc_library(
    name = "immediate_execution_operation",
    hdrs = ["immediate_execution_operation.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":abstract_operation",
        ":abstract_tensor_handle",
        ":immediate_execution_tensor_handle",
        "//tensorflow/c:tensor_interface",
        "//tensorflow/core:framework",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core/util:abstract_stack_trace",
        "@com_google_absl//absl/types:span",
    ],
)

cc_library(
    name = "abstract_context",
    hdrs = ["abstract_context.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":abstract_function",
        ":abstract_operation",
    ],
)

cc_library(
    name = "abstract_function",
    hdrs = ["abstract_function.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core/platform:status",
    ],
)

cc_library(
    name = "immediate_execution_context",
    hdrs = ["immediate_execution_context.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":abstract_context",
        ":immediate_execution_operation",
        ":immediate_execution_tensor_handle",
        "//tensorflow/c:tensor_interface",
        "//tensorflow/core:framework",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "@com_google_absl//absl/types:optional",
        "@com_google_absl//absl/types:span",
    ],
)

cc_library(
    name = "tfe_context_internal",
    hdrs = ["tfe_context_internal.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":immediate_execution_context",
        "//tensorflow/c:conversion_macros",
    ],
)

cc_library(
    name = "tfe_cancellation_manager_internal",
    hdrs = ["tfe_cancellation_manager_internal.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        "//tensorflow/core:framework",
    ],
)

cc_library(
    name = "tfe_executor_internal",
    hdrs = ["tfe_executor_internal.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        "//tensorflow/core/common_runtime/eager:eager_executor",
    ],
)

cc_library(
    name = "tfe_monitoring_internal",
    hdrs = ["tfe_monitoring_internal.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        "//tensorflow/core:lib",
        "@com_google_absl//absl/memory",
    ],
)

cc_library(
    name = "tfe_op_attrs_internal",
    hdrs = ["tfe_op_attrs_internal.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        "//tensorflow/c:conversion_macros",
        "//tensorflow/c:tf_status",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core/common_runtime/eager:attr_builder",
    ],
)

cc_library(
    name = "tfe_op_internal",
    hdrs = ["tfe_op_internal.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":immediate_execution_operation",
        "//tensorflow/c:conversion_macros",
    ],
)

cc_library(
    name = "tfe_tensor_debug_info_internal",
    hdrs = ["tfe_tensor_debug_info_internal.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        "//tensorflow/core:lib",
    ],
)

cc_library(
    name = "tfe_tensorhandle_internal",
    hdrs = ["tfe_tensorhandle_internal.h"],
    visibility = [
        "//tensorflow:internal",
    ],
    deps = [
        ":immediate_execution_tensor_handle",
        "//tensorflow/c:conversion_macros",
    ],
)

tf_cuda_library(
    name = "c_api_test_util",
    testonly = 1,
    srcs = ["c_api_test_util.cc"],
    hdrs = ["c_api_test_util.h"],
    visibility = [
        "//learning/brain:__subpackages__",
        "//tensorflow:__subpackages__",
    ],
    deps = [
        ":c_api",
        ":c_api_experimental",
        "//tensorflow/c:c_test_util",
        "//tensorflow/core:framework",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core:test",
    ],
)

tf_cuda_cc_test(
    name = "c_api_test",
    size = "small",
    srcs = [
        "c_api_debug_test.cc",
        "c_api_test.cc",
    ],
    extra_copts = tfe_xla_copts(),
    tags = [
        "noguitar",  # TODO(b/155445984): flaky
        #"guitar",
        "notap",  # TODO(b/156981931): flaky
        "multi_gpu",
    ],
    deps = [
        ":c_api",
        ":c_api_experimental",
        ":c_api_internal",
        ":c_api_test_util",
        ":tfe_op_internal",
        ":tfe_tensorhandle_internal",
        "//tensorflow/c:c_test_util",
        "//tensorflow/core:lib",
        "//tensorflow/core:lib_internal",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core:test",
        "//tensorflow/core:test_main",
        "//tensorflow/core/common_runtime/eager:eager_operation",
        "//tensorflow/core/common_runtime/eager:tensor_handle",
        "@com_google_absl//absl/strings",
    ],
)

tf_cuda_cc_test(
    name = "c_api_remote_test",
    size = "small",
    srcs = [
        "c_api_remote_test.cc",
    ],
    # TODO(b/136478427): Figure out how to correctly shut the server down
    args = ["--heap_check=local"],
    extra_copts = tfe_xla_copts(),
    tags = [
        "no_windows",
    ],
    deps = [
        ":c_api",
        ":c_api_experimental",
        ":c_api_internal",
        ":c_api_test_util",
        ":tfe_tensorhandle_internal",
        "//tensorflow/c:c_test_util",
        "//tensorflow/core:framework",
        "//tensorflow/core:graph",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core:test",
        "//tensorflow/core:test_main",
        "//tensorflow/core/common_runtime:function_optimization_registry",
        "//tensorflow/core/common_runtime/eager:eager_operation",
        "//tensorflow/core/distributed_runtime/rpc:grpc_server_lib",
        "@com_google_absl//absl/strings",
    ],
)

tf_cuda_cc_test(
    name = "c_api_distributed_test",
    size = "small",
    srcs = [
        "c_api_distributed_test.cc",
    ],
    # TODO(b/136478427): Figure out how to correctly shut the server down
    args = ["--heap_check=local"],
    extra_copts = tfe_xla_copts(),
    tags = [
        "no_windows",
        "noasan",  # leaks gRPC server instances
    ],
    deps = [
        ":c_api",
        ":c_api_experimental",
        ":c_api_internal",
        ":c_api_test_util",
        ":tfe_tensorhandle_internal",
        "//tensorflow/c:c_test_util",
        "//tensorflow/core:framework",
        "//tensorflow/core:graph",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core:test",
        "//tensorflow/core:test_main",
        "//tensorflow/core/common_runtime:function_optimization_registry",
        "//tensorflow/core/common_runtime:optimization_registry",
        "//tensorflow/core/common_runtime/eager:eager_operation",
        "//tensorflow/core/distributed_runtime/rpc:grpc_server_lib",
        "@com_google_absl//absl/strings",
    ],
)

tf_cuda_cc_test(
    name = "c_api_cluster_test",
    size = "small",
    srcs = [
        "c_api_cluster_test.cc",
    ],
    # TODO(b/136478427): Figure out how to correctly shut the server down
    args = ["--heap_check=local"],
    extra_copts = tfe_xla_copts(),
    tags = [
        "no_windows",
    ],
    deps = [
        ":c_api",
        ":c_api_experimental",
        ":c_api_internal",
        ":c_api_test_util",
        ":tfe_tensorhandle_internal",
        "//tensorflow/c:c_test_util",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core:test",
        "//tensorflow/core:test_main",
        "//tensorflow/core/common_runtime/eager:eager_operation",
        "//tensorflow/core/distributed_runtime/rpc:grpc_server_lib",
        "//tensorflow/core/platform:env",
        "@com_google_absl//absl/strings",
    ],
)

tf_cuda_library(
    name = "c_api_experimental",
    srcs = [
        "c_api_experimental.cc",
        "c_api_unified_experimental.cc",
        "c_api_unified_experimental_eager.cc",
        "c_api_unified_experimental_graph.cc",
        "c_api_unified_experimental_internal.h",
    ],
    hdrs = [
        "c_api_experimental.h",
        "c_api_unified_experimental.h",
    ],
    copts = tf_copts() + tfe_xla_copts(),
    visibility = ["//visibility:public"],
    deps = select({
        "//tensorflow:android": [
            "//tensorflow/core:portable_tensorflow_lib_lite",
        ],
        "//conditions:default": [
            ":c_api",
            ":c_api_internal",
            ":tfe_context_internal",
            ":tfe_op_internal",
            ":tfe_tensorhandle_internal",
            ":abstract_operation",
            ":abstract_context",
            ":abstract_tensor_handle",
            ":immediate_execution_tensor_handle",
            ":immediate_execution_context",
            "//tensorflow/core/lib/llvm_rtti",
            "//tensorflow/c:c_api",
            "//tensorflow/c:c_api_internal",
            "//tensorflow/core:core_cpu",
            "//tensorflow/core/common_runtime/eager:attr_builder",
            "//tensorflow/core/common_runtime/eager:context",
            "//tensorflow/core/common_runtime/eager:eager_executor",
            "//tensorflow/core/common_runtime/eager:eager_operation",
            "//tensorflow/core/common_runtime/eager:execute",
            "//tensorflow/core/common_runtime/eager:kernel_and_device",
            "//tensorflow/core/common_runtime/eager:tensor_handle",
            "//tensorflow/core/common_runtime/eager:copy_to_device_node",
            "//tensorflow/core:core_cpu_internal",
            "//tensorflow/core:framework",
            "//tensorflow/core:framework_internal",
            "//tensorflow/core:lib",
            "//tensorflow/core:lib_internal",
            "//tensorflow/core:protos_all_cc",
            "@com_google_absl//absl/types:variant",
            "//tensorflow/c:conversion_macros",
        ],
    }) + select({
        "//tensorflow:with_xla_support": [
            "//tensorflow/compiler/tf2xla:xla_compiler",
            "//tensorflow/compiler/jit",
            "//tensorflow/compiler/jit:xla_device",
        ],
        "//conditions:default": [],
    }) + [
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/container:flat_hash_map",
        "//tensorflow/c:tf_status_helper",
        "//tensorflow/core/distributed_runtime/eager:eager_client",
        "//tensorflow/core/distributed_runtime/rpc/eager:grpc_eager_client",
        "//tensorflow/core/distributed_runtime/rpc:grpc_channel",
        "//tensorflow/core/distributed_runtime/rpc:grpc_server_lib",
        "//tensorflow/core/distributed_runtime/rpc:grpc_worker_cache",
        "//tensorflow/core/distributed_runtime/rpc:grpc_worker_service",
        "//tensorflow/core/distributed_runtime/rpc:rpc_rendezvous_mgr",
        "//tensorflow/core/distributed_runtime:remote_device",
        "//tensorflow/core/distributed_runtime:server_lib",
        "//tensorflow/core/distributed_runtime:worker_env",
        "//tensorflow/core:gpu_runtime",
    ],
    alwayslink = 1,
)

tf_cuda_cc_test(
    name = "c_api_experimental_test",
    size = "small",
    srcs = [
        "c_api_experimental_test.cc",
    ],
    args = ["--heap_check=local"],
    extra_copts = tfe_xla_copts(),
    linkstatic = tf_kernel_tests_linkstatic(),
    tags = tf_cuda_tests_tags() + ["nomac"],
    deps = [
        ":c_api",
        ":c_api_experimental",
        ":c_api_test_util",
        "//tensorflow/c:c_test_util",
        "//tensorflow/cc/profiler",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core:test",
        "//tensorflow/core:test_main",
        "@com_google_absl//absl/strings",
    ],
)

tf_cuda_cc_test(
    name = "c_api_unified_experimental_test",
    size = "small",
    srcs = [
        "c_api_unified_experimental_test.cc",
    ],
    args = ["--heap_check=local"],
    extra_copts = tfe_xla_copts(),
    linkstatic = tf_kernel_tests_linkstatic(),
    tags = tf_cuda_tests_tags() + ["nomac"],
    deps = [
        ":c_api",
        ":c_api_experimental",
        ":c_api_test_util",
        "//tensorflow/c:c_api",
        "//tensorflow/c:c_test_util",
        "//tensorflow/cc/profiler",
        "//tensorflow/compiler/mlir/tensorflow/c:mlir_c_api_registration",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core:test",
        "//tensorflow/core:test_main",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "custom_device_testutil",
    testonly = True,
    srcs = ["custom_device_testutil.cc"],
    hdrs = ["custom_device_testutil.h"],
    visibility = ["//tensorflow:internal"],
    deps = [
        ":c_api",
        ":c_api_experimental",
        ":c_api_test_util",
        "//tensorflow/c:c_api",
        "//tensorflow/core:lib",
        "//tensorflow/core:test",
    ],
)

tf_cc_test(
    name = "custom_device_test",
    size = "small",
    srcs = [
        "custom_device_test.cc",
    ],
    deps = [
        ":c_api",
        ":c_api_experimental",
        ":c_api_test_util",
        ":custom_device_testutil",
        "//tensorflow/c:c_api",
        "//tensorflow/c:c_test_util",
        "//tensorflow/cc/profiler",
        "//tensorflow/core:lib",
        "//tensorflow/core:protos_all_cc",
        "//tensorflow/core:test",
        "//tensorflow/core:test_main",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "tape",
    hdrs = ["tape.h"],
    visibility = ["//tensorflow:internal"],
    deps = [
        "//tensorflow/core:framework",
        "//tensorflow/core:lib",
    ],
)

filegroup(
    name = "headers",
    srcs = [
        "c_api.h",
        "c_api_experimental.h",
        "dlpack.h",
    ],
    visibility = ["//tensorflow:__subpackages__"],
)

cc_library(
    name = "dlpack",
    srcs = ["dlpack.cc"],
    hdrs = ["dlpack.h"],
    copts = [
        "-fexceptions",
        "-fno-strict-aliasing",
    ],
    features = ["-use_header_modules"],
    visibility = ["//tensorflow:__subpackages__"],
    deps = [
        ":c_api",
        ":c_api_experimental",
        ":tfe_tensorhandle_internal",
        "//tensorflow/c:tf_status_helper",
        "//tensorflow/c:tf_status_internal",
        "//tensorflow/core:framework",
        "//tensorflow/core:framework_internal",
        "//tensorflow/core:lib",
        "//tensorflow/core/common_runtime/eager:tensor_handle",
        "@dlpack",
    ],
    alwayslink = 1,
)

# TODO(karllessard): only used by //tensorflow/core:mobile_srcs_only_runtime
# right now, remove this public rule when no longer needed (it should be
# replaced by TF Lite)
filegroup(
    name = "srcs",
    srcs = glob(
        [
            "*.cc",
            "*.h",
        ],
        exclude = [
            "c_api_experimental.cc",
            "c_api_unified_experimental.cc",
            "c_api_unified_experimental_eager.cc",
            "c_api_unified_experimental_graph.cc",
            "c_api_unified_experimental_internal.h",
            "gradients.cc",  # Uses RTTI.
            "*test*",
            "*dlpack*",
        ],
    ),
    visibility = ["//visibility:public"],
)
