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

using namespace rti::core::policy;

namespace pyrti {

template<>
void init_class_defs(py::class_<Property>& cls)
{
    cls.def(py::init<>(), "Creates an empty Property container.")
            .def(py::init([](py::dict& d,
                             bool propagate) {
                     Property p;
                     for (auto it : d) {
                         p.set({py::cast<std::string>(it.first),
                                py::cast<std::string>(it.second)}, 
                                propagate);
                     }
                     return p;
                 }),
                 py::arg("entries"),
                 py::arg("propagate") = false,
                 "Creates a Property container with entries from a dictionary "
                 "of entries")
            .def(py::init([](const std::vector<
                                     std::pair<std::string, std::string>>
                                     init_list,
                             bool p) {
                     return Property(init_list.begin(), init_list.end(), p);
                 }),
                 py::arg("entries"),
                 py::arg("propagate") = false,
                 "Creates a Property container with entries from a sequence of "
                 "entries")
            .def("exists",
                 &Property::exists,
                 py::arg("key"),
                 "Returns true if a property exists.")
            .def("get",
                 &Property::get,
                 py::arg("key"),
                 "Returns the value of a property identified by a key if it "
                 "exists.")
            .def("try_get",
                 &Property::try_get,
                 py::arg("key"),
                 "Returns the value of a property identified by a key if it "
                 "exists.")
            .def("set",
                 (Property
                  & (Property::*) (const std::pair<std::string, std::string>&, bool) )
                         & Property::set,
                 py::arg("entry"),
                 py::arg("propagate") = false,
                 "Adds or assigns a property from a pair of strings.")
            .def(
                    "set",
                    [](Property& p,
                       const std::string& k,
                       const std::string& v,
                       bool propagate) {
                        return p.set({k, v}, propagate);
                    },
                    py::arg("key"),
                    py::arg("value"),
                    py::arg("propagate") = false,
                    "Adds or assigns a property from a key and a value.")
            .def(
                    "set",
                    [](Property& p,
                       const std::vector<std::pair<std::string, std::string>> v,
                       bool prop) { return p.set(v.begin(), v.end(), prop); },
                    py::arg("entries"),
                    py::arg("propagate") = false,
                    "Adds a range of properties.")
            .def(
                    "set",
                    [](Property& p, py::dict& entries, bool propagate) {
                        for (auto kv : entries) {
                            std::string key = py::cast<std::string>(kv.first);
                            std::string value =
                                    py::cast<std::string>(kv.second);
                            p.set({key, value}, propagate);
                        }
                    },
                    py::arg("entries"),
                    py::arg("propagate") = false,
                    "Adds a range of properties.")
            .def("remove",
                 &Property::remove,
                 py::arg("key"),
                 "Removes the property identified by a key.")
            .def("size", &Property::size, "Returns the number of properties.")
            .def("get_all",
                 &Property::get_all,
                 "Retrieves a copy of all the entries in a map.")
            .def("propagate",
                 &Property::propagate,
                 py::arg("key"),
                 "Returns whether the 'propagate' attribute for a property is "
                 "set "
                 "or not.")
            .def("__len__", &Property::size)
            .def("__contains__", &Property::exists)
            .def("__getitem__", &Property::get)
            .def("__setitem__",
                 [](Property& p, const std::string& k, const std::string& v) {
                     return p.set({k, v});
                 })
            .def("__setitem__",
                 [](Property& p,
                    const std::string& k,
                    const std::pair<std::string, bool>& v) {
                     return p.set({k, v.first}, v.second);
                 })
            .def(py::self == py::self, "Test for equality.")
            .def(py::self != py::self, "Test for inequality.");
}

template<>
void process_inits<Property>(py::module& m, ClassInitList& l)
{
    l.push_back([m]() mutable { return init_class<Property>(m, "Property"); });
}

}  // namespace pyrti
