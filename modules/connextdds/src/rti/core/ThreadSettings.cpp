/*
 * (c) 2020 Copyright, Real-Time Innovations, Inc.  All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the Software solely for use with RTI products.  The Software is
 * provided "as is", with no warranty of any type, including any warranty for
 * fitness for any purpose. RTI is under no obligation to maintain or support
 * the Software.  RTI shall not be liable for any incidental or consequential
 * damages arising out of the use or inability to use the software.
 */

#include "PyConnext.hpp"
#include <rti/core/ThreadSettings.hpp>
#include "PySafeEnum.hpp"
#include "PyMaskType.hpp"

using namespace rti::core;

namespace pyrti {

template<>
void init_class_defs(py::class_<ThreadSettingsKindMask>& cls)
{
    cls.def_property_readonly_static(
               "FLOATING_POINT",
               [](py::object&) {
                    return ThreadSettingsKindMask::floating_point();
               },
               "Create a mask with the floating point option set."
               "\n\n"
               "With this option enabled, code in the thread may perform "
               "floating point operations."
               "\n\n"
               "This options is only relevant for VxWorks platforms where user"
               "callbacks use floating point operations.")
            .def_property_readonly_static(
                    "STDIO",
                    [](py::object&) {
                        return ThreadSettingsKindMask::stdio();
                    },
                    "Create a mask with the standard I/O option set."
                    "\n\n"
                    "With this option enabled, code in the thread may perform "
                    "standard I/O operations."
                    "\n\n"
                    "This options is only relevant for VxWorks platforms where "
                    "user"
                    "callbacks use standard I/O operations.")
            .def_property_readonly_static(
                    "REALTIME_PRIORITY",
                    [](py::object&) {
                        return ThreadSettingsKindMask::realtime_priority();
                    },
                    "Create a mask with the realtime priority option set."
                    "\n\n"
                    "With this option enabled, the thread will be scheduled on "
                    "a FIFO"
                    "basis.")
            .def_property_readonly_static(
                    "PRIORITY_ENFORCE",
                    [](py::object&) {
                        return ThreadSettingsKindMask::priority_enforce();
                    },
                    "Create a mask with the priority enforcement option set."
                    "\n\n"
                    "With this option enabled, the thread's priority will be "
                    "strictly "
                    "enforced.")
            .def_property_readonly_static(
                    "CANCEL_ASYNCHRONOUS",
                    [](py::object&) {
                        return ThreadSettingsKindMask::cancel_asynchronous();
                    },
                    "Create a mask with the asynchronous cancellation option "
                    "set."
                    "\n\n"
                    "With this option enabled, the thread may be cancelled "
                    "without "
                    "reaching a cancellable state or a cancellation point.");
}

template<>
void init_class_defs(py::class_<ThreadSettings>& cls)
{
    cls.def(py::init<>(),
               "Create a ThreadSettings object with default settings.")
            .def(py::init<
                         ThreadSettingsKindMask,
                         int32_t,
                         int32_t,
                         dds::core::vector<int32_t>,
                         ThreadSettingsCpuRotationKind::type>(),
                    py::arg("mask"),
                    py::arg("priority"),
                    py::arg("stack_size"),
                    py::arg("cpu_list"),
                    py::arg("cpu_rotation"),
                    "Create a ThreadSettings object with the specified "
                    "parameters.")
            .def_property(
                    "mask",
                    (ThreadSettingsKindMask(ThreadSettings::*)() const)
                            & ThreadSettings::mask,
                    (ThreadSettings
                            & (ThreadSettings::*) (ThreadSettingsKindMask))
                            & ThreadSettings::mask,
                    "Get/set a copy of the thread settings mask.")
            .def_property(
                    "priority",
                    (int32_t(ThreadSettings::*)() const)
                            & ThreadSettings::priority,
                    (ThreadSettings & (ThreadSettings::*) (int32_t))
                            & ThreadSettings::priority,
                    "Get/set a copy of the thread priority.")
            .def_property(
                    "stack_size",
                    (int32_t(ThreadSettings::*)() const)
                            & ThreadSettings::stack_size,
                    (ThreadSettings & (ThreadSettings::*) (int32_t))
                            & ThreadSettings::stack_size,
                    "Get/set a copy of the thread stack size.")
            .def_property(
                    "cpu_list",
                    [](ThreadSettings& ts) {
                        return std::vector<int32_t>(ts.cpu_list());
                    },
                    [](ThreadSettings& ts, std::vector<int32_t> list) {
                        ts.cpu_list(list);
                    },
                    "Get/set a copy of the list of CPUs available to the "
                    "thread.")
            .def_property(
                    "cpu_rotation",
                    (ThreadSettingsCpuRotationKind(ThreadSettings::*)() const)
                            & ThreadSettings::cpu_rotation,
                    (ThreadSettings
                            & (ThreadSettings::*) (ThreadSettingsCpuRotationKind))
                            & ThreadSettings::cpu_rotation,
                    "Get/set a copy of the thread settings mask.")
            .def(py::self == py::self)
            .def(py::self != py::self);
}

template<>
void process_inits<ThreadSettings>(py::module& m, ClassInitList& l)
{
    init_dds_safe_enum<ThreadSettingsCpuRotationKind_def>(
            m,
            "ThreadSettingsCpuRotationKind",
            [](py::object& o) {
                py::enum_<ThreadSettingsCpuRotationKind::type>(o, "ThreadSettingsCpuRotationKind")
                        .value("NO_ROTATION",
                               ThreadSettingsCpuRotationKind::NO_ROTATION,
                               "Any thread controlled by this QoS can run on "
                               "any listed "
                               "processor, as determined by OS scheduling.")
                        .value("ROUND_ROBIN",
                               ThreadSettingsCpuRotationKind::ROUND_ROBIN,
                               "Threads controlled by this QoS will be "
                               "assigned one processor "
                               "from the list in round-robin order.")
                        .export_values();
            });

    l.push_back([m]() mutable {
        auto cls = init_mask_type<ThreadSettingsKindMask, uint64_t>(
                m,
                "ThreadSettingsKindMask",
                "Create a ThreadSettingsKindMask with default thread "
                "settings.");
        return [cls]() mutable {
            init_class_defs<ThreadSettingsKindMask>(cls);
        };
    });

    l.push_back([m]() mutable {
        return init_class<ThreadSettings>(m, "ThreadSettings");
    });
}

}  // namespace pyrti
