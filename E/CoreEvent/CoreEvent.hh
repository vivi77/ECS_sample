#pragma once

#include "CRTPE.hpp"
#include "coreevent_export.h"
#include <string>
#include <vector>

class COREEVENT_EXPORT CoreEvent : public CRTPE<CoreEvent>
{
public:
  enum class Type : char
  {
    EXIT,
    ADD_SYSTEM,
    REM_SYSTEM,

    CLOSING,
    ADD_SYSTEM_SUCCESS,
    REM_SYSTEM_SUCCESS,

    ALREADY_ADDED_SYSTEM,

    INVALID_SYSTEM,
    SYSTEM_NOT_FOUND,
    ADD_SYSTEM_FAILURE,
    REM_SYSTEM_FAILURE,
  };

public:
  CoreEvent(Type t);
  CoreEvent(Type t, const std::string& data);
  template <typename ... Args>
  CoreEvent(Type t, Args&& ... args)
    : _type{t}
    , _data{std::forward<Args>(args)...}
  {}
  virtual ~CoreEvent() = default;

  Type getType() const;
  std::vector<std::string> getData() const;

private:
  Type _type;
  std::vector<std::string> _data;
};
