#pragma once

#include "E/CRTPE.hpp"

namespace lel::ecs::event
{
  class CLISystemEvent : public CRTPE<CLISystemEvent>
  {
  public:
    enum class Type : char
    {
      //Commands
      DISABLE,
      ENABLE,
    };

  public:
    CLISystemEvent(Type t);
    ~CLISystemEvent() override = default;

    Type getType() const;

  private:
    Type _t;
  };
} /* !lel::ecs::event */
