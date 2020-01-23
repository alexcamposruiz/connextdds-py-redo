#include "PyConnext.hpp"
#include <rti/core/policy/CorePolicy.hpp>
#include "PySafeEnum.hpp"

using namespace rti::core::policy;

template<>
void pyrti::process_inits<AcknowledgmentKind>(py::module& m, pyrti::ClassInitList& l) {
    auto ak = init_dds_safe_enum<AcknowledgmentKind_def>(m, "AcknowledgmentKind");

    py::enum_<AcknowledgmentKind::type>(ak, "AcknowledgmentKind")
        .value(
            "PROTOCOL",
            AcknowledgmentKind::type::PROTOCOL,
            "Samples are acknowledged by RTPS protocol."
            "\n\n"
            "Samples are acknowledged according to the Real-Time "
            "Publish-Subscribe (RTPS) interoperability protocol."
        )
        .value(
            "APPLICATION_AUTO",
            AcknowledgmentKind::type::APPLICATION_AUTO,
            "Samples are acknowledged automatically after a subscribing "
            "application has accessed them."
            "\n\n"
            "The DataReader automatically acknowledges a sample after it has "
            "been taken and the loan returned."
        )
        .value(
            "APPLICATION_ORDERED",
            AcknowledgmentKind::type::APPLICATION_ORDERED,
            "Samples up to a specified sequence number are acknowledged."
        )
        .value(
            "APPLICATION_EXPLICIT",
            AcknowledgmentKind::type::APPLICATION_EXPLICIT,
            "Samples are acknowledged after the subscribing application "
            "explicitly calls acknowledge on the samples."
            "\n\n"
            "Samples received by a DataReader are explicitly acknowledged "
            "by the subscribing application, after it calls either "
            "DataReader.acknowledge_all or DataReader.acknowledge_sample."
        )
        .export_values();
}