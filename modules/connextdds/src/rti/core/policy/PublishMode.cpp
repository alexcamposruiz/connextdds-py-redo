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
#include <rti/core/policy/CorePolicy.hpp>
#include "PySafeEnum.hpp"

using namespace rti::core::policy;

namespace pyrti {

template<>
void init_class_defs(py::class_<PublishMode>& cls)
{
    cls.def(py::init<>(),
               "Creates a PublishMode qos policy of synchronous kind.")
            .def_property(
                    "kind",
                    (PublishModeKind(PublishMode::*)() const)
                            & PublishMode::kind,
                    (PublishMode & (PublishMode::*) (const PublishModeKind))
                            & PublishMode::kind,
                    "The publish mode (synchronous or asynchronous) for a "
                    "DataWriter.")
            .def_property(
                    "flow_controller_name",
                    (std::string(PublishMode::*)() const)
                            & PublishMode::flow_controller_name,
                    (PublishMode & (PublishMode::*) (const std::string&) )
                            & PublishMode::flow_controller_name,
                    "The flow controller name associated to a DataWriter.")
            .def_property(
                    "priority",
                    (int32_t(PublishMode::*)() const) & PublishMode::priority,
                    (PublishMode & (PublishMode::*) (int32_t))
                            & PublishMode::priority,
                    "The priority of all samples written by a DataWriter.")
            .def(py::self == py::self, "Test for equality.")
            .def(py::self != py::self, "Test for inequality.")
            .def_property_readonly_static(
                    "synchronous",
                    [](py::object&) { return PublishMode::Synchronous(); },
                    "Creates a PublishMode qos policy of synchronous kind.")
            .def_static(
                    "asynchronous",
                    (PublishMode(*)()) & PublishMode::Asynchronous,
                    "Creates a PublishMode qos policy of asynchronous kind "
                    "with "
                    "default flow controller and undefined priority.")
            .def_static(
                    "asynchronous",
                    (PublishMode(*)(const std::string&))
                            & PublishMode::Asynchronous,
                    py::arg("flow_controller_name"),
                    "Creates a PublishMode qos policy of asynchronous kind "
                    "with a "
                    "specific flow controller and undefined priority.")
            .def_static(
                    "asynchronous",
                    (PublishMode(*)(const std::string&, int32_t))
                            & PublishMode::Asynchronous,
                    py::arg("flow_controller_name"),
                    py::arg("priority"),
                    "Creates a PublishMode qos policy of asynchronous kind "
                    "with "
                    "specific flow controller and priority.")
            .def_property_readonly_static(
                    "PUBLICATION_PRIORITY_UNDEFINED",
                    [](py::object&) {
                        return DDS_PUBLICATION_PRIORITY_UNDEFINED;
                    },
                    "The default value for the priority.");
}

template<>
void process_inits<PublishMode>(py::module& m, ClassInitList& l)
{
    init_dds_safe_enum<
            PublishModeKind_def>(m, "PublishModeKind", [](py::object& o) {
        py::enum_<PublishModeKind::type>(o, "PublishModeKind")
                .value("SYNCHRONOUS",
                       PublishModeKind::type::SYNCHRONOUS,
                       "Indicates to send data synchronously."
                       "\n\n"
                       "If DataWriterProtocol.push_on_write is true, data is "
                       "sent "
                       "immediately in the context of DataWriter.write()."
                       "\n\n"
                       "As data is sent immediately in the context of the user "
                       "thread, "
                       "no flow control is applied.")
                .value("ASYNCHRONOUS",
                       PublishModeKind::type::ASYNCHRONOUS,
                       "Indicates to send data asynchronously."
                       "\n\n"
                       "Configures the DataWriter to delegate the task of data "
                       "transmission to a separate publishing thread. The "
                       "DataWriter.write() call does not send the data, but "
                       "instead "
                       "schedules the data to be sent later by its associated "
                       "Publisher."
                       "\n\n"
                       "Each Publisher uses its dedicated publishing thread "
                       "(AsynchronousPublisher) to send data for all its "
                       "asynchronous "
                       "DataWriters. For each asynchronous DataWriter, the "
                       "associated "
                       "FlowController determines when the publishing thread "
                       "is allowed "
                       "to send the data."
                       "\n\n"
                       "DataWriter.wait_for_asynchronous_publishing and "
                       "Publisher.wait_for_asynchronous_publishing enable you "
                       "to "
                       "determine when the data has actually been sent.")
                .export_values();
    });

    l.push_back([m]() mutable {
        return init_class<PublishMode>(m, "PublishMode");
    });
}

}  // namespace pyrti
