#ifndef FIX_H__
#define FIX_H__

#include <string>

namespace llvm {

class raw_ostream;
class RecordKeeper;

extern void EmitFixedLenDecoder(RecordKeeper &RK, raw_ostream &OS,
                                const std::string &PredicateNamespace,
                                const std::string &GPrefix,
                                const std::string &GPostfix,
                                const std::string &ROK,
                                const std::string &RFail, const std::string &L);

}

#endif // FIX_H__
