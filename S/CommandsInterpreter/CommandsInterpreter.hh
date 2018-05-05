#pragma once

#include "S/CRTPS.hpp"
#include "E/IEListener.hh"

namespace lel::ecs::component
{
  class CommandsStr;
} /* !lel::ecs::component */

namespace lel::ecs::system
{
  class CommandsInterpreter : public CRTPS<CommandsInterpreter>, public event::IEListener
  {
    using CommandsStrPtr = std::shared_ptr<component::CommandsStr>;

  private:
    struct Wrapper
    {
      CommandsStrPtr commands = nullptr;

      bool isValid()
      {
        return commands != nullptr;
      }
    };

  public:
    CommandsInterpreter(std::unique_ptr<CoreProxy>& proxy);

    ~CommandsInterpreter() override = default;

    void exec() override;
    void registerEntity(const EntityPtr&) override;
    void deregisterEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

    void update(const EPtr&) override;

  private:
    std::vector<Wrapper> _entities;
  };
} /* !lel::ecs::component */
