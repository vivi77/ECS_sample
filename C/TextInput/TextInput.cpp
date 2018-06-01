#include "TextInput.hh"
#include "EManager.hh"

namespace lel::ecs::component
{
  namespace details
  {
    BaseTextInput::BaseTextInput(const std::string& input, const bool active)
      : active{active}
      , input{input}
    {
    }
  }
} /* !lel::ecs::component */
