#include "PyConnext.hpp"
#include <dds/core/policy/CorePolicy.hpp>

using namespace dds::core::policy;

template<>
void pyrti::init_class_defs(py::class_<OwnershipStrength>& cls) {
    cls
        .def(
            py::init<>(),
            "Creates an instance with the default strength (0)."
        )
        .def(
            py::init<
                int32_t
            >(),
            py::arg("strength"),
            "Creates an instance with the specified strength value."
        )
        .def_property(
            "value",
            (int32_t (OwnershipStrength::*)() const) &OwnershipStrength::value,
            (OwnershipStrength& (OwnershipStrength::*)(int32_t)) &OwnershipStrength::value,
            "The ownership kind."
        )
        .def(
            py::self == py::self,
            "Test for equality."
        )
        .def(
            py::self != py::self,
            "Test for inequality."
        );
}

template<>
void pyrti::process_inits<OwnershipStrength>(py::module& m, pyrti::ClassInitList& l) {
    l.push_back(
        [m]() mutable {
            return pyrti::init_class<OwnershipStrength>(m, "OwnershipStrength");
        }
    );
}