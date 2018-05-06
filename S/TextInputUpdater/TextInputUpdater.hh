#pragma once

#include "S/CRTPS.hpp"
#include "E/IEListener.hh"
#include "C/TextInput/TextInput.hh"
#include "C/TerminalComponents/Text.hh"

namespace lel::ecs::system
{
  class TextInputUpdater : public CRTPS<TextInputUpdater>, public event::IEListener
  {
  public:
    using TextInputCompPtr = std::shared_ptr<component::TextInputStr>;
    using TextCompPtr = std::shared_ptr<component::TerminalText>;

  private:
    struct Item
    {
      TextInputCompPtr inputComp = nullptr;
      TextCompPtr textComp = nullptr;

      bool isValid() const
      {
        return inputComp != nullptr && textComp != nullptr;
      }
    };

  public:
    TextInputUpdater(std::unique_ptr<CoreProxy>& proxy);
    ~TextInputUpdater() override = default;
    void exec() override;
    void registerEntity(const EntityPtr&) override;
    void deregisterEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

    void update(const EPtr&) override;

  private:
    std::vector<Item> _components;
  };
} /* !lel::ecs::system */
