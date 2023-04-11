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
#include <dds/topic/Filter.hpp>

using namespace dds::topic;

namespace pyrti {

template<>
void init_class_defs(py::class_<Filter>& cls)
{
    cls.def(py::init<const std::string&>(),
            py::arg("expression"),
            "Create a Filter with the specified expression.")
            .def(py::init<
                         const std::string&,
                         const std::vector<std::string>&>(),
                 py::arg("expression"),
                 py::arg("parameters"),
                 "Create a Filter with the specified expression and "
                 "parameters.")
            .def_property_readonly(
                    "expression",
                    &Filter::expression,
                    "Get the Filter's expression.")
            .def(
                    "__iter__",
                    [](Filter& f) {
                        return py::make_iterator(f.begin(), f.end());
                    },
                    py::keep_alive<0, 1>())
            .def(
                    "set_parameters",
                    [](Filter& f, std::vector<std::string>& params) {
                        f.parameters(params.begin(), params.end());
                    },
                    "Set the parameters for the Filter.")
            .def("add_parameters",
                 &Filter::add_parameter,
                 py::arg("parameter"),
                 "Append a parameter to the Filter.")
            .def_property_readonly(
                    "parameter_count",
                    &Filter::parameters_length,
                    "Get the number of parameters.")
            .def_property(
                    "name",
                    [](const Filter& f) { return f->name(); },
                    [](Filter& f, std::string& name) { return f->name(name); },
                    "The name of the type of Filter.")
            .def_property_readonly_static(
                    "SQL_FILTER_NAME",
                    [](py::object&) { return rti::topic::sql_filter_name(); },
                    "The name of the SQL filter.")
            .def_property_readonly_static(
                    "STRINGMATCH_FILTER_NAME",
                    [](py::object&) {
                        return rti::topic::stringmatch_filter_name();
                    },
                    "The name of the string match filter.");

    py::implicitly_convertible<std::string, Filter>();
}

template<>
void process_inits<Filter>(py::module& m, ClassInitList& l)
{
    l.push_back([m]() mutable { return init_class<Filter>(m, "Filter"); });
}

}  // namespace pyrti
