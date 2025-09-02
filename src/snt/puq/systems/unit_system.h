#ifndef PUQ_UNIT_SYSTEM_H
#define PUQ_UNIT_SYSTEM_H

namespace snt::puq {

  extern std::unordered_map<SystemType, SystemDataType*> SystemMap;

  class UnitSystem {
    bool closed;
    static std::stack<SystemDataType*> systemStack;

  public:
    static SystemDataType* Data;
    static SystemType System;
    UnitSystem(const SystemType st = SystemType::NONE);
    ~UnitSystem();
    void change(const SystemType st);
    void close();
  };

} // namespace snt::puq

#endif // PUQ_UNIT_SYSTEM_H
